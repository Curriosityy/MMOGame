#include "Tags.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "BattleSystem/DamageSpecBuilder.h"
#include "FunctionLibraries/MMOAbilityBlueprintLibrary.h"
#include "FunctionLibraries/TestsFunctionLibrary.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleDamageCalculationTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.SimpleDamageCalculationTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleStrDamageCalculationTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.SimpleStrDamageCalculationTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleIntDamageCalculationTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.SimpleIntDamageCalculationTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleWisDamageCalculationTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.SimpleWisDamageCalculationTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleChaDamageCalculationTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.SimpleChaDamageCalculationTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleDexDamageCalculationTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.SimpleDexDamageCalculationTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleKillTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.SimpleKillTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleFaiDamageCalculationTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.SimpleFaiDamageCalculationTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleMultiplierCalculationTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.SimpleMultiplierCalculationTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(DodgedTagTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.DodgedTagTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(WeaponHitTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.WeaponHitTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SpellDamageTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.SpellDamageTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SpellDamageSumTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.SpellDamageSumTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SpellDamageMultiplierTest,
                                 "TurnBasedMMORPG.TurnBasedMMORPG.Private.Tests.SpellDamageMultiplierTest",
                                 EAutomationTestFlags::ServerContext | EAutomationTestFlags::ClientContext |
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::CriticalPriority |
                                 EAutomationTestFlags::ProductFilter)


bool SimpleDamageCalculationTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};

	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);
	PlayerAttributeSet->InitMaxHealth(100);
	PlayerAttributeSet->InitHealth(100);
	//PlayerAttributeSet->Init(0);
	UMonsterAttributeSet* MonsterAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, MonsterAttributeSet);
	MonsterAttributeSet->InitMaxHealth(100);
	MonsterAttributeSet->InitHealth(100);

	FGameplayEffectSpec Spec;
	UTestsFunctionLibrary::Native_GenerateDamageSpec(World, PlayerAttributeSet, Spec);


	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		Spec, MonsterAttributeSet->GetOwningAbilitySystemComponent());

	TestEqual(TEXT("Effect should not deal damage"), MonsterAttributeSet->GetHealth(), 100.f);

	return true;
}

bool DodgedTagTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};

	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);
	UMonsterAttributeSet* MonsterAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, MonsterAttributeSet);

	FGameplayEffectSpec Spec;
	UTestsFunctionLibrary::Native_GenerateDamageSpec(World, PlayerAttributeSet, Spec);


	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		Spec, MonsterAttributeSet->GetOwningAbilitySystemComponent());

	TestEqual(TEXT("Effect should not deal damage"), MonsterAttributeSet->GetHealth(), 100.f);
	TestTrue(
		TEXT("Effect should not deal damage"),
		MonsterAttributeSet->GetOwningAbilitySystemComponent()->HasMatchingGameplayTag(
			MMOGameplayTags::Shared_Status_Dodged));
	return true;
}

bool SimpleStrDamageCalculationTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};

	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);
	UMonsterAttributeSet* MonsterAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, MonsterAttributeSet);
	UDamageSpecBuilder* Builder = NewObject<UDamageSpecBuilder>();
	Builder->AddStrMul(1);
	Builder->AddSkillHitChance(100 / 100.f);
	Builder->AddWeaponHitChance(100 / 100.f);

	FGameplayEffectSpec Spec = Builder->Build(PlayerAttributeSet->GetOwningAbilitySystemComponent());

	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		Spec, MonsterAttributeSet->GetOwningAbilitySystemComponent());

	TestEqual(TEXT("Effect should deal damage"), MonsterAttributeSet->GetHealth(), 90.f);
	return true;
}

bool SimpleIntDamageCalculationTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};

	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);
	UMonsterAttributeSet* MonsterAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, MonsterAttributeSet);
	UDamageSpecBuilder* Builder = NewObject<UDamageSpecBuilder>();
	Builder->AddIntMul(1);
	Builder->AddSkillHitChance(100 / 100.f);
	Builder->AddWeaponHitChance(100 / 100.f);

	FGameplayEffectSpec Spec = Builder->Build(PlayerAttributeSet->GetOwningAbilitySystemComponent());

	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		Spec, MonsterAttributeSet->GetOwningAbilitySystemComponent());

	TestEqual(TEXT("Effect should deal damage"), MonsterAttributeSet->GetHealth(), 90.f);
	return true;
}

bool SimpleDexDamageCalculationTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};

	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);
	UMonsterAttributeSet* MonsterAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, MonsterAttributeSet);
	UDamageSpecBuilder* Builder = NewObject<UDamageSpecBuilder>();
	Builder->AddDexMul(1);
	Builder->AddSkillHitChance(100 / 100.f);
	Builder->AddWeaponHitChance(100 / 100.f);

	FGameplayEffectSpec Spec = Builder->Build(PlayerAttributeSet->GetOwningAbilitySystemComponent());

	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		Spec, MonsterAttributeSet->GetOwningAbilitySystemComponent());

	TestEqual(TEXT("Effect should deal damage"), MonsterAttributeSet->GetHealth(), 90.f);
	return true;
}

bool SimpleChaDamageCalculationTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};

	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);
	UMonsterAttributeSet* MonsterAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, MonsterAttributeSet);
	UDamageSpecBuilder* Builder = NewObject<UDamageSpecBuilder>();
	Builder->AddChaMul(1);
	Builder->AddSkillHitChance(100 / 100.f);
	Builder->AddWeaponHitChance(100 / 100.f);

	FGameplayEffectSpec Spec = Builder->Build(PlayerAttributeSet->GetOwningAbilitySystemComponent());

	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		Spec, MonsterAttributeSet->GetOwningAbilitySystemComponent());

	TestEqual(TEXT("Effect should deal damage"), MonsterAttributeSet->GetHealth(), 90.f);
	return true;
}

bool SimpleFaiDamageCalculationTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};

	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);
	UMonsterAttributeSet* MonsterAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, MonsterAttributeSet);
	UDamageSpecBuilder* Builder = NewObject<UDamageSpecBuilder>();
	Builder->AddFaiMul(1);
	Builder->AddSkillHitChance(100 / 100.f);
	Builder->AddWeaponHitChance(100 / 100.f);

	FGameplayEffectSpec Spec = Builder->Build(PlayerAttributeSet->GetOwningAbilitySystemComponent());

	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		Spec, MonsterAttributeSet->GetOwningAbilitySystemComponent());

	TestEqual(TEXT("Effect should deal damage"), MonsterAttributeSet->GetHealth(), 90.f);
	return true;
}

bool SimpleWisDamageCalculationTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};

	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);
	UMonsterAttributeSet* MonsterAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, MonsterAttributeSet);
	UDamageSpecBuilder* Builder = NewObject<UDamageSpecBuilder>();
	Builder->AddWisMul(1);
	Builder->AddSkillHitChance(100 / 100.f);
	Builder->AddWeaponHitChance(100 / 100.f);

	FGameplayEffectSpec Spec = Builder->Build(PlayerAttributeSet->GetOwningAbilitySystemComponent());

	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		Spec, MonsterAttributeSet->GetOwningAbilitySystemComponent());

	TestEqual(TEXT("Effect should deal damage"), MonsterAttributeSet->GetHealth(), 90.f);
	return true;
}

bool SimpleMultiplierCalculationTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};

	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);
	UMonsterAttributeSet* MonsterAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, MonsterAttributeSet);
	UDamageSpecBuilder* Builder = NewObject<UDamageSpecBuilder>();
	Builder->AddChaMul(.1f);
	Builder->AddDexMul(.1f);
	Builder->AddFaiMul(.1f);
	Builder->AddIntMul(.1f);
	Builder->AddStrMul(.1f);
	Builder->AddWisMul(.1f);

	Builder->AddSkillHitChance(100 / 100.f);
	Builder->AddWeaponHitChance(100 / 100.f);

	FGameplayEffectSpec Spec = Builder->Build(PlayerAttributeSet->GetOwningAbilitySystemComponent());

	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		Spec, MonsterAttributeSet->GetOwningAbilitySystemComponent());

	TestEqual(TEXT("Effect should deal damage"), MonsterAttributeSet->GetHealth(), 94.f);
	return true;
}


