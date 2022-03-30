#include "ConfigLoader.h"
#include "DynamicArmorManager.h"
#include "FormUtil.h"

void ConfigLoader::LoadConfigs()
{
	const auto dataHandler = RE::TESDataHandler::GetSingleton();
	if (!dataHandler)
		return;

	for (auto& file : dataHandler->files) {
		if (!file)
			continue;

		auto fileName = fs::path(file->fileName);
		fileName.replace_extension("json"sv);
		auto directory = fs::path("SKSE/Plugins/DynamicArmorVariants");
		auto dynamicArmorFile = directory / fileName;

		LoadConfig(dynamicArmorFile);
	}
}

void ConfigLoader::LoadConfig(fs::path a_path)
{
	RE::BSResourceNiBinaryStream fileStream{ a_path.string() };

	if (!fileStream.good())
		return;

	Json::Value root;
	try {
		fileStream >> root;
	}
	catch (...) {
		logger::error("Parse errors in file: {}"sv, a_path.filename().string());
	}

	if (!root.isObject())
		return;

	Json::Value variants = root["variants"];
	if (variants.isArray()) {
		for (auto& variant : variants) {
			auto name = variant["name"].asString();
			LoadVariant(name, variant);
		}
	}

	Json::Value states = root["states"];
	if (states.isArray()) {
		for (auto& state : states) {
			auto variant = state["variant"].asString();

			ConditionParser::RefMap refMap;
			refMap["PLAYER"s] = RE::PlayerCharacter::GetSingleton();

			Json::Value refs = state["refs"];

			if (refs.isObject()) {
				for (auto& name : refs.getMemberNames()) {
					auto identifier = refs[name].asString();

					if (auto form = FormUtil::LookupByIdentifier(identifier)) {
						auto name_upper = util::str_toupper(name);
						refMap[name_upper] = form;
					}
				}
			}

			LoadConditions(variant, state["conditions"], refMap);
		}
	}
}

void ConfigLoader::LoadVariant(std::string_view a_name, Json::Value a_variant)
{
	if (!a_variant.isObject())
		return;

	ArmorVariant armorVariant{};

	armorVariant.Linked = a_variant["linkTo"].asString();
	armorVariant.DisplayName = a_variant["displayName"].asString();

	auto& showHead = a_variant["showHead"];
	if (showHead.isBool()) {
		armorVariant.ShowHead = showHead.asBool();
	}

	auto& showHair = a_variant["showHair"];
	if (showHair.isBool()) {
		armorVariant.ShowHair = showHair.asBool();
	}

	LoadFormMap(a_variant["replaceByForm"], armorVariant.ReplaceByForm);
	LoadSlotMap(a_variant["replaceBySlot"], armorVariant.ReplaceBySlot);

	DynamicArmorManager::GetSingleton()->RegisterArmorVariant(a_name, std::move(armorVariant));
}

void ConfigLoader::LoadConditions(
	std::string_view a_variant,
	Json::Value a_conditions,
	const ConditionParser::RefMap& a_refs)
{
	if (!a_conditions.isArray())
		return;

	auto condition = std::make_shared<RE::TESCondition>();
	RE::TESConditionItem** head = std::addressof(condition->head);

	for (auto& item : a_conditions) {
		auto text = item.asString();

		if (text.empty())
			continue;

		if (auto conditionItem = ConditionParser::Parse(text, a_refs)) {
			*head = conditionItem;
			head = std::addressof(conditionItem->next);
		}
		else {
			logger::info("Aborting condition parsing"sv);
			return;
		}
	}

	DynamicArmorManager::GetSingleton()->SetCondition(a_variant, condition);
}

void ConfigLoader::LoadFormMap(Json::Value a_replaceByForm, ArmorVariant::FormMap& a_formMap)
{
	if (!a_replaceByForm.isObject())
		return;

	for (auto& formIdentifier : a_replaceByForm.getMemberNames()) {

		auto addon = FormUtil::LookupByIdentifier<RE::TESObjectARMA>(formIdentifier);
		if (!addon)
			continue;

		std::vector<RE::TESObjectARMA*> replacementForms;

		Json::Value addons = a_replaceByForm[formIdentifier];
		if (addons.isString()) {
			if (auto variantAddon = FormUtil::LookupByIdentifier<RE::TESObjectARMA>(
					addons.asString())) {

				replacementForms.push_back(variantAddon);
			}
			else {
				logger::warn("Could not resolve form: {}"sv, addons.asString());
			}
		}
		else if (addons.isArray()) {
			for (auto& identifier : addons) {
				if (auto variantAddon = FormUtil::LookupByIdentifier<RE::TESObjectARMA>(
						identifier.asString())) {

					replacementForms.push_back(variantAddon);
				}
				else {
					logger::warn("Could not resolve form: {}"sv, identifier.asString());
				}
			}
		}

		if (!replacementForms.empty()) {
			a_formMap.emplace(addon, std::move(replacementForms));
		}
		else {
			logger::warn("Replacements for {} are not valid, ignoring"sv, formIdentifier);
		}
	}
}

void ConfigLoader::LoadSlotMap(Json::Value a_replaceBySlot, ArmorVariant::SlotMap& a_slotMap)
{
	if (!a_replaceBySlot.isObject())
		return;

	for (auto& slotIndex : a_replaceBySlot.getMemberNames()) {

		auto bipedObject = static_cast<BipedObject>(std::stoi(slotIndex) - 30);

		if (bipedObject > 31)
			continue;

		a_slotMap.emplace(bipedObject, std::vector<RE::TESObjectARMA*>());

		Json::Value addons = a_replaceBySlot[slotIndex];
		if (addons.isString()) {
			if (auto variantAddon = FormUtil::LookupByIdentifier<RE::TESObjectARMA>(
					addons.asString())) {

				a_slotMap[bipedObject].push_back(variantAddon);
			}
		}
		else if (addons.isArray()) {
			for (auto& identifier : addons) {
				if (auto variantAddon = FormUtil::LookupByIdentifier<RE::TESObjectARMA>(
						identifier.asString())) {

					a_slotMap[bipedObject].push_back(variantAddon);
				}
			}
		}
	}
}
