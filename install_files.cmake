install(
	FILES
		"$<TARGET_FILE:${PROJECT_NAME}>"
		"$<TARGET_PDB_FILE:${PROJECT_NAME}>"
	DESTINATION "SKSE/Plugins"
	COMPONENT SKSEPlugin
)

install(
	FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/scripts/DynamicArmor.psc"
	DESTINATION "Source/Scripts"
	COMPONENT Data
)

install(
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/Scripts/DynamicArmor.pex"
	DESTINATION "Scripts"
	COMPONENT Data
)

install(
	FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/scripts/DynamicArmor_MCM.psc"
		"${CMAKE_CURRENT_SOURCE_DIR}/scripts/DynamicArmor_Menu.psc"
		"${CMAKE_CURRENT_SOURCE_DIR}/scripts/DynamicArmor_MenuPower.psc"
	DESTINATION "Source/Scripts"
	COMPONENT UIExtensions_Menu
)

install(
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/Scripts/DynamicArmor_MCM.pex"
		"${CMAKE_CURRENT_BINARY_DIR}/Scripts/DynamicArmor_Menu.pex"
		"${CMAKE_CURRENT_BINARY_DIR}/Scripts/DynamicArmor_MenuPower.pex"
	DESTINATION "Scripts"
	COMPONENT UIExtensions_Menu
)

install(
	FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/data/DynamicArmorMenu.esp"
	DESTINATION "."
	COMPONENT UIExtensions_Menu
)

install(
	FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/data/MCM/Config/DynamicArmorMenu/config.json"
		"${CMAKE_CURRENT_SOURCE_DIR}/data/MCM/Config/DynamicArmorMenu/keybinds.json"
		"${CMAKE_CURRENT_SOURCE_DIR}/data/MCM/Config/DynamicArmorMenu/settings.ini"
	DESTINATION "MCM/Config/DynamicArmorMenu"
	COMPONENT UIExtensions_Menu
)

install(
	FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/data/Interface/Translations/DynamicArmorMenu_ENGLISH.txt"
	DESTINATION "Interface/Translations"
	COMPONENT UIExtensions_Menu
)

install(
	FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/data/DAV_HiddenEquipment.esp"
	DESTINATION "."
	COMPONENT HiddenEquipment
)

install(
	FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/data/SKSE/Plugins/DynamicArmorVariants/DAV_HiddenEquipment.json"
	DESTINATION "SKSE/Plugins/DynamicArmorVariants"
	COMPONENT HiddenEquipment
)

install(
	FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/data/Interface/Translations/DAV_HiddenEquipment_ENGLISH.txt"
	DESTINATION "Interface/Translations"
	COMPONENT HiddenEquipment
)

install(
	FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/data/fomod/info.xml"
		"${CMAKE_CURRENT_SOURCE_DIR}/data/fomod/ModuleConfig.xml"
	DESTINATION "fomod"
	COMPONENT Fomod
	EXCLUDE_FROM_ALL
)

install(
	FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/data/fomod/images/skyrim_se.jpg"
		"${CMAKE_CURRENT_SOURCE_DIR}/data/fomod/images/skyrim_vr.jpg"
		"${CMAKE_CURRENT_SOURCE_DIR}/data/fomod/images/uiextensions.jpg"
	DESTINATION "fomod/images"
	COMPONENT Fomod
	EXCLUDE_FROM_ALL
)
