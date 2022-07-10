// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCEDebugChangeMap.h"

#include "Kismet/GameplayStatics.h"

void UAGCEDebugChangeMap::ButtonPressLogic_Implementation()
{
	const FString PrintString = TEXT("Opening ") + Level.GetAssetName();
	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Magenta, PrintString);

	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Level, true, TEXT("listen"));
}
