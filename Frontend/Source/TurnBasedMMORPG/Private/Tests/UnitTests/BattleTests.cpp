#include <gtest/gtest.h>

#include "LevelEditor.h"
#include "UnrealEdGlobals.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "BattleSystem/BattleComponent.h"
#include "BattleSystem/BattleComponentInterface.h"
#include "Character/MMORPGCharacter.h"
#include "Editor/UnrealEdEngine.h"
#include "FunctionLibraries/TestsFunctionLibrary.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/Interactable.h"
#include "Misc/AutomationTest.h"
#include "Settings/LevelEditorPlaySettings.h"
#include "Tests/AutomationEditorCommon.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestSetup,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.AbilitySystem.EffectExecutionEffects.TestSetup",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestSetup::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);
	UAbilitySystemComponent* PlayerASC = PlayerAttributeSet->GetOwningAbilitySystemComponent();
	AActor* Player = PlayerASC->GetOwnerActor();
	IBattleComponentInterface* PlayerBCI = Cast<IBattleComponentInterface>(Player);
	TestTrue("Player GetOwnerActor should be PlayerState", Cast<APlayerState>(Player) != nullptr);
	TestTrue("Player GetOwnerActor should IBattleComponentInterface",
	         PlayerBCI != nullptr);
	TestTrue("Player IBattleComponentInterface should return pointer to Battle Component",
	         PlayerBCI->GetBattleComponent() != nullptr);
	TestTrue("Player State should implement Interactable", Cast<IInteractable>(Player) != nullptr);

	UMonsterAttributeSet* MonsterAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, MonsterAttributeSet);
	UAbilitySystemComponent* MonsterASC = MonsterAttributeSet->GetOwningAbilitySystemComponent();
	AActor* Monster = MonsterASC->GetOwnerActor();
	IBattleComponentInterface* MonsterBCI = Cast<IBattleComponentInterface>(Monster);
	TestTrue("Monster GetOwnerActor should be Pawn", Cast<APawn>(Monster) != nullptr);
	TestTrue("Monster GetOwnerActor should IBattleComponentInterface",
	         MonsterBCI != nullptr);
	TestTrue("Monster IBattleComponentInterface should return pointer to Battle Component",
	         MonsterBCI->GetBattleComponent() != nullptr);
	TestTrue("Monster should implement Interactable", Cast<IInteractable>(MonsterBCI) != nullptr);

	return true;
}
