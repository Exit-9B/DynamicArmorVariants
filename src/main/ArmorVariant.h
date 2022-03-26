#pragma once

struct ArmorVariant
{
	using AddonList = std::vector<RE::TESObjectARMA*>;

	ArmorVariant() = default;

	auto HasSlotOverrides() -> bool { return ShowHead || ShowHair; }

	auto WouldReplace(RE::TESObjectARMA* a_armorAddon) -> bool;
	auto GetAddonList(RE::TESObjectARMA* a_armorAddon) -> AddonList*;

	std::string Name;
	std::string Linked;
	std::string DisplayName;
	bool ShowHead;
	bool ShowHair;
	std::unordered_map<RE::TESObjectARMA*, AddonList> ReplaceByForm;
	std::map<BipedObject, AddonList> ReplaceBySlot;
};
