#pragma once

namespace Ext
{
	namespace Actor
	{
		bool Update3D(RE::Actor* a_actor);
		void Update3DSafe(RE::Actor* a_actor);
		bool IsSkin(RE::Actor* a_actor, RE::TESObjectARMO* a_armor);
		bool IsSkin(RE::Actor* a_actor, RE::TESObjectARMA* a_armorAddon);
	}
}
