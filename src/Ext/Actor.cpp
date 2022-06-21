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
				if (auto actor = handle.get(); actor && actor->Is3DLoaded()) {
					Update3D(actor.get());
				}
			});
	}

	bool Actor::IsSkin(RE::Actor* a_actor, RE::TESObjectARMO* a_armor) {
		if (const auto base = a_actor->GetActorBase(); base && base->skin) {
			return a_armor == base->skin;
		} else if (const auto aRace = a_actor->GetRace(); aRace && aRace->skin) {
			return a_armor == aRace->skin;
		}

		return false;
	}

	bool Actor::IsSkin(RE::Actor* a_actor, RE::TESObjectARMA* a_armorAddon) {
		const RE::TESObjectARMO* skin = nullptr;

		if (const auto base = a_actor->GetActorBase(); base && base->skin) {
			skin = base->skin;
		} else if (const auto aRace = a_actor->GetRace(); aRace && aRace->skin) {
			skin = aRace->skin;
		}

		if (!skin) {
			return false;
		}

		auto it = std::find(skin->armorAddons.begin(), skin->armorAddons.end(), a_armorAddon);
		return it != skin->armorAddons.end();
	}
}
