#pragma once

namespace RE
{
	struct TESActorLocationChangeEvent
	{
		RE::Actor*       actor;   // 00
		RE::BGSLocation* oldLoc;  // 08
		RE::BGSLocation* newLoc;  // 10
	};
}
