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

		BHopHandler(const BHopHandler&) = delete;
		BHopHandler(BHopHandler&&) = delete;
		BHopHandler& operator=(const BHopHandler&) = delete;
		BHopHandler& operator=(BHopHandler&&) = delete;

	protected:
		BHopHandler() = default;
		~BHopHandler() = default;

		int safeStartCountdown = 12;
	};


	class LoadGameHandler final : public RE::BSTEventSink<RE::TESLoadGameEvent>
	{
	public:
		using EventResult = RE::BSEventNotifyControl;

		static LoadGameHandler* GetSingleton()
		{
			static LoadGameHandler singleton;
			return std::addressof(singleton);
		}

		EventResult ProcessEvent(const RE::TESLoadGameEvent* a_event, RE::BSTEventSource<RE::TESLoadGameEvent>* a_eventSource) override;

		LoadGameHandler(const LoadGameHandler&) = delete;
		LoadGameHandler(LoadGameHandler&&) = delete;
		LoadGameHandler& operator=(const LoadGameHandler&) = delete;
		LoadGameHandler& operator=(LoadGameHandler&&) = delete;

	protected:
		LoadGameHandler() = default;
		~LoadGameHandler() = default;

		int safeStartCountdown = 12;
	};
}
