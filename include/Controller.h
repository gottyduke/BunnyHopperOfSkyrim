#pragma once

#include "Crouch.h"
#include "Height.h"
#include "Ram.h"
#include "Speed.h"
#include "Strafe.h"


class Controller
{
public:
	void TryAccelerate();
	void TestHeight();
	void TryCrouchBoost();

	void CountStop();
	void HaltProcess();

	constexpr void ResetCounter() noexcept { g_stopCounter = 0; }
	
	Controller(const Controller&) = delete;
	Controller(Controller&&) = delete;
	Controller();
	
	Controller& operator=(const Controller&) = delete;
	Controller& operator=(Controller&&) = delete;
	
	Controller* operator->() { return singleton; }
	Controller& operator*() { return *singleton; }
	const Controller* operator->() const { return singleton; }
	const Controller& operator*() const { return *singleton; }
	
private:
	CrouchController Crouch;
	StrafeController Strafe;
	SpeedController Speed;
	HeightController Height;
	RamController Ram;

	int g_stopCounter;
	static Controller* singleton;
};


inline Controller* Controller::singleton;