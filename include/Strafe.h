#pragma once

#include <cmath>  // abs

#include "RE/Skyrim.h"


class StrafeController
{
public:
	struct NiPoint3
	{
		float x;
		float y;
		float z;
	};

	
	static StrafeController* GetSingleton();

	void RecordChanges();
	void SetBase();
	
	
	StrafeController(const StrafeController&) = delete;
	StrafeController(StrafeController&&) = delete;

	StrafeController& operator=(const StrafeController&) = delete;
	StrafeController& operator=(StrafeController&&) = delete;

protected:
	StrafeController() = default;
	~StrafeController() = default;
	
private:
	RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
	NiPoint3 pos;
};