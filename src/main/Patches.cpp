#include "Patches.h"
#include "RE/Offset.Ext.h"

void Patches::WriteInitWornPatch(InitWornArmorFunc* a_func)
{
	REL::Relocation<std::uintptr_t> hook{ RE::Offset::TESNPC::InitWornForm, 0x2F0 };

	// Expected size: 0x12
	struct Patch : Xbyak::CodeGenerator
	{
		Patch(std::uintptr_t a_funcAddr)
		{
			mov(rdx, r13);
			mov(rcx, rbp);
			mov(rax, a_funcAddr);
			call(rax);
		}
	};

	Patch patch{ reinterpret_cast<std::uintptr_t>(a_func) };
	patch.ready();

	if (patch.getSize() > 0x17) {
		util::report_and_fail("Patch was too large, failed to install"sv);
	}

	REL::safe_fill(hook.address(), REL::NOP, 0x17);
	REL::safe_write(hook.address(), patch.getCode(), patch.getSize());
}

void Patches::WriteGetWornMaskPatch(GetWornMaskFunc* a_func)
{
	REL::Relocation<std::uintptr_t> hook{ RE::Offset::InventoryChanges::GetWornMask };

	// Expected size: 0x15
	struct Patch : Xbyak::CodeGenerator
	{
		Patch(std::uintptr_t a_funcAddr)
		{
			sub(rsp, 0x8);
			mov(rax, a_funcAddr);
			call(rax);
			add(rsp, 0x8);
			ret();
		}
	};

	Patch patch{ reinterpret_cast<std::uintptr_t>(a_func) };
	patch.ready();

	if (patch.getSize() > 0x40) {
		util::report_and_fail("Patch was too large, failed to install"sv);
	}

	REL::safe_fill(hook.address(), REL::INT3, 0x40);
	REL::safe_write(hook.address(), patch.getCode(), patch.getSize());
}
