// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/NetHUD.h"
#include "Framework/NetGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UNetHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (WinText)
	{
		WinText->SetVisibility(ESlateVisibility::Hidden);
	}

	if (LoseText)
	{
		LoseText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UNetHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!CachedGameState.IsValid())
	{
		CachedGameState = Cast<ANetGameState>(UGameplayStatics::GetGameState(this));
	}

	if (CachedGameState.IsValid())
	{
		UpdateTimeDisplay();
		UpdateScoreDisplay();
		CheckGameOver();
	}
}

void UNetHUD::UpdateTimeDisplay()
{
	if (CachedGameState.IsValid() && TimeText)
	{
		float Remaining = CachedGameState->GetRemainingTime();

		int32 TotalSeconds = FMath::FloorToInt(Remaining);
		int32 Minutes = TotalSeconds / 60;
		int32 Seconds = TotalSeconds % 60;

		TimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
	}
}

void UNetHUD::UpdateScoreDisplay()
{
	if (CachedGameState.IsValid())
	{
		if (MyScore)
		{
			MyScore->SetText(FText::AsNumber(CachedGameState->Player1Score));
		}

		if (OtherScore)
		{
			OtherScore->SetText(FText::AsNumber(CachedGameState->Player2Score));
		}
	}
}

void UNetHUD::CheckGameOver()
{
	if (bResultShown || !CachedGameState.IsValid() || CachedGameState->WinnerIndex == -1)
	{
		return;
	}
	bResultShown = true;

	int32 WinnerIndex = CachedGameState->WinnerIndex;

	int32 MyIndex = GetOwningPlayer()->HasAuthority() ? 0 : 1;

	if (WinnerIndex == 2)
	{
		if (LoseText)
		{
			LoseText->SetText(FText::FromString(TEXT("DRAW!")));
			LoseText->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		if (WinnerIndex == MyIndex)
		{
			if (WinText)
			{
				WinText->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else
		{
			if (LoseText)
			{
				LoseText->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}
