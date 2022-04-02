#pragma once

namespace Serialization
{
	constexpr std::uint32_t ID = 'AAVF';

	void SaveCallback(SKSE::SerializationInterface* a_skse);

	void LoadCallback(SKSE::SerializationInterface* a_skse);

	void RevertCallback(SKSE::SerializationInterface* a_skse);
}
