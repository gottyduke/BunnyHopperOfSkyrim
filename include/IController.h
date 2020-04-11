#pragma once

#include <cmath> 

#include "RE/Skyrim.h"


namespace
{	
	struct Coord2
	{
		float x;
		float y;
	};

	struct Coord3 : Coord2
	{
		float z;
	};


	// fast square root
	[[nodiscard]] float __fsqrt(const float& n)
	{
		static union { int i; float f; } u;
		u.i = 0x5F375A86 - (*(int*)&n >> 1);
		return (int(3) - n * u.f * u.f) * n * u.f * 0.5f;
	}


	// distance between 2d points
	[[nodiscard]] auto CalcDistance2D(const Coord2& P1, const Coord2& P2) noexcept
	-> double
	{
		return __fsqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));
	}


	// distance between 3d points
	[[nodiscard]] auto CalcDistance3D(const Coord3& P1, const Coord3& P2) noexcept
	-> double
	{
		return __fsqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2) + pow(P1.z - P2.z, 2));
	}


	// diffY / hypo
	[[nodiscard]] auto CalcAngle2D(const Coord2& P1, const Coord2& P2) noexcept
	-> double
	{
		const auto rad = acos((P1.y - P2.y) / CalcDistance2D(P1, P2));
		return rad * (180.0 / 3.141592653589793238463);
	}


	// diffX / hypo
	[[nodiscard]] auto CalcAngle3D(const Coord3& P1, const Coord3& P2) noexcept
	-> double
	{
		const auto theta = acos(CalcDistance2D(P1, P2) / CalcDistance3D(P1, P2));
		return theta * (180.0 / 3.141592653589793238463);
	}
}


class IController
{
public:
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

