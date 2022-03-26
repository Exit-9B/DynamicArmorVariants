#pragma once

#include "ArmorVariant.h"

class Condition;
class DynamicArmorManager
{
public:
	~DynamicArmorManager() = default;
	DynamicArmorManager(const DynamicArmorManager&) = delete;
	DynamicArmorManager(DynamicArmorManager&&) = delete;
	DynamicArmorManager& operator=(const DynamicArmorManager&) = delete;
	DynamicArmorManager& operator=(DynamicArmorManager&&) = delete;

	static auto GetSingleton() -> DynamicArmorManager*;

	void RegisterArmorVariant(ArmorVariant&& a_variant);
	void SetCondition(const std::string& a_state, std::shared_ptr<RE::TESCondition> a_condition);

	void VisitArmorAddons(
		RE::Actor* a_actor,
		RE::TESObjectARMA* a_armorAddon,
		std::function<void(RE::TESObjectARMA*)> a_visit);

	auto GetBipedObjectSlots(RE::Actor* a_actor, RE::TESObjectARMO* a_armor) -> BipedObjectSlot;

private:
	DynamicArmorManager() = default;

	auto IsUsingVariant(RE::Actor* a_actor, std::string a_state) -> bool;

	std::vector<ArmorVariant> _variants;

	std::unordered_map<std::string, std::shared_ptr<RE::TESCondition>> _conditions;
	std::unordered_map<RE::Actor*, tsl::ordered_set<std::string>> _stateOverrides;
};
