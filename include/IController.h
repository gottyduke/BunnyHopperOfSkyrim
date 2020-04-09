#pragma once

#include "RE/Skyrim.h"


class IController
{
public:
	struct NiPoint3
	{
		float x;
		float y;
		float z;
	};

	STATIC_ASSERT(sizeof(NiPoint3) == 0xc);

	virtual void Halt() noexcept = 0;

	IController() = default;
	virtual ~IController() = default;

protected:

	virtual void Reset() noexcept = 0;
	virtual void Update() noexcept = 0;

	RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
	RE::PlayerCamera* camera = RE::PlayerCamera::GetSingleton();
	RE::bhkCharacterController* bhk = player->GetCharController();
};
