#pragma once

namespace Papyrus
{
	namespace DynamicArmor
	{
		auto GetAPIVersion(RE::StaticFunctionTag*) -> std::int32_t;

		auto GetVariants(RE::StaticFunctionTag*, RE::TESObjectARMO* a_armor)
			-> std::vector<std::string>;

		auto GetDisplayName(RE::StaticFunctionTag*, std::string a_variant) -> std::string;

		void ApplyVariant(RE::StaticFunctionTag*, RE::Actor* a_actor, std::string a_variant);

		void ResetVariant(RE::StaticFunctionTag*, RE::Actor* a_actor, RE::TESObjectARMO* a_armor);

		auto GetEquippedArmorsWithVariants(RE::StaticFunctionTag*, RE::Actor* a_actor)
			-> std::vector<RE::TESObjectARMO*>;

		bool RegisterFuncs(RE::BSScript::IVirtualMachine* a_vm);
	}
}
