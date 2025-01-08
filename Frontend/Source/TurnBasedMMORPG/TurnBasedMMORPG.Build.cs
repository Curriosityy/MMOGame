// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class TurnBasedMMORPG : ModuleRules
{
	public TurnBasedMMORPG(ReadOnlyTargetRules ROTargetRules) : base(ROTargetRules)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"OWSPlugin",
			"AIModule",
			"Json",
			"JsonUtilities",
			"Niagara",
			"EnhancedInput",
			"OnlineSubsystem",
			"OnlineSubsystemUtils",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"GameplayMessageRuntime",
			"GameplayMessageNodes",
			"HTTP",
			"UnrealEd",
			"CommonUI",
			"NavigationSystem",
			"FunctionalTesting",
			"GoogleTest",
			"Gauntlet"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePathModuleNames.AddRange(new[] { "OWSPlugin", "GameplayMessageRuntime", "GameplayMessageNodes" });

		// Uncomment if you are using Slate UI
		//PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
		//Definitions.Add("AES_KEY=FF82B5451E21C090AE76622AAF24BCB0");
	}
}