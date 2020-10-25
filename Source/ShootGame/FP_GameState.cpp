#include "FP_GameState.h"

#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "FPCharacter_OnlyArms.h"
#include "FP_PlayerState.h"

void AFP_GameState::SetRemainingTime(int32 NewRemainingTime)
{
	RemainingTime = NewRemainingTime;
}

uint32 AFP_GameState::GetRemainingTime()
{
	return RemainingTime;
}

void  AFP_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFP_GameState, RemainingTime);

}

FString AFP_GameState::GetRemaingTimeText() {
	FString ans;
	if (RemainingTime > 0) {
		ans = FString::Printf(TEXT("Time Left: %d second(s)"), RemainingTime);
	}
	else {
		FString WinPlayerName = "None";
		float WinPlayerScore = -1;

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFPCharacter_OnlyArms::StaticClass(), FoundActors);
		for (auto Actor : FoundActors) {
			AFPCharacter_OnlyArms* MyChar = Cast<AFPCharacter_OnlyArms>(Actor);
			if (MyChar) {
				AFP_PlayerState* mps = Cast<AFP_PlayerState>(MyChar->GetPlayerState());
				if (mps) {
					float  s = mps->GetPlayerScore();
					if (s > WinPlayerScore) {
						WinPlayerScore = s;
						WinPlayerName = MyChar->GetName();
					}
				}
			}
		}

		ans = FString::Printf(TEXT("Winner Player Local Name: %s,\nWinner Score: %f\n"), *WinPlayerName, WinPlayerScore);
	}
	return ans;
}
AFP_GameState::AFP_GameState() {
}
void AFP_GameState::BeginPlay() {
	Super::BeginPlay();
}
FString AFP_GameState::GetScoreListText() {

	FString ans = TEXT("");

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFPCharacter_OnlyArms::StaticClass(), FoundActors);

	struct S1 {
		float score;
		FString txt;
		S1(float s, FString t) {
			score = s;
			txt = t;
		}
	};
	TArray<S1> arrs;

	for (auto Actor : FoundActors) {
		AFPCharacter_OnlyArms* MyChar = Cast<AFPCharacter_OnlyArms>(Actor);
		if (MyChar) {
			AFP_PlayerState* mps = Cast<AFP_PlayerState>(MyChar->GetPlayerState());
			if (mps) {
				float  sco = mps->GetPlayerScore();
				FString s = FString::Printf(TEXT("Local Player Name: %s, Score: %f\n"), *MyChar->GetName(), sco);
				arrs.Add(S1(sco, s));
			}
		}
	}
	arrs.Sort([](const S1& s1, const S1& s2) {
		return s1.score > s2.score;
	});

	for (auto tmps : arrs) {
		ans = ans + tmps.txt;
	}

	return ans;
}