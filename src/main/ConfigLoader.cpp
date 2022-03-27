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
	fileStream >> root;

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

			RefMap refMap;
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

void ConfigLoader::LoadVariant(const std::string& a_name, Json::Value a_variant)
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
	const std::string& a_variant,
	Json::Value a_conditions,
	const RefMap& a_refs)
{
	if (!a_conditions.isArray())
		return;

	auto condition = std::make_shared<RE::TESCondition>();
	RE::TESConditionItem** head = std::addressof(condition->head);

	for (auto& item : a_conditions) {
		auto text = item.asString();

		if (text.empty())
			continue;

		if (auto conditionItem = ParseCondition(text, a_refs)) {
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

		a_formMap.emplace(addon, std::vector<RE::TESObjectARMA*>());

		Json::Value addons = a_replaceByForm[formIdentifier];
		if (addons.isString()) {
			if (auto variantAddon = FormUtil::LookupByIdentifier<RE::TESObjectARMA>(
					addons.asString())) {

				a_formMap[addon].push_back(variantAddon);
			}
		}
		else if (addons.isArray()) {
			for (auto& identifier : addons) {
				if (auto variantAddon = FormUtil::LookupByIdentifier<RE::TESObjectARMA>(
						identifier.asString())) {

					a_formMap[addon].push_back(variantAddon);
				}
			}
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

auto ConfigLoader::ParseCondition(const std::string& a_text, const RefMap& a_refs)
	-> RE::TESConditionItem*
{
	static std::regex re{
		R"((\w+)\s+((\w+)(\s+(\w+))?\s*)?(==|!=|>|>=|<|<=)\s*(\w+)(\s+(AND|OR))?)"
	};

	std::cmatch m;
	if (!std::regex_match(a_text.data(), m, re)) {
		logger::error("Could not parse condition: {}"sv, a_text);
		return nullptr;
	}

	RE::CONDITION_ITEM_DATA data;
	auto& mFunction = m[1];
	auto& mParam1 = m[3];
	auto& mParam2 = m[5];
	auto& mOperator = m[6];
	auto& mComparand = m[7];
	auto& mConnective = m[9];

	auto function = RE::SCRIPT_FUNCTION::LocateScriptCommand(mFunction.str().data());

	if (!function || !function->conditionFunction) {
		logger::error("Did not find condition function: {}"sv, mFunction.str());
		return nullptr;
	}

	auto functionIndex = util::to_underlying(function->output) - 0x1000;
	data.functionData.function = static_cast<RE::FUNCTION_DATA::FunctionID>(functionIndex);

	if (mParam1.matched) {
		auto param = util::str_toupper(mParam1.str());
		if (auto it = a_refs.find(param); it != a_refs.end()) {
			data.functionData.params[0] = it->second;
		}
		else if (auto form = RE::TESForm::LookupByEditorID(param)) {
			data.functionData.params[0] = form;
		}
	}

	if (mParam2.matched) {
		auto param = util::str_toupper(mParam2.str());
		if (auto it = a_refs.find(param); it != a_refs.end()) {
			data.functionData.params[1] = it->second;
		}
		else if (auto form = RE::TESForm::LookupByEditorID(param)) {
			data.functionData.params[1] = form;
		}
	}

	if (mOperator.matched) {
		auto op = mOperator.str();
		if (op == "=="s) {
			data.flags.opCode = RE::CONDITION_ITEM_DATA::OpCode::kEqualTo;
		}
		else if (op == "!="s) {
			data.flags.opCode = RE::CONDITION_ITEM_DATA::OpCode::kNotEqualTo;
		}
		else if (op == ">"s) {
			data.flags.opCode = RE::CONDITION_ITEM_DATA::OpCode::kGreaterThan;
		}
		else if (op == ">="s) {
			data.flags.opCode = RE::CONDITION_ITEM_DATA::OpCode::kGreaterThanOrEqualTo;
		}
		else if (op == "<"s) {
			data.flags.opCode = RE::CONDITION_ITEM_DATA::OpCode::kLessThan;
		}
		else if (op == "<="s) {
			data.flags.opCode = RE::CONDITION_ITEM_DATA::OpCode::kLessThanOrEqualTo;
		}
	}
	else {
		data.flags.opCode = RE::CONDITION_ITEM_DATA::OpCode::kNotEqualTo;
	}

	if (mComparand.matched) {
		auto comparand = mComparand.str();
		if (auto global = RE::TESForm::LookupByEditorID<RE::TESGlobal>(comparand)) {
			data.comparisonValue.g = global;
		}
		else {
			data.comparisonValue.f = std::stof(comparand);
		}
	}
	else {
		data.comparisonValue.f = 0.f;
	}

	if (mConnective.matched) {
		auto connective = mConnective.str();
		if (connective == "OR"s) {
			data.flags.isOR = true;
		}
	}

	auto conditionItem = new RE::TESConditionItem();
	conditionItem->data = data;
	return conditionItem;
}
