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
		// ��ʾ������Ϣ���롣 
		// -1"��"ֵ���׸�������˵������������»�ˢ�´���Ϣ��
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
	}
}