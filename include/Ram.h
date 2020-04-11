#pragma once

#define IMPULSE_KEY_PER_FRAME 2
#define IMPULSE_VALIDATE_COUNT 3

#define IMPULSE_GRAVITY 9.8f
#define IMPULSE_DAMPING 2.0f
#define IMPULSE_X_OFFSET 10.0f
#define IMPULSE_Y_OFFSET 10.0f
#define IMPULSE_Z_OFFSET 10.0f

#define IMPULSE_TO_DISPLACEMENT(V, A) ((V) * IMPULSE_KEY_PER_FRAME - (A) * 0.5f * pow(IMPULSE_KEY_PER_FRAME, 2))
#define IMPULSE_VALIDATE_COLLISION(X, Y, Z) ()

#include "IController.h"

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
			RE::SpellItem* force;
		};
		STATIC_ASSERT(sizeof(ImpulseData) == 0x20);
		
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
	RamController() { hkp = new ForceImpl; }
	~RamController() { delete hkp; }

	RamController& operator=(const RamController&) = delete;
	RamController& operator=(RamController&&) = delete;

private:
	void TestRange(RE::Actor* a_actor) const noexcept;
	
	void Reset() noexcept override;
	void Update() noexcept override;

	ForceImpl* hkp;
};
STATIC_ASSERT(sizeof(RamController) == 0x28);