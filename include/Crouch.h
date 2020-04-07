#pragma once

#include "RE/Skyrim.h"


class CrouchController
{
public:
	static CrouchController* GetSingleton();



	CrouchController(const CrouchController&) = delete;
	CrouchController(CrouchController&&) = delete;

	CrouchController& operator=(const CrouchController&) = delete;
	CrouchController& operator=(CrouchController&&) = delete;

protected:
	CrouchController() = default;
	~CrouchController() = default;


};