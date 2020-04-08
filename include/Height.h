#pragma once

#include "IController.h"

#include "RE/Skyrim.h"


class HeightController final : public IController<HeightController>
{
public:
	enum class State : UInt8
	{
		kNone = 1 << 0,
		kStair = 1 << 1,
		kLaunch = 1 << 2
	};
	//STATIC_ASSERT(sizeof(State) == 0x1);
	

	// methods
	void CalcHeightDiff();
	void GainHeightBonus();
	void InitState(State a_state);
	void ResetPos() noexcept;
	void Halt() noexcept override { Reset(); }
	[[nodiscard]] constexpr State GetLastState() const noexcept { return state; }
	[[nodiscard]] constexpr float GetBaseJumpHeight() const noexcept { return baseJumpHeight; }
	[[nodiscard]] constexpr float GetCurrJumpHeight() const noexcept { return currJumpHeight; }


	// ctor dtor
	HeightController(const HeightController&) = delete;
	HeightController(HeightController&&) = delete;
	HeightController();
	~HeightController() = default;

	HeightController& operator=(const HeightController&) = delete;
	HeightController& operator=(HeightController&&) = delete;

private:

	// methods
	void Reset() noexcept override;
	void Update() noexcept override;
	
	// members
	float baseJumpHeight;
	float currJumpHeight;

	State state;
	NiPoint3 pos;
};