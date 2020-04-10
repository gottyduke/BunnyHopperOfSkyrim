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

	
	[[nodiscard]] float __fsqrt(const float& n)
	{
		static union { int i; float f; } u;
		u.i = 0x5F375A86 - (*(int*)&n >> 1);
		return (int(3) - n * u.f * u.f) * n * u.f * 0.5f;
	}


	[[nodiscard]] double __fpow(const double a, const double b)
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


	// for hypotenuse when strafe
	[[nodiscard]] auto CalcDistance2D(const Coord2& a_co_1, const Coord2& a_co_2) noexcept
	-> double
	{
		return __fsqrt(__fpow(a_co_1.x - a_co_2.x, 2) + __fpow(a_co_1.y - a_co_2.y, 2));
	}


	// for projectile angle when ram
	[[nodiscard]] auto CalcDistance3D(const Coord3& a_co_1, const Coord3& a_co_2) noexcept
	-> double
	{
		return __fsqrt(__fpow(a_co_1.x - a_co_2.x, 2) + __fpow(a_co_1.y - a_co_2.y, 2) + __fpow(a_co_1.z - a_co_2.z, 2));
	}


	[[nodiscard]] auto CalcAngle2D(const Coord2& a_co_1, const Coord2& a_co_2) noexcept
	-> double
	{
		const auto hypo = CalcDistance2D(a_co_1, a_co_2);
		const auto rad = acos((__fpow(hypo, 2) + __fpow(a_co_1.y - a_co_2.y, 2) - __fpow(a_co_1.x - a_co_2.x, 2)) / (2 * hypo * fabs(a_co_1.y - a_co_2.y)));
		return rad * (180.0 / 3.141592653589793238463);
	}


	[[nodiscard]] auto CalcAngle3D(const Coord3& a_co_1, const Coord3& a_co_2) noexcept
	-> double
	{
		const auto height = fabs(a_co_1.z - a_co_2.z);
		const auto base = CalcDistance2D(a_co_1, a_co_2);
		const auto hypo = __fsqrt(__fpow(base, 2) + __fpow(height, 2));
		const auto rad = acos((__fpow(hypo, 2) + __fpow(base, 2) - __fpow(height, 2)) / (2 * hypo * height));
		return rad * (180.0 / 3.141592653589793238463);
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

