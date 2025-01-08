#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BattleComponentInterface.generated.h"

class UBattleComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, NotBlueprintable)
class UBattleComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TURNBASEDMMORPG_API IBattleComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual UBattleComponent* GetBattleComponent() const = 0;
};
