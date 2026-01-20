
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NetHUD.generated.h"

class UTextBlock;

/**
 * 1:1 멀티플레이 점수 및 시간을 표시하는 HUD 위젯
 */
UCLASS()
class WEEKENDNETWORK_API UNetHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void UpdateTimeDisplay();

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void UpdateScoreDisplay();

	void CheckGameOver();
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeText = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> MyScore = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> OtherScore = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> WinText = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> LoseText = nullptr;

private:
	TWeakObjectPtr<class ANetGameState> CachedGameState = nullptr;
	bool bResultShown = false;

};