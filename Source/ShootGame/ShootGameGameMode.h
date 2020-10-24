// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootGameGameMode.generated.h"

UCLASS(minimalapi)
class AShootGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	// display log in screen
	virtual void StartPlay() override;

	AShootGameGameMode();
};



