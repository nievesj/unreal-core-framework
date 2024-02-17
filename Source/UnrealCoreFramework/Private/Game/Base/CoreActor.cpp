// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Base/CoreActor.h"

// Sets default values
ACoreActor::ACoreActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACoreActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoreActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

