#pragma once

#include "Ext/IItemChangeVisitor.h"

class GetWornMaskVisitor : public Ext::IItemChangeVisitor
{
public:
	GetWornMaskVisitor(RE::Actor* a_actor) : actor{ a_actor } {}

	std::uint32_t Visit(RE::InventoryEntryData* a_entryData) override;

	// members (InventoryUtils::GetWornMaskVisitor)
	util::enumeration<BipedObjectSlot, std::uint32_t> slotMask;
	std::uint32_t pad0C;
	// add
	RE::Actor* actor;
};
static_assert(offsetof(GetWornMaskVisitor, actor) == 0x10);
