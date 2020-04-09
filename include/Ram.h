#pragma once

#include "IController.h"

#include <unordered_set>  // unordered_set

#include "RE/Skyrim.h"


class RamController final : public IController
{
public:

	static RamController* GetSingleton()
	{
		static RamController singleton;
		return std::addressof(singleton);
	}

	void TestRam();
	
	void Halt() noexcept override { Reset(); }


	RamController(const RamController&) = delete;
	RamController(RamController&&) = delete;
	RamController() = default;
	~RamController() = default;

	RamController& operator=(const RamController&) = delete;
	RamController& operator=(RamController&&) = delete;

private:
	void SwingBy(RE::Actor* a_actor);
	void Knockback(RE::Actor* a_actor);
	void InitRam(RE::Actor* a_actor);
	
	void TestRange(RE::Actor* a_actor) noexcept;
	
	void Reset() noexcept override;
	void Update() noexcept override;

	std::unordered_set<RE::Actor*> cooldownActor;
};
