#pragma once

#include "IController.h"
#include "RE/Skyrim.h"


class RamController final : public IController
{
public:

	static RamController* GetSingleton()
	{
		static RamController singleton;
		return std::addressof(singleton);
	}

	void Halt() noexcept override { Reset(); }


	RamController(const RamController&) = delete;
	RamController(RamController&&) = delete;
	RamController() = default;
	~RamController() = default;

	RamController& operator=(const RamController&) = delete;
	RamController& operator=(RamController&&) = delete;

private:

	void Reset() noexcept override;
	void Update() noexcept override;
};
