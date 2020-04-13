#pragma once

#include "Json2Settings.h"

namespace J2S = Json2Settings;

class Settings
{
public:
	static bool LoadSettings(bool a_dumpParse = false);

	// global
	static J2S::fSetting globalSpeedMult;
	static J2S::fSetting maxSpeed;
	static J2S::iSetting misttepAllowed;
	
	// base
	static J2S::fSetting baseSpeedBoost;
	static J2S::fSetting baseSpeedMult;

	// strafe
	static J2S::fSetting minStrafeAngle;
	static J2S::fSetting maxStrafeAngle;
	static J2S::fSetting strafeDeadzone;
	static J2S::fSetting strafeSpeedMult;
	
	// height
	static J2S::fSetting minHeightLaunch;
	static J2S::fSetting heightLaunchMult;

	// crouch
	static J2S::fSetting crouchSpeedBoost;
	static J2S::fSetting crouchBoostMult;
	static J2S::iSetting crouchBoostCooldown;

	// ram
	static J2S::fSetting ramDamage;
	static J2S::fSetting ramDamageMult;
	static J2S::fSetting ramSpeedThreshold;
	static J2S::fSetting ramSpeedReduction;
	
	// visual
	static J2S::bSetting enableTrail;
	static J2S::bSetting enableJumpFeedback;

	// simulation
	static J2S::bSetting enableSimulation;
	
	Settings() = delete;

private:
	static constexpr char* FILE_NAME = "Data\\SKSE\\Plugins\\BunnyHopperOfSkyrim.json";
};
