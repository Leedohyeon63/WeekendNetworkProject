#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NetGameState.generated.h"

UCLASS()
class WEEKENDNETWORK_API ANetGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ANetGameState();

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	FORCEINLINE float GetGameElapsedTime() const { return GameElapsedTime; }
	FORCEINLINE float GetMaxGameTime() const { return MaxGameTime; }

	float GetRemainingTime() const { return FMath::Max(0.0f, MaxGameTime - GameElapsedTime); }

	void AddScore(int32 PlayerIndex, int32 Amount);

public:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Data")
	float GameElapsedTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Data")
	float MaxGameTime = 60.0f; 

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Data")
	int32 Player1Score = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Data")
	int32 Player2Score = 0;
};