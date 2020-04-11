#include "Ram.h"
#include "Speed.h" // SpeedController
#include "Settings.h"  // Settings

#include <thread>
#include <chrono>

#include "SKSE/API.h"

void RamController::Reset() noexcept
{
	// suppose to reset
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


void RamController::TestRange(RE::Actor* a_actor) const noexcept
{
	if (player->GetPositionZ() - a_actor->GetPositionZ() >= 64.0f) {
		return;
	}

	if (!a_actor->Is3DLoaded()) {
		return;
	}

	const float distance = CalcDistance2D(
		Coord2{
			player->GetPositionX(),
			player->GetPositionY()},
		Coord2{
			a_actor->GetPositionX(),
			a_actor->GetPositionY()});
	
	if (distance < 24.0f || distance > 60.0f) {
		return;
	}

	if (distance <= 44.0f) {
		_DMESSAGE("Rammed %s %x", a_actor->GetName(), a_actor->GetFormID());
		hkp->ApplyForce(a_actor, 1.0f);
	} else if (distance <= 55.0f) {
		_DMESSAGE("Knockback %s %x", a_actor->GetName(), a_actor->GetFormID());
		hkp->ApplyForce(a_actor, 0.5f);
	} else if (distance <= 66.0f) {
		_DMESSAGE("Swingby %s %x", a_actor->GetName(), a_actor->GetFormID());
		hkp->ApplyForce(a_actor, 0.1f);
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
	const float damage = strength * *Settings::ramDamage * *Settings::ramDamageMult;

	force->effects[0]->effectItem.magnitude = strength;

	if (a_target->GetActorValue(RE::ActorValue::kHealth) <= damage) {
		a_target->KillImpl(player, damage, true, true);
	}
	a_target->SetActorValue(RE::ActorValue::kHealth, a_target->GetActorValue(RE::ActorValue::kHealth) - damage);

	player->SetActorValue(RE::ActorValue::kHealth, a_target->GetActorValue(RE::ActorValue::kHealth) - damage * *Settings::ramSelfReduction);

	//speed->SpeedUp(-1 * strength); // For every action, there is an equal and opposite reaction.
	
	ImpulseData impData{ a_target, player, strength, force };

	// send an impulse
	const auto task = SKSE::GetTaskInterface();
	task->AddTask([impData]() -> void
	{
		std::thread impulse([impData]() -> void
		{
			double theta;
			double phi;
			{
				Coord3 Points[]{
					{
						impData.source->GetPositionX(),
						impData.source->GetPositionY(),
						impData.source->GetPositionZ()
					},
					{
						impData.target->GetPositionX(),
						impData.target->GetPositionY(),
						impData.target->GetPositionZ()
					}
				};
				theta = CalcAngle3D(Points[0], Points[1]);
				phi = CalcAngle2D(Points[0], Points[1]);
			}
			
			const auto xVelocity = impData.strength * cos(theta) * cos(phi) / 60;
			const auto yVelocity = impData.strength * cos(theta) * sin(phi) / 60;
			const auto zVelocity = impData.strength * sin(theta) / 60;
			
			_DMESSAGE("\n%f\n%f\n%f", xVelocity, yVelocity, zVelocity);

			const auto xDisplacement = xVelocity * IMPULSE_KEY_PER_FRAME;
			const auto yDisplacement = yVelocity * IMPULSE_KEY_PER_FRAME;
			const auto zDisplacement = zVelocity * IMPULSE_KEY_PER_FRAME;

			_DMESSAGE("\n%f\n%f\n%f", xDisplacement, yDisplacement, zDisplacement);
			
			auto ui = RE::UI::GetSingleton();
			auto iter = 0;
			while (!ui->GameIsPaused() || iter > 300) {
				impData.target->DispellEffectsWithArchetype(RE::MagicTarget::Archetype::kStagger, true);

				impData.target->AddSpell(impData.force);

				impData.target->data.location.x += xDisplacement;
				impData.target->data.location.y += yDisplacement;
				impData.target->data.location.z += zDisplacement;

				std::this_thread::sleep_for(std::chrono::milliseconds(16));
				++iter;
			}

			});
		impulse.detach();
	});
}