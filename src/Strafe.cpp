#include "Strafe.h"
#include "Speed.h"  // SpeedController
#include "Settings.h"  // Settings

#include <cmath>  // fabs


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
	diff = FastTrig(fabs(player->GetPositionX() - pos.x), fabs(player->GetPositionY() - pos.y));
}


void StrafeController::TryStrafe()
{
	Reset();

	// GFx Notify("TryStrafe")
}


void StrafeController::CalcDipChange()
{
	Update();

	// GFx Log("TestNewRecord")
}


void StrafeController::GainStrafeBonud() const
{
	if (!_isnanf(diff)) {
		return;
	}
	
	if (diff >= *Settings::minStrafeAngle) {
		auto Speed = SpeedController::GetSingleton();
		const auto StrafeBonus = diff >= *Settings::maxStrafeAngle
			                         ? *Settings::maxStrafeAngle - *Settings::strafeDeadzone
			                         : diff - *Settings::strafeDeadzone;

		Speed->SpeedUp(*Settings::globalSpeedMult * *Settings::strafeSpeedMult * StrafeBonus);
		
		// GFx Notify("StrafeBonus")
	}
}


inline auto StrafeController::FastTrig(const float a_b, const float a_c) const noexcept
-> float
{
	const auto a_a = __fsqrt(__fpow(a_b, 2) + __fpow(a_c, 2));
	const auto rad = acos((__fpow(a_a, 2) + __fpow(a_b, 2) - __fpow(a_c, 2)) / (2 * a_a * a_b));
	return rad * (180.0 / 3.141592653589793238463);
}