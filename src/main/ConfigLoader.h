#pragma once

#include "ArmorVariant.h"
#include "Json.h"

class ConfigLoader
{
public:
	using RefMap = std::unordered_map<std::string, void*>;

	ConfigLoader() = delete;

	static void LoadConfigs();

private:
	static void LoadConfig(fs::path a_path);

	static void LoadVariant(std::string_view a_name, Json::Value a_variant);

	static void LoadConditions(
		std::string_view a_variant,
		Json::Value a_conditions,
		const RefMap& a_refs);

	static void LoadFormMap(Json::Value a_replaceByForm, ArmorVariant::FormMap& a_formMap);

	static void LoadSlotMap(Json::Value a_replaceBySlot, ArmorVariant::SlotMap& a_slotMap);

	static auto ParseCondition(std::string_view a_text, const RefMap& a_refs)
		-> RE::TESConditionItem*;
};
