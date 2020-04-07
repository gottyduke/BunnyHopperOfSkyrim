#pragma once

#include "Settings.h"

#include "RE/Skyrim.h"


class SpeedController
{
public:
	
	static SpeedController* GetSingleton();

	
	void SpeedUp();
	void CountStop();

	inline void ResetCounter() noexcept;

	// getter
	[[nodiscard]] constexpr float GetBaseSpeed() const noexcept { return baseSpeed; }
	[[nodiscard]] constexpr float GetCurrSpeed() const noexcept { return currSpeed; }

	// tor
	SpeedController(const SpeedController&) = delete;
	SpeedController(SpeedController&&) = delete;

	SpeedController& operator=(const SpeedController&) = delete;
	SpeedController& operator=(SpeedController&&) = delete;
	
protected:
	SpeedController() = default;
	~SpeedController() = default;

	// methods
	void ResetBaseSpeed();
	void UpdateBaseSpeed();

	// members
	float baseSpeed = -1;
	float currSpeed = -1;
	int stopCounter = 0;

	// controllers
	RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
	RE::bhkCharacterController* bhk = player->GetCharController();
};