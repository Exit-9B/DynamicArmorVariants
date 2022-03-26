#pragma once

namespace FormUtil
{
	template <typename T = RE::TESForm>
	inline auto LookupByIdentifier(const std::string& a_identifier) -> T*
	{
		std::istringstream ss{ a_identifier };
		std::string plugin, id;

		std::getline(ss, plugin, '|');
		std::getline(ss, id);
		RE::FormID relativeID;
		std::istringstream{ id } >> std::hex >> relativeID;

		const auto dataHandler = RE::TESDataHandler::GetSingleton();
		auto form = dataHandler ? dataHandler->LookupForm(relativeID, plugin) : nullptr;

		return form ? form->As<T>() : nullptr;
	}
}
