#include "Ram.h"
#include "Speed.h"  // SpeedController
#include "Settings.h"  // Settings

#include "SKSE/RegistrationSet.h"  // TaskInterface


void RamController::Reset() noexcept
{
	
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
	if (player->GetPositionZ() - a_actor->GetPositionZ() >= 48.0f) {
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

	if (distance <= 44.0f) {
		ApplyForce(a_actor, 0.6f);
	} else if (distance <= 57.0f) {
		ApplyForce(a_actor, 0.3f);
	} else if (distance <= 70.0f) {
		ApplyForce(a_actor, 0.1f);
	}
}


void RamController::ApplyForce(RE::Actor* a_target, const float a_mult) const
{
	const auto speed = SpeedController::GetSingleton();

	const float strength = a_mult * (speed->GetCurrSpeed() - *Settings::ramSpeedThreshold);
	const float damage = strength * *Settings::ramDamage * *Settings::ramDamageMult;
	
	speed->SpeedUp(-*Settings::ramSpeedReduction * (speed->GetCurrSpeed() - *Settings::ramSpeedThreshold)); // For every action, there is an equal and opposite reaction

	a_target->SetActorValue(RE::ActorValue::kHealth, a_target->GetActorValue(RE::ActorValue::kHealth) - damage);

	char command[48];
	std::sprintf(command, "Player.PushActorAway %lx %d", a_target->GetFormID(), static_cast<int>(strength));
	
	const auto script = RE::IFormFactory::GetConcreteFormFactoryByType<RE::Script>()->Create();
	script->SetCommand(command);
	script->CompileAndRun(player);
	
	if (a_target->GetActorValue(RE::ActorValue::kHealth) <= 0) {
		a_target->KillImpl(player, 0, true, true);
	}
}