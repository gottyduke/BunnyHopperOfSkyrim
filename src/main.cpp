#include "Events.h"
#include "version.h"
#include "Settings.h"

#include "RE/Skyrim.h"
#include "SKSE/API.h"


namespace
{
	class TESObjectLoadedEventHandler final : public RE::BSTEventSink<RE::TESObjectLoadedEvent>
	{
	public:
		using EventResult = RE::BSEventNotifyControl;


		static TESObjectLoadedEventHandler* GetSingleton()
		{
			static TESObjectLoadedEventHandler singleton;
			return std::addressof(singleton);
		}


		auto ProcessEvent(const RE::TESObjectLoadedEvent* a_event, RE::BSTEventSource<RE::TESObjectLoadedEvent>* a_eventSource)
			-> EventResult override
		{
			if (!a_event) {
				return EventResult::kContinue;
			}

			const auto player = RE::PlayerCharacter::GetSingleton();
			if (a_event->formID == player->formID) {
				AnimationGraphEventHandler(Events::BHopHandler::GetSingleton());
			}

			return EventResult::kContinue;
		}

		TESObjectLoadedEventHandler(const TESObjectLoadedEventHandler&) = delete;
		TESObjectLoadedEventHandler(TESObjectLoadedEventHandler&&) = delete;

		TESObjectLoadedEventHandler& operator=(const TESObjectLoadedEventHandler&) = delete;
		TESObjectLoadedEventHandler& operator=(TESObjectLoadedEventHandler&&) = delete;

	protected:
		TESObjectLoadedEventHandler() = default;
		virtual ~TESObjectLoadedEventHandler() = default;
	};


	void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type) {
		case SKSE::MessagingInterface::kDataLoaded:
			{
				auto sourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
				sourceHolder->AddEventSink<RE::TESObjectLoadedEvent>(TESObjectLoadedEventHandler::GetSingleton());
			}
			break;
		default:;
		}
	}
}


extern "C"
{
	bool SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
	{
		SKSE::Logger::OpenRelative(FOLDERID_Documents, L"\\My Games\\Skyrim Special Edition\\SKSE\\BunnyHopperOfSkyrim.log");
		SKSE::Logger::SetPrintLevel(SKSE::Logger::Level::kDebugMessage);
		SKSE::Logger::SetFlushLevel(SKSE::Logger::Level::kDebugMessage);
		SKSE::Logger::UseLogStamp(true);

		_MESSAGE("BunnyHopperOfSkyrim v%s", BHOS_VERSION_VERSTRING);

		a_info->infoVersion = SKSE::PluginInfo::kVersion;
		a_info->name = "BunnyHopperOfSkyrim";
		a_info->version = BHOS_VERSION_MAJOR;

		if (a_skse->IsEditor()) {
			_FATALERROR("Loaded in editor, marking as incompatible!\n");
			return false;
		}

		const auto ver = a_skse->RuntimeVersion();
		if (ver <= SKSE::RUNTIME_1_5_39) {
			_FATALERROR("Unsupported runtime version %s!", ver.GetString().c_str());
			return false;
		}

		return true;
	}


	bool SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
	{
		_MESSAGE("BunnyHopperOfSkyrim loaded");

		if (!Init(a_skse)) {
			return false;
		}

		const auto messaging = SKSE::GetMessagingInterface();
		if (messaging->RegisterListener("SKSE", MessageHandler)) {
			_MESSAGE("Messaging interface registration successful");
		} else {
			_FATALERROR("Messaging interface registration failed!\n");
			return false;
		}

		if (Settings::LoadSettings()) {
			_MESSAGE("Settings successfully loaded");
		} else {
			_FATALERROR("Settings failed to load!\n");
			return false;
		}

		return true;
	}
};