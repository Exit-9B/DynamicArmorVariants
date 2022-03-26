#pragma once

namespace Ext
{
	namespace TESObjectARMA
	{
		bool HasRace(RE::TESObjectARMA* a_armorAddon, RE::TESRace* a_race);

		void InitWornArmorAddon(
			RE::TESObjectARMA* a_armorAddon,
			RE::TESObjectARMO* a_armor,
			RE::BSTSmartPointer<RE::BipedAnim>* a_biped,
			RE::SEX a_sex);
	}
}
