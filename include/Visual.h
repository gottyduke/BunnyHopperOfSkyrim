#pragma once

#include "IController.h"

#include "RE/Skyrim.h"


class VisualController final : public IController
{
public:
	static VisualController* GetSingleton()
	{
		static VisualController singleton;
		return std::addressof(singleton);
	}

	void ApplyEffect();
	void RenderTrail();
	
	void Halt() noexcept override { Reset(); }

	VisualController() = default;
	~VisualController() = default;

	VisualController(const VisualController&) = delete;
	VisualController(VisualController&&) = delete;
	VisualController& operator=(const VisualController&) = delete;
	VisualController& operator=(VisualController&&) = delete;
	
private:
	void Update() noexcept override;
	void Reset() noexcept override;

	int bhkOffsetCountdown = 4;
};