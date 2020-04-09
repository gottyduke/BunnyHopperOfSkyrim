#pragma once

#include "IController.h"
#include "RE/Skyrim.h"


class CrouchController final : public IController
{
public:

	static CrouchController* GetSingleton()
	{
		static CrouchController singleton;
		return std::addressof(singleton);
	}

	void GainCrouchBonus();
	
	void Halt() noexcept override { Reset(); }

	CrouchController(const CrouchController&) = delete;
	CrouchController(CrouchController&&) = delete;
	CrouchController() = default;
	~CrouchController() = default;

	CrouchController& operator=(const CrouchController&) = delete;
	CrouchController& operator=(CrouchController&&) = delete;

private:

	void Reset() noexcept override;
	void Update() noexcept override;

	int cooldown = 0;
};
