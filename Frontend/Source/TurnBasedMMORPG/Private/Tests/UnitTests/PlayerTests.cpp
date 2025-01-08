#include "MMOPlayerState.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "Character/PlayerCharacter.h"
#include "Engine/World.h"
#include "FunctionLibraries/TestsFunctionLibrary.h"
#include "GameFramework/PlayerState.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(AttributeClampZeroTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.ClampZero",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext |
                                 EAutomationTestFlags::CriticalPriority | EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(AttributeSetCurrentAboveMax,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.SetCurrentAboveMax",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(AttributeSetMaxUnderCurrent,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.SetMaxUnderCurrent",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(AttributeExpTest, "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.ExpTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)


bool AttributeClampZeroTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	{
		UPlayerAttributeSet* AttributeSet;
		UTestsFunctionLibrary::Native_GetAttributeSet(World, AttributeSet);

		AttributeSet->SetArmour(-1);
		AttributeSet->SetCharisma(-1);
		AttributeSet->SetDexterity(-1);
		AttributeSet->SetFaith(-1);
		AttributeSet->SetHealing(-1);
		AttributeSet->SetHealth(-1);
		AttributeSet->SetIntelligence(-1);
		AttributeSet->SetLevel(-1);
		AttributeSet->SetMana(-1);
		AttributeSet->SetStamina(-1);
		AttributeSet->SetStrength(-1);
		AttributeSet->SetDamageTaken(-1);
		AttributeSet->SetWisdom(-1);
		AttributeSet->SetManaRegen(-1);
		AttributeSet->SetManaTaken(-1);
		AttributeSet->SetMaxHealth(-1);
		AttributeSet->SetMaxMana(-1);
		AttributeSet->SetMaxStamina(-1);
		AttributeSet->SetStaminaRegen(-1);
		AttributeSet->SetStaminaTaken(-1);
		AttributeSet->SetCurrentAbilityPoints(-1);
		AttributeSet->SetMaxAbilityPoints(-1);

		TestEqual(TEXT("Armour should be clamped to 0"), AttributeSet->GetArmour(), 0.f);
		TestEqual(TEXT("Charisma should be clamped to 0"), AttributeSet->GetCharisma(), 0.f);
		TestEqual(TEXT("Dexterity should be clamped to 0"), AttributeSet->GetDexterity(), 0.f);
		TestEqual(TEXT("Faith should be clamped to 0"), AttributeSet->GetFaith(), 0.f);
		TestEqual(TEXT("Healing should be clamped to 0"), AttributeSet->GetHealing(), 0.f);
		TestEqual(TEXT("Health should not be clamped to 0"), AttributeSet->GetHealth(), -1.f);
		TestEqual(TEXT("Intelligence should be clamped to 0"), AttributeSet->GetIntelligence(), 0.f);
		TestEqual(TEXT("Level should be clamped to 1"), AttributeSet->GetLevel(), 1.f);
		TestEqual(TEXT("Mana should be clamped to 0"), AttributeSet->GetMana(), 0.f);
		TestEqual(TEXT("Stamina should be clamped to 0"), AttributeSet->GetStamina(), 0.f);
		TestEqual(TEXT("Strength should be clamped to 0"), AttributeSet->GetStrength(), 0.f);
		TestEqual(TEXT("DamageTaken should be clamped to 0"), AttributeSet->GetDamageTaken(), 0.f);
		TestEqual(TEXT("Wisdom should be clamped to 0"), AttributeSet->GetWisdom(), 0.f);
		TestEqual(TEXT("ManaRegen should be clamped to 0"), AttributeSet->GetManaRegen(), 0.f);
		TestEqual(TEXT("ManaTaken should be clamped to 0"), AttributeSet->GetManaTaken(), 0.f);
		TestEqual(TEXT("MaxHealth should be clamped to 1"), AttributeSet->GetMaxHealth(), 1.f);
		TestEqual(TEXT("MaxMana should be clamped to 1"), AttributeSet->GetMaxMana(), 1.f);
		TestEqual(TEXT("MaxStamina should be clamped to 1"), AttributeSet->GetMaxStamina(), 1.f);
		TestEqual(TEXT("StaminaRegen should be clamped to 0"), AttributeSet->GetStaminaRegen(), 0.f);
		TestEqual(TEXT("CurrentAbilityPoints should be clamped to 0"), AttributeSet->GetCurrentAbilityPoints(), 0.f);
		TestEqual(TEXT("MaxAbilityPoints should be clamped to 0"), AttributeSet->GetMaxAbilityPoints(), 0.f);
	}
	return true;
}

bool AttributeSetMaxUnderCurrent::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	{
		UPlayerAttributeSet* AttributeSet;
		UTestsFunctionLibrary::Native_GetAttributeSet(World, AttributeSet);

		AttributeSet->SetMaxHealth(100);
		AttributeSet->SetHealth(100);
		AttributeSet->SetMaxMana(100);
		AttributeSet->SetMana(100);
		AttributeSet->SetMaxStamina(100);
		AttributeSet->SetStamina(100);
		AttributeSet->SetMaxAbilityPoints(100);
		AttributeSet->SetCurrentAbilityPoints(100);

		AttributeSet->SetMaxHealth(50);
		AttributeSet->SetMaxMana(50);
		AttributeSet->SetMaxStamina(50);
		AttributeSet->SetMaxAbilityPoints(50);

		TestEqual(TEXT("Health should not go over Max Health"), AttributeSet->GetMaxHealth(),
		          AttributeSet->GetHealth());
		TestEqual(TEXT("Stamina should not go over Max Stamina"), AttributeSet->GetMaxStamina(),
		          AttributeSet->GetStamina());
		TestEqual(TEXT("Mana should not go over Max Mana"), AttributeSet->GetMaxMana(), AttributeSet->GetMana());
		TestEqual(TEXT("AbilityPoints should not go over Max AbilityPoints"), AttributeSet->GetCurrentAbilityPoints(),
		          AttributeSet->GetMaxAbilityPoints());
	}
	return true;
}


