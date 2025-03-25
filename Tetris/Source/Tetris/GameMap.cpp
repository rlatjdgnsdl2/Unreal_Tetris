// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMap.h"
#include "MyDataAsset.h"

// Sets default values
AGameMap::AGameMap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameMap::BeginPlay()
{
	Super::BeginPlay();
	if (MapSize != nullptr)
	{

		SetActorScale3D(FVector(MapSize->Width, MapSize->Height, 1));
	}

}

// Called every frame
void AGameMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

