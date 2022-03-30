#pragma once

namespace RE
{
	namespace Offset
	{
		namespace Actor
		{
			// SkyrimSE 1.6.353: 0x2A69D0
			inline constexpr auto Update3D = MAKE_OFFSET(19743, 0x2A5AC0);
		}

		namespace InventoryChanges
		{
			// SkyrimSE 1.6.353: 0x1E4AA0
			inline constexpr auto GetWornMask = MAKE_OFFSET(16044, 0x1E9BE0);
			// SkyrimSE 1.6.353: 0x1F08A0
			inline constexpr auto Accept = MAKE_OFFSET(16096, 0x1F5D90);
		}

		namespace InventoryUtils
		{
			namespace GetWornMaskVisitor
			{
				// SkyrimSE 1.6.353: 0x1FB510
				inline constexpr auto Visit = MAKE_OFFSET(16233, 0x2009A0);
			}
		}

		namespace TESNPC
		{
			// SkyrimSE 1.6.353: 0x37B430
			inline constexpr auto InitWornForm = MAKE_OFFSET(24736, 0x373CB0);
		}

		namespace TESObjectARMA
		{
			// SkyrimSE 1.6.353: 0x235A00
			inline constexpr auto HasRace = MAKE_OFFSET(17757, 0x2380A0);
			// SkyrimSE 1.6.353: 0x235D10
			inline constexpr auto InitWornArmorAddon = MAKE_OFFSET(17759, 0x2383A0);
		}
	}
}
