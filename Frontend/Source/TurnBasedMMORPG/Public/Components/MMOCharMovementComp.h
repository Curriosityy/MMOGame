// 

#pragma once

#include "CoreMinimal.h"
#include "OWSCharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MMOCharMovementComp.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TURNBASEDMMORPG_API UMMOCharMovementComp : public UOWSCharacterMovementComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMMOCharMovementComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
