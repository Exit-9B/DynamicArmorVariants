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

	void RegisterArmorVariant(std::string_view a_name, ArmorVariant&& a_variant);
	void SetCondition(std::string_view a_state, std::shared_ptr<RE::TESCondition> a_condition);

	void VisitArmorAddons(
		RE::Actor* a_actor,
		RE::TESObjectARMA* a_armorAddon,
		std::function<void(RE::TESObjectARMA*)> a_visit) const;

	auto GetBipedObjectSlots(RE::Actor* a_actor, RE::TESObjectARMO* a_armor) const
		-> BipedObjectSlot;

	auto GetVariants(RE::TESObjectARMO* a_armor) const -> std::vector<std::string>;

	auto GetEquippedArmorsWithVariants(RE::Actor* a_actor) -> std::vector<RE::TESObjectARMO*>;

	auto GetDisplayName(const std::string& a_variant) const -> std::string;

	void ApplyVariant(RE::Actor* a_actor, const std::string& a_variant);

	void ApplyVariant(
		RE::Actor* a_actor,
		const RE::TESObjectARMO* a_armor,
		const std::string& a_variant);

	void ResetVariant(RE::Actor* a_actor, const RE::TESObjectARMO* a_armor);

	void ResetAllVariants(RE::Actor* a_actor);

	void ResetAllVariants(RE::FormID a_formID);

	void Serialize(SKSE::SerializationInterface* a_skse);

	void Deserialize(SKSE::SerializationInterface* a_skse);

	void Revert();

private:
	static constexpr std::uint32_t SerializationVersion = 1;
	static constexpr std::uint32_t SerializationType = 'DAVO';

	DynamicArmorManager() = default;

	auto IsUsingVariant(RE::Actor* a_actor, std::string a_state) const -> bool;

	tsl::ordered_map<std::string, ArmorVariant> _variants;

	std::unordered_map<std::string, std::shared_ptr<RE::TESCondition>> _conditions;
	std::unordered_map<RE::FormID, std::unordered_set<std::string>> _variantOverrides;
};
