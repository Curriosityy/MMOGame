#include "DTOs/TryAddAbilityDTO.h"

#include "AbilitySystem/Abilities/MMOBattleAbility.h"

UMMOBattleAbility* UTryAddAbilityDTO::GetAbility() const
{
	return AbilityToActivate;
}
