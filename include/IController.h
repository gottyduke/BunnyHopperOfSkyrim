#pragma once
#define DUMP

#include "RE/Skyrim.h"


namespace
{
	// x y z w
	typedef __m128 __declspec(align(16)) Vector;

	
	// fast square root
	[[nodiscard]] float __fsqrt(const float& n)
	{
		static union { int i; float f; } u;
		u.i = 0x5F375A86 - (*(int*)&n >> 1);
		return (int(3) - n * u.f * u.f) * n * u.f * 0.5f;
	}


	// distance in 2d / 3d
	[[nodiscard]] auto CalcDistance(const Vector& v1, const Vector& v2, const bool calc_Z = false) noexcept
	-> float
	{
		const auto diff = _mm_sub_ps(v1, v2);
		const auto power = _mm_mul_ps(diff, diff);
		return __fsqrt(power.m128_f32[0] + power.m128_f32[1] + (calc_Z ? power.m128_f32[2] : 0.0f));
	}


	// radian acos ( Y / dist )
	[[nodiscard]] auto CalcAngle2D(Vector& v1, Vector& v2) noexcept
	-> float
	{
		return acosf((v1.m128_f32[1] - v2.m128_f32[1]) / CalcDistance(v1, v2));
	}


	// radian acos ( X / dist )
	[[nodiscard]] auto CalcAngle3D(Vector& v1, Vector& v2) noexcept
	-> float
	{
		return acosf(CalcDistance(v1, v2) / CalcDistance(v1, v2, true));
	}
}


class IController
{
public:
	virtual void Halt() noexcept = 0;

	IController() = default;
	virtual ~IController() = default;

	IController(const IController&) = delete;
	IController(IController&&) = delete;
	IController& operator=(const IController&) = delete;
	IController& operator=(IController&&) = delete;
	
protected:
	
	virtual void Reset() noexcept = 0;
	virtual void Update() noexcept = 0;

	RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
	RE::bhkCharacterController* bhk = player->GetCharController();
	RE::PlayerCamera* camera = RE::PlayerCamera::GetSingleton();
};

