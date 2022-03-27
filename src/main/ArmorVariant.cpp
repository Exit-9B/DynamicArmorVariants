#include "ArmorVariant.h"

auto ArmorVariant::GetAddonList(const RE::TESObjectARMA* a_armorAddon) const -> const AddonList*
{
	if (auto it = ReplaceByForm.find(a_armorAddon); it != ReplaceByForm.end()) {
		return std::addressof(it->second);
	}

	auto slots = a_armorAddon->bipedModelData.bipedObjectSlots;
	for (auto& [bipedObject, addonList] : ReplaceBySlot) {
		auto bipedSlot = static_cast<BipedObjectSlot>(1 << bipedObject);
		if (slots.all(bipedSlot)) {
			// Short-circuit on lowest slot
			return std::addressof(addonList);
		}
	}

	return nullptr;
}

auto ArmorVariant::WouldReplace(const RE::TESObjectARMA* a_armorAddon) const -> bool
{
	return GetAddonList(a_armorAddon) != nullptr;
}

auto ArmorVariant::WouldReplaceAny(const RE::TESObjectARMO* a_armor) const -> bool
{
	for (auto& armorAddon : a_armor->armorAddons) {
		if (WouldReplace(armorAddon)) {
			return true;
		}
	}

	return false;
}
