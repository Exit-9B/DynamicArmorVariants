#include "GetWornMaskVisitor.h"
#include "DynamicArmorManager.h"
#include "RE/Offset.Ext.h"

std::uint32_t GetWornMaskVisitor::Visit(RE::InventoryEntryData* a_entryData)
{
	using func_t = decltype(&GetWornMaskVisitor::Visit);
	static REL::Relocation<func_t> func{ RE::Offset::InventoryUtils::GetWornMaskVisitor::Visit };

	RE::TESObject* object = a_entryData->object;
	auto armor = object ? object->As<RE::TESObjectARMO>() : nullptr;

	if (armor) {
		auto slot = DynamicArmorManager::GetSingleton()->GetBipedObjectSlots(actor, armor);
		slotMask |= slot;
		return 1;
	}
	else {
		return func(this, a_entryData);
	}
}
