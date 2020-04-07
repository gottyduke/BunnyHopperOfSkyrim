#pragma once

#include "Crouch.h"
#include "Height.h"
#include "Ram.h"
#include "Speed.h"
#include "Strafe.h"

#include "Settings.h"

#include "RE/Skyrim.h"


namespace Controller
{
	struct SubControllers
	{
		CrouchController* Crouch = CrouchController::GetSingleton();
		HeightController* Height = HeightController::GetSingleton();
		RamController* Ram = RamController::GetSingleton();
		SpeedController* Speed = SpeedController::GetSingleton();
		StrafeController* Strafe = StrafeController::GetSingleton();
	};

	static SubControllers* Ptr = new SubControllers;

	
	void TryAccelerate();
	void CountStop();

	void TryHeightLaunch();
	void TryCrouchBoost();
}