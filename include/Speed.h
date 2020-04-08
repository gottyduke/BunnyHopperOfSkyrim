#pragma once

#include "IController.h"
#include "Settings.h"

#include "RE/Skyrim.h"


class SpeedController final : public IController<SpeedController>
{
public:
		
	void SpeedUp();
	
	void Halt() noexcept override { Reset(); }
	
	
	[[nodiscard]] constexpr float GetBaseSpeed() const noexcept { return baseSpeed; }
	[[nodiscard]] constexpr float GetCurrSpeed() const noexcept { return currSpeed; }

	
	SpeedController(const SpeedController&) = delete;
	SpeedController(SpeedController&&) = delete;
	SpeedController();
	~SpeedController() = default;

	SpeedController& operator=(const SpeedController&) = delete;
	SpeedController& operator=(SpeedController&&) = delete;
	
private:

	// methods
	void Reset() noexcept override;
	void Update() noexcept override;

	
	// members
	float baseSpeed = -1;
	float currSpeed = -1;
	int stopCounter = 0;
};