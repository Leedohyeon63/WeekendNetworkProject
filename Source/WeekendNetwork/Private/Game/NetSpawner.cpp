
#include "Game/NetSpawner.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

ANetSpawner::ANetSpawner()
{
    PrimaryActorTick.bCanEverTick = false;

    bReplicates = true;

}

void ANetSpawner::BeginPlay()
{
    Super::BeginPlay();
    if (HasAuthority())
    {
        GetWorldTimerManager().SetTimer(
            SpawnTimerHandle,
            this,
            &ANetSpawner::SpawnScoreActor,
            SpawnInterval,
            true 
        );
    }
	
}

void ANetSpawner::SpawnScoreActor()
{
    if (!ScoreActor) return;

    FVector RandomLocation = GetActorLocation() + FVector(
        UKismetMathLibrary::RandomFloatInRange(-SpawnRange.X, SpawnRange.X),
        UKismetMathLibrary::RandomFloatInRange(-SpawnRange.Y, SpawnRange.Y),
        100.0f
    );

    FRotator RandomRotation = FRotator(0.0f, UKismetMathLibrary::RandomFloatInRange(0.0f, 360.0f), 0.0f);

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AActor* SpawnedItem = GetWorld()->SpawnActor<AActor>(ScoreActor, RandomLocation, RandomRotation, SpawnParams);

}



