#pragma once

namespace Patches
{
	using InitWornArmorFunc = void(
		RE::TESObjectARMO* a_armor,
		RE::Actor* a_actor,
		RE::BSTSmartPointer<RE::BipedAnim>* a_biped);

	void WriteInitWornPatch(InitWornArmorFunc* a_func);

	using GetWornMaskFunc = auto(RE::InventoryChanges* a_inventoryChanges) -> BipedObjectSlot;

	void WriteGetWornMaskPatch(GetWornMaskFunc* a_func);
}
