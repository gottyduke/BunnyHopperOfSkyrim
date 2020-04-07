#pragma once

#include "RE/Skyrim.h"


class RamController
{
public:
	static RamController* GetSingleton();


	RamController(const RamController&) = delete;
	RamController(RamController&&) = delete;

	RamController& operator=(const RamController&) = delete;
	RamController& operator=(RamController&&) = delete;

protected:
	RamController() = default;
	~RamController() = default;
};