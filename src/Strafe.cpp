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
	pos.x = player->GetPositionX();
	pos.y = player->GetPositionY();
}


void StrafeController::Update() noexcept
{
	diff = CalcAngle2D(Coord2{ player->GetPositionX(), player->GetPositionY() }, pos);
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


void StrafeController::GainStrafeBonud() const
{
	if (_isnanf(diff)) {
		return;
	}
	
	if (diff >= *Settings::minStrafeAngle) {
		auto Speed = SpeedController::GetSingleton();
		auto StrafeBonus = diff >= *Settings::maxStrafeAngle
			                         ? *Settings::maxStrafeAngle - *Settings::strafeDeadzone
			                         : diff - *Settings::strafeDeadzone;

		// bi-directional
		StrafeBonus /= 4;
		Speed->SpeedUp(*Settings::globalSpeedMult * *Settings::strafeSpeedMult * StrafeBonus);
		// GFx Notify("StrafeBonus")
	}
}