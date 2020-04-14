#include "Visual.h"
#include "Settings.h"  // Settings

#include <thread>  // thread
#include <chrono>  // chrono

#include "RE/Skyrim.h"
#include "SKSE/RegistrationSet.h"  // TaskInterface
#include "Speed.h"


void VisualController::Reset() noexcept
{
	bhkOffsetCountdown = 4;
	bhk->direction.quad.m128_f32[2] = 1.0144f;
}


void VisualController::Update() noexcept
{
	
}


void VisualController::ApplyEffect()
{
	if (!*Settings::enableJumpFeedback) {
		return;
	}

	if (State(camera->currentState->id) == State::kThirdPerson) {
		Reset();
		return;
	}
	
	if (*Settings::enableFovZoom) {
		const auto task = SKSE::GetTaskInterface();
		task->AddTask([]() -> void
		{
			std::thread zoom([]() -> void
			{
				auto camera = RE::PlayerCamera::GetSingleton();
				
				auto qtframe = 0;
				while (qtframe < 32) {
					camera->worldFOV += qtframe >= 16 ? 0.1f : -0.1f;
					
					std::this_thread::sleep_for(std::chrono::milliseconds(4));
					++qtframe;
				}
			});
			zoom.detach();
		});
	}

	if (*Settings::enableTremble) {
		// may cause serious visual artifact
		bhk->direction.quad.m128_f32[2] += 0.5f;
		
		if (--bhkOffsetCountdown < 0) {
			Reset();
		}
	}
	
#ifdef DUMP
	_DMESSAGE("Visual-ApplyEffect");
#endif
}