#include "Controller.h"
#include "Settings.h"

#include "Crouch.h"
#include "Height.h"
#include "Ram.h"
#include "Speed.h"
#include "Strafe.h"


auto Controller::GetSingleton()
-> Controller*
{
	static Controller singleton;
	return std::addressof(singleton);
}


void Controller::TryAccelerate()
{
	auto Speed = SpeedController::GetSingleton();
	auto Height = HeightController::GetSingleton();

	Speed->SpeedUp();
	Height->GainHeightBonus();
	
	ResetCounter();
}


void Controller::TestHeightBonus()
{
	auto Height = HeightController::GetSingleton();

	Height->CalcHeightDiff();
	Height->InitState(Height->GetLastState());
}


void Controller::CaptureStrafe()
{
	auto Strafe = StrafeController::GetSingleton();

	Strafe->TryStrafe();
}


void Controller::TestStrafeBonus()
{
	auto Strafe = StrafeController::GetSingleton();

	Strafe->CalcDipChange();
	Strafe->GainStrafeBonud();
}


void Controller::TryCrouchBoost()
{
	auto Crouch = CrouchController::GetSingleton();

	Crouch->GainCrouchBonus();
}


void Controller::CountStop()
{
	if (++g_stopCounter >= *Settings::misttepAllowed) {
		g_stopCounter = 0;
		HaltProcess();
	}
}


void Controller::HaltProcess()
{
	auto Speed = SpeedController::GetSingleton();
	auto Strafe = StrafeController::GetSingleton();
	auto Height = HeightController::GetSingleton();

	Speed->Halt();
	Strafe->Halt();
	Height->Halt();
}
