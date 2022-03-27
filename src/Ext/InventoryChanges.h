#pragma once

#include "IItemChangeVisitor.h"

namespace Ext
{
	namespace InventoryChanges
	{
		void Accept(RE::InventoryChanges* a_inventoryChanges, IItemChangeVisitor* a_visitor);
	}
}
