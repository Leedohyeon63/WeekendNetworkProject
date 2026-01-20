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
		if (WinnerIndex != -1)
		{
			return;
		}

		if (GameElapsedTime < MaxGameTime)
		{
			GameElapsedTime += DeltaTime;
		}
		else
		{
			if (Player1Score > Player2Score)
			{
				WinnerIndex = 0; 
			}
			else if (Player2Score > Player1Score)
			{
				WinnerIndex = 1;
			}
			else
			{
				WinnerIndex = 2;
			}

			OnRep_WinnerIndex();
		}
	}
}

void ANetGameState::AddScore(int32 PlayerIndex, int32 Amount)
{
	if (!HasAuthority())
	{
		return;
	} 

	if (PlayerIndex == 0)
	{
		Player1Score += Amount;
	}

	else if (PlayerIndex == 1)
	{
		 Player2Score += Amount;
	}
}

void ANetGameState::OnRep_WinnerIndex()
{
}

void ANetGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetGameState, GameElapsedTime);
	DOREPLIFETIME(ANetGameState, Player1Score);
	DOREPLIFETIME(ANetGameState, Player2Score);
	DOREPLIFETIME(ANetGameState, WinnerIndex);
}