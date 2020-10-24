// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create ThirdPersonCamera
	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	// add camera component to capsule component
	ThirdPersonCameraComponent->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	// can use pawn to rotation
	ThirdPersonCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	// verify if is FPCharacter runing
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	}
	
}

// Called every frame
void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 绑定移动
	PlayerInputComponent->BindAxis("MoveForward", this, &AFirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFirstPersonCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AFirstPersonCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFirstPersonCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFirstPersonCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFirstPersonCharacter::StopJump);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AFirstPersonCharacter::StartAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AFirstPersonCharacter::StopAim);
}

void AFirstPersonCharacter::MoveForward(float Value)
{
	if (Controller) {
		// 明确哪个方向是"前进"，并记录玩家试图向此方向移动。
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFirstPersonCharacter::MoveRight(float Value)
{
	if (Controller) {
		// 明确哪个方向是"向右"，并记录玩家试图向此方向移动。
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AFirstPersonCharacter::StartJump()
{
	if (Controller) {
		bPressedJump = true;
	}
}

void AFirstPersonCharacter::StopJump()
{
	if (Controller) {
		bPressedJump = false;
	}
}

void AFirstPersonCharacter::StartAim()
{
	if (Controller) {}
}

void AFirstPersonCharacter::StopAim()
{
	if (Controller) {}
}