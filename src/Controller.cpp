#include "Controller.h"

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


void Controller::TryInitRam()
{
	auto Ram = RamController::GetSingleton();

	Ram->TestRam();
}


void Controller::CountStop()
{	
	if (++stopCounter >= *Settings::misttepAllowed) {
		ResetCounter();
		HaltProcess();
	}
}


void Controller::HaltProcess()
{
	auto Crouch = CrouchController::GetSingleton();
	auto Height = HeightController::GetSingleton();
	auto Ram = RamController::GetSingleton();
	auto Speed = SpeedController::GetSingleton();
	auto Strafe = StrafeController::GetSingleton();

	Crouch->Halt();
	Height->Halt();
	Ram->Halt();
	Speed->Halt();
	Strafe->Halt();
	
	ResetCounter();

	// GFx Notify("HaltProcess")
}
