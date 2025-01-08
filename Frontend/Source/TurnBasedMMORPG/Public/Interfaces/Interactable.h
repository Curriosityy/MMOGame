#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class AMMORPGCharacter;

UENUM(Meta = (Bitflags), BlueprintType)
enum class EInteractType:uint8
{
	None = 0,
	Attack = 1 << 0,
	Pickup = 1 << 1,
	Trade = 1 << 2,
	Party = 1 << 3
};

ENUM_CLASS_FLAGS(EInteractType);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TURNBASEDMMORPG_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual EInteractType GetInteractionType() = 0;

	UFUNCTION()
	virtual void Interact(EInteractType Interaction, AMMORPGCharacter* Instigator);

	UFUNCTION()
	virtual AActor* GetActor() = 0;
};
