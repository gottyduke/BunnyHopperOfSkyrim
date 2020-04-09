#include "Ram.h"
#include "Speed.h" // SpeedController
#include "Settings.h"  // Settings

#include <cmath>  // fabs


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
	//	Update();
	}
}


void RamController::SwingBy(RE::Actor* a_actor)
{
	if (!cooldownActor.count(a_actor)) {
		_DMESSAGE("Swingby %s", a_actor->GetName());
		cooldownActor.insert(a_actor);
	}
}


void RamController::Knockback(RE::Actor* a_actor)
{
	if (!cooldownActor.count(a_actor)) {
		_DMESSAGE("konckback %s", a_actor->GetName());
		cooldownActor.insert(a_actor);
	}
}


void RamController::InitRam(RE::Actor* a_actor)
{
	if (!cooldownActor.count(a_actor)) {
		_DMESSAGE("Rammed %s", a_actor->GetName());
		cooldownActor.insert(a_actor);
	}
}


// swingby range : 96x96 ft
// knockback range : 64x64 ft
// ram range : 48x48 ft
// immunity reset distance : 640 ft
// ++++++++++++++++
// +   swingby    +
// + +~~~~~~~~~~+ +
// + / knockback\ +
// + /   +|+    \ +    
// + /   ram    \ +
// + +~~~~~~~~~~+ +
// ++++++++++++++++


void RamController::TestRange(RE::Actor* a_actor) noexcept
{
	const NiPoint3 diff{
	fabs(player->GetPositionX() - a_actor->GetPositionX()),
	fabs(player->GetPositionY() - a_actor->GetPositionY()),
	fabs(player->GetPositionZ() - a_actor->GetPositionZ())
	};

	if (diff.z >= 25.0f) {
		return;
	}

	const auto distance = __fsqrt(__fpow(diff.x, 2) + __fpow(diff.y, 2));
	if (distance > 1440.0f) {
		cooldownActor.erase(a_actor);
		return;
	}
	if (distance <= 48.0f) {
		InitRam(a_actor);
		return;
	}
	if (distance <= 64.0f) {
		SwingBy(a_actor);
		return;
	}
	if (distance <= 96.0f) {
		SwingBy(a_actor);
	}
}
