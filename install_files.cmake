install(
	FILES
		"${PROJECT_SOURCE_DIR}/data/DynamicArmorMenu.esp"
	DESTINATION "."
	COMPONENT UIExtensions_Menu
)

install(
	FILES
		"${PROJECT_SOURCE_DIR}/data/MCM/Config/DynamicArmorMenu/config.json"
		"${PROJECT_SOURCE_DIR}/data/MCM/Config/DynamicArmorMenu/keybinds.json"
		"${PROJECT_SOURCE_DIR}/data/MCM/Config/DynamicArmorMenu/settings.ini"
	DESTINATION "MCM/Config/DynamicArmorMenu"
	COMPONENT UIExtensions_Menu
)

install(
	FILES
		"${PROJECT_SOURCE_DIR}/data/Interface/Translations/DynamicArmorMenu_ENGLISH.txt"
	DESTINATION "Interface/Translations"
	COMPONENT UIExtensions_Menu
)

install(
	FILES
		"${PROJECT_SOURCE_DIR}/data/DAV_HiddenEquipment.esp"
	DESTINATION "."
	COMPONENT HiddenEquipment
)

install(
	FILES
		"${PROJECT_SOURCE_DIR}/data/SKSE/Plugins/DynamicArmorVariants/DAV_HiddenEquipment.json"
	DESTINATION "SKSE/Plugins/DynamicArmorVariants"
	COMPONENT HiddenEquipment
)

install(
	FILES
		"${PROJECT_SOURCE_DIR}/data/Interface/Translations/DAV_HiddenEquipment_ENGLISH.txt"
	DESTINATION "Interface/Translations"
	COMPONENT HiddenEquipment
)

install(
	FILES
		"${PROJECT_SOURCE_DIR}/data/fomod/info.xml"
		"${PROJECT_SOURCE_DIR}/data/fomod/ModuleConfig.xml"
	DESTINATION "fomod"
	COMPONENT Fomod
	EXCLUDE_FROM_ALL
)

install(
	FILES
		"${PROJECT_SOURCE_DIR}/data/fomod/images/skyrim_se.jpg"
		"${PROJECT_SOURCE_DIR}/data/fomod/images/skyrim_vr.jpg"
		"${PROJECT_SOURCE_DIR}/data/fomod/images/uiextensions.jpg"
	DESTINATION "fomod/images"
	COMPONENT Fomod
	EXCLUDE_FROM_ALL
)
