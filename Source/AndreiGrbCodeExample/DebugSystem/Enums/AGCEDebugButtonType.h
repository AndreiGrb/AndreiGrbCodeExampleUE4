// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"

UENUM(BlueprintType)
enum class EDebugButtonType : uint8
{
    BUTTON_SUBCAT UMETA(DisplayName = "Subcat"),
    BUTTON_REGULAR UMETA(DisplayName = "Regular"),
    BUTTON_RADIO UMETA(DisplayName = "Radio"),
    BUTTON_RADIOTOGGLE UMETA(DisplayName = "RadioPlusToggle"),
    BUTTON_TOGGLE UMETA(DisplayName = "Toggle"),
    BUTTON_HIDDEN UMETA(DisplayName = "Hidden")
};