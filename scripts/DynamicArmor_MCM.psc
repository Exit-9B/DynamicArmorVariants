Scriptname DynamicArmor_MCM extends MCM_ConfigBase

Actor Property PlayerRef Auto

Spell Property DAV_ConfigPower Auto
Spell Property DAV_NPCConfigSpell Auto

bool Property PlayerHasConfigPower Auto
bool Property PlayerHasNPCConfigSpell Auto

Event OnConfigInit()
	if GetModSettingBool("bUseConfigPower:DynamicArmorMenu")
		PlayerRef.AddSpell(DAV_ConfigPower)
		PlayerHasConfigPower = true
	endif

	if GetModSettingBool("bUseNPCConfigSpell:DynamicArmorMenu")
		PlayerRef.AddSpell(DAV_NPCConfigSpell)
		PlayerHasNPCConfigSpell = true
	endif
EndEvent

Event OnConfigOpen()
	PlayerHasConfigPower = PlayerRef.HasSpell(DAV_ConfigPower)
	PlayerHasNPCConfigSpell = PlayerRef.HasSpell(DAV_NPCConfigSpell)
	RefreshMenu()
EndEvent

Function AddPower()
	PlayerRef.AddSpell(DAV_ConfigPower)
	PlayerHasConfigPower = true
	SetModSettingBool("bUseConfigPower:DynamicArmorMenu", true)
	ForcePageReset()
EndFunction

Function RemovePower()
	PlayerRef.RemoveSpell(DAV_ConfigPower)
	PlayerHasConfigPower = false
	SetModSettingBool("bUseConfigPower:DynamicArmorMenu", false)
	ForcePageReset()
EndFunction

Function AddNPCSpell()
	PlayerRef.AddSpell(DAV_NPCConfigSpell)
	PlayerHasNPCConfigSpell = true
	SetModSettingBool("bUseNPCConfigSpell:DynamicArmorMenu", true)
	ForcePageReset()
EndFunction

Function RemoveNPCSpell()
	PlayerRef.RemoveSpell(DAV_NPCConfigSpell)
	PlayerHasNPCConfigSpell = false
	SetModSettingBool("bUseNPCConfigSpell:DynamicArmorMenu", false)
	ForcePageReset()
EndFunction
