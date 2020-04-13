#include "Controller.h"

#include "Crouch.h"
#include "Height.h"
#include "Ram.h"
#include "Speed.h"
#include "Strafe.h"
#include "Visual.h"

#include "Settings.h"


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
	
	ResetCounter();
}


void Controller::OnFalling()
{
	auto Height = HeightController::GetSingleton();
	auto Ram = RamController::GetSingleton();
	auto Speed = SpeedController::GetSingleton();
	auto Strafe = StrafeController::GetSingleton();

	Height->GainHeightBonus();

	Ram->TestRam();
	
	Speed->SpeedUp();

	Strafe->CalcDipChange();
	Strafe->GainStrafeBonud();
}


void Controller::OnLanding()
{
	auto Crouch = CrouchController::GetSingleton();
	auto Height = HeightController::GetSingleton();
	auto Ram = RamController::GetSingleton();
	auto Strafe = StrafeController::GetSingleton();
	auto Visual = VisualController::GetSingleton();

	Crouch->GainCrouchBonus();

	Height->CalcHeightDiff();
	Height->InitState(Height->GetLastState());

	Ram->TestRam();
	
	Strafe->CalcDipChange();
	Strafe->GainStrafeBonud();

	Visual->ApplyEffect();
	Visual->RenderTrail();
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
