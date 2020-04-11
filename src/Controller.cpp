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


void Controller::OnJumping()
{
	auto Strafe = StrafeController::GetSingleton();
	Strafe->TryStrafe();
}


void Controller::OnFalling()
{
	auto Speed = SpeedController::GetSingleton();
	auto Height = HeightController::GetSingleton();
	auto Strafe = StrafeController::GetSingleton();

	Speed->SpeedUp();
	Height->GainHeightBonus();

	ResetCounter();

	Strafe->CalcDipChange();
	Strafe->GainStrafeBonud();
}


void Controller::OnLanding()
{
	auto Crouch = CrouchController::GetSingleton();
	auto Height = HeightController::GetSingleton();
	auto Ram = RamController::GetSingleton();
	auto Strafe = StrafeController::GetSingleton();
	
	Crouch->GainCrouchBonus();

	Height->CalcHeightDiff();
	Height->InitState(Height->GetLastState());

	Ram->TestRam();
	
	Strafe->CalcDipChange();
	Strafe->GainStrafeBonud();
}


void Controller::OnGround()
{
	if (++stopCounter >= *Settings::misttepAllowed) {
		ResetCounter();
		HaltProcess();
	}
	
	auto Height = HeightController::GetSingleton();
	auto Ram = RamController::GetSingleton();

	Height->CalcHeightDiff();
	Height->InitState(Height->GetLastState());

	Ram->TestRam();
}


void Controller::OnDelete()
{
	HaltProcess();
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
