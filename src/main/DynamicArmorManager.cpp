#include "DynamicArmorManager.h"

auto DynamicArmorManager::GetSingleton() -> DynamicArmorManager*
{
	static DynamicArmorManager singleton{};
	return std::addressof(singleton);
}

void DynamicArmorManager::RegisterArmorVariant(ArmorVariant&& a_variant)
{
	_variants.push_back(std::move(a_variant));
}

void DynamicArmorManager::SetCondition(
	const std::string& a_state,
	std::shared_ptr<RE::TESCondition> a_condition)
{
	_conditions.insert_or_assign(a_state, a_condition);
}

void DynamicArmorManager::VisitArmorAddons(
	RE::Actor* a_actor,
	RE::TESObjectARMA* a_armorAddon,
	std::function<void(RE::TESObjectARMA*)> a_visit)
{
	std::unordered_map<std::string, ArmorVariant::AddonList*> addonLists;
	std::string variantState;

	for (auto& variant : _variants) {

		auto addonList = variant.GetAddonList(a_armorAddon);
		if (!addonList)
			continue;

		if (!variant.Linked.empty()) {
			addonLists.insert_or_assign(variant.Linked, addonList);
		}

		if (IsUsingVariant(a_actor, variant.Name)) {
			variantState = variant.Name;
			addonLists.try_emplace(variant.Name, addonList);
		}
	}

	if (!variantState.empty()) {
		auto& variantAddons = addonLists[variantState];
		for (auto& armorAddon : *variantAddons) {
			a_visit(armorAddon);
		}
	}
	else {
		a_visit(a_armorAddon);
	}
}

auto DynamicArmorManager::GetBipedObjectSlots(RE::Actor* a_actor, RE::TESObjectARMO* a_armor)
	-> BipedObjectSlot
{
	if (!a_armor)
		return BipedObjectSlot::kNone;

	auto slot = a_armor->bipedModelData.bipedObjectSlots;

	auto race = a_actor ? a_actor->GetRace() : nullptr;

	if (!race)
		return slot.get();

	bool showHead = false;
	bool showHair = false;

	for (auto& armorAddon : a_armor->armorAddons) {
		for (auto& variant : _variants) {

			if (!variant.HasSlotOverrides())
				continue;

			if (!variant.WouldReplace(armorAddon))
				continue;

			if (IsUsingVariant(a_actor, variant.Name)) {
				if (variant.ShowHead) {
					showHead = true;
				}
				if (variant.ShowHair) {
					showHair = true;
				}
			}
		}
	}

	auto headSlot = static_cast<BipedObjectSlot>(1 << race->data.headObject.get());
	auto hairSlot = static_cast<BipedObjectSlot>(1 << race->data.hairObject.get());

	if (showHair) {
		slot.reset(headSlot, hairSlot);
	}
	else if (showHead) {
		slot.reset(headSlot);
	}

	return slot.get();
}

auto DynamicArmorManager::IsUsingVariant(RE::Actor* a_actor, std::string a_state) -> bool
{
	if (auto it = _stateOverrides.find(a_actor); it != _stateOverrides.end()) {
		if (it->second.contains(a_state)) {
			return true;
		}
	}

	if (auto it = _conditions.find(a_state); it != _conditions.end()) {
		auto& condition = it->second;
		return condition ? condition->IsTrue(a_actor, a_actor) : false;
	}
	else {
		return false;
	}
}
