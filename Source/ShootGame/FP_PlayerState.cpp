// Fill out your copyright notice in the Description page of Project Settings.


#include "FP_PlayerState.h"
#include "Net/UnrealNetwork.h"

AFP_PlayerState::AFP_PlayerState()
{
	PlayerScore = 0;
}

float AFP_PlayerState::GetPlayerScore()
{
	return PlayerScore;
}

void AFP_PlayerState::UpdateScore(float x)
{
	PlayerScore += x;
}

void AFP_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFP_PlayerState, PlayerScore);
}