bool SimpleKillTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};

	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);
	UMonsterAttributeSet* MonsterAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, MonsterAttributeSet);
	UDamageSpecBuilder* Builder = NewObject<UDamageSpecBuilder>();
	Builder->AddStrMul(100);
	Builder->AddSkillHitChance(100 / 100.f);
	Builder->AddWeaponHitChance(100 / 100.f);

	FGameplayEffectSpec Spec = Builder->Build(PlayerAttributeSet->GetOwningAbilitySystemComponent());

	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		Spec, MonsterAttributeSet->GetOwningAbilitySystemComponent());

	TestEqual(TEXT("Effect should deal damage"), MonsterAttributeSet->GetHealth(), -900.f);
	TestTrue(
		TEXT("Effect should deal damage"),
		MonsterAttributeSet->GetOwningAbilitySystemComponent()->HasMatchingGameplayTag(
			MMOGameplayTags::Shared_Status_Death));
	return true;
}

bool WeaponHitTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};

	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);
	UMonsterAttributeSet* MonsterAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, MonsterAttributeSet);
	UDamageSpecBuilder* Builder = NewObject<UDamageSpecBuilder>();
	Builder->AddSkillHitChance(1);
	Builder->AddWeaponHitChance(1);
	Builder->AddWeaponDmg(10, 10);
	FGameplayEffectSpec Spec = Builder->Build(PlayerAttributeSet->GetOwningAbilitySystemComponent());

	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		Spec, MonsterAttributeSet->GetOwningAbilitySystemComponent());

	TestEqual(TEXT("Effect should deal damage"), MonsterAttributeSet->GetHealth(), 90.f);

	return true;
}

bool SpellDamageTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};

	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);
	UMonsterAttributeSet* MonsterAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, MonsterAttributeSet);
	UDamageSpecBuilder* Builder = NewObject<UDamageSpecBuilder>();
	Builder->AddSkillHitChance(1);
	Builder->AddWeaponHitChance(1);
	Builder->AddSkillDmg(10);
	FGameplayEffectSpec Spec = Builder->Build(PlayerAttributeSet->GetOwningAbilitySystemComponent());

	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		Spec, MonsterAttributeSet->GetOwningAbilitySystemComponent());

	TestEqual(TEXT("Effect should deal damage"), MonsterAttributeSet->GetHealth(), 90.f);

	return true;
}

bool SpellDamageSumTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};

	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);
	UMonsterAttributeSet* MonsterAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, MonsterAttributeSet);
	UDamageSpecBuilder* Builder = NewObject<UDamageSpecBuilder>();
	Builder->AddSkillHitChance(1);
	Builder->AddWeaponHitChance(1);

	Builder->AddSkillDmg(10);
	Builder->AddStrMul(1);
	Builder->AddWeaponDmg(10, 10);

	FGameplayEffectSpec Spec = Builder->Build(PlayerAttributeSet->GetOwningAbilitySystemComponent());

	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		Spec, MonsterAttributeSet->GetOwningAbilitySystemComponent());

	TestEqual(TEXT("Effect should deal damage"), MonsterAttributeSet->GetHealth(), 70.f);

	return true;
}

bool SpellDamageMultiplierTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	UPlayerAttributeSet* PlayerAttributeSet = {};

	UTestsFunctionLibrary::Native_GetAttributeSet(World, PlayerAttributeSet);
	UMonsterAttributeSet* MonsterAttributeSet = {};
	UTestsFunctionLibrary::Native_GetAttributeSet(World, MonsterAttributeSet);
	UDamageSpecBuilder* Builder = NewObject<UDamageSpecBuilder>();
	Builder->AddSkillHitChance(1);
	Builder->AddWeaponHitChance(1);

	Builder->AddSkillDmg(10);
	Builder->AddStrMul(1);
	Builder->AddWeaponDmg(10, 10);
	Builder->AddSkillMul(1);
	FGameplayEffectSpec Spec = Builder->Build(PlayerAttributeSet->GetOwningAbilitySystemComponent());

	PlayerAttributeSet->GetOwningAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		Spec, MonsterAttributeSet->GetOwningAbilitySystemComponent());

	TestEqual(TEXT("Effect should deal damage"), MonsterAttributeSet->GetHealth(), 40.f);

	return true;
}
