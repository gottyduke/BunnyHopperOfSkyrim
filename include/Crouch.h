#pragma once

#include "IController.h"
#include "RE/Skyrim.h"


class CrouchController final : public IController<CrouchController>
{
public:

	void Halt() noexcept override { Reset(); }

	
	CrouchController(const CrouchController&) = delete;
	CrouchController(CrouchController&&) = delete;
	CrouchController();
	~CrouchController() = default;

	CrouchController& operator=(const CrouchController&) = delete;
	CrouchController& operator=(CrouchController&&) = delete;

private:

	void Reset() noexcept override;
	void Update() noexcept override;
};