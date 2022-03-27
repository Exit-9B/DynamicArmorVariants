#pragma once

#include "ArmorVariant.h"

class DynamicArmorManager
{
public:
	~DynamicArmorManager() = default;
	DynamicArmorManager(const DynamicArmorManager&) = delete;
	DynamicArmorManager(DynamicArmorManager&&) = delete;
	DynamicArmorManager& operator=(const DynamicArmorManager&) = delete;
	DynamicArmorManager& operator=(DynamicArmorManager&&) = delete;

	static auto GetSingleton() -> DynamicArmorManager*;

	void RegisterArmorVariant(const std::string& a_name, ArmorVariant&& a_variant);
	void SetCondition(const std::string& a_state, std::shared_ptr<RE::TESCondition> a_condition);

	void VisitArmorAddons(
		RE::Actor* a_actor,
		RE::TESObjectARMA* a_armorAddon,
		std::function<void(RE::TESObjectARMA*)> a_visit) const;

	auto GetBipedObjectSlots(RE::Actor* a_actor, RE::TESObjectARMO* a_armor) const
		-> BipedObjectSlot;

	auto GetVariants(RE::TESObjectARMO* a_armor) const -> std::vector<std::string>;

	auto GetDisplayName(const std::string& a_variant) const -> const std::string&;

	void ApplyVariant(RE::Actor* a_actor, const std::string& a_variant);

	void ApplyVariant(
		RE::Actor* a_actor,
		const RE::TESObjectARMO* a_armor,
		const std::string& a_variant);

	void ResetVariant(RE::Actor* a_actor, const RE::TESObjectARMO* a_armor);

	auto GetEquippedArmorsWithVariants(RE::Actor* a_actor) -> std::vector<RE::TESObjectARMO*>;

private:
	DynamicArmorManager() = default;

	auto IsUsingVariant(RE::Actor* a_actor, std::string a_state) const -> bool;

	tsl::ordered_map<std::string, ArmorVariant> _variants;

	std::unordered_map<std::string, std::shared_ptr<RE::TESCondition>> _conditions;
	std::unordered_map<RE::Actor*, tsl::ordered_set<std::string>> _variantOverrides;
};
