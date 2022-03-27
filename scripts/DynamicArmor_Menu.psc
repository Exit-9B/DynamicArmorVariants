Scriptname DynamicArmor_Menu Hidden

Function OpenMenu(Actor akActor) global
	Armor[] wornArmors = DynamicArmor.GetEquippedArmorsWithVariants(akActor)
	if wornArmors.Length == 0
		return
	endif

	UIListMenu menu = Game.GetFormFromFile(0xE05, "UIExtensions.esp") as UIListMenu

	if menu
		menu.ResetMenu()
	else
		return
	endif

	string[] variantCache = new string[128]
	Armor[] armorCache = new Armor[128]

	int iArmor = 0
	while iArmor < wornArmors.Length
		Armor wornArmor = wornArmors[iArmor]
		string[] variants = DynamicArmor.GetVariants(wornArmor)
		if variants.Length > 0
			int parent = menu.AddEntryItem(wornArmor.GetName(), entryHasChildren = true)

			int defaultEntry = menu.AddEntryItem("$Default", entryParent = parent)
			variantCache[defaultEntry] = ""
			armorCache[defaultEntry] = wornArmor

			int iVariant = 0
			while iVariant < variants.Length
				string variant = variants[iVariant]
				string displayName = DynamicArmor.GetDisplayName(variant)
				int entry = menu.AddEntryItem(displayName, entryParent = parent)
				variantCache[entry] = variant
				armorCache[entry] = wornArmor
				iVariant += 1
			endwhile
		endif
		iArmor += 1
	endwhile

	; I think it's supposed to return 1, but in testing I get 0
	int ret = menu.OpenMenu()

	int result = menu.GetResultInt()
	if result >= 0
		string variant = variantCache[result]
		Armor wornArmor = armorCache[result]
		if variant != ""
			DynamicArmor.ApplyVariant(akActor, variant)
		else
			DynamicArmor.ResetVariant(akActor, wornArmor)
		endif
	endif

EndFunction
