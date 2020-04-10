#pragma once

constexpr int IMPULSE_KEY_FRAME = 16;
constexpr int IMPULSE_SMOOTH_FRAME = 4;
constexpr int IMPULSE_GAP_FRAME = IMPULSE_KEY_FRAME / IMPULSE_SMOOTH_FRAME;
constexpr float IMPULSE_GRAVITY = 2.22f;
constexpr float IMPULSE_Z_OFFSET = 10.0f;

#include "IController.h"

#include <unordered_set>  // unordered_set

#include "RE/Skyrim.h"


class RamController final : public IController
{
public:
	// RE::hkpMotion not implemented yet, this is script-level fake
	class ForceImpl
	{
	public:
		struct ImpulseData
		{
			RE::Actor* target;
			RE::Actor* source;
			float strength;
		};
		STATIC_ASSERT(sizeof(ImpulseData) == 0x18);
		
		ForceImpl();

		void ApplyForce(RE::Actor* a_target, float a_mult) const;
		
		ForceImpl(const ForceImpl&) = delete;
		ForceImpl(ForceImpl&&) = delete;
		ForceImpl& operator=(const ForceImpl&) = delete;
		ForceImpl& operator=(ForceImpl&&) = delete;
		
	private:
		RE::SpellItem* force;
	};

	
	static RamController* GetSingleton()
	{
		static RamController singleton;
		return std::addressof(singleton);
	}

	void TestRam();
	
	void Halt() noexcept override { Reset(); }


	RamController(const RamController&) = delete;
	RamController(RamController&&) = delete;
	RamController() { hkp = new ForceImpl(); }
	~RamController() { delete hkp; }

	RamController& operator=(const RamController&) = delete;
	RamController& operator=(RamController&&) = delete;

private:
	void TestRange(RE::Actor* a_actor) noexcept;
	
	void Reset() noexcept override;
	void Update() noexcept override;

	std::unordered_set<RE::Actor*> cooldownActor;
	ForceImpl* hkp;
};
STATIC_ASSERT(sizeof(RamController) == 0x68);