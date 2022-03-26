#include "Actor.h"
#include "RE/Offset.Ext.h"

namespace Ext
{
	bool Actor::Update3D(RE::Actor* a_actor)
	{
		using func_t = decltype(Update3D);
		static REL::Relocation<func_t> func{ RE::Offset::Actor::Update3D };
		return func(a_actor);
	}
}