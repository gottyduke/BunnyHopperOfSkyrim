#include "Ram.h"
#include "Speed.h"  // SpeedController
#include "Settings.h"  // Settings

#include <thread>  // thread
#include <chrono>  // chrono

#include "SKSE/RegistrationSet.h"  // TaskInterface


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
			if (actor->GetActorValue(RE::ActorValue::kHealth) <= 0) {
				actor->KillImpl(player, 0, true, true);
				return;
			}
			TestRange(actor);
		}
	}
}


void RamController::TestRam()
{
	const auto speed = SpeedController::GetSingleton();

	if (speed->GetCurrSpeed() >= *Settings::ramSpeedThreshold) {
		Update();
	}
}


void RamController::TestRange(RE::Actor* a_actor) const noexcept
{
	if (a_actor->IsPlayerTeammate()) {
		return;
	}
	if (!a_actor->Is3DLoaded()) {
		return;
	}
	if (player->GetPositionZ() - a_actor->GetPositionZ() >= 64.0f) {
		return;
	}

	const auto distance = CalcDistance(
		Vector{
			player->GetPositionX(),
			player->GetPositionY()},
		Vector{
			a_actor->GetPositionX(),
			a_actor->GetPositionY()});

	if (distance < 24.0f || distance > 60.0f) {
		return;
	}

	if (distance <= 48.0f) {
		hkp->ApplyForce(a_actor, 1.0f);
	} else if (distance <= 60.0f) {
		hkp->ApplyForce(a_actor, 0.5f);
	} else if (distance <= 72.0f) {
		hkp->ApplyForce(a_actor, 0.1f);
	}
}


RamController::ForceImpl::ForceImpl()
{
	force = RE::IFormFactory::GetConcreteFormFactoryByType<RE::SpellItem>()->Create();
	force->Copy(RE::TESForm::LookupByID(0x00013F3A));

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
	const auto task = SKSE::GetTaskInterface();

	const float strength = a_mult * (speed->GetCurrSpeed() - *Settings::ramSpeedThreshold);
	const float damage = strength * *Settings::ramDamage * *Settings::ramDamageMult;

	force->effects[0]->effectItem.magnitude = strength;
	
	speed->SpeedUp(-*Settings::ramSpeedReduction * strength); // For every action, there is an equal and opposite reaction

	a_target->SetActorValue(RE::ActorValue::kHealth, a_target->GetActorValue(RE::ActorValue::kHealth) - damage);

	ImpulseData impData{a_target, player, force};
	if (true || !*Settings::enableSimulation) {
		task->AddTask([impData, damage]() -> void
		{
			std::thread ragdoll([impData, damage]() -> void
			{
				impData.target->DispellEffectsWithArchetype(RE::MagicTarget::Archetype::kStagger, true);
				impData.target->AddSpell(impData.force);
				
				std::this_thread::sleep_for(std::chrono::seconds(3));
			});
			ragdoll.detach();
		});
	} else { // motion simulation is still under development
		GetSingleton()->simulate = true;
		// send an impulse
		task->AddTask([impData, strength]() -> void
		{
			std::thread impulse([impData, strength]() -> void
			{
				float theta;
				float phi;
				{
					Vector source
					{
						impData.source->GetPositionX(),
						impData.source->GetPositionY(),
						impData.source->GetPositionZ()
					};
					Vector target{
						impData.target->GetPositionX(),
						impData.target->GetPositionY(),
						impData.target->GetPositionZ()
					};
		
					theta = CalcAngle3D(source, target);
					phi = CalcAngle2D(source, target);
				}
				_DMESSAGE("%f %f", strength, IMPULSE_ACCELERATION_VEC(theta, phi));

				const auto xVelocity = strength * cosf(theta) * cosf(phi);
				const auto yVelocity = strength * cosf(theta) * sinf(phi);
				const auto zVelocity = strength * sinf(theta);
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

					while (iter < 62) {
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