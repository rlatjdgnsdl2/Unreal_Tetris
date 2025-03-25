// Fill out your copyright notice in the Description page of Project Settings.


#include "Blocks.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values
ABlocks::ABlocks()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverrideInputComponentClass = UEnhancedInputComponent::StaticClass();
}

// Called when the game starts or when spawned
void ABlocks::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABlocks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABlocks::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInput != nullptr)
	{
		if (nullptr != MoveUpAction)
		{
			EnhancedInput->BindAction(MoveUpAction,ETriggerEvent::Started,this,&ABlocks::MoveUp);
		}
		if (nullptr != MoveDownAction)
		{
			EnhancedInput->BindAction(MoveDownAction, ETriggerEvent::Started, this, &ABlocks::MoveDown);
		}
		if (nullptr != MoveLeftAction)
		{
			EnhancedInput->BindAction(MoveLeftAction, ETriggerEvent::Started, this, &ABlocks::MoveLeft);
		}
		if (nullptr != MoveRightAction)
		{
			EnhancedInput->BindAction(MoveRightAction, ETriggerEvent::Started, this, &ABlocks::MoveRight);
		}
		if (nullptr != RotateLeftAction)
		{
			EnhancedInput->BindAction(RotateLeftAction, ETriggerEvent::Started, this, &ABlocks::RotateLeft);
		}
		if (nullptr != RotateRightAction)
		{
			EnhancedInput->BindAction(RotateRightAction, ETriggerEvent::Started, this, &ABlocks::RotateRight);
		}


	}

}

void ABlocks::MoveUp(const FInputActionValue& Value)
{
	SetActorLocation(GetActorLocation() + FVector(0, 0, 100));
}

void ABlocks::MoveDown(const FInputActionValue& Value)
{
	SetActorLocation(GetActorLocation() + FVector(0, 0, -100));
}

void ABlocks::MoveLeft(const FInputActionValue& Value)
{
	SetActorLocation(GetActorLocation() + FVector(0, -100, 0));
}

void ABlocks::MoveRight(const FInputActionValue& Value)
{
	SetActorLocation(GetActorLocation() + FVector(0, 100, 0));
}

void ABlocks::RotateLeft(const FInputActionValue& Value)
{
	
}

void ABlocks::RotateRight(const FInputActionValue& Value)
{
	
}




