// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "MainCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API AMainCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;	
	
};
