// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FirstPerson_Fire.generated.h"

UCLASS()
class SHOOTGAME_API AFirstPerson_Fire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFirstPerson_Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// collision component
	UPROPERTY(VisibleDefaultsOnly, Category = "CollisionComponent")
	USphereComponent* CollisionComponent;

	// bullet movement component
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovementComponent;

	// initial speed in direction
	void FireInDirection(const FVector& ShootDirection);

	// 发射物命中物体时调用的函数。
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};