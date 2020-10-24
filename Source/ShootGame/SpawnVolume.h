// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class SHOOTGAME_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	// Return WhereToSpawn
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	// find a random point within the BoxComponent
	UFUNCTION(BlueprintPure, Category = "Spawning")
		FVector GetRandomPointInVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// decide what to spawn
	UPROPERTY(EditAnyWhere, Category = "Spawning")
		TSubclassOf<class ATarget> WhatToSpawn;

	// Spawn timer handler
	FTimerHandle SpawnTimer;

	// max spawn delay
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Spawning")
		float SpawnMaxDelayRange;

	// min spawn delay
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Spawning")
		float SpawnMinDelayRange;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// where target spawn
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* WhereToSpawn;

	// Spawn a new target
	void SpawnTarget();

	// current spawn delay
	float SpawnDelay;
};
