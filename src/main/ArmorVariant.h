#pragma once

struct ArmorVariant
{
	using AddonList = std::vector<RE::TESObjectARMA*>;
	using FormMap = std::unordered_map<const RE::TESObjectARMA*, AddonList>;
	using SlotMap = std::map<BipedObject, AddonList>;

	ArmorVariant() = default;

	auto HasSlotOverrides() const -> bool { return ShowHead || ShowHair; }

	auto GetAddonList(const RE::TESObjectARMA* a_armorAddon) const -> const AddonList*;
	auto WouldReplace(const RE::TESObjectARMA* a_armorAddon) const -> bool;
	auto WouldReplaceAny(const RE::TESObjectARMO* a_armor) const -> bool;

	std::string Linked;
	std::string DisplayName;
	bool ShowHead;
	bool ShowHair;
	FormMap ReplaceByForm;
	SlotMap ReplaceBySlot;
};
