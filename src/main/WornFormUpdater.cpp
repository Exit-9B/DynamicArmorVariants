#include "WornFormUpdater.h"

auto WornFormUpdater::GetSingleton() -> WornFormUpdater*
{
	static WornFormUpdater singleton{};
	return std::addressof(singleton);
}

void WornFormUpdater::Install()
{
	RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink(GetSingleton());
}

auto WornFormUpdater::ProcessEvent(
	const RE::TESActorLocationChangeEvent* a_event,
	[[maybe_unused]] RE::BSTEventSource<RE::TESActorLocationChangeEvent>* a_eventSource)
	-> RE::BSEventNotifyControl
{
	auto& actor = a_event->actor;
	if (actor && actor->Is3DLoaded()) {
		Ext::Actor::Update3D(actor);
	}

	return RE::BSEventNotifyControl::kContinue;
}
