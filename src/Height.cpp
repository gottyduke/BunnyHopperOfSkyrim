#include "Controller.h"
#include "Height.h"
#include "Speed.h"


HeightController::HeightController() :
baseJumpHeight(-1),
currJumpHeight(-1),
state(State::kNone),
pos()
{}


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
	const auto diff = player->GetPositionZ() - pos.z;
	if (diff > 5) {
		state = State::kStair;
		return;
	}
	if (abs(diff) >= *Settings::minHeightLaunch) {
		state = State::kLaunch;
		return;
	}
	state = State::kNone;
}


void HeightController::GainHeightBonus()
{
	const SpeedController speed;
	const auto bonusHeight = speed->GetCurrSpeed() / 1000;
	
	if (currJumpHeight < baseJumpHeight + bonusHeight) {
		currJumpHeight = baseJumpHeight + bonusHeight;
	}

	Update();
}


void HeightController::InitState(const State a_state)
{
	switch (a_state) {
	case State::kNone: break;
	case State::kStair:
		{
			auto Controller = Controller::GetSingleton();
			Controller->ResetCounter();
		}
		break;
	case State::kLaunch:
		{
			
		}
		break;
	default: break;
	}
	ResetPos();
}


void HeightController::ResetPos() noexcept
{
	pos.z = player->GetPositionZ();
}
