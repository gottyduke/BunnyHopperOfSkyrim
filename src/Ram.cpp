#include "Ram.h"
#include "Speed.h" // SpeedController
#include "Settings.h"  // Settings

#include <thread>
#include <chrono>

#include "SKSE/API.h"


void RamController::Reset() noexcept
{
	simulate = false;
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

	player->SetActorValue(RE::ActorValue::kHealth, a_target->GetActorValue(RE::ActorValue::kHealth) - damage * *Settings::ramSelfReduction);

	if (!*Settings::enableSimulation) {
		a_target->DispellEffectsWithArchetype(RE::MagicTarget::Archetype::kStagger, true);
		a_target->AddSpell(force);
		if (a_target->GetActorValue(RE::ActorValue::kHealth) <= damage) {
			a_target->KillImpl(player, damage, true, true);
		} else {
			a_target->SetActorValue(RE::ActorValue::kHealth, a_target->GetActorValue(RE::ActorValue::kHealth) - damage);
		}
	} else {
		//speed->SpeedUp(-1 * strength); // For every action, there is an equal and opposite reaction.

		GetSingleton()->simulate = true;
		ImpulseData impData{a_target, player, force};
		// send an impulse
		const auto task = SKSE::GetTaskInterface();
		task->AddTask([impData, strength]() -> void
		{
			std::thread impulse([impData, strength]() -> void
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
				_DMESSAGE("%f %f", strength, IMPULSE_ACCELERATION_VEC(theta, phi));

				const auto xVelocity = strength * cos(theta) * cos(phi);
				const auto yVelocity = strength * cos(theta) * sin(phi);
				const auto zVelocity = strength * sin(theta);
				_DMESSAGE("\n%f\n%f\n%f", xVelocity, yVelocity, zVelocity);

				const auto xDisplacement = IMPULSE_TO_DISPLACEMENT(xVelocity, IMPULSE_DAMPING);
				const auto yDisplacement = IMPULSE_TO_DISPLACEMENT(yVelocity, IMPULSE_DAMPING);
				const auto zDisplacement = IMPULSE_TO_DISPLACEMENT(zVelocity, IMPULSE_GRAVITY);
				_DMESSAGE("\n%f\n%f\n%f", xDisplacement, yDisplacement, zDisplacement);
				
				auto ui = RE::UI::GetSingleton();
				while (!ui->GameIsPaused() && impData.target->GetActorValue(RE::ActorValue::kHealth) > 0) {
					if (!GetSingleton()->simulate) {
						return;
					}

					auto iter = 0;

					impData.target->DispellEffectsWithArchetype(RE::MagicTarget::Archetype::kStagger, true);

					impData.target->AddSpell(impData.force);

					while (iter < 31) {
						impData.target->data.location.x += xDisplacement;
						impData.target->data.location.y += yDisplacement;
						//impData.target->data.location.z += zDisplacement;

						std::this_thread::sleep_for(std::chrono::milliseconds(16));
						++iter;
					}
				}
			});
			impulse.detach();
		});
	}
}