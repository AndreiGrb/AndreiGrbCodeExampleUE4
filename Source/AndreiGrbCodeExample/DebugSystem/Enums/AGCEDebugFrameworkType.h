// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"

UENUM(BlueprintType)
enum class EAGCEDebugType : uint8
{
    DEBUG_MAINMENU UMETA(DisplayName = "MainMenu"),
    DEBUG_SANDBOX UMETA(DisplayName = "Sandbox")
};