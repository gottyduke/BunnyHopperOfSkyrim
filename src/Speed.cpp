#include "Speed.h"
#include "Controller.h"


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
	
	if (currSpeed > * Settings::maxSpeed) {
		currSpeed = *Settings::maxSpeed;
	}
	
	player->SetActorValue(RE::ActorValue::kSpeedMult, currSpeed);
}


void SpeedController::SpeedUp()
{	
	const float speedBoost = *Settings::globalSpeedMult * (*Settings::baseSpeedBoost * *Settings::baseSpeedBoost);

	currSpeed += speedBoost;
	
	UpdateBaseSpeed();
}


void SpeedController::CountStop()
{
	if (++stopCounter == 3) {
		ResetCounter();
		
		ResetBaseSpeed();
	}
}


void SpeedController::ResetCounter() noexcept
{
	stopCounter = 0;
}
