#include "Controller.h"
#include "Height.h"
#include "Speed.h"
#include "Settings.h"

#include <cmath>  // fabs


void HeightController::Reset() noexcept
{
	Update();

	bhk->jumpHeight = baseJumpHeight;

	currJumpHeight = baseJumpHeight;
}


void HeightController::Update() noexcept
{
	if (baseJumpHeight == -1) {
		baseJumpHeight = bhk->jumpHeight;
		currJumpHeight = baseJumpHeight;
	}

	bhk->jumpHeight = currJumpHeight;
}


void HeightController::CalcHeightDiff()
{
	const auto diff = player->GetPositionZ() - pos;
	// average height for stairs & hills
	if (diff >= 68.6f) {
		state = State::kStair;
		return;
	}
	if (diff < 0.0f && 
		abs(diff) >= *Settings::minHeightLaunch) {
		state = State::kLaunch;
		return;
	}
	state = State::kNone;
}


// distinguish : This HeightBonus is kJumpHeight not HeightLaunch
void HeightController::GainHeightBonus()
{
	const auto Speed = SpeedController::GetSingleton();
	const auto bonusHeight = Speed->GetCurrSpeed() / 1000;

	if (currJumpHeight < baseJumpHeight + bonusHeight) {
		currJumpHeight = baseJumpHeight + bonusHeight;
		
		// GFx Notify("HeightBonus")
	}

	Update();
}


void HeightController::InitState(const State a_state)
{
	auto controller = Controller::GetSingleton();
	switch (a_state) {
	case State::kNone: break;
	case State::kStair:
		{
			controller->ResetCounter();
		}
		break;
	case State::kLaunch:
		{
			TryHeightLaunch();
			controller->ResetCounter();
		}
		break;
	default: break;
	}
	ResetPos();
}


void HeightController::TryHeightLaunch() const
{
	const auto Speed = SpeedController::GetSingleton();
	const auto diff = player->GetPositionZ() - pos;
	
	Speed->SpeedUp(*Settings::globalSpeedMult * *Settings::heightLaunchMult * fabs(diff));
	// GFx Notify("HeightLaunch")
}


void HeightController::ResetPos() noexcept
{
	pos = player->GetPositionZ();
}
