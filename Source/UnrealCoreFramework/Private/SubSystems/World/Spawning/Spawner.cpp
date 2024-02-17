// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/World/Spawning/Spawner.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//FActorSpawnParameters params;
	//params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	//params.bDeferConstruction = true;
	//FTransform SpawnTransform(GetActorRotation(), SpawnLocation);
	//APawn* SpawningPawn = GetWorld()->SpawnActor<APawn>(AIType, SpawnTransform, params);
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

