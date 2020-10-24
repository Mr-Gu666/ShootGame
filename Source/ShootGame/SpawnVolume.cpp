// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Target.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create a box component
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;

	// init delays
	SpawnMaxDelayRange = 4.5f;
	SpawnMinDelayRange = 1.0f;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	SpawnDelay = FMath::FRandRange(SpawnMinDelayRange, SpawnMinDelayRange);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnTarget, SpawnDelay, false);
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ASpawnVolume::SpawnTarget()
{
	// if have somthing to spawn
	if (WhatToSpawn != NULL) {
		// check for a vaild world
		UWorld* World = GetWorld();
		if (World) {
			// set spawn params
			FActorSpawnParameters SpawnParam;
			SpawnParam.Owner = this;
			SpawnParam.Instigator = GetInstigator();

			// get spawn location
			FVector SpawnLocation = GetRandomPointInVolume();

			// get spawn rotation
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;

			// spawn target
			ATarget* const Target = World->SpawnActor<ATarget>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParam);
			SpawnDelay = FMath::FRandRange(SpawnMinDelayRange, SpawnMinDelayRange);
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnTarget, SpawnDelay, false);
		}
	}
}