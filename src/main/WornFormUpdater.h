#pragma once

#include "Ext/Actor.h"
#include "RE/TESActorLocationChangeEvent.h"

class WornFormUpdater : public RE::BSTEventSink<RE::TESActorLocationChangeEvent>
{
public:
	~WornFormUpdater() = default;
	WornFormUpdater(const WornFormUpdater&) = delete;
	WornFormUpdater(WornFormUpdater&&) = delete;
	WornFormUpdater& operator=(const WornFormUpdater&) = delete;
	WornFormUpdater& operator=(WornFormUpdater&&) = delete;

	static auto GetSingleton() -> WornFormUpdater*;

	static void Install();

	auto ProcessEvent(
		const RE::TESActorLocationChangeEvent* a_event,
		RE::BSTEventSource<RE::TESActorLocationChangeEvent>* a_eventSource)
		-> RE::BSEventNotifyControl override;

private:
	WornFormUpdater() = default;
};
