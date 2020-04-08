#include "Controller.h"
#include "Settings.h"


Controller::Controller() :
g_stopCounter(0)
{}


void Controller::TryAccelerate()
{
	Speed->SpeedUp();
	Height->GainHeightBonus();
}


void Controller::TestHeight()
{
	Height->CalcHeightDiff();
	Height->InitState(Height->GetLastState());
}


void Controller::TryCrouchBoost()
{
	
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
	Speed->Halt();
	Strafe->Halt();
	Height->Halt();
}
