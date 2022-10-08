cmake_minimum_required(VERSION 3.24)

project(
	DynamicArmorVariants
	VERSION 1.0.5
	LANGUAGES CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

list(APPEND CMAKE_IGNORE_PATH "${PROJECT_BINARY_DIR}")
list(APPEND CMAKE_MODULE_PATH
	"${PROJECT_SOURCE_DIR}/tools/SKSE-CMakeModules/Modules"
	"${PROJECT_SOURCE_DIR}/tools/BethesdaCMakeModules/Modules"
)

include(SKSEPlugin)
include(Papyrus)

set(SKSE_SUPPORT_VR ON)
set(SKSE_USE_XBYAK ON)

SKSEPlugin_Add(
	${PROJECT_NAME}
	SOURCE_DIR src
	SOURCES
		.clang-format
		.editorconfig
		README.md
		vcpkg.json
	PRECOMPILE_HEADERS
		src/PCH/PCH.h
)

find_path(SRELL_INCLUDE_DIRS "srell.hpp")
find_package(jsoncpp CONFIG REQUIRED)
find_package(tsl-ordered-map CONFIG REQUIRED)

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
		${SRELL_INCLUDE_DIRS}
)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		tsl::ordered_map
		jsoncpp_static
)

set(PAPYRUS_IMPORTS
	"${PROJECT_SOURCE_DIR}/scripts"
	"$ENV{UIExtensionsPath}/scripts/source"
	"$ENV{MCMPath}/Source/Scripts"
	"$ENV{SKSE64Path}/Scripts/Source"
)

Papyrus_Add(
	"DynamicArmorSDK"
	GAME ${SkyrimSE_PATH}
	IMPORTS ${PAPYRUS_IMPORTS}
	SOURCES
		"${PROJECT_SOURCE_DIR}/scripts/DynamicArmor.psc"
	OPTIMIZE
	ANONYMIZE
	COMPONENT Data
)

Papyrus_Add(
	"DynamicArmorMenu"
	GAME ${SkyrimSE_PATH}
	IMPORTS ${PAPYRUS_IMPORTS}
	SOURCES
		"${PROJECT_SOURCE_DIR}/scripts/DynamicArmor_MCM.psc"
		"${PROJECT_SOURCE_DIR}/scripts/DynamicArmor_Menu.psc"
		"${PROJECT_SOURCE_DIR}/scripts/DynamicArmor_MenuPower.psc"
	OPTIMIZE
	ANONYMIZE
	COMPONENT UIExtensions_Menu
)

include(install_files.cmake)
