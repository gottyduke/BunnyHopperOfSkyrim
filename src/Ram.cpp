#include "Ram.h"
#include "Speed.h" // SpeedController
#include "Settings.h"  // Settings

#include <thread>
#include <chrono>

#include "SKSE/API.h"

void RamController::Reset() noexcept
{
	cooldownActor.clear();
}


void RamController::Update() noexcept
{
	const auto cell = player->GetParentCell();
	auto cellRefset = cell->references;
	for (const auto& ref : cellRefset) {
		const auto actor = RE::TESForm::LookupByID<RE::Actor>(ref->GetFormID());
		if (actor && !actor->IsPlayer() && !actor->IsPlayerRef()) {
			TestRange(actor);
		}
	}
}


void RamController::TestRam()
{
	const auto Speed = SpeedController::GetSingleton();
	
	Update();
	if (Speed->GetCurrSpeed() >= *Settings::ramSpeedThreshold) {
		//Update();
	}
}


// swingby range : 60x60 ft
// knockback range : 48x48 ft
// ram range : 36x36 ft
// immunity reset distance : 640 ft
void RamController::TestRange(RE::Actor* a_actor) noexcept
{
	if (player->GetPositionZ() - a_actor->GetPositionZ() >= 64.0f) {
		return;
	}
	
	if (!a_actor->Is3DLoaded()) {
		return;
	}
	
	const auto distance = CalcDistance2D(Coord2{player->GetPositionX(), player->GetPositionY()}, Coord2{a_actor->GetPositionX(), a_actor->GetPositionY()});
	if (distance >= 640.0f) {
		cooldownActor.erase(a_actor);
		return;
	}
	if (distance > 60.0f || distance < 24.0f) {
		return;
	}
	if (cooldownActor.count(a_actor) != 1) {
		if (distance <= 36.0f) {
			_DMESSAGE("Rammed %s", a_actor->GetName());
			hkp->ApplyForce(a_actor, 1.0f);
		} else if (distance <= 48.0f) {
			_DMESSAGE("Knockback %s", a_actor->GetName());
			hkp->ApplyForce(a_actor, 0.5f);
		} else if (distance <= 60.0f) {
			_DMESSAGE("Swingby %s", a_actor->GetName());
			hkp->ApplyForce(a_actor, 0.1f);
		}
		_DMESSAGE("%f", distance);
		cooldownActor.insert(a_actor);
	}
}


RamController::ForceImpl::ForceImpl()
{
	force = RE::IFormFactory::GetConcreteFormFactoryByType<RE::SpellItem>()->Create();
	force->Copy(RE::TESForm::LookupByID<RE::SpellItem>(0x00013F3A));

	// selfcast
	force->data.spellType = RE::MagicSystem::SpellType::kAbility;
	force->data.delivery = RE::MagicSystem::Delivery::kSelf;

	// rebase
	force->effects[0]->baseEffect->effectSounds.clear();
	if (force->effects[0]->baseEffect->conditions)
		force->effects[0]->baseEffect->conditions.head->data.flags.opCode = RE::CONDITION_ITEM_DATA::OpCode::kGreaterThanOrEqualTo;
	force->effects[1] = force->effects[2];
}


void RamController::ForceImpl::ApplyForce(RE::Actor* a_target, const float a_mult) const
{
	const auto speed = SpeedController::GetSingleton();
	const auto player = RE::PlayerCharacter::GetSingleton();
	
	const float strength = a_mult * (speed->GetCurrSpeed() + *Settings::ramSpeedThreshold);
	const float damage = a_mult * (speed->GetCurrSpeed() + *Settings::ramSpeedThreshold) * *Settings::ramDamage * *Settings::ramDamageMult;

	force->effects[0]->effectItem.magnitude = strength;

	if (a_target->GetActorValue(RE::ActorValue::kHealth) <= damage) {
		a_target->KillImpl(a_target, damage, false, true);
	} else {
		a_target->AddSpell(force);
		a_target->SetActorValue(RE::ActorValue::kHealth, a_target->GetActorValue(RE::ActorValue::kHealth) - damage);
	}
	player->SetActorValue(RE::ActorValue::kHealth, a_target->GetClampedActorValue(RE::ActorValue::kHealth) - damage * *Settings::ramSelfReduction);

	ImpulseData impData{ a_target, player, strength };

	// send an impulse
	const auto task = SKSE::GetTaskInterface();
	task->AddTask([impData]() -> void
	{
		std::thread impulse([impData]() -> void
		{
			// calc impulse vector
			Coord3 coords[]{
				{
					impData.source->GetPositionX(),
					impData.source->GetPositionY(),
					impData.source->GetPositionZ()
				},
				{
					impData.target->GetPositionX(),
					impData.target->GetPositionY(),
					impData.target->GetPositionZ() + IMPULSE_Z_OFFSET  // impulse offset
				}};
			const auto delta = CalcAngle2D(coords[0], coords[1]);
			const auto theta = CalcAngle3D(coords[0], coords[1]);
			const auto xVelocity = impData.strength * cosf(theta);
			const auto zVelocity = impData.strength * sinf(theta);
			const auto zDisplacement = impData.strength * sinf(theta) * IMPULSE_KEY_FRAME - 0.5f * IMPULSE_GRAVITY * __fpow(IMPULSE_KEY_FRAME, 2);
			const auto xDisplacement = xVelocity * IMPULSE_KEY_FRAME;

			_DMESSAGE("\ndelta %f\ntheta %f", delta, theta);
			while (zVelocity >= 0.0f) {
				impData.target->data.location.x += xDisplacement;
				
				impData.target->data.location.z += zDisplacement;
				
				
				std::this_thread::sleep_for(std::chrono::milliseconds(IMPULSE_GAP_FRAME));
			}
		});
		impulse.detach();
	});
}