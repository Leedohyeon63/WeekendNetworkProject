#include "Framework/NetGameState.h"
#include "Net/UnrealNetwork.h"

ANetGameState::ANetGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANetGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (GameElapsedTime < MaxGameTime)
		{
			GameElapsedTime += DeltaTime;
		}
		else
		{
			// 게임 종료 로직 (여기서 승패 판정 함수 호출 가능)
		}
	}
}

void ANetGameState::AddScore(int32 PlayerIndex, int32 Amount)
{
	if (!HasAuthority()) return;

	if (PlayerIndex == 0) Player1Score += Amount;
	else if (PlayerIndex == 1) Player2Score += Amount;
}

void ANetGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetGameState, GameElapsedTime);
	DOREPLIFETIME(ANetGameState, Player1Score);
	DOREPLIFETIME(ANetGameState, Player2Score);
}