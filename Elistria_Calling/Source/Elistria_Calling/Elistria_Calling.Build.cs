// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class Elistria_Calling : ModuleRules
{
	public Elistria_Calling(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","GameplayAbilities", "GameplayTags", "GameplayTasks", "EnhancedInput","TargetingSystem" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		PrivateDependencyModuleNames.Add("OnlineSubsystem");
		
		PublicIncludePaths.AddRange(new string[]{Path.Combine(ModuleDirectory, "Public")});
		
		PrivateIncludePaths.AddRange(new string[]{Path.Combine(ModuleDirectory, "Private")});

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
