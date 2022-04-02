#include "Serialization.h"

#include "DynamicArmorManager.h"

void Serialization::SaveCallback(SKSE::SerializationInterface* a_skse)
{
	DynamicArmorManager::GetSingleton()->Serialize(a_skse);
}

void Serialization::LoadCallback(SKSE::SerializationInterface* a_skse)
{
	DynamicArmorManager::GetSingleton()->Deserialize(a_skse);
}

void Serialization::RevertCallback([[maybe_unused]] SKSE::SerializationInterface* a_skse)
{
	DynamicArmorManager::GetSingleton()->Revert();
}
