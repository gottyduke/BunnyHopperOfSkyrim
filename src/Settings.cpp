#include "Settings.h"


bool Settings::LoadSettings(const bool a_dumpParse)
{
	auto [log, success] = J2S::load_settings(FILE_NAME, a_dumpParse);

	if (!log.empty()) {
		_ERROR("%s", log.c_str());
	}

	return success;
}


decltype(Settings::globalSpeedMult)		Settings::globalSpeedMult("globalSpeedMult", 1.0f);
decltype(Settings::baseSpeedBoost)		Settings::baseSpeedBoost("baseSpeedBoost", 2.0f);
decltype(Settings::baseSpeedMult)		Settings::baseSpeedMult("baseSpeedMult", 1.0f);
decltype(Settings::minStrafeAngle)		Settings::minStrafeAngle("minStrafeAngle", 25.0f);
decltype(Settings::strafeSpeedMult)		Settings::strafeSpeedMult("strafeSpeedMult", 1.0f);
decltype(Settings::minHeightLaunch)		Settings::minHeightLaunch("minHeightLaunch", 5.0f);
decltype(Settings::heightLaunchMult)	Settings::heightLaunchMult("heightLaunchMult", 1.0f);
decltype(Settings::crouchSpeedBoost)	Settings::crouchSpeedBoost("crouchSpeedBoost", 3.0f);
decltype(Settings::crouchBoostMult)		Settings::crouchBoostMult("crouchBoostMult", 1.0f);
decltype(Settings::maxSpeed)			Settings::maxSpeed("maxSpeed", 400.0f);
decltype(Settings::enableTrail)			Settings::enableTrail("enableTrail", true);
decltype(Settings::ramDamage)			Settings::ramDamage("ramDamage", 5.0f);
decltype(Settings::ramDamageMult)		Settings::ramDamageMult("ramDamageMult", 1.0f);
