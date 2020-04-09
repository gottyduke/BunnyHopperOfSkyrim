#include "Settings.h"


bool Settings::LoadSettings(const bool a_dumpParse)
{
	auto [log, success] = J2S::load_settings(FILE_NAME, a_dumpParse);

	if (!log.empty()) {
		_ERROR("%s", log.c_str());
	}

	return success;
}


decltype(Settings::globalSpeedMult) Settings::globalSpeedMult("globalSpeedMult", 1.0f);
decltype(Settings::maxSpeed) Settings::maxSpeed("maxSpeed", 450.0f);
decltype(Settings::misttepAllowed) Settings::misttepAllowed("misstepAllowed", 4);

decltype(Settings::baseSpeedBoost) Settings::baseSpeedBoost("baseSpeedBoost", 3.0f);
decltype(Settings::baseSpeedMult) Settings::baseSpeedMult("baseSpeedMult", 1.0f);

decltype(Settings::minStrafeAngle) Settings::minStrafeAngle("minStrafeAngle", 35.0f);
decltype(Settings::maxStrafeAngle) Settings::maxStrafeAngle("maxStrafeAngle", 85.0f);
decltype(Settings::strafeDeadzone) Settings::strafeDeadzone("strafeDeadzone", 35.0f);
decltype(Settings::strafeSpeedMult) Settings::strafeSpeedMult("strafeSpeedMult", 1.0f);

decltype(Settings::minHeightLaunch) Settings::minHeightLaunch("minHeightLaunch", 5.0f);
decltype(Settings::heightLaunchMult) Settings::heightLaunchMult("heightLaunchMult", 1.0f);

decltype(Settings::crouchSpeedBoost) Settings::crouchSpeedBoost("crouchSpeedBoost", 3.0f);
decltype(Settings::crouchBoostMult) Settings::crouchBoostMult("crouchBoostMult", 1.0f);
decltype(Settings::crouchBoostCooldown) Settings::crouchBoostCooldown("crouchBoostCooldown", 6);


decltype(Settings::ramDamage) Settings::ramDamage("ramDamage", 5.0f);
decltype(Settings::ramDamageMult) Settings::ramDamageMult("ramDamageMult", 0.2f);
decltype(Settings::ramSpeedThreshold) Settings::ramSpeedThreshold("ramSpeedThreshold", 220.0f);
decltype(Settings::ramSelfReduction) Settings::ramSelfReduction("ramSelfReduction", 50.0f);

decltype(Settings::enableTrail) Settings::enableTrail("enableTrail", true);