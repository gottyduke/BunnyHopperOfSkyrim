#pragma once

#include "RE/Skyrim.h"


class StrafeController
{
public:
	static StrafeController* GetSingleton();

	void RecordChanges();
	
protected:

	RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
	
};