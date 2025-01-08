#include "Engine/ObjectLibrary.h"
#include "FunctionLibraries/TestsFunctionLibrary.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleDamageTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.SimpleDamageTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleDamageNegateTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.SimpleDamageNegateTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleDealDamageOnDeathPlayerTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.SimpleDealDamageOnDeathPlayerTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleHealingTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.SimpleHealingTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleNegativeHealingTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.SimpleNegativeHealingTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleHealingDeathPlayer,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.SimpleHealingDeathPlayer",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleManaRegenTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.SimpleManaRegenTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleNegativeManaRegenTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.SimpleNegativeManaRegenTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleDeathManaRegenTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.SimpleDeathManaRegenTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleStaminaRegenTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.SimpleStaminaRegenTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleNegativeStaminaRegenTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.SimpleNegativeStaminaRegenTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleDeathStaminaRegenTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.Attribute.SimpleDeathStaminaRegenTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)


bool SimpleDamageTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);

	UGameplayEffect* Eff = UTestsFunctionLibrary::Native_GenerateSimpleAttriubuteGameplayEffect(
		World, 50, EGameplayModOp::Additive,
		UPlayerAttributeSet::GetDamageTakenAttribute());

	FGameplayEffectContextHandle ctx = PlayerAttributeSet->GetOwningAbilitySystemComponent()->MakeEffectContext();
	PlayerAttributeSet->InitMaxHealth(50);
	PlayerAttributeSet->InitHealth(50);
	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectToSelf(Eff, 1, ctx);
	TestTrue(TEXT("Deal damage not working"), PlayerAttributeSet->GetHealth() == 0);

	return true;
}

bool SimpleDamageNegateTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);

	UGameplayEffect* Eff = UTestsFunctionLibrary::Native_GenerateSimpleAttriubuteGameplayEffect(
		World, -50, EGameplayModOp::Additive,
		UPlayerAttributeSet::GetDamageTakenAttribute());

	FGameplayEffectContextHandle ctx = PlayerAttributeSet->GetOwningAbilitySystemComponent()->MakeEffectContext();
	PlayerAttributeSet->InitMaxHealth(50);
	PlayerAttributeSet->InitHealth(50);
	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectToSelf(Eff, 1, ctx);
	TestTrue(TEXT("Negate deal damage should not deal damage/regen health"), PlayerAttributeSet->GetHealth() == 50);

	return true;
}

bool SimpleDealDamageOnDeathPlayerTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);

	UGameplayEffect* Eff = UTestsFunctionLibrary::Native_GenerateSimpleAttriubuteGameplayEffect(
		World, 50, EGameplayModOp::Additive,
		UPlayerAttributeSet::GetDamageTakenAttribute());

	FGameplayEffectContextHandle ctx = PlayerAttributeSet->GetOwningAbilitySystemComponent()->MakeEffectContext();
	PlayerAttributeSet->InitMaxHealth(50);
	PlayerAttributeSet->InitHealth(50);
	PlayerAttributeSet->SetHealth(-50);

	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectToSelf(Eff, 1, ctx);
	TestTrue(TEXT("Damage dealing should not work on death player"), PlayerAttributeSet->GetHealth() == -50);

	return true;
}

bool SimpleHealingTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);

	UGameplayEffect* Eff = UTestsFunctionLibrary::Native_GenerateSimpleAttriubuteGameplayEffect(
		World, 50, EGameplayModOp::Additive,
		UPlayerAttributeSet::GetHealingAttribute());

	auto ctx = PlayerAttributeSet->GetOwningAbilitySystemComponent()->MakeEffectContext();
	PlayerAttributeSet->InitMaxHealth(100);
	PlayerAttributeSet->InitHealth(50);
	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectToSelf(Eff, 1, ctx);
	TestTrue(TEXT("Healing not working"), PlayerAttributeSet->GetHealth() == 100);

	return true;
}

bool SimpleNegativeHealingTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);

	UGameplayEffect* Eff = UTestsFunctionLibrary::Native_GenerateSimpleAttriubuteGameplayEffect(
		World, -50, EGameplayModOp::Additive,
		UPlayerAttributeSet::GetHealingAttribute());

	FGameplayEffectContextHandle ctx = PlayerAttributeSet->GetOwningAbilitySystemComponent()->MakeEffectContext();
	PlayerAttributeSet->InitMaxHealth(100);
	PlayerAttributeSet->InitHealth(50);
	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectToSelf(Eff, 1, ctx);
	TestTrue(TEXT("Negative healing should not interact with health"), PlayerAttributeSet->GetHealth() == 50);

	return true;
}

