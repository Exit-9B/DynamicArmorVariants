#include "Actor.h"
#include "RE/Offset.Ext.h"

namespace Ext
{
	bool Actor::Update3D(RE::Actor* a_actor)
	{
		using func_t = decltype(Update3D);
		static REL::Relocation<func_t> func{ RE::Offset::Actor::Update3D };
		return func(a_actor);
	}

	void Actor::Update3DSafe(RE::Actor* a_actor)
	{
		auto handle = a_actor->GetHandle();
		SKSE::GetTaskInterface()->AddTask([handle]
			{
				if (auto actor = handle.get()) {
					Update3D(actor.get());
				}
			});
	}
}
