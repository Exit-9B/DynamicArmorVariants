Scriptname DynamicArmor Hidden

; Gets the current Dynamic Armor Variants API version.
int Function GetAPIVersion() global native

; Gets available variants for an armor.
string[] Function GetVariants(Armor akArmor) global native

; Gets all equipped armors with variants.
Armor[] Function GetEquippedArmorsWithVariants(Actor akActor) global native

; Gets the display name for a variant that can be shown to the player.
string Function GetDisplayName(string asVariant) global native

; Applies a variant to armor items worn by the given character.
; This will take precedence over dynamic states.
Function ApplyVariant(Actor akActor, string asVariant) global native

; Resets an armor to its default/dynamic appearance for the given character.
Function ResetVariant(Actor akActor, Armor akArmor) global native

; Resets all armor variants to default/dynamic for the given character.
Function ResetAllVariants(Actor akActor) global native
