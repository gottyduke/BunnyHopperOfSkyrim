#pragma once

#include "IController.h"
#include "RE/Skyrim.h"


class RamController final : public IController<RamController>
{
public:
	
	void Halt() noexcept override { Reset(); }
	

	RamController(const RamController&) = delete;
	RamController(RamController&&) = delete;
	RamController();
	~RamController() = default;

	RamController& operator=(const RamController&) = delete;
	RamController& operator=(RamController&&) = delete;

private:

	void Reset() noexcept override;
	void Update() noexcept override;
};