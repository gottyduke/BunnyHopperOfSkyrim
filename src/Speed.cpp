#include "Speed.h"
#include "Settings.h"


auto SpeedController::GetSingleton()
-> SpeedController*
{
	static SpeedController singleton;
	return std::addressof(singleton);
}


void SpeedController::ResetBaseSpeed()
{
	UpdateBaseSpeed();
	
	player->SetActorValue(RE::ActorValue::kSpeedMult, baseSpeed);
	
	currSpeed = baseSpeed;
}


void SpeedController::UpdateBaseSpeed()
{	
	if (baseSpeed == -1) {
		baseSpeed = player->GetActorValue(RE::ActorValue::kSpeedMult);
		currSpeed = baseSpeed;
	}
	
	player->SetActorValue(RE::ActorValue::kSpeedMult, currSpeed);
}


void SpeedController::ResetJumpHeight()
{
	UpdateJumpHeight();

	bhk->jumpHeight = baseHeight;

	currHeight = baseHeight;
}


void SpeedController::UpdateJumpHeight()
{
	if (baseHeight == -1) {
		baseHeight = bhk->jumpHeight;
		currHeight = baseHeight;
	}

	bhk->jumpHeight = currHeight;
}


void SpeedController::SpeedUp()
{	
	const float speedBoost = *Settings::globalSpeedMult * (*Settings::baseSpeedBoost * *Settings::baseSpeedBoost);

	currSpeed += speedBoost;

	if (currSpeed > *Settings::maxSpeed) {
		currSpeed = *Settings::maxSpeed;
	}
	
	UpdateBaseSpeed();
}


void SpeedController::CountStop()
{
	if (++stopCounter == 3) {
		ResetCounter();
		
		ResetBaseSpeed();
		ResetJumpHeight();
	}
}


void SpeedController::StepUp()
{
	if (currSpeed / 1150 + baseHeight > currHeight) {
		currHeight = currSpeed / 1150 + baseHeight;
		UpdateJumpHeight();
	}
}


void SpeedController::ResetCounter()
{
	stopCounter = 0;
}
