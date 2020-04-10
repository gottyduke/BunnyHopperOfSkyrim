#include "Events.h"

#include "Animations.h"
#include "Controller.h"

#include "RE/Skyrim.h"


namespace Events
{
	bool AnimationGraphEventHandler(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink)
	{
		const auto player = RE::PlayerCharacter::GetSingleton();
		RE::BSAnimationGraphManagerPtr graphManager;
		player->GetAnimationGraphManager(graphManager);
		if (graphManager) {
			auto sinked = false;
			for (auto& animationGraph : graphManager->graphs) {
				if (sinked) {
					break;
				}

				auto eventSource = animationGraph->GetEventSource<RE::BSAnimationGraphEvent>();
				for (auto& sink : eventSource->sinks) {
					if (sink == a_sink) {
						sinked = true;
						break;
					}
				}
			}

			if (!sinked) {
				graphManager->graphs.front()->GetEventSource<RE::BSAnimationGraphEvent>()->AddEventSink(a_sink);
				_MESSAGE("Registered animation event handler");

				return true;
			}
		}
		return false;
	}

	auto BHopHandler::ProcessEvent(const RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource)
	-> EventResult
	{
		if (!a_event || !a_event->holder || !a_event->holder->IsPlayerRef()) {
			return EventResult::kContinue;
		}

		auto controller = Controller::GetSingleton();
		if (--safeStartCountdown >= 0) {
			controller->HaltProcess();
		}
		
		switch (HashAnimation(a_event->tag)) {
		case Anim::kUp:
			{
				controller->CaptureStrafe();
			}
			break;
		case Anim::kFall:
		case Anim::kFallDirectional:
		case Anim::kDown:
			{
				controller->TryAccelerate();
				controller->TestStrafeBonus();
			}
			break;
		case Anim::kLandEnd:
			{
				controller->TestStrafeBonus();
				controller->TestHeightBonus();
				controller->TryCrouchBoost();
				controller->TryInitRam();
			}
			break;
		case Anim::kFootLeft:
		case Anim::kFootRight:
			{
				controller->CountStop();
				controller->TestHeightBonus();
				controller->TryInitRam();
			}
			break;
		case Anim::kGraphDeleting:
			{
				controller->HaltProcess();
			}
			break;
		default: ;
		}

		return EventResult::kContinue;
	}
}
