// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/Base/CoreCharacter.h"

// Sets default values
ACoreCharacter::ACoreCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACoreCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACoreCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACoreCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
