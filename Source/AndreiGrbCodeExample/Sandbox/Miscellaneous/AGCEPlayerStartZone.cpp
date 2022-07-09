// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCEPlayerStartZone.h"
#include "Components/BillboardComponent.h"
#include "Components/ShapeComponent.h"
#include "Kismet/KismetMathLibrary.h"


AAGCEPlayerStartZone::AAGCEPlayerStartZone()
{
	ConstructorHelpers::FObjectFinder<UTexture2D> PlayerStartTextureObject(TEXT("/Engine/EditorResources/S_Player"));
	if(PlayerStartTextureObject.Succeeded())
		GetSpriteComponent()->Sprite = PlayerStartTextureObject.Object;
}

FVector AAGCEPlayerStartZone::GetRandomSpawnPointInZone() const
{
	const FVector BoxExtent = GetCollisionComponent()->GetCollisionShape().GetBox();
	FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), BoxExtent);

	RandomPoint.Z = GetActorLocation().Z;
	
	return RandomPoint;
}



