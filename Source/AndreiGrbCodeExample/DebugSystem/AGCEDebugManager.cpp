// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCEDebugManager.h"

#include "AGCEDebugActor.h"
#include "AndreiGrbCodeExample/HUD/DebugWidget/AGCEDebugWidget.h"

void UAGCEDebugManager::InitCheatManager()
{
	Super::InitCheatManager();

	if(GetOuterAPlayerController()->HasAuthority() && DebugActorClass)
	{
		FActorSpawnParameters ActorSpawnParam;
		ActorSpawnParam.Owner = GetOuterAPlayerController();

		DebugActorPtr = GetWorld()->SpawnActor<AAGCEDebugActor>(DebugActorClass, FVector(), FRotator(), ActorSpawnParam);
	}
}

void UAGCEDebugManager::CreateDebugWidget()
{
	if (!DebugWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("UAGCEDebugManager::CreateDebugWidget() DebugWidgetClass = nullptr"));
		return;
	}

	if(!IsValid(DebugWidgetPtr))
		DebugWidgetPtr = CreateWidget<UAGCEDebugWidget>(GetOuterAPlayerController(), DebugWidgetClass);

	if(DebugWidgetPtr)
	{
		DebugWidgetPtr->AddToViewport(DebugWidgetZOrder);
	}
}
