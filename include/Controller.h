#pragma once


class Controller
{
public:
	static Controller* GetSingleton();

	void TryAccelerate();
	void TestHeightBonus();
	void CaptureStrafe();
	void TestStrafeBonus();
	void TryCrouchBoost();

	void CountStop();
	void HaltProcess();

	void ResetCounter() noexcept { g_stopCounter = 0; }

	Controller(const Controller&) = delete;
	Controller(Controller&&) = delete;
	Controller() = default;
	~Controller() = default;

	Controller& operator=(const Controller&) = delete;
	Controller& operator=(Controller&&) = delete;

private:

	int g_stopCounter = 0;
};
