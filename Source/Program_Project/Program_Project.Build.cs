// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Program_Project : ModuleRules
{
	public Program_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "NavigationSystem", "GameplayTasks" });
    }
}
