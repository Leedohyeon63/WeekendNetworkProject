// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreCharacter.h"

// Sets default values
AScoreCharacter::AScoreCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScoreCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScoreCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AScoreCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

