// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCECheatManager.h"

#include "AndreiGrbCodeExample/HUD/DebugWidget/AGCEDebugWidget.h"

void UAGCECheatManager::InitCheatManager()
{
	Super::InitCheatManager();

	if(GetOuterAPlayerController()->HasAuthority())
	{
		if(!DebugRPCActorClass.IsNull() && PlayerControllerForRPC.Get())
		{
			UClass* LoadedRPCActorClass = DebugRPCActorClass.LoadSynchronous();

			FActorSpawnParameters ActorSpawnParam;
			ActorSpawnParam.Owner = GetOuterAPlayerController();

			GetWorld()->SpawnActor<AActor>(LoadedRPCActorClass, FVector(), FRotator(), ActorSpawnParam);
		}
	}
}

void UAGCECheatManager::CreateDebugWidget()
{
	if (!DebugWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("UAGCECheatManager::CreateDebugWidget() DebugWidgetClass = nullptr"));
		return;
	}

	if(!IsValid(DebugWidgetPtr))
		DebugWidgetPtr = CreateWidget<UAGCEDebugWidget>(GetOuterAPlayerController(), DebugWidgetClass);

	if(DebugWidgetPtr)
	{
		DebugWidgetPtr->AddToViewport(DebugWidgetZOrder);
	}
}
