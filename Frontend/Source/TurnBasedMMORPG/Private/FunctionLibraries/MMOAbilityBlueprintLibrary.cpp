#include "FunctionLibraries/MMOAbilityBlueprintLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "Tags.h"
#include "AbilitySystem/MMOAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MMOBattleAbility.h"
#include "DTOs/TryAddAbilityDTO.h"
#include "DTOs/VectorDTO.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UMMOAbilityBlueprintLibrary::GenerateTryAddAbilityPayload(const FGameplayTag& InputTag,
                                                               FGameplayEventData& OutEventData,
                                                               UMMOAbilitySystemComponent* Asc)
{
	//TODO Make some kind of switch based on EventTag
	UTryAddAbilityDTO* DTO = NewObject<UTryAddAbilityDTO>(Asc->GetWorld());
	OutEventData.EventTag = MMOGameplayTags::Shared_Event_TryAddAbility;
	SetupSimpleEventData(OutEventData, Asc->GetOwner(), Asc->GetOwner());
	FGameplayAbilitySpec* Spec = Asc->GetAbilitiesByDynamicTag(InputTag);

	if (!Spec)
	{
		return;
	}


	DTO->AbilityToActivate = Cast<UMMOBattleAbility>(Spec->Ability);
	OutEventData.OptionalObject = DTO;
}

void UMMOAbilityBlueprintLibrary::GetHitUnderCursor(const UMMOAbilitySystemComponent* Asc, FHitResult& Hit)
{
	FVector WorldLocation;
	FVector WorldDirection;
	FVector2D MousePosition;
	UWorld* World = Asc->GetWorld();

	World->GetFirstLocalPlayerFromController()->ViewportClient->GetMousePosition(MousePosition);
	UGameplayStatics::DeprojectScreenToWorld(World->GetFirstPlayerController(), MousePosition,
	                                         WorldLocation, WorldDirection);


	bool bHit = UKismetSystemLibrary::LineTraceSingleForObjects(Asc,
	                                                            WorldLocation,
	                                                            WorldLocation + WorldDirection * 20000,
	                                                            {ObjectTypeQuery2, ObjectTypeQuery3},
	                                                            true,
	                                                            {},
	                                                            EDrawDebugTrace::Persistent,
	                                                            Hit,
	                                                            true);
}

void UMMOAbilityBlueprintLibrary::GenerateInteractionPayload(const FGameplayTag& InputTag,
                                                             FGameplayEventData& OutEventData,
                                                             const UMMOAbilitySystemComponent* Asc)
{
	SetupSimpleEventData(OutEventData, Asc->GetOwner(), Asc->GetOwner());
	OutEventData.EventTag = MMOGameplayTags::InputTag_Interaction;
	FHitResult Hit;
	GetHitUnderCursor(Asc, Hit);

	OutEventData.TargetData.Add(new FGameplayAbilityTargetData_SingleTargetHit(Hit));
}

void UMMOAbilityBlueprintLibrary::SetupSimpleEventData(FGameplayEventData& OutEventData, AActor* Instigator,
                                                       AActor* Target)
{
	if (Target)
	{
		OutEventData.Instigator = Instigator;
		OutEventData.InstigatorTags = Cast<IAbilitySystemInterface>(Instigator)->
		                              GetAbilitySystemComponent()->
		                              GetOwnedGameplayTags();
	}

	if (Instigator)
	{
		OutEventData.Target = Target;
		OutEventData.TargetTags = Cast<IAbilitySystemInterface>(Target)->
		                          GetAbilitySystemComponent()->
		                          GetOwnedGameplayTags();
	}
}

void UMMOAbilityBlueprintLibrary::GenerateEventData(UMMOAbilitySystemComponent* ASC, const FGameplayTag& InputTag,
                                                    FGameplayEventData& OutEventData)
{
	check(ASC)
	if (InputTag.MatchesTag(MMOGameplayTags::InputTag_Event_Ability))
	{
		GenerateTryAddAbilityPayload(InputTag, OutEventData, ASC);
	}
	if (InputTag.MatchesTag(MMOGameplayTags::InputTag_Interaction))
	{
		GenerateInteractionPayload(InputTag, OutEventData, ASC);
	}
}

UMMOAbilitySystemComponent* UMMOAbilityBlueprintLibrary::GetMMOAbilityComponentSystem(APawn* Pawn)
{
	return Cast<UMMOAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Pawn));
}

