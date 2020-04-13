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
				controller->OnJumping();
			}
			break;
		case Anim::kFall:
		case Anim::kFallDirectional:
			{
				controller->OnFalling();
			}
			break;
		case Anim::kDown:
			{
				controller->OnLanding();
			}
			break;
		case Anim::kLandEnd:
		case Anim::kFootLeft:
		case Anim::kFootRight:
			{
				controller->OnGround();
			}
			break;
		case Anim::kGraphDeleting:
			{
				controller->OnDelete();
			}
			break;
		default: ;
		}

		return EventResult::kContinue;
	}


	auto LoadGameHandler::ProcessEvent(const RE::TESLoadGameEvent* a_event, RE::BSTEventSource<RE::TESLoadGameEvent>* a_eventSource)
	-> EventResult
	{
		if (!a_event) {
			return EventResult::kContinue;
		}

		auto controller = Controller::GetSingleton();
		controller->HaltProcess();
		
		return EventResult::kContinue;
	}

}
