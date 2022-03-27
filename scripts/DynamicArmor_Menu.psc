Scriptname DynamicArmor_Menu Hidden

Function OpenMenu(Actor akActor) global
	Armor[] wornArmors = GetWornArmors(akActor)

	UIListMenu menu = Game.GetFormFromFile(0xE05, "UIExtensions.esp") as UIListMenu

	if menu
		menu.ResetMenu()
	else
		return
	endif

	string[] variantCache = new string[128]
	Armor[] armorCache = new Armor[128]

	int iArmor = 0
	while iArmor < wornArmors.Length && wornArmors[iArmor] != None
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

Armor[] Function GetWornArmors(Actor akActor) global
	Armor[] wornArmors = new Armor[32]
	int numWorn = 0

	int slot = 30
	while slot < 62
		Armor wornArmor = akActor.GetEquippedArmorInSlot(slot)

		if wornArmor
			bool alreadyInList = false

			int i = 0
			while i < numWorn
				if wornArmors[i] == wornArmor
					alreadyInList = true
					i = numWorn
				endif

				i += 1
			endwhile

			if !alreadyInList
				wornArmors[numWorn] = wornArmor
				numWorn += 1
			endif
		endif

		slot += 1
	endwhile

	return wornArmors
EndFunction
