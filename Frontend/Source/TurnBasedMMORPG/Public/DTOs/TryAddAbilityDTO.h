#pragma once

#include "CoreMinimal.h"
#include "DebugHelper.h"
#include "GameplayAbilitySpec.h"
#include "UObject/NoExportTypes.h"
#include "TryAddAbilityDTO.generated.h"

class UMMOBattleAbility;
/**
 * 
 */
UCLASS(Blueprintable)
class TURNBASEDMMORPG_API UTryAddAbilityDTO : public UObject
{
	GENERATED_BODY()

public:
	//TODO: WHEN IMPLEMENTED SKILL PANEL THEN CHANGE HERE
	UPROPERTY(BlueprintReadOnly)
	UMMOBattleAbility* AbilityToActivate;

	UMMOBattleAbility* GetAbility() const;
};