void UMMOAbilityBlueprintLibrary::MakeEffectSpecHandle(
	const UGameplayAbility* SourceAbility,
	const UAbilitySystemComponent* SourceAsc,
	const TSubclassOf<UGameplayEffect>& Effect,
	const TMap<FGameplayTag, float>& EffectData,
	FGameplayEffectSpecHandle& OutHandle
)
{
	FGameplayEffectContextHandle ContextHandle = SourceAsc->MakeEffectContext();
	ContextHandle.SetAbility(SourceAbility);
	ContextHandle.AddSourceObject(SourceAbility->GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(SourceAbility->GetAvatarActorFromActorInfo(),
	                            SourceAbility->GetAvatarActorFromActorInfo());

	OutHandle = SourceAsc->MakeOutgoingSpec(
		Effect,
		SourceAbility->GetAbilityLevel(),
		ContextHandle
	);

	for (const TTuple<FGameplayTag, float>& Data : EffectData)
	{
		if (!Data.Key.IsValid() || OutHandle.Data->SetByCallerTagMagnitudes.Find(Data.Key))
		{
			continue;
		}

		OutHandle.Data->SetSetByCallerMagnitude(Data.Key, Data.Value);
	}
}


void UMMOAbilityBlueprintLibrary::MakeDamageEffectMap(const TArray<float>& Values, TMap<FGameplayTag, float>& OutMap)
{
	//TODO BUILDER
	check(Values.Num() == 11);
	OutMap.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Strength, Values[0]});
	OutMap.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Dexterity, Values[1]});
	OutMap.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Intelligence, Values[2]});
	OutMap.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Wisdom, Values[3]});
	OutMap.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Faith, Values[4]});
	OutMap.Add({MMOGameplayTags::Shared_SetByCaller_SpellDamageMultiplier_Charisma, Values[5]});
	OutMap.Add({MMOGameplayTags::Shared_SetByCaller_HitChance_Base, Values[6]});
	OutMap.Add({MMOGameplayTags::Shared_SetByCaller_HitChance_Weapon, Values[7]});
	OutMap.Add({MMOGameplayTags::Shared_SetByCaller_SkillDamage, Values[8]});
	OutMap.Add({MMOGameplayTags::Shared_SetByCaller_WeaponDamage_Low, Values[9]});
	OutMap.Add({MMOGameplayTags::Shared_SetByCaller_WeaponDamage_Max, Values[10]});
}

void UMMOAbilityBlueprintLibrary::Native_ApplyEffectSpecHandle(AActor* TargetActor,
                                                               UAbilitySystemComponent* InstigatorASC,
                                                               const FGameplayEffectSpecHandle& InSpecHandle,
                                                               FActiveGameplayEffectHandle& OutHandle)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	checkf(ASC, TEXT("UARPGGameplayAbility::Native_ApplyEffectSpecHandle Target Actor has no ASC"));
	checkf(InSpecHandle.IsValid(), TEXT("UARPGGameplayAbility::Native_ApplyEffectSpecHandle InSpecHandle is invalid"));

	OutHandle = InstigatorASC
		->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, ASC);
}

void UMMOAbilityBlueprintLibrary::BP_ApplyEffectSpecHandle(AActor* TargetActor,
                                                           UAbilitySystemComponent* InstigatorAsc,
                                                           const FGameplayEffectSpecHandle& InSpecHandle,
                                                           EARPGSuccessType& Success,
                                                           FActiveGameplayEffectHandle& OutHandle)
{
	Native_ApplyEffectSpecHandle(TargetActor, InstigatorAsc, InSpecHandle, OutHandle);
	Success = OutHandle.WasSuccessfullyApplied() ? EARPGSuccessType::Successful : EARPGSuccessType::Unsuccessful;
	Debug::Print(UEnum::GetValueAsString(Success), InstigatorAsc);
}

void UMMOAbilityBlueprintLibrary::Native_AddLooseGameplayTagsToAll(UAbilitySystemComponent* Asc,
                                                                   const FGameplayTag& LooseGameplayTag)
{
	if (!Asc->HasMatchingGameplayTag(LooseGameplayTag))
	{
		Asc->AddLooseGameplayTag(LooseGameplayTag);
		Asc->AddReplicatedLooseGameplayTag(LooseGameplayTag);
	}
}
