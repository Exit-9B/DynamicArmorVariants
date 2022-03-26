#include "InventoryChanges.h"
#include "RE/Offset.Ext.h"

namespace Ext
{
	void InventoryChanges::Accept(
		RE::InventoryChanges* a_inventoryChanges,
		IItemChangeVisitor* a_visitor)
	{
		using func_t = decltype(Accept);
		static REL::Relocation<func_t> func{ RE::Offset::InventoryChanges::Accept };
		return func(a_inventoryChanges, a_visitor);
	}
}
