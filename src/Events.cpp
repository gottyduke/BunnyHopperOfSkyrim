#include "Events.h"

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

	
	auto PlayerJumpHandler::GetSingleton()
		-> PlayerJumpHandler*
	{
		static PlayerJumpHandler singleton;
		return std::addressof(singleton);
	}


	auto PlayerJumpHandler::ProcessEvent(const RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource)
	-> EventResult
	{
		if (!a_event || !a_event->holder || !a_event->holder->IsPlayerRef()) {
			return EventResult::kContinue;
		}

		//_DMESSAGE(a_event->tag.c_str());
		
		auto controller = SpeedController::GetSingleton();
		auto strafe = StrafeController::GetSingleton();
		
		switch (HashAnimation(a_event->tag)) {
		case Anim::kUp:
			{
				controller->StepUp();
				strafe->RecordChanges();
			}
			break;
		case Anim::kFall:
		case Anim::kDown:
		case Anim::kLandEnd:
			{
				controller->SpeedUp();
				controller->ResetCounter();
			}
			break;
		case Anim::kFootLeft:
		case Anim::kFootRight:
		case Anim::kGraphDeleting:
			{
				controller->CountStop();
			}
			break;
		default: ;
		}
		
		return EventResult::kContinue;
	}
}