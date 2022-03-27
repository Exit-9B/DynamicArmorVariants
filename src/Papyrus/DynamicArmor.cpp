#include "DynamicArmor.h"
#include "main/DynamicArmorManager.h"

#define REGISTER(a_vm, a_function) \
	a_vm->RegisterFunction(#a_function##sv, "DynamicArmor"sv, &a_function)

namespace Papyrus
{
	auto DynamicArmor::GetAPIVersion(RE::StaticFunctionTag*) -> std::int32_t { return 1; }

	auto DynamicArmor::GetVariants(RE::StaticFunctionTag*, RE::TESObjectARMO* a_armor)
		-> std::vector<std::string>
	{
		return DynamicArmorManager::GetSingleton()->GetVariants(a_armor);
	}

	auto DynamicArmor::GetEquippedArmorsWithVariants(RE::StaticFunctionTag*, RE::Actor* a_actor)
		-> std::vector<RE::TESObjectARMO*>
	{
		return DynamicArmorManager::GetSingleton()->GetEquippedArmorsWithVariants(a_actor);
	}

	auto DynamicArmor::GetDisplayName(RE::StaticFunctionTag*, std::string a_variant) -> std::string
	{
		return DynamicArmorManager::GetSingleton()->GetDisplayName(a_variant);
	}

	void DynamicArmor::ApplyVariant(
		RE::StaticFunctionTag*,
		RE::Actor* a_actor,
		std::string a_variant)
	{
		DynamicArmorManager::GetSingleton()->ApplyVariant(a_actor, a_variant);
	}

	void DynamicArmor::ResetVariant(
		RE::StaticFunctionTag*,
		RE::Actor* a_actor,
		RE::TESObjectARMO* a_armor)
	{
		DynamicArmorManager::GetSingleton()->ResetVariant(a_actor, a_armor);
	}

	bool DynamicArmor::RegisterFuncs(RE::BSScript::IVirtualMachine* a_vm)
	{
		REGISTER(a_vm, GetAPIVersion);
		REGISTER(a_vm, GetVariants);
		REGISTER(a_vm, GetDisplayName);
		REGISTER(a_vm, ApplyVariant);
		REGISTER(a_vm, ResetVariant);
		REGISTER(a_vm, GetEquippedArmorsWithVariants);

		return true;
	}
}
