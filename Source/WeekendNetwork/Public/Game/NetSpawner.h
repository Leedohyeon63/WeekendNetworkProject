// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetSpawner.generated.h"

UCLASS()
class WEEKENDNETWORK_API ANetSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANetSpawner();

protected:
	virtual void BeginPlay() override;
    void SpawnScoreActor();

    FTimerHandle SpawnTimerHandle;

public:
    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<AActor> ScoreActor;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    float SpawnInterval = 3.0f;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    FVector SpawnRange = FVector(1000.0f, 1000.0f, 0.0f);
};
