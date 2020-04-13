#include "Crouch.h"
#include "Speed.h"  // SpeedController
#include "Settings.h"  // Settings


void CrouchController::Reset() noexcept
{
	cooldown = *Settings::crouchBoostCooldown;
}


void CrouchController::Update() noexcept
{
	--cooldown;
}


void CrouchController::GainCrouchBonus()
{
	Update();

	if (cooldown <= 0 && player->IsSneaking()) {
		const auto CrouchBonus = *Settings::globalSpeedMult * *Settings::crouchBoostMult * *Settings::crouchSpeedBoost;

		auto Speed = SpeedController::GetSingleton();
		Speed->SpeedUp(CrouchBonus);

		Reset();

#ifdef DUMP
		_DMESSAGE("Crouch-Bonus %f", CrouchBonus);
#endif
		// GFx Notify("CrouchBonus")
	} else {
		// GFx Notify("CrouchCooldown")
	}
}