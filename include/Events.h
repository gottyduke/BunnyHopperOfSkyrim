#pragma once

#include "Ram.h"
#include "RE/Skyrim.h"


namespace Events
{
	bool AnimationGraphEventHandler(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink);


	class BHopHandler final : public RE::BSTEventSink<RE::BSAnimationGraphEvent>
	{
	public:
		using EventResult = RE::BSEventNotifyControl;

		static BHopHandler* GetSingleton()
		{
			static BHopHandler singleton;
			return std::addressof(singleton);
		}

		EventResult ProcessEvent(const RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource) override;

	protected:
		BHopHandler() = default;
		~BHopHandler() = default;
	};
}
