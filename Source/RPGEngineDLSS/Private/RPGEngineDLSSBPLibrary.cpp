// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGEngineDLSSBPLibrary.h"

URPGEngineDLSSBPLibrary::URPGEngineDLSSBPLibrary(
    const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

EUpscaleModes URPGEngineDLSSBPLibrary::CurrentUpscaleMode = EUpscaleModes::DLSS;

TArray<FName>
URPGEngineDLSSBPLibrary::CollectDLSSModes(bool& IndexedValue)
{
    TArray<FName> DLSSModes;
    for (int i = 0; i < UDLSSLibrary::GetSupportedDLSSModes().Num(); i++) {
        FString Data =
            *UEnum::GetDisplayValueAsText(UDLSSLibrary::GetSupportedDLSSModes()[i])
            .ToString();
        DLSSModes.Add(FName(Data));
    }
    DLSSModes.Add(FName("Auto"));
    IndexedValue = true;
    return DLSSModes;
}

TArray<FName>
URPGEngineDLSSBPLibrary::CollectRTXModes(bool& IndexedValue)
{
    IndexedValue = true;
    return { "0", "1" };
}

TArray<FName>
URPGEngineDLSSBPLibrary::CollectUpscaleModes(bool& IndexedValue)
{
    TArray<FName> UpscaleModes;

    const UEnum* EnumPtr = StaticEnum<EUpscaleModes>();
    if (!EnumPtr)
        return UpscaleModes;

    for (int32 i = 0; i < EnumPtr->NumEnums() - 1; i++) {
        EUpscaleModes Mode =
            static_cast<EUpscaleModes>(EnumPtr->GetValueByIndex(i));
        FString FMode = EnumPtr->GetDisplayNameTextByIndex(i).ToString();

        switch (Mode) {
        case EUpscaleModes::BuiltIn:
            UpscaleModes.Add(FName("BuiltIn"));
            break;

        case EUpscaleModes::DLSS:

            if (UDLSSLibrary::IsDLSSSupported() == true) {
                UpscaleModes.Add(FName("DLSS"));
                //Log("DLSS YES");
            }
            else {
                //Log("DLSS NOT");
            }
            break;

        case EUpscaleModes::ImageScaling:
            if (UNISLibrary::IsNISSupported()) {
                UpscaleModes.Add(FName("ImageScaling"));
            }
            break;
        }
    }
    IndexedValue = true;
    return UpscaleModes;
}

TArray<FName>
URPGEngineDLSSBPLibrary::CollectReflexModes(bool& bNotSupported,
    bool& IndexedValue)
{
    TArray<FName> ReflexModes;

    for (int i = 0; i < UStreamlineLibraryReflex::GetSupportedReflexModes().Num();
        i++) {
        FString Data = *UEnum::GetDisplayValueAsText(
            UStreamlineLibraryReflex::GetSupportedReflexModes()[i])
            .ToString();
        ReflexModes.Add(FName(Data));
    }
    bNotSupported = !(UStreamlineLibraryReflex::IsReflexSupported());
    IndexedValue = true;

    return ReflexModes;
}

TArray<FName>
URPGEngineDLSSBPLibrary::CollectDLSSRR(bool& IndexedValue)
{
    IndexedValue = true;
    return { "0", "1" };
}

TArray<FName>
URPGEngineDLSSBPLibrary::CollectDVMModes(bool& IndexedValue)
{
    TArray<FName> DVAModes;

    for (int i = 0;
        i < UStreamlineLibraryDeepDVC::GetSupportedDeepDVCModes().Num();
        i++) {
        FString Data = *UEnum::GetDisplayValueAsText(
            UStreamlineLibraryDeepDVC::GetSupportedDeepDVCModes()[i])
            .ToString();
        DVAModes.Add(FName(Data));
    }
    IndexedValue = true;
    return DVAModes;
}

TArray<FName>
URPGEngineDLSSBPLibrary::CollectNISModes(bool& IndexedValue)
{
    TArray<FName> NISModes;

    for (int i = 0; i < UNISLibrary::GetSupportedNISModes().Num(); i++) {
        FString Data =
            *UEnum::GetDisplayValueAsText(UNISLibrary::GetSupportedNISModes()[i])
            .ToString();
        NISModes.Add(FName(Data));
    }
    IndexedValue = true;
    return NISModes;
}

TArray<FName>
URPGEngineDLSSBPLibrary::CollectDLSSFG(bool& bNotSupported, bool& IndexedValue)
{
    TArray<FName> DLSSFGModes;
    if ((UStreamlineLibraryDLSSG::GetSupportedDLSSGModes().Num() == 1) &&
        (UStreamlineLibraryDLSSG::GetSupportedDLSSGModes()[0] ==
            EStreamlineDLSSGMode::Off)) {
        bNotSupported = true;
        return DLSSFGModes;
    }
    else {
        for (int i = 0; i < UStreamlineLibraryDLSSG::GetSupportedDLSSGModes().Num();
            i++) {
            FString Data = *UEnum::GetDisplayValueAsText(
                UStreamlineLibraryDLSSG::GetSupportedDLSSGModes()[i])
                .ToString();
            DLSSFGModes.Add(FName(Data));
        }
        bNotSupported = false;
        IndexedValue = true;
        return DLSSFGModes;
    }
}

ENVIDIASettings
URPGEngineDLSSBPLibrary::ConvertByteToNVIDIA(uint8 SettingType, bool& Contains)
{
    ENVIDIASettings NvidiaOutput = ENVIDIASettings::DLSS;
    Contains = true;
    if (SettingType < 24 || SettingType > 37) {
        Contains = false;
        return NvidiaOutput;
    }
    switch (SettingType) {
    case 24:
        NvidiaOutput = ENVIDIASettings::RTX;
        break;

    case 25:
        NvidiaOutput = ENVIDIASettings::Upscaling;
        break;

    case 26:
        NvidiaOutput = ENVIDIASettings::DLSS;
        break;

    case 27:
        NvidiaOutput = ENVIDIASettings::DLSSSharpness;
        break;

    case 28:
        NvidiaOutput = ENVIDIASettings::ReflexMode;
        break;

    case 29:
        NvidiaOutput = ENVIDIASettings::DLSSRR;
        break;

    case 30:
        NvidiaOutput = ENVIDIASettings::DVM;
        break;

    case 31:
        NvidiaOutput = ENVIDIASettings::DVI;
        break;

    case 32:
        NvidiaOutput = ENVIDIASettings::NISMode;
        break;

    case 33:
        NvidiaOutput = ENVIDIASettings::NISCustomResolution;
        break;

    case 34:
        NvidiaOutput = ENVIDIASettings::NISSharpness;
        break;

    case 35:
        NvidiaOutput = ENVIDIASettings::DVSB;
        break;

    case 36:
        NvidiaOutput = ENVIDIASettings::ResolutionScale;
        break;

    case 37:
        NvidiaOutput = ENVIDIASettings::DLSSFG;
        break;
    }
    return NvidiaOutput;
}

void
URPGEngineDLSSBPLibrary::TryToApplyIndexedNVIDIASetting(uint8 SettingType,
    int32 Index,
    bool& isNvidia)
{
    bool Contains;
    ENVIDIASettings SettingNVIDIA = ConvertByteToNVIDIA(SettingType, Contains);
    if (!Contains) {
        isNvidia = false;
        return;
    }

    switch (SettingNVIDIA) {
    case ENVIDIASettings::RTX:
        ApplyRTX(Index);
        isNvidia = true;
        return;

    case ENVIDIASettings::Upscaling:
        ApplyUpscaling(Index);
        isNvidia = true;
        return;

    case ENVIDIASettings::DLSS:
        ApplyDLSSMode(Index);
        isNvidia = true;
        return;

    case ENVIDIASettings::DLSSSharpness:

        return;

    case ENVIDIASettings::ReflexMode:
        ApplyReflexMode(Index);
        isNvidia = true;
        return;

    case ENVIDIASettings::DLSSRR:
        ApplyDLSSRR(Index);
        isNvidia = true;
        return;

    case ENVIDIASettings::DVM:
        ApplyDVM(Index);
        isNvidia = true;
        return;

    case ENVIDIASettings::DVI:

        isNvidia = true;
        return;

    case ENVIDIASettings::NISMode:
        ApplyNISMode(Index);
        isNvidia = true;
        return;

    case ENVIDIASettings::NISCustomResolution:

        isNvidia = true;
        return;

    case ENVIDIASettings::NISSharpness:

        isNvidia = true;
        return;

    case ENVIDIASettings::DVSB:

        isNvidia = true;
        return;

    case ENVIDIASettings::ResolutionScale:

        isNvidia = true;
        return;

    case ENVIDIASettings::DLSSFG:
        ApplyDLSSFG(Index);
        isNvidia = true;
        return;
    }
    return;
}

void
URPGEngineDLSSBPLibrary::TryToApplyFloatNVIDIASettings(uint8 SettingType,
    float Value,
    bool& isNVIDIA)
{
    bool Contains;
    isNVIDIA = false;
    ENVIDIASettings SettingNVIDIA = ConvertByteToNVIDIA(SettingType, Contains);
    if (!Contains) {
        return;
    }

    switch (SettingNVIDIA) {
    case ENVIDIASettings::RTX:

        break;

    case ENVIDIASettings::Upscaling:

        break;

    case ENVIDIASettings::DLSS:

        break;

    case ENVIDIASettings::DLSSSharpness:
        isNVIDIA = true;
        ApplyDLSSSharpness(Value);
        break;

    case ENVIDIASettings::ReflexMode:

        break;

    case ENVIDIASettings::DLSSRR:

        break;

    case ENVIDIASettings::DVM:

        break;

    case ENVIDIASettings::DVI:
        isNVIDIA = true;
        ApplyDVI(Value);
        break;

    case ENVIDIASettings::NISMode:

        break;

    case ENVIDIASettings::NISCustomResolution:
        isNVIDIA = true;
        ApplyNISCustomResolution(Value);
        break;

    case ENVIDIASettings::NISSharpness:
        isNVIDIA = true;
        ApplyNISSharpness(Value);
        break;

    case ENVIDIASettings::DVSB:
        isNVIDIA = true;
        ApplyDeepDVCSaturationBoost(Value);
        break;

    case ENVIDIASettings::ResolutionScale:
        isNVIDIA = true;
        ApplyNISCustomScreenPercentage(Value);
        break;

    case ENVIDIASettings::DLSSFG:
        break;
    }
    return;
}

void
URPGEngineDLSSBPLibrary::UpdateActualUpscaleStaticValue(
    EUpscaleModes ActualUpscale)
{
    CurrentUpscaleMode = ActualUpscale;
}

TArray<FName>
URPGEngineDLSSBPLibrary::TryToCollectVariantsNVIDIAParameters(
    uint8 RPGEngineSettingType,
    bool& NotSupported,
    bool& IndexedData,
    bool& isNVIDIA)
{
    TArray<FName> Parameters;
    isNVIDIA = false;
    bool Contains;

    ENVIDIASettings SettingNVIDIA =
        ConvertByteToNVIDIA(RPGEngineSettingType, Contains);
    if (!Contains) {
        return Parameters;
    }

    switch (SettingNVIDIA) {
    case ENVIDIASettings::RTX:
        Parameters = CollectRTXModes(IndexedData);
        isNVIDIA = true;
        break;

    case ENVIDIASettings::Upscaling:
        Parameters = CollectUpscaleModes(IndexedData);
        isNVIDIA = true;
        break;

    case ENVIDIASettings::DLSS:
        Parameters = CollectDLSSModes(IndexedData);
        isNVIDIA = true;
        break;

    case ENVIDIASettings::DLSSSharpness:
        isNVIDIA = true;
        IndexedData = false;
        break;

    case ENVIDIASettings::ReflexMode:
        Parameters = CollectReflexModes(NotSupported, IndexedData);
        isNVIDIA = true;
        break;

    case ENVIDIASettings::DLSSRR:
        Parameters = CollectDLSSRR(IndexedData);
        isNVIDIA = true;
        break;

    case ENVIDIASettings::DVM:
        Parameters = CollectDVMModes(IndexedData);
        isNVIDIA = true;
        break;

    case ENVIDIASettings::DVI:
        IndexedData = false;
        isNVIDIA = true;
        break;

    case ENVIDIASettings::NISMode:
        Parameters = CollectNISModes(IndexedData);
        isNVIDIA = true;
        break;

    case ENVIDIASettings::NISCustomResolution:
        IndexedData = false;
        isNVIDIA = true;
        break;

    case ENVIDIASettings::NISSharpness:
        IndexedData = false;
        isNVIDIA = true;
        break;

    case ENVIDIASettings::DVSB:
        IndexedData = false;
        isNVIDIA = true;
        break;

    case ENVIDIASettings::ResolutionScale:
        IndexedData = false;
        isNVIDIA = true;
        break;

    case ENVIDIASettings::DLSSFG:
        Parameters = CollectDLSSFG(NotSupported, IndexedData);
        isNVIDIA = true;
        break;
    }

    return Parameters;
}

void
URPGEngineDLSSBPLibrary::ApplyRTX(int32 Index)
{
    // Log("ApplyRTX");
    switch (Index) {
    case 0:
        SetConsoleVariableInt("r.RayTracing.ForceAllRayTracingEffects", 0);
        SetConsoleVariableInt("r.Lumen.HardwareRayTracing", 0);
        break;

    case 1:
        SetConsoleVariableInt("r.RayTracing.ForceAllRayTracingEffects", -1);
        SetConsoleVariableInt("r.Lumen.HardwareRayTracing", 1);
        break;
    }
}

// Upscaling
void
URPGEngineDLSSBPLibrary::SetUpscaleBuiltIn()
{

    SetDLSSMode(UDLSSMode::Off);
    UNISLibrary::SetNISMode(UNISMode::Off);
    UNISLibrary::SetNISSharpness(0);

    SetConsoleVariableFloat("r.ScreenPercentage", 100.f);
    SetConsoleVariableInt("r.AntiAliasingMethod", 2);
}

void
URPGEngineDLSSBPLibrary::SetUpscaleDLSS()
{
    SetDLSSMode(UDLSSLibrary::GetDefaultDLSSMode());
    UNISLibrary::SetNISSharpness(0.f);

    SetConsoleVariableInt("r.AntiAliasingMethod", 4);
}

void
URPGEngineDLSSBPLibrary::ApplyUpscaling(int32 Index)
{
    // Log("ApplyUpscaling");

    switch (Index) {
    case 0:
        SetUpscaleBuiltIn();
        break;

    case 1:
        SetUpscaleDLSS();
        break;

    case 2:
        UNISLibrary::SetNISMode(UNISLibrary::GetDefaultNISMode());
        break;
    }
    return;
}

// DLSS

void
URPGEngineDLSSBPLibrary::ApplyDLSSMode(int32 Index)
{

    if (CurrentUpscaleMode == EUpscaleModes::DLSS) {
        TArray<UDLSSMode> Mode = UDLSSLibrary::GetSupportedDLSSModes();

        if (!Mode.IsValidIndex(Index)) {
            //Log("AUTO DLSS MODE");
            SetDLSSMode(UDLSSMode::Auto);
        }
        else {
            /*Log(*UEnum::GetDisplayValueAsText(
                UDLSSLibrary::GetSupportedDLSSModes()[Index])
                .ToString());*/
            //Log("NEW DLSS MODE");
            SetDLSSMode(Mode[Index]);
        }

        if (!UDLSSLibrary::IsDLSSEnabled()) {
            UDLSSLibrary::EnableDLSSRR(false);
        }
    }
}

void
URPGEngineDLSSBPLibrary::SetDLSSMode(UDLSSMode Mode)
{
    if (Mode == UDLSSMode::Auto) {
        SetDLSSDLAAAutoMode(true, false, true);
        //Log("SetDLSS AUTO Mode");
    }
    else {
        SetDLSSDLAANoAutoMode(Mode, false, true);
    }
}

void
URPGEngineDLSSBPLibrary::SetDLSSDLAAAutoMode(bool DLSSAuto,
    bool DLAAEnabled,
    bool RestoreFullResWhenDisabled)
{
    FVector2D ViewportSize;
    GEngine->GameViewport->GetViewportSize(ViewportSize);

    bool bIsSupported;
    bool bIsFixedPercentage;
    bool bEnableDLSSRR;

    float OptimalScreenPercentage;
    float MinScreenPercentage;
    float MaxScreenPercentage;
    float OptimalSharpness;

    UDLSSLibrary::GetDLSSModeInformation(UDLSSMode::Auto,
        ViewportSize,
        bIsSupported,
        OptimalScreenPercentage,
        bIsFixedPercentage,
        MinScreenPercentage,
        MaxScreenPercentage,
        OptimalSharpness);

    bEnableDLSSRR = (OptimalScreenPercentage > 0 && DLSSAuto) || DLAAEnabled;

    UDLSSLibrary::EnableDLSSRR(bEnableDLSSRR);

    // Set DLSS/DLAA (auto mode)
    if (bEnableDLSSRR || RestoreFullResWhenDisabled) {
        float CommandValue;
        if (!(OptimalScreenPercentage > 0 && DLSSAuto == true) ||
            DLAAEnabled == true) {
            CommandValue = 100.f;
        }
        else {
            CommandValue = OptimalScreenPercentage;
        }

        SetConsoleVariableFloat("r.ScreenPercentage", CommandValue);
    }
    else
        return;
}

void
URPGEngineDLSSBPLibrary::SetDLSSDLAANoAutoMode(UDLSSMode Mode,
    bool DLAAEnabled,
    bool RestoreFullResWhenDisabled)
{
    bool bIsSupported;
    bool bIsFixedPercentage;
    bool bEnableDLSSRR;

    float OptimalScreenPercentage;
    float MinScreenPercentage;
    float MaxScreenPercentage;
    float OptimalSharpness;

    UDLSSLibrary::GetDLSSModeInformation(Mode,
        FVector2D(0, 0),
        bIsSupported,
        OptimalScreenPercentage,
        bIsFixedPercentage,
        MinScreenPercentage,
        MaxScreenPercentage,
        OptimalSharpness);

    bEnableDLSSRR = !(Mode == UDLSSMode::Off) || (DLAAEnabled);
    UDLSSLibrary::EnableDLSSRR(bEnableDLSSRR);

    if (bEnableDLSSRR || RestoreFullResWhenDisabled == true) {
        float CommandValue;
        if ((Mode == UDLSSMode::Off) || DLAAEnabled == true) {
            //Log("SetDLSS Mode OFF");
            CommandValue = 100.f;
        }
        else {
            CommandValue = OptimalScreenPercentage;
            //Log("SetDLSS Mode ON");
        }
        SetConsoleVariableFloat("r.ScreenPercentage", CommandValue);
        //Log(FString::SanitizeFloat(CommandValue, 2));
    }
    else
        return;
}

// Reflex
void
URPGEngineDLSSBPLibrary::ApplyReflexMode(int32 Index)
{
    TArray<EStreamlineReflexMode> Modes =
        UStreamlineLibraryReflex::GetSupportedReflexModes();
    UStreamlineLibraryReflex::SetReflexMode(Modes[Index]);
}

// DLSS RR
void
URPGEngineDLSSBPLibrary::ApplyDLSSRR(int32 Index)
{
    bool bValue;
    switch (Index) {
    case 0:
        bValue = false;
        break;
    case 1:
        bValue = true;
        break;
    }
    UDLSSLibrary::EnableDLSSRR(bValue);
}

void
URPGEngineDLSSBPLibrary::ApplyDVM(int32 Index)
{
    EStreamlineDeepDVCMode Value;
    switch (Index) {
    case 0:
        Value = EStreamlineDeepDVCMode::Off;
        break;
    case 1:
        Value = EStreamlineDeepDVCMode::On;
        break;
    }
    UStreamlineLibraryDeepDVC::SetDeepDVCMode(Value);
}

void
URPGEngineDLSSBPLibrary::ApplyNISMode(int32 Index)
{

    if (CurrentUpscaleMode == EUpscaleModes::ImageScaling) {
        if (!UNISLibrary::GetSupportedNISModes().IsValidIndex(Index)) {
            return;
        }

        UNISLibrary::SetNISMode(static_cast<UNISMode>(Index));

        if (static_cast<UNISMode>(Index) == UNISMode::Off) {
            SetConsoleVariableFloat("r.ScreenPercentage", 100);
        }
    }
}

// DLSS Frame Generation - RTX 40xx ++
void
URPGEngineDLSSBPLibrary::ApplyDLSSFG(int32 Index)
{
    TArray<EStreamlineDLSSGMode> Modes =
        UStreamlineLibraryDLSSG::GetSupportedDLSSGModes();
    if (Modes.IsValidIndex(Index)) {
        UStreamlineLibraryDLSSG::SetDLSSGMode(Modes[Index]);
    }
}

// Float parameters

void
URPGEngineDLSSBPLibrary::ApplyDLSSSharpness(float Value)
{
    if (CurrentUpscaleMode == EUpscaleModes::DLSS) {
        UNISLibrary::SetNISSharpness(Value);
    }
}

void
URPGEngineDLSSBPLibrary::ApplyDVI(float Value)
{
    UStreamlineLibraryDeepDVC::SetDeepDVCIntensity(Value);
}

void
URPGEngineDLSSBPLibrary::ApplyNISCustomResolution(float Value)
{
    if (CurrentUpscaleMode == EUpscaleModes::ImageScaling) {
        UNISLibrary::SetNISCustomScreenPercentage(Value);
    }
}

void
URPGEngineDLSSBPLibrary::ApplyNISSharpness(float Value)
{

    if (CurrentUpscaleMode == EUpscaleModes::ImageScaling) {
        UNISLibrary::SetNISSharpness(Value);
    }
}

void
URPGEngineDLSSBPLibrary::ApplyDeepDVCSaturationBoost(float Value)
{
    UStreamlineLibraryDeepDVC::SetDeepDVCSaturationBoost(Value);
}

void
URPGEngineDLSSBPLibrary::ApplyNISCustomScreenPercentage(float Value)
{
    //Log("Try ApplyNISSharpness");
    UNISLibrary::SetNISCustomScreenPercentage(Value);
}

UDLSSMode
URPGEngineDLSSBPLibrary::ConvertByteToDLSSMode(uint8 Byte)
{
    UDLSSMode Converted;
    switch (Byte) {
    case 0:
        Converted = UDLSSMode::Off;
        break;
    case 1:
        Converted = UDLSSMode::Auto;
        break;
    case 2:
        Converted = UDLSSMode::DLAA;
        break;
    case 3:
        Converted = UDLSSMode::UltraQuality;
        break;
    case 4:
        Converted = UDLSSMode::Quality;
        break;
    case 5:
        Converted = UDLSSMode::Balanced;
        break;
    case 6:
        Converted = UDLSSMode::Performance;
        break;
    case 7:
        Converted = UDLSSMode::UltraPerformance;
        break;
    }
    return Converted;
}

EStreamlineReflexMode
URPGEngineDLSSBPLibrary::ConvertByteToReflexMode(uint8 Byte)
{
    EStreamlineReflexMode Converted;
    switch (Byte) {
    case 0:
        Converted = EStreamlineReflexMode::Off;
        break;

    case 1:
        Converted = EStreamlineReflexMode::Enabled;
        break;

    case 2:
        Converted = EStreamlineReflexMode::Boost;
        break;
    }
    return Converted;
}

EStreamlineDeepDVCMode
URPGEngineDLSSBPLibrary::ConvertByteToDeepDVC(uint8 Byte)
{
    EStreamlineDeepDVCMode Converted;
    switch (Byte) {
    case 0:
        Converted = EStreamlineDeepDVCMode::Off;
        break;

    case 1:
        Converted = EStreamlineDeepDVCMode::On;
        break;
    }
    return Converted;
}

int32
URPGEngineDLSSBPLibrary::GetIndexedSettingNVIDIA(uint8 RPGEngineSettingType,
    bool& IsNvidia,
    bool RTX,
    const uint8 DLSS,
    const uint8 NISMode,
    const uint8 Upscaling,
    const bool DLSSRRInput,
    const uint8 DLSSFGMode,
    const uint8 DeepDVC,
    const uint8 ReflexMode)
{
    int32 ResultIndex = -1;
    IsNvidia = false;
    bool Contains;
    ENVIDIASettings Parameters =
        ConvertByteToNVIDIA(RPGEngineSettingType, Contains);
    if (!Contains) {
        return -1;
    }
    switch (Parameters) {
    case ENVIDIASettings::RTX:
        if (UDLSSLibrary::IsRayTracingAvailable()) {
            switch (RTX) {
            case 0:
                ResultIndex = 0;
                break;
            case 1:
                ResultIndex = 1;
                break;
            }
        }
        else
            ResultIndex = 0;
        IsNvidia = true;
        break;

    case ENVIDIASettings::Upscaling:
        switch (Upscaling) {
            // BuiltIn
        case 0:
            ResultIndex = 0;
            break;

            // DLSS
        case 1:
            if (UDLSSLibrary::IsDLSSSupported()) {
                ResultIndex = 1;
            }
            else
                ResultIndex = 0;
            break;

            // Image Scaling
        case 2:
            if (UNISLibrary::IsNISSupported()) {
                ResultIndex = 2;
            }
            else
                ResultIndex = 0;
            break;
        }
        IsNvidia = true;
        break;

    case ENVIDIASettings::DLSS:

        if (UDLSSLibrary::GetSupportedDLSSModes().Find(
            ConvertByteToDLSSMode(DLSS)) == -1) {
            // Correct?
            ResultIndex =
                UDLSSLibrary::GetSupportedDLSSModes().Find(UDLSSMode::Auto);
        }
        else {
            ResultIndex = UDLSSLibrary::GetSupportedDLSSModes().Find(
                ConvertByteToDLSSMode(DLSS));
        }
        IsNvidia = true;
        break;

    case ENVIDIASettings::DLSSSharpness:
        ResultIndex = 0;
        IsNvidia = true;
        break;

    case ENVIDIASettings::ReflexMode:

        if (UStreamlineLibraryReflex::GetSupportedReflexModes().Find(
            ConvertByteToReflexMode(ReflexMode)) == -1) {
            ResultIndex = 0;
        }
        else {
            ResultIndex = UStreamlineLibraryReflex::GetSupportedReflexModes().Find(
                ConvertByteToReflexMode(ReflexMode));
        }
        IsNvidia = true;
        break;

    case ENVIDIASettings::DLSSRR:
        switch (DLSSRRInput) 
        {
            case false:
                ResultIndex = 0;
            case true:
                ResultIndex = 1;
        }
        IsNvidia = true;
        break;

    case ENVIDIASettings::DVM:

        if (UStreamlineLibraryDeepDVC::IsDeepDVCSupported()) {
            ResultIndex =
                UStreamlineLibraryDeepDVC::GetSupportedDeepDVCModes().Find(
                    ConvertByteToDeepDVC(DeepDVC));
        }
        IsNvidia = true;
        break;

    case ENVIDIASettings::DVI:
        ResultIndex = 0;
        IsNvidia = true;
        break;

    case ENVIDIASettings::NISMode:
        ResultIndex = 0;
        IsNvidia = true;
        break;

    case ENVIDIASettings::NISCustomResolution:
        ResultIndex = 0;
        IsNvidia = true;
        break;

    case ENVIDIASettings::NISSharpness:
        ResultIndex = 0;
        IsNvidia = true;
        break;

    case ENVIDIASettings::DVSB:
        ResultIndex = 0;
        IsNvidia = true;
        break;

    case ENVIDIASettings::ResolutionScale:
        ResultIndex = 0;
        IsNvidia = true;
        break;

    case ENVIDIASettings::DLSSFG:
        ResultIndex = 0;
        IsNvidia = true;
        break;
    }
    return ResultIndex;
}

UNISMode
URPGEngineDLSSBPLibrary::ConvertByteToNISMode(uint8 NISMode)
{
    UNISMode Mode;
    switch (NISMode) {
    case 0:
        Mode = UNISMode::Off;
        break;
    case 1:
        Mode = UNISMode::UltraQuality;
        break;

    case 2:
        Mode = UNISMode::Balanced;
        break;

    case 3:
        Mode = UNISMode::Performance;
        break;

    case 4:
        Mode = UNISMode::Custom;
        break;
    }
    return Mode;
}

int32
URPGEngineDLSSBPLibrary::GetNISMode(uint8 NISMode)
{
    UNISMode Mode = ConvertByteToNISMode(NISMode);

    int32 Index = UNISLibrary::GetSupportedNISModes().Find(Mode);

    if (Index == -1) {
        return 0;
    }
    else {
        return Index;
    }
}

EStreamlineDLSSGMode
URPGEngineDLSSBPLibrary::GetDLSSFGMode(uint8 DLSSFG)
{
    EStreamlineDLSSGMode Mode;
    switch (DLSSFG) {
    case 0:
        Mode = EStreamlineDLSSGMode::Off;
        break;

    case 1:
        Mode = EStreamlineDLSSGMode::Auto;
        break;

    case 2:
        Mode = EStreamlineDLSSGMode::On2X;
        break;

    case 3:
        Mode = EStreamlineDLSSGMode::On3X;
        break;

    case 4:
        Mode = EStreamlineDLSSGMode::On4X;
        break;
    }
    return Mode;
}

int32
URPGEngineDLSSBPLibrary::GetSupportedDLSSFGModes(uint8 Byte)
{
    return (UStreamlineLibraryDLSSG::GetSupportedDLSSGModes().Find(
        GetDLSSFGMode(Byte)));
}

// Widget

bool
URPGEngineDLSSBPLibrary::OnValueComittedDLSSFG(int32 Index, bool& Visible)
{
    if (UStreamlineLibraryDLSSG::QueryDLSSGSupport() ==
        EStreamlineFeatureSupport::Supported ||
        !UStreamlineLibraryDLSSG::GetSupportedDLSSGModes().IsEmpty()) {
        TArray<EStreamlineDLSSGMode> DLSSModes =
            UStreamlineLibraryDLSSG::GetSupportedDLSSGModes();
        return DLSSModes[Index] == EStreamlineDLSSGMode::Off;
    }
    else {
        return false;
    }
}

void
URPGEngineDLSSBPLibrary::SetConsoleVariableFloat(FString Name, float Value)
{
    if (Name.IsEmpty()) {
        // UE_LOG(LogTemp, Error, TEXT("Console variable name is empty!"));
        return;
    }

    if (IConsoleVariable* ConsoleVariable =
        IConsoleManager::Get().FindConsoleVariable(*Name)) {
        ConsoleVariable->Set(Value, EConsoleVariableFlags::ECVF_SetByConsole);
    }
}

void
URPGEngineDLSSBPLibrary::SetConsoleVariableInt(FString Name, int32 Value)
{
    if (Name.IsEmpty()) {
        UE_LOG(LogTemp, Error, TEXT("Console variable name is empty!"));
        return;
    }

    if (IConsoleVariable* ConsoleVariable =
        IConsoleManager::Get().FindConsoleVariable(*Name)) {
        ConsoleVariable->Set(Value, EConsoleVariableFlags::ECVF_SetByConsole);

        UE_LOG(LogTemp, Log, TEXT("Variable '%s' set to %d"), *Name, Value);
    }
    else {
        UE_LOG(
            LogTemp, Warning, TEXT("Console variable '%s' does not exist!"), *Name);
    }
}
