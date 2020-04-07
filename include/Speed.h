#pragma once

#include "Settings.h"

#include "RE/Skyrim.h"


class SpeedController
{
public:
	
	static SpeedController* GetSingleton();


	void ResetBaseSpeed();
	void ResetJumpHeight();

	void UpdateBaseSpeed();
	void UpdateJumpHeight();
	
	void SpeedUp();
	void CountStop();

	void StepUp();
	
	inline void ResetCounter();
	
	SpeedController(const SpeedController&) = delete;
	SpeedController(SpeedController&&) = delete;

	SpeedController& operator=(const SpeedController&) = delete;
	SpeedController& operator=(SpeedController&&) = delete;
	
protected:
	SpeedController() = default;
	~SpeedController() = default;

	// members
	float baseSpeed = -1;
	float currSpeed = -1;

	float baseHeight = -1;
	float currHeight = -1;
	
	int stopCounter = 0;

	// controllers
	RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
	RE::bhkCharacterController* bhk = player->GetCharController();
};