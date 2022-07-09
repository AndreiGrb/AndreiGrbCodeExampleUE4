// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCEPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AAGCEPlayer::AAGCEPlayer()
{
	//PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(0.f,0.f,8.492264));
	CameraBoom->bUsePawnControlRotation = true;

	TPCamera = CreateDefaultSubobject<UCameraComponent>("TPCamera");
	TPCamera->SetupAttachment(CameraBoom);
}

void AAGCEPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("GamepadTurn", this, &AAGCEPlayer::GamepadTurn);
	PlayerInputComponent->BindAxis("GamepadLookUp", this, &AAGCEPlayer::GamepadLookUp);
	PlayerInputComponent->BindAxis("MouseTurn", this, &AAGCEPlayer::MouseTurn);
	PlayerInputComponent->BindAxis("MouseLookUp", this, &AAGCEPlayer::MouseLookUp);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAGCEPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAGCEPlayer::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AAGCEPlayer::JumpPressed);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AAGCEPlayer::JumpReleased);
}

void AAGCEPlayer::GamepadTurn(const float Value)
{
	const float DeltaSec = UGameplayStatics::GetWorldDeltaSeconds(this);
	AddControllerYawInput(Value * GamepadBaseTurnRate * DeltaSec);
}

void AAGCEPlayer::GamepadLookUp(const float Value)
{
	const float DeltaSec = UGameplayStatics::GetWorldDeltaSeconds(this);
	AddControllerPitchInput(Value * GamepadBaseLookUpRate * DeltaSec);
}

void AAGCEPlayer::MouseTurn(const float Value)
{
	AddControllerYawInput(Value * MouseBaseTurnRate);
}

void AAGCEPlayer::MouseLookUp(const float Value)
{
	AddControllerPitchInput(Value * MouseBaseTurnRate);
}

void AAGCEPlayer::MoveForward(const float Value)
{
	const FRotator YawRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(YawRotation);

	AddMovementInput(ForwardVector, Value);
}

void AAGCEPlayer::MoveRight(const float Value)
{
	const FRotator YawRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	const FVector RightVector = UKismetMathLibrary::GetRightVector(YawRotation);

	AddMovementInput(RightVector, Value);
}

void AAGCEPlayer::JumpPressed()
{
	Jump();
}

void AAGCEPlayer::JumpReleased()
{
	StopJumping();
}
