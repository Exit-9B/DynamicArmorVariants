#include "ArmorVariant.h"

auto ArmorVariant::WouldReplace(RE::TESObjectARMA* a_armorAddon) -> bool
{
	return GetAddonList(a_armorAddon) != nullptr;
}

auto ArmorVariant::GetAddonList(RE::TESObjectARMA* a_armorAddon) -> AddonList*
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
