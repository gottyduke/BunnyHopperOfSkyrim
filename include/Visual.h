#pragma once

#include "IController.h"

#include "RE/Skyrim.h"


class VisualController final : public IController
{
public:
	enum class State : UInt32
	{
		kFirstPerson = 901943132160,
		kThirdPerson = 901943132169
	};
	
	static VisualController* GetSingleton()
	{
		static VisualController singleton;
		return std::addressof(singleton);
	}
	
	void ApplyEffect();
	
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