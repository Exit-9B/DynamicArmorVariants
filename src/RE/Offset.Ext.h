#pragma once

namespace RE
{
	namespace Offset
	{
		namespace Actor
		{
			// SkyrimSE 1.6.353: 0x2A69D0
			inline constexpr REL::ID Update3D(19743);
		}

		namespace InventoryChanges
		{
			// SkyrimSE 1.6.353: 0x1E4AA0
			inline constexpr REL::ID GetWornMask(16044);
			// SkyrimSE 1.6.353: 0x1F08A0
			inline constexpr REL::ID Accept(16096);
		}

		namespace InventoryUtils
		{
			namespace GetWornMaskVisitor
			{
				// SkyrimSE 1.6.353: 0x1FB510
				inline constexpr REL::ID Visit(16233);
			}
		}

		namespace TESNPC
		{
			// SkyrimSE 1.6.353: 0x37B430
			inline constexpr REL::ID InitWornForm(24736);
		}

		namespace TESObjectARMA
		{
			// SkyrimSE 1.6.353: 0x235A00
			inline constexpr REL::ID HasRace(17757);
			// SkyrimSE 1.6.353: 0x235D10
			inline constexpr REL::ID InitWornArmorAddon(17759);
		}
	}
}
