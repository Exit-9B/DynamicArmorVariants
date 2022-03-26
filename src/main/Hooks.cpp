#include "Hooks.h"
#include "DynamicArmorManager.h"
#include "Ext/InventoryChanges.h"
#include "Ext/TESObjectARMA.h"
#include "GetWornMaskVisitor.h"
#include "Patches.h"

void Hooks::Install()
{
	Patches::WriteInitWornPatch(&InitWornArmor);
	Patches::WriteGetWornMaskPatch(&GetWornMask);
}

void Hooks::InitWornArmor(
	RE::TESObjectARMO* a_armor,
	RE::Actor* a_actor,
	RE::BSTSmartPointer<RE::BipedAnim>* a_biped)
{
	auto race = a_actor->GetRace();
	auto sex = a_actor->GetActorBase()->GetSex();

	for (auto& armorAddon : a_armor->armorAddons) {
		if (Ext::TESObjectARMA::HasRace(armorAddon, race)) {

			auto visitor = std::bind(
				Ext::TESObjectARMA::InitWornArmorAddon,
				std::placeholders::_1,
				a_armor,
				a_biped,
				sex);

			DynamicArmorManager::GetSingleton()->VisitArmorAddons(a_actor, armorAddon, visitor);
		}
	}
}

auto Hooks::GetWornMask(RE::InventoryChanges* a_inventoryChanges) -> BipedObjectSlot
{
	auto owner = a_inventoryChanges->owner;
	auto actor = owner->As<RE::Actor>();

	GetWornMaskVisitor visitor{ actor };
	Ext::InventoryChanges::Accept(a_inventoryChanges, std::addressof(visitor));
	return visitor.slotMask.get();
}