bool AttributeSetCurrentAboveMax::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	{
		UPlayerAttributeSet* AttributeSet;
		UTestsFunctionLibrary::Native_GetAttributeSet(World, AttributeSet);

		AttributeSet->SetMaxHealth(100);
		AttributeSet->SetHealth(100);
		AttributeSet->SetMaxMana(100);
		AttributeSet->SetMana(100);
		AttributeSet->SetMaxStamina(100);
		AttributeSet->SetStamina(100);
		AttributeSet->SetMaxAbilityPoints(100);
		AttributeSet->SetCurrentAbilityPoints(100);

		AttributeSet->SetHealth(150);
		AttributeSet->SetMana(150);
		AttributeSet->SetStamina(150);
		AttributeSet->SetCurrentAbilityPoints(150);

		TestEqual(TEXT("Health should not go over Max Health"), AttributeSet->GetMaxHealth(),
		          AttributeSet->GetHealth());
		TestEqual(TEXT("Stamina should not go over Max Stamina"), AttributeSet->GetMaxStamina(),
		          AttributeSet->GetStamina());
		TestEqual(TEXT("Mana should not go over Max Mana"), AttributeSet->GetMaxMana(), AttributeSet->GetMana());
		TestEqual(TEXT("AbilityPoints should not go over Max AbilityPoints"), AttributeSet->GetCurrentAbilityPoints(),
		          AttributeSet->GetMaxAbilityPoints());
	}
	return true;
}


bool AttributeExpTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	{
		UPlayerAttributeSet* AttributeSet;
		UTestsFunctionLibrary::Native_GetAttributeSet(World, AttributeSet);

		AttributeSet->InitExp(0);
		AttributeSet->SetExp(-1);
		TestEqual(TEXT("Exp should be clamped to 0"), AttributeSet->GetExp(), 0.f);
	}
	return true;
	
}
