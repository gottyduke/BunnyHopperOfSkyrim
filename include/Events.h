#pragma once

#include "RE/Skyrim.h"


namespace Events
{
	bool AnimationGraphEventHandler(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink);


	class BHopHandler final : public RE::BSTEventSink<RE::BSAnimationGraphEvent>
	{
	public:
		using EventResult = RE::BSEventNotifyControl;

		static BHopHandler* GetSingleton();

		EventResult ProcessEvent(const RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource) override;

		BHopHandler(const BHopHandler&) = delete;
		BHopHandler(BHopHandler&&) = delete;

		BHopHandler& operator=(const BHopHandler&) = delete;
		BHopHandler& operator=(BHopHandler&&) = delete;

	protected:
		BHopHandler() = default;
		~BHopHandler() = default;
	};
}
