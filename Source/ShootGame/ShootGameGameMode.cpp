// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootGameGameMode.h"
#include "ShootGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShootGameGameMode::AShootGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/FirstPersonCharacter_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AShootGameGameMode::StartPlay()
{
	Super::StartPlay();
	
	if (GEngine)
	{
		// 显示调试信息五秒。 
		// -1"键"值（首个参数）说明我们无需更新或刷新此消息。
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
	}
}