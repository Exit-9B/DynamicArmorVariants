#pragma once

#pragma warning(disable : 5105)
#pragma warning(push, 0)
#include <tsl/ordered_map.h>
#include <tsl/ordered_set.h>

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

#include <regex>

#ifdef NDEBUG
#include <spdlog/sinks/basic_file_sink.h>
#else
#include <spdlog/sinks/msvc_sink.h>
#endif

#include <xbyak/xbyak.h>
#pragma warning(pop)

using namespace std::literals;

namespace fs = std::filesystem;

namespace logger = SKSE::log;

namespace util
{
	using SKSE::stl::enumeration;
	using SKSE::stl::report_and_fail;
	using SKSE::stl::to_underlying;

	inline std::string str_toupper(std::string s)
	{
		std::transform(
			s.begin(),
			s.end(),
			s.begin(),
			[](unsigned char c)
			{
				return static_cast<char>(std::toupper(c));
			});
		return s;
	}
}

using BipedObject = RE::BIPED_OBJECTS::BIPED_OBJECT;
using BipedObjectSlot = RE::BIPED_MODEL::BipedObjectSlot;

#define DLLEXPORT __declspec(dllexport)

#include "Plugin.h"
