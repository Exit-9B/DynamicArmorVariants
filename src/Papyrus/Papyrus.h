#pragma once

#include "DynamicArmor.h"

namespace Papyrus
{
	bool RegisterFuncs(RE::BSScript::IVirtualMachine* a_vm)
	{
		DynamicArmor::RegisterFuncs(a_vm);
		return true;
	}
}
