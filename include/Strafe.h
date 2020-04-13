#pragma once

#include "IController.h"

#include "RE/Skyrim.h"


class StrafeController final : public IController
{
public:
	static StrafeController* GetSingleton()
	{
		static StrafeController singleton;
		return std::addressof(singleton);
	}

	// methods
	void TryStrafe();
	void CalcDipChange();
	void GainStrafeBonud();
	void Halt() noexcept override { Reset(); }
	
	StrafeController(const StrafeController&) = delete;
	StrafeController(StrafeController&&) = delete;
	StrafeController();
	~StrafeController() = default;

	StrafeController& operator=(const StrafeController&) = delete;
	StrafeController& operator=(StrafeController&&) = delete;

private:	
	void Reset() noexcept override;
	void Update() noexcept override;

	float scale;
	float diff;
	Vector pos;
};