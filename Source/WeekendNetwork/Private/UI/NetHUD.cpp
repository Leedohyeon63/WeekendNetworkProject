// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/NetHUD.h"
#include "Framework/NetGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

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