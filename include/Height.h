#pragma once

#include "RE/Skyrim.h"


class HeightController
{
public:
	static HeightController* GetSingleton();


	HeightController(const HeightController&) = delete;
	HeightController(HeightController&&) = delete;

	HeightController& operator=(const HeightController&) = delete;
	HeightController& operator=(HeightController&&) = delete;

protected:
	HeightController() = default;
	~HeightController() = default;


};