#include "Interfaces/Interactable.h"

#include "Character/MMORPGCharacter.h"
#include "Engine/World.h"
#include "GameState/InGameGameState.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.
void IInteractable::Interact(const EInteractType Interaction, AMMORPGCharacter* Instigator)
{
	if ((GetInteractionType() & Interaction) == Interaction)
	{
		Instigator->GetWorld()->GetGameState<AInGameGameState>()->TryInteract(Interaction, GetActor(), Instigator);
	}
}
