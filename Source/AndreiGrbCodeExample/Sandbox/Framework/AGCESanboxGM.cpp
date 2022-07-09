// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCESanboxGM.h"

#include "AndreiGrbCodeExample/Sandbox/Miscellaneous/AGCEPlayerStartZone.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void AAGCESanboxGM::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, AAGCEPlayerStartZone::StaticClass(), OutActors);

	for(AActor* StartZoneAsActor : OutActors)
	{
		PlayerStartingZones.Add(Cast<AAGCEPlayerStartZone>(StartZoneAsActor));
	}
}

void AAGCESanboxGM::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	if (NewPlayer->IsPendingKillPending())
	{
		return;
	}

	PlayerControllers.Add(NewPlayer);
	
	// If players should start as spectators, leave them in the spectator state
	if (!bStartPlayersAsSpectators && !MustSpectate(NewPlayer) && PlayerCanRestart(NewPlayer))
	{
		// Otherwise spawn their pawn immediately
		SpawnNewPlayer(NewPlayer);
	}
}

void AAGCESanboxGM::SpawnNewPlayer(APlayerController* NewPlayer)
{
	FTransform SpawnPoint;

	//if less or equal 4 players, get SpawnPoint at specific Player Start
	if(PlayerControllers.Num() <= 4)
	{
		const FString PlayerNumber = FString::FromInt(PlayerControllers.Num());
		if(const AActor* FoundPlayerStart = FindPlayerStart(NewPlayer, PlayerNumber))
		{
			SpawnPoint = GetSpawnPointFromActor(FoundPlayerStart);
		}
		//if couldn't found specific Player Start, find some random Player Start
		else if(const AActor* FoundRandomPlayerStart = FindPlayerStart(NewPlayer))
		{
			SpawnPoint = GetSpawnPointFromActor(FoundRandomPlayerStart);
		}
		//if no Player Start exist, try finding Player Starting Zone
		else if(PlayerStartingZones.Num() > 0)
		{
			SpawnPoint = GetSpawnPointFromStartingZone();
		}
	}
	//if more then 4 players, get SpawnPoint at random Player Starting Zone
	else if(PlayerStartingZones.Num() > 0)
	{
		SpawnPoint = GetSpawnPointFromStartingZone();
	}
	//if more then 4 players and no Player Starting Zones exist, get SpawnPoint at regular Player Start
	else if(const AActor* FoundPlayerStart = FindPlayerStart(NewPlayer))
	{
		SpawnPoint = GetSpawnPointFromActor(FoundPlayerStart);
	}

	if(!SpawnPoint.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("AAGCESanboxGM::HandleStartingNewPlayer: Couldn't found player start!"));
		return;
	}

	if (GetDefaultPawnClassForController(NewPlayer) != nullptr)
	{
		NewPlayer->SetPawn(SpawnDefaultPawnAtTransform(NewPlayer, SpawnPoint));
		NewPlayer->Possess(NewPlayer->GetPawn());
	}
}

FTransform AAGCESanboxGM::GetSpawnPointFromStartingZone() const
{
	FTransform ReturnValue;
	
	const int32 RandomIndex = UKismetMathLibrary::RandomInteger(PlayerStartingZones.Num());
			
	if(const AAGCEPlayerStartZone* StartingZone = PlayerStartingZones[RandomIndex])
	{
		const FVector SpawnPointLocation = StartingZone->GetRandomSpawnPointInZone();
		const FRotator SpawnPointRotation = StartingZone->GetActorRotation();

		ReturnValue = FTransform(SpawnPointRotation, SpawnPointLocation);
	}

	return ReturnValue;
}

FTransform AAGCESanboxGM::GetSpawnPointFromActor(const AActor* _Actor) const
{
	const FVector SpawnPointLocation = _Actor->GetActorLocation();
	const FRotator SpawnPointRotation = _Actor->GetActorRotation();
	const FVector SpawnPointScale = _Actor->GetActorScale3D();
				
	return FTransform(SpawnPointRotation, SpawnPointLocation, SpawnPointScale);
}
