#pragma once

#include "Crouch.h"
#include "Height.h"
#include "Speed.h"
#include "Strafe.h"



namespace Controller
{
	inline auto Crouch = CrouchController::GetSingleton();
	inline auto Height = HeightController::GetSingleton();
	inline auto Speed = SpeedController::GetSingleton();
	inline auto Strafe = StrafeController::GetSingleton();
}