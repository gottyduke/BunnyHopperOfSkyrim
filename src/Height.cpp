#include "Height.h"


auto HeightController::GetSingleton()
-> HeightController*
{
	static HeightController singleton;
	return std::addressof(singleton);
}


void HeightController::ResetJumpHeight()
{
	UpdateJumpHeight();

	bhk->jumpHeight = baseJumpHeight;

	currJumpHeight = baseJumpHeight;
}


void HeightController::UpdateJumpHeight()
{
	if (baseJumpHeight == -1) {
		baseJumpHeight = bhk->jumpHeight;
		currJumpHeight = baseJumpHeight;
	}

	bhk->jumpHeight = currJumpHeight;
}


void HeightController::CalcHeightDiff()
{
	
}


void HeightController::GainHeightBonus()
{
	
}
