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


inline float __fsqrt(const float& n)
{
	static union { int i; float f; } u;
	u.i = 0x5F375A86 - (*(int*)&n >> 1);
	return (int(3) - n * u.f * u.f) * n * u.f * 0.5f;
}


inline double __fpow(const double a, const double b)
{
	union
	{
		double d;
		int x[2];
	} u = { a };
	u.x[1] = static_cast<int>(b * (u.x[1] - 1072632447) + 1072632447);
	u.x[0] = 0;

	return u.d;
}