#pragma once

#include "RE/Skyrim.h"


class HeightController
{
public:
	static HeightController* GetSingleton();


	void CalcHeightDiff();
	void GainHeightBonus();
	
	
	HeightController(const HeightController&) = delete;
	HeightController(HeightController&&) = delete;

	HeightController& operator=(const HeightController&) = delete;
	HeightController& operator=(HeightController&&) = delete;

protected:
	HeightController() = default;
	~HeightController() = default;

	// methods
	void ResetJumpHeight();
	void UpdateJumpHeight();
	
	// members
	float baseJumpHeight = -1;
	float currJumpHeight = -1;
	
	// controllers
	RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
	RE::bhkCharacterController* bhk = player->GetCharController();
};