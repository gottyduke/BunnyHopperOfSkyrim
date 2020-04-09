#include "Crouch.h"
#include "Speed.h"  // SpeedController
#include "Settings.h"  // Settings


void CrouchController::Reset() noexcept
{
	jumpCount = 0;
}


void CrouchController::Update() noexcept
{
	++jumpCount;
}


void CrouchController::GainCrouchBonus()
{
	Update();

	if (jumpCount >= *Settings::crouchBoostCooldown) {
		const auto CrouchBonus = *Settings::globalSpeedMult * *Settings::crouchBoostMult * *Settings::crouchSpeedBoost;

		auto Speed = SpeedController::GetSingleton();
		Speed->SpeedUp(CrouchBonus);

		Reset();

		// GFx Notify("CrouchBonus")
	} else {
		// GFx Notify("CrouchCooldown")
	}
}