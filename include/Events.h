#pragma once


#include "RE/Skyrim.h"


namespace Events
{
	bool AnimationGraphEventHandler(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink);

	
	class PlayerJumpHandler final : public RE::BSTEventSink<RE::BSAnimationGraphEvent>
	{
	public:
		using EventResult = RE::BSEventNotifyControl;

		static PlayerJumpHandler* GetSingleton();

		EventResult ProcessEvent(const RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource) override;


		PlayerJumpHandler(const PlayerJumpHandler&) = delete;
		PlayerJumpHandler(PlayerJumpHandler&&) = delete;

		PlayerJumpHandler& operator=(const PlayerJumpHandler&) = delete;
		PlayerJumpHandler& operator=(PlayerJumpHandler&&) = delete;

	protected:
		PlayerJumpHandler() = default;
		~PlayerJumpHandler() = default;
	};


}