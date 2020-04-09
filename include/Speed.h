#pragma once

#include "IController.h"


class SpeedController final : public IController
{
public:

	void SpeedUp(float a_speedOffset = 0.0f);

	void Halt() noexcept override { Reset(); }

	static SpeedController* GetSingleton()
	{
		static SpeedController singleton;
		return std::addressof(singleton);
	}

	[[nodiscard]] constexpr float GetBaseSpeed() const noexcept { return baseSpeed; }
	[[nodiscard]] constexpr float GetCurrSpeed() const noexcept { return currSpeed; }


	SpeedController(const SpeedController&) = delete;
	SpeedController(SpeedController&&) = delete;
	SpeedController() = default;
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
};
