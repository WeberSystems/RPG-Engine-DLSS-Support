// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "RPGEngineDLSS.h"
#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Engine/World.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "DLSS/Public/DLSS.h"
#include "DLSSBlueprint/Public/DLSSLibrary.h"
#include "NISBlueprint/Public/NISLibrary.h"
#include "StreamlineCore/Public/StreamlineCore.h"
#include "StreamlineDLSSGBlueprint/Public/StreamlineLibraryDLSSG.h"
#include "StreamlineDeepDVCBlueprint/Public/StreamlineLibraryDeepDVC.h"
#include "StreamlineReflexBlueprint/Public/StreamlineLibraryReflex.h"

#include "HAL/IConsoleManager.h"

#include "RPGEngineDLSSBPLibrary.generated.h"

UENUM(BlueprintType)
enum class EUpscaleModes : uint8
{
    BuiltIn UMETA(DisplayName = "BuiltIn"),
    DLSS UMETA(DisplayName = "DLSS"),
    ImageScaling UMETA(DisplayName = "ImageScaling"),
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ENVIDIASettings : uint8
{
    RTX,
    Upscaling,
    DLSS,
    DLSSSharpness,
    ReflexMode,
    DLSSRR,
    DVM,
    DVI,
    NISMode,
    NISCustomResolution,
    NISSharpness,
    DVSB,
    ResolutionScale,
    DLSSFG
};

UENUM(BlueprintType)
enum class EBuiltInAAModes : uint8
{
    Off,
    FXAA,
    TemporalAA,
    MSAA,
    TSR
};

UCLASS(meta = (Blueprintable, Category = "RPGEngineDLSS|Utilities"))

class URPGEngineDLSSBPLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    URPGEngineDLSSBPLibrary(const FObjectInitializer& ObjectInitializer);
    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static TArray<FName> CollectDLSSModes(bool& IndexedValue);
    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static TArray<FName> CollectRTXModes(bool& IndexedValue);
    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static TArray<FName> CollectUpscaleModes(bool& IndexedValue);
    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static TArray<FName> CollectReflexModes(bool& bNotSupported,
        bool& IndexedValue);
    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static TArray<FName> CollectDLSSRR(bool& IndexedValue);
    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static TArray<FName> CollectDVMModes(bool& IndexedValue);
    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static TArray<FName> CollectNISModes(bool& IndexedValue);
    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static TArray<FName> CollectDLSSFG(bool& bNotSupported, bool& IndexedValue);

    // Upscaling
    static void ApplyUpscaling(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static void SetUpscaleBuiltIn();

    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static void SetUpscaleDLSS();

    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static void ApplyRTX(int32 Index);

    // DLSS mode
    static void SetDLSSMode(UDLSSMode Mode);
    static void SetDLSSDLAAAutoMode(bool DLSSAuto,
        bool DLAAEnabled,
        bool RestoreFullResWhenDisabled);
    static void SetDLSSDLAANoAutoMode(UDLSSMode Mode,
        bool DLAAEnabled,
        bool RestoreFullResWhenDisabled);

    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static void ApplyDLSSMode(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static void ApplyReflexMode(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static void ApplyDLSSRR(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static void ApplyDVM(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static void ApplyNISMode(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static void ApplyDLSSFG(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static ENVIDIASettings ConvertByteToNVIDIA(uint8 SettingType, bool& Contains);

    UFUNCTION(BlueprintCallable,
        Category = "RPG Engine DLSS",
        meta = (DisplayName = "Try Apply Index Settings NVIDIA"))
    static void TryToApplyIndexedNVIDIASetting(uint8 SettingType,
        int32 Index,
        bool& isNVIDIA);

    UFUNCTION(BlueprintCallable,
        Category = "RPG Engine DLSS",
        meta = (DisplayName = "Try Apply Float Settings NVIDIA"))
    static void TryToApplyFloatNVIDIASettings(uint8 SettingType,
        float Value,
        bool& isNVIDIA);

    UFUNCTION(BlueprintCallable,
        Category = "RPG Engine DLSS",
        meta = (DisplayName = "Update Actual Upscale Static Value"))
    static void UpdateActualUpscaleStaticValue(EUpscaleModes ActualUpscale);

    UFUNCTION(BlueprintCallable,
        Category = "RPG Engine DLSS",
        meta = (DisplayName = "Try Collect Variants NVIDIA Parameters"))
    static TArray<FName> TryToCollectVariantsNVIDIAParameters(uint8 SettingType,
        bool& NotSupported,
        bool& IndexedData,
        bool& isNVIDIA);

    // Float parameters
    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static void ApplyDLSSSharpness(float Value);

    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static void ApplyDVI(float Value);

    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static void ApplyNISCustomResolution(float Value);

    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static void ApplyNISSharpness(float Value);

    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static void ApplyDeepDVCSaturationBoost(float Value);

    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static void ApplyNISCustomScreenPercentage(float Value);

    // Converters
    static UDLSSMode ConvertByteToDLSSMode(uint8 Byte);
    static EStreamlineReflexMode ConvertByteToReflexMode(uint8 Byte);
    static UNISMode ConvertByteToNISMode(uint8 Byte);
    static EStreamlineDeepDVCMode ConvertByteToDeepDVC(uint8 Byte);

    // Getters (BP_DA_Settings_Master)
    UFUNCTION(BlueprintCallable, Category = "RPG Engine DLSS")
    static int32 GetIndexedSettingNVIDIA(uint8 SettingType,
        bool& IsNvidia,
        bool RTX,
        const uint8 DLSS,
        const uint8 NISMode,
        const uint8 Upscaling,
        const bool DLSSRRInput,
        const uint8 DLSSFGMode,
        const uint8 DeepDVC,
        const uint8 ReflexMode);

    static int32 GetNISMode(uint8 NISMode);
    static EStreamlineDLSSGMode GetDLSSFGMode(uint8 DLSSFG);
    static int32 GetSupportedDLSSFGModes(uint8 Byte);

    // Widgets
    static bool OnValueComittedDLSSFG(int32 Index, bool& Visible);

    // Logger
    static void Log(const FString& Message)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
    }

    // Helpers
    static void SetConsoleVariableInt(FString Name, int32 Value);

    static void SetConsoleVariableFloat(FString Name, float Value);

protected:
    static EUpscaleModes CurrentUpscaleMode;
};
