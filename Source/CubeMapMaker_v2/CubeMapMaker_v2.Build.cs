// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CubeMapMaker_v2 : ModuleRules
{
	public CubeMapMaker_v2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"CubeMapMaker_v2",
			"CubeMapMaker_v2/Variant_Horror",
			"CubeMapMaker_v2/Variant_Horror/UI",
			"CubeMapMaker_v2/Variant_Shooter",
			"CubeMapMaker_v2/Variant_Shooter/AI",
			"CubeMapMaker_v2/Variant_Shooter/UI",
			"CubeMapMaker_v2/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
