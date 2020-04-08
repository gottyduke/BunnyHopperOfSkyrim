#include "Speed.h"


SpeedController::SpeedController()
{
	
}


void SpeedController::Reset() noexcept
{
	Update();
	
	player->SetActorValue(RE::ActorValue::kSpeedMult, baseSpeed);
	
	currSpeed = baseSpeed;
}


void SpeedController::Update() noexcept
{	
	if (baseSpeed == -1) {
		baseSpeed = player->GetActorValue(RE::ActorValue::kSpeedMult);
		currSpeed = baseSpeed;
	}
	
	if (currSpeed > * Settings::maxSpeed) {
		currSpeed = *Settings::maxSpeed;
	}
	
	player->SetActorValue(RE::ActorValue::kSpeedMult, currSpeed);
}


void SpeedController::SpeedUp()
{	
	const float speedBoost = *Settings::globalSpeedMult * (*Settings::baseSpeedBoost * *Settings::baseSpeedBoost);

	currSpeed += speedBoost;
	
	Update();
}