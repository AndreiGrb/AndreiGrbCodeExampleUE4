// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCESanboxGM.h"

#include "AndreiGrbCodeExample/Sandbox/Miscellaneous/AGCEPlayerStartZone.h"
#include "AndreiGrbCodeExample/Sandbox/Player/AGCEPlayer.h"
#include "GameFramework/PlayerStart.h"
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

void AAGCESanboxGM::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	APlayerController* ExitingPlayer = Cast<APlayerController>(Exiting);

	PlayerControllers.Remove(Cast<APlayerController>(ExitingPlayer));
}

void AAGCESanboxGM::SpawnNewPlayer(APlayerController* NewPlayer)
{
	bIsSpawnPointSet = false;

	const int32 PlayerNumber = PlayerControllers.Num();

	//if less or equal 4 players, get SpawnPoint at specific Player Start
	if(PlayerControllers.Num() <= 4)
	{
		const FString PlayerNumberAsString = FString::FromInt(PlayerNumber);
		if(const AActor* FoundPlayerStart = FindPlayerStart(NewPlayer, PlayerNumberAsString))
		{
			if(Cast<APlayerStart>(FoundPlayerStart)->PlayerStartTag.ToString().Equals(PlayerNumberAsString))
			{
				SetSpawnPoint(GetSpawnPointFromActor(FoundPlayerStart));
			}
		}
	}
	//if more then 4 players, get SpawnPoint at random Player Starting Zone
	if(!bIsSpawnPointSet && PlayerStartingZones.Num() > 0)
	{
		SetSpawnPoint(GetSpawnPointFromStartingZone());
	}
	//if more then 4 players and no Player Starting Zones exist, get SpawnPoint at regular Player Start
	else if(const AActor* FoundPlayerStart = FindPlayerStart(NewPlayer))
	{
		if(!bIsSpawnPointSet)	
			SetSpawnPoint(GetSpawnPointFromActor(FoundPlayerStart));
	}

	if(!bIsSpawnPointSet)
	{
		UE_LOG(LogTemp, Error, TEXT("AAGCESanboxGM::HandleStartingNewPlayer: Couldn't found player start!"));
		return;
	}

	if (GetDefaultPawnClassForController(NewPlayer) != nullptr)
	{
		NewPlayer->SetPawn(SpawnDefaultPawnAtTransform(NewPlayer, SpawnPoint));
		NewPlayer->Possess(NewPlayer->GetPawn());
		
		if(AAGCEPlayer* PlayerCharacter = Cast<AAGCEPlayer>(NewPlayer->GetPawn()))
		{
			PlayerCharacter->PlayerNumber = PlayerNumber;
			if(!IsRunningDedicatedServer())	
				PlayerCharacter->SetPlayerColor(); //set player color if standalone or listen server
		}
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
