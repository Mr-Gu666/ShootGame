// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

UCLASS()
class SHOOTGAME_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();

	// Return Target mesh
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return TargetMesh; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Static Mesh in level
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Target", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TargetMesh;
};
