// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCharacter_OnlyArms.h"
#include "Camera/CameraComponent.h"
#include "FirstPerson_Fire.h"

// Sets default values
AFPCharacter_OnlyArms::AFPCharacter_OnlyArms()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create FPCamera
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	// add camera component to capsule component
	FPCameraComponent->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	// can use pawn to rotation
	FPCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AFPCharacter_OnlyArms::BeginPlay()
{
	Super::BeginPlay();
	
	// verify if is FPCharacter runing
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("First person view."));
	}
}

// Called every frame
void AFPCharacter_OnlyArms::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPCharacter_OnlyArms::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 绑定移动
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPCharacter_OnlyArms::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPCharacter_OnlyArms::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AFPCharacter_OnlyArms::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPCharacter_OnlyArms::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPCharacter_OnlyArms::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPCharacter_OnlyArms::StopJump);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AFPCharacter_OnlyArms::StartAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AFPCharacter_OnlyArms::StopAim);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPCharacter_OnlyArms::Fire);
}

void  AFPCharacter_OnlyArms::MoveForward(float Value)
{
	if (Controller) {
		// 明确哪个方向是"前进"，并记录玩家试图向此方向移动。
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void  AFPCharacter_OnlyArms::MoveRight(float Value)
{
	if (Controller) {
		// 明确哪个方向是"向右"，并记录玩家试图向此方向移动。
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void  AFPCharacter_OnlyArms::StartJump()
{
	if (Controller) {
		bPressedJump = true;
	}
}

void  AFPCharacter_OnlyArms::StopJump()
{
	if (Controller) {
		bPressedJump = false;
	}
}

void AFPCharacter_OnlyArms::StartAim()
{
	if (Controller) {}
}

void AFPCharacter_OnlyArms::StopAim()
{
	if (Controller) {}
}

void AFPCharacter_OnlyArms::Fire()
{
	if (Controller) {
		// 有要射出的东西
		if (WhatToShoot)
		{
			// 获取摄像机变换。
			FVector CameraLocation;
			FRotator CameraRotation;
			GetActorEyesViewPoint(CameraLocation, CameraRotation);

			// 将 WhereToShoot 从摄像机空间变换到世界空间。
			FVector WhereToShoot_L = CameraLocation + FTransform(CameraRotation).TransformVector(WhereToShoot);
			FRotator WhereToShoot_R = CameraRotation;
			// 将准星稍微上抬。
			WhereToShoot_R.Pitch += 10.0f;
			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();
				// 在枪口处生成发射物。
				AFirstPerson_Fire* Shooted = World->SpawnActor<AFirstPerson_Fire>(WhatToShoot, WhereToShoot_L, WhereToShoot_R, SpawnParams);
				if (Shooted)
				{
					// 设置发射物的初始轨道。
					FVector LaunchDirection =WhereToShoot_R.Vector();
					Shooted->FireInDirection(LaunchDirection);
				}
			}
		}
	}
}