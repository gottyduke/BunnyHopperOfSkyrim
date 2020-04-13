#include "Strafe.h"
#include "Speed.h"  // SpeedController
#include "Settings.h"  // Settings


StrafeController::StrafeController() :
scale(0),
diff(0),
pos()
{}


void StrafeController::Reset() noexcept
{
	pos.m128_f32[0] = player->GetPositionX();
	pos.m128_f32[1] = player->GetPositionY();
}


void StrafeController::Update() noexcept
{
	diff = CalcAngle2D(Vector{ player->GetPositionX(), player->GetPositionY() }, pos);
}


void StrafeController::TryStrafe()
{
	Reset();

	// GFx Notify("TryStrafe")
}


void StrafeController::CalcDipChange()
{
	Update();

	// GFx Notify("TestNewRecord")
}


void StrafeController::GainStrafeBonud()
{
	if (_isnanf(diff)) {
		return;
	}

	diff *= 180.0 / 3.14159265358979323846;
	
	if (diff >= *Settings::minStrafeAngle) {
		auto speed = SpeedController::GetSingleton();
		const auto angle = (diff >= *Settings::maxStrafeAngle ? *Settings::maxStrafeAngle : diff) - *Settings::strafeDeadzone;
		const auto strafeBonus = *Settings::globalSpeedMult * *Settings::strafeSpeedMult * angle / 3;

		speed->SpeedUp(strafeBonus);
		// GFx Notify("StrafeBonus")

#ifdef DUMP
		_DMESSAGE("Strafe-Bonus %f %f", angle, strafeBonus);
#endif
	}
}