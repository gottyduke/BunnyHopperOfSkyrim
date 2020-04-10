#pragma once

#include "Settings.h"


class Controller
{
public:
	static Controller* GetSingleton();

	void TryAccelerate();
	void TestHeightBonus();
	void CaptureStrafe();
	void TestStrafeBonus();
	void TryCrouchBoost();
	void TryInitRam();
	
	void CountStop();
	void HaltProcess();

	void ResetCounter() noexcept { stopCounter = 0; }

	Controller(const Controller&) = delete;
	Controller(Controller&&) = delete;
	Controller() = default;
	~Controller() = default;

	Controller& operator=(const Controller&) = delete;
	Controller& operator=(Controller&&) = delete;

private:
	int stopCounter = 2147483646;
};
