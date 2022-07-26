// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCEDebugActor.h"

#include "AGCEDebugManager.h"
#include "AndreiGrbCodeExample/HUD/DebugWidget/AGCEDebugWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Structures/AGCEDebugButtonStruct.h"


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

void AAGCEDebugActor::LoadDebugLogicListServer_Implementation(TSoftObjectPtr<UDataTable> DataTableToLoad)
{
	if(DataTableToLoad.IsNull())
		return;

	UDataTable* DataTable = DataTableToLoad.LoadSynchronous();
	
	TArray<FDebugButtonStruct*> DebugButtonsArray;
	DataTable->GetAllRows<FDebugButtonStruct>(FString("Context"), DebugButtonsArray);

	for(FDebugButtonStruct* DebugButton : DebugButtonsArray)
	{
		if(!DebugButton)
		{
			UE_LOG(LogTemp, Error,
			       TEXT("AAGCEDebugActor::LoadDebugLogicListServer: DataTableToLoad is not FDebugButtonStruct type"));
			return;
		}

		//DebugButton->ButtonLogic;
	}
}
