Scriptname DynamicArmor_MenuPower extends ActiveMagicEffect

Function OnEffectStart(Actor akTarget, Actor akCaster)
	DynamicArmor_Menu.OpenMenu(akTarget)
EndFunction
