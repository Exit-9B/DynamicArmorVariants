#pragma once

#include "Json.h"

class ConfigLoader
{
public:
	ConfigLoader() = delete;

	static void LoadConfigs();

private:
	static void LoadConfig(fs::path a_path);

	static void LoadVariant(const std::string& a_name, Json::Value a_variant);

	static void LoadConditions(
		const std::string& a_variant,
		Json::Value a_conditions,
		const std::unordered_map<std::string, void*>& a_refs);

	static void LoadFormMap(
		Json::Value a_replaceByForm,
		std::unordered_map<RE::TESObjectARMA*, std::vector<RE::TESObjectARMA*>>& a_formMap);

	static void LoadSlotMap(
		Json::Value a_replaceBySlot,
		std::map<BipedObject, std::vector<RE::TESObjectARMA*>>& a_slotMap);

	static auto ParseCondition(
		const std::string& a_text,
		const std::unordered_map<std::string, void*>& a_refs) -> RE::TESConditionItem*;
};
