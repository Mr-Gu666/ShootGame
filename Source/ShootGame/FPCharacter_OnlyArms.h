// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPCharacter_OnlyArms.generated.h"

UCLASS()
class SHOOTGAME_API AFPCharacter_OnlyArms : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPCharacter_OnlyArms();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// move forward or backward
	UFUNCTION()
		void MoveForward(float Value);

	// move right or left
	UFUNCTION()
		void MoveRight(float Value);

	// press jump key
	UFUNCTION()
		void StartJump();

	// relese jump key
	UFUNCTION()
		void StopJump();

	// Third Person Camera
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* FPCameraComponent;

	UFUNCTION()
		void StartAim();

	UFUNCTION()
		void StopAim();

	UFUNCTION()
		void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhereToShoot")
		FVector WhereToShoot;

	UPROPERTY(EditDefaultsOnly, Category = "WhatToShoot")
		TSubclassOf<class AFirstPerson_Fire> WhatToShoot;

};
