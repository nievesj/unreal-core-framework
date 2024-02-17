// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Base/CorePawn.h"

// Sets default values
ACorePawn::ACorePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACorePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACorePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACorePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

