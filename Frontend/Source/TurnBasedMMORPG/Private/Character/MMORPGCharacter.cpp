// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/MMORPGCharacter.h"

#include "DebugHelper.h"
#include "NavigationInvokerComponent.h"
#include "Tags.h"
#include "AbilitySystem/MMOAbilitySystemComponent.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "BattleSystem/BattleComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MMOCharMovementComp.h"
#include "Components/WidgetComponent.h"
#include "DataAsset/AbilityStartupDataAsset.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Interfaces/OnlineGameMatchesInterface.h"
#include "Net/UnrealNetwork.h"


AMMORPGCharacter::AMMORPGCharacter(const FObjectInitializer& ObjectInitializer): Super(
	ObjectInitializer.SetDefaultSubobjectClass<UMMOCharMovementComp>(CharacterMovementComponentName))
{
	SetReplicates(true);

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f * 2;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	AboveHeadWidget = CreateDefaultSubobject<UWidgetComponent>("AboveHeadWidget");
	AboveHeadWidget->SetupAttachment(GetRootComponent());
	AboveHeadWidget->SetDrawAtDesiredSize(true);
	AboveHeadWidget->SetWidgetSpace(EWidgetSpace::Screen);

	NavigationInvoker = CreateDefaultSubobject<UNavigationInvokerComponent>("NavigationInvoker");
}

void AMMORPGCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMMORPGCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	checkf(!BaseStartupData.IsNull(), TEXT("BaseStartupData is not Set at %s"), *GetPathName());


	if (!GetAbilitySystemComponent()->HasAnyMatchingGameplayTags(
		MMOGameplayTags::Shared_Status_AbilityGranted.GetTag().GetSingleTagContainer()))
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			BaseStartupData.ToSoftObjectPath(),
			[this]()
			{
				auto loadedData = BaseStartupData.Get();
				if (!loadedData)
				{
					return;
				}


				loadedData->GiveToASC(GetAbilitySystemComponent());
			});
	}
}

EInteractType AMMORPGCharacter::GetInteractionType()
{
	return EInteractType::None;
}

void AMMORPGCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

UBattleComponent* AMMORPGCharacter::GetBattleComponent() const
{
	PURE_VIRTUAL()
	return nullptr;
}

ETeamAttitude::Type AMMORPGCharacter::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);

	if (&Other == this)
	{
		return ETeamAttitude::Friendly;
	}

	if (GetGenericTeamId() == FGenericTeamId::NoTeam)
	{
		return ETeamAttitude::Hostile;
	}

	return IGenericTeamAgentInterface::GetTeamAttitudeTowards(Other);
}

FVector AMMORPGCharacter::GetNavigationInvokerLocation() const
{
	return GetActorLocation();
}
