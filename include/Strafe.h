#pragma once

#include "IController.h"

#include "RE/Skyrim.h"

class StrafeController final : public IController
{
public:
	static StrafeController* GetSingleton()
	{
		static StrafeController singleton;
		return std::addressof(singleton);
	}

	// methods
	void TryStrafe();
	void CalcDipChange();
	void GainStrafeBonud() const;
	void Halt() noexcept override { Reset(); }
	
	StrafeController(const StrafeController&) = delete;
	StrafeController(StrafeController&&) = delete;
	StrafeController();
	~StrafeController() = default;

	StrafeController& operator=(const StrafeController&) = delete;
	StrafeController& operator=(StrafeController&&) = delete;

private:

	[[nodiscard]] inline float FastTrig(float a_b, float a_c) const noexcept;
	
	void Reset() noexcept override;
	void Update() noexcept override;

	float scale;
	float diff;
	NiPoint3 pos;
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