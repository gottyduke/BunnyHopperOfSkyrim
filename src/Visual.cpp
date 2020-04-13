#include "Visual.h"
#include "Settings.h"  // Settings

#include <thread>
#include <chrono>

#include "RE/Skyrim.h"
#include "SKSE/RegistrationSet.h"  // TaskInterface


void VisualController::Reset() noexcept
{
	bhkOffsetCountdown = 4;
	bhk->direction.quad = { 0.0f, 0.0f, 1.0144f, 0.0f };
}


void VisualController::Update() noexcept
{
}


void VisualController::ApplyEffect()
{
	if (!*Settings::enableJumpFeedback) {
		return;
	}

	// serious visual artifacts
	bhk->direction.quad = _mm_add_ps(bhk->direction.quad, { 0.0f, 0.0f, 1.0f, 0.0f });

	Update();
	
	if (--bhkOffsetCountdown <= 0) {
		Reset();
	}

#ifdef DUMP
	_DMESSAGE("Visual-ApplyEffect");
#endif
}
 

void VisualController::RenderTrail()
{
	if (!*Settings::enableTrail) {
		return;
	}

	// how do I achieve this within skse?
	
	Update();
	
#ifdef DUMP
	_DMESSAGE("Visual-RenderTrail");
#endif
}

