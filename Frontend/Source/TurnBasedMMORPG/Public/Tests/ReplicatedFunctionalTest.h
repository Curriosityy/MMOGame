// 

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "ReplicatedFunctionalTest.generated.h"

class APlayerCharacter;

UCLASS()
class TURNBASEDMMORPG_API AReplicatedFunctionalTest : public AFunctionalTest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<APlayerCharacter> PlayerCharacter1;

	UPROPERTY(EditAnywhere)
	TObjectPtr<APlayerCharacter> PlayerCharacter2;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController1;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController2;

public:
	// Sets default values for this actor's properties
	AReplicatedFunctionalTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PrepareTest() override;
	virtual void StartTest() override;
	UFUNCTION(NetMulticast, Reliable)
	void Test();
};
