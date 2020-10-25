#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FP_GameState.generated.h"

/**
 *
 */
UCLASS()
class SHOOTGAME_API AFP_GameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Replicated)
		int32 RemainingTime;

	TArray<class FPCharacter_OnlyAmrs*> MyChars;
public:
	AFP_GameState();

	void BeginPlay() override;
	void SetRemainingTime(int32 NewRemainingTime);

	UFUNCTION(BlueprintPure, Category = "ShootGame")
		FString GetRemaingTimeText();

	uint32 GetRemainingTime();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	UFUNCTION(BlueprintPure, Category = "ShootGame")
		FString GetScoreListText();
};