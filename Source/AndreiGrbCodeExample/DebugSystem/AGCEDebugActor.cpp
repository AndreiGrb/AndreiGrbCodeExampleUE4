// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCEDebugActor.h"

#include "AGCEDebugManager.h"
#include "AndreiGrbCodeExample/HUD/DebugWidget/AGCEDebugWidget.h"
#include "Kismet/GameplayStatics.h"


AAGCEDebugActor::AAGCEDebugActor()
{
	//PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bOnlyRelevantToOwner = true;
}

void AAGCEDebugActor::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
	if(PlayerController->IsLocalController())
	{
		if(UCheatManager* CheatManager = PlayerController->CheatManager)
		{
			if(UAGCEDebugManager* DebugManager = Cast<UAGCEDebugManager>(CheatManager))
				DebugManager->GetDebugButtonWidget()->SetIsEnabled(true);
		}
	}
}
