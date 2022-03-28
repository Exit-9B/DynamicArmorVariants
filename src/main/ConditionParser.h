#pragma once

class ConditionParser
{
public:
	using RefMap = std::unordered_map<std::string, RE::TESForm*>;

	ConditionParser() = delete;

	static auto Parse(std::string_view a_text, const RefMap& a_refs) -> RE::TESConditionItem*;

private:
	union ConditionParam
	{
		char c;
		std::int32_t i;
		float f;
		RE::TESForm* form;
	};

	static auto ParseParam(
		const std::string& a_text,
		RE::SCRIPT_PARAM_TYPE a_type,
		const RefMap& a_refs) -> ConditionParam;

	template <typename T = RE::TESForm>
	static auto LookupForm(const std::string& a_text, const RefMap& a_refs) -> T*
	{
		if (auto it = a_refs.find(a_text); it != a_refs.end()) {
			return it->second->As<T>();
		}
		else if (auto form = RE::TESForm::LookupByEditorID(a_text)) {
			return form->As<T>();
		}

		return nullptr;
	}
};