bool SimpleHealingDeathPlayer::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);

	UGameplayEffect* RegenEff = UTestsFunctionLibrary::Native_GenerateSimpleAttriubuteGameplayEffect(
		World, 50, EGameplayModOp::Additive,
		UPlayerAttributeSet::GetHealingAttribute());

	PlayerAttributeSet->InitMaxHealth(100);
	PlayerAttributeSet->InitHealth(50);
	PlayerAttributeSet->SetHealth(-50);

	FGameplayEffectContextHandle ctx = PlayerAttributeSet->GetOwningAbilitySystemComponent()->MakeEffectContext();
	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectToSelf(RegenEff, 1, ctx);

	TestTrue(TEXT("Healing should not work at death player"), PlayerAttributeSet->GetHealth() == -50);

	return true;
}

bool SimpleManaRegenTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);

	UGameplayEffect* RegenEff = UTestsFunctionLibrary::Native_GenerateSimpleAttriubuteGameplayEffect(
		World, 50, EGameplayModOp::Additive,
		UPlayerAttributeSet::GetManaRegenAttribute());

	PlayerAttributeSet->InitMaxMana(100);
	PlayerAttributeSet->InitMana(50);

	FGameplayEffectContextHandle ctx = PlayerAttributeSet->GetOwningAbilitySystemComponent()->MakeEffectContext();
	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectToSelf(RegenEff, 1, ctx);

	TestTrue(TEXT("Mana regen not working"), PlayerAttributeSet->GetMana() == 100);

	return true;
}

bool SimpleNegativeManaRegenTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);

	UGameplayEffect* RegenEff = UTestsFunctionLibrary::Native_GenerateSimpleAttriubuteGameplayEffect(
		World, -50, EGameplayModOp::Additive,
		UPlayerAttributeSet::GetManaRegenAttribute());

	PlayerAttributeSet->InitMaxMana(100);
	PlayerAttributeSet->InitMana(50);

	FGameplayEffectContextHandle ctx = PlayerAttributeSet->GetOwningAbilitySystemComponent()->MakeEffectContext();
	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectToSelf(RegenEff, 1, ctx);

	TestTrue(TEXT("Negative mana regen should not work"), PlayerAttributeSet->GetMana() == 50);

	return true;
}

bool SimpleDeathManaRegenTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);

	UGameplayEffect* RegenEff = UTestsFunctionLibrary::Native_GenerateSimpleAttriubuteGameplayEffect(
		World, 50, EGameplayModOp::Additive,
		UPlayerAttributeSet::GetManaRegenAttribute());

	PlayerAttributeSet->InitMaxMana(100);
	PlayerAttributeSet->InitMana(50);
	PlayerAttributeSet->SetHealth(-1);

	FGameplayEffectContextHandle ctx = PlayerAttributeSet->GetOwningAbilitySystemComponent()->MakeEffectContext();
	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectToSelf(RegenEff, 1, ctx);

	TestTrue(TEXT("Mana regen should not work on death player"), PlayerAttributeSet->GetMana() == 50);

	return true;
}

bool SimpleStaminaRegenTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);

	UGameplayEffect* RegenEff = UTestsFunctionLibrary::Native_GenerateSimpleAttriubuteGameplayEffect(
		World, 50, EGameplayModOp::Additive,
		UPlayerAttributeSet::GetStaminaRegenAttribute());

	PlayerAttributeSet->InitMaxStamina(100);
	PlayerAttributeSet->InitStamina(50);

	FGameplayEffectContextHandle ctx = PlayerAttributeSet->GetOwningAbilitySystemComponent()->MakeEffectContext();
	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectToSelf(RegenEff, 1, ctx);

	TestTrue(TEXT("Mana regen not working"), PlayerAttributeSet->GetStamina() == 100);

	return true;
}

bool SimpleNegativeStaminaRegenTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);

	UGameplayEffect* RegenEff = UTestsFunctionLibrary::Native_GenerateSimpleAttriubuteGameplayEffect(
		World, -50, EGameplayModOp::Additive,
		UPlayerAttributeSet::GetStaminaRegenAttribute());

	PlayerAttributeSet->InitMaxStamina(100);
	PlayerAttributeSet->InitStamina(50);

	FGameplayEffectContextHandle ctx = PlayerAttributeSet->GetOwningAbilitySystemComponent()->MakeEffectContext();
	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectToSelf(RegenEff, 1, ctx);

	TestTrue(TEXT("Negative mana regen should not work"), PlayerAttributeSet->GetStamina() == 50);

	return true;
}

bool SimpleDeathStaminaRegenTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);

	UGameplayEffect* RegenEff = UTestsFunctionLibrary::Native_GenerateSimpleAttriubuteGameplayEffect(
		World, 50, EGameplayModOp::Additive,
		UPlayerAttributeSet::GetStaminaRegenAttribute());

	PlayerAttributeSet->InitMaxStamina(100);
	PlayerAttributeSet->InitStamina(50);
	PlayerAttributeSet->SetHealth(-1);

	FGameplayEffectContextHandle ctx = PlayerAttributeSet->GetOwningAbilitySystemComponent()->MakeEffectContext();
	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectToSelf(RegenEff, 1, ctx);

	TestTrue(TEXT("Mana regen should not work on death player"), PlayerAttributeSet->GetStamina() == 50);

	return true;
}
