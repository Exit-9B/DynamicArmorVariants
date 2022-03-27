#pragma once

namespace Ext
{
	// Clone of InventoryChanges::IItemChangeVisitor
	class IItemChangeVisitor
	{
	public:
		inline static constexpr auto RTTI = RE::RTTI_InventoryChanges__IItemChangeVisitor;

		virtual ~IItemChangeVisitor() = default;  // 00

		// add
		virtual std::uint32_t Visit(RE::InventoryEntryData* a_entryData) = 0;  // 01

		virtual bool Unk_02(RE::FormType)  // 02
		{
			return true;
		}

		virtual void Unk_03(RE::InventoryEntryData* a_entryData, std::int64_t, bool& a_visited)  // 03
		{
			a_visited = true;
			Visit(a_entryData);
		}
	};
	static_assert(sizeof(IItemChangeVisitor) == 0x8);
}
