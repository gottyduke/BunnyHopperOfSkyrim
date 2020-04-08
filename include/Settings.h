#pragma once

#include "Json2Settings.h"

namespace J2S = Json2Settings;

class Settings
{
public:
	static bool LoadSettings(bool a_dumpParse = false);

	static J2S::fSetting	globalSpeedMult;
	
	static J2S::fSetting	baseSpeedBoost;
	static J2S::fSetting	baseSpeedMult;

	static J2S::fSetting	minStrafeAngle;
	static J2S::fSetting	strafeSpeedMult;
	
	static J2S::fSetting	minHeightLaunch;
	static J2S::fSetting	heightLaunchMult;
	
	static J2S::fSetting	crouchSpeedBoost;
	static J2S::fSetting	crouchBoostMult;

	static J2S::iSetting	misttepAllowed;
	
	static J2S::fSetting	maxSpeed;
	
	static J2S::bSetting	enableTrail;
	
	static J2S::fSetting	ramDamage;
	static J2S::fSetting	ramDamageMult;

	
	Settings() = delete;
	
private:
	static constexpr char* FILE_NAME = "Data\\SKSE\\Plugins\\BunnyHopperOfSkyrim.json";
};