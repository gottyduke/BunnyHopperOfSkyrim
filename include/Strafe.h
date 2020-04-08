#pragma once

#include "IController.h"

#include <cmath>  // abs

#include "RE/Skyrim.h"


class StrafeController final : public IController<StrafeController>
{
public:
	struct NiPoint3
	{
		float x;
		float y;
		float z;
	};

	void RecordChanges();
	void SetBase();
	
	void Halt() noexcept override { Reset(); }

	
	StrafeController(const StrafeController&) = delete;
	StrafeController(StrafeController&&) = delete;
	StrafeController();
	~StrafeController() = default;

	StrafeController& operator=(const StrafeController&) = delete;
	StrafeController& operator=(StrafeController&&) = delete;

private:

	void Reset() noexcept override;
	void Update() noexcept override;

	NiPoint3 pos;
};