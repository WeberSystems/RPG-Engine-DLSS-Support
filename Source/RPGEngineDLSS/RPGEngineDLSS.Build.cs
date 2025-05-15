// Some copyright should be here...
using System.IO;
using UnrealBuildTool;

public class RPGEngineDLSS : ModuleRules
{
	public RPGEngineDLSS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "StreamlineDLSSGBlueprint",
                "DLSS",
                "DLSSBlueprint",
                "StreamlineDeepDVCBlueprint",
                "NISBlueprint",
                "StreamlineCore",
                "StreamlineReflexBlueprint"
				// ... add other public dependencies that you statically link with here ...
			}
			);

        string StreamlineDLSSGPath = Path.Combine(EngineDirectory, "Plugins", "Marketplace", "StreamlineDLSSG", "Source", "StreamlineDLSSGBlueprint");
        PublicIncludePaths.Add(Path.Combine(StreamlineDLSSGPath, "Public"));

        string DLSSPath = Path.Combine(EngineDirectory, "Plugins", "Marketplace", "DLSS", "Source", "DLSS");
        PublicIncludePaths.Add(Path.Combine(DLSSPath, "Public"));

        string StreamlineCorePath = Path.Combine(EngineDirectory, "Plugins", "Marketplace", "StreamlineCore", "Source", "StreamlineCore");
        PublicIncludePaths.Add(Path.Combine(StreamlineCorePath, "Public"));

        string StreamlineDeepDVCPath = Path.Combine(EngineDirectory, "Plugins", "Marketplace", "StreamlineDeepDVC", "Source", "StreamlineDeepDVCBlueprint");
        PublicIncludePaths.Add(Path.Combine(StreamlineDeepDVCPath, "Public"));

        string NISPath = Path.Combine(EngineDirectory, "Plugins", "Marketplace", "NIS", "Source", "NISBlueprint");
        PublicIncludePaths.Add(Path.Combine(NISPath, "Public"));

        string StreamlineReflexPath = Path.Combine(EngineDirectory, "Plugins", "Marketplace", "StreamlineReflex", "Source", "StreamlineReflexBlueprint");
        PublicIncludePaths.Add(Path.Combine(StreamlineReflexPath, "Public"));

        PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
