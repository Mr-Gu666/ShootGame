// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FP_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTGAME_API AFP_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	AFP_PlayerState();

	UPROPERTY(EditAnywhere, Replicated)
		float PlayerScore;

	UFUNCTION(BlueprintPure, Category = "ShootGame")
		float GetPlayerScore();

	void UpdateScore(float);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
