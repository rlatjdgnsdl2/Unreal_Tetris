// Fill out your copyright notice in the Description page of Project Settings.


#include "Blocks.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Block.h"

#include "Engine/DataTable.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ABlocks::ABlocks()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverrideInputComponentClass = UEnhancedInputComponent::StaticClass();

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

}

// Called when the game starts or when spawned
void ABlocks::BeginPlay()
{
	Super::BeginPlay();
	for (int32 i = 0; i < 4; i++)
	{
		ABlock* NewBlock = GetWorld()->SpawnActor<ABlock>(BlockClass);
		if (NewBlock)
		{
			NewBlock->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
			NewBlock->SetActorRelativeLocation(FVector(0, 0, 0));
			BlockArray.Add(NewBlock);
		}
	}
	InitBlock();
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
			EnhancedInput->BindAction(MoveUpAction, ETriggerEvent::Started, this, &ABlocks::MoveUp);
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
		if (nullptr != RandomBlockAction)
		{
			EnhancedInput->BindAction(RandomBlockAction, ETriggerEvent::Started, this, &ABlocks::RandomBlock);
		}
	}

}

void ABlocks::MoveUp(const FInputActionValue& Value)
{
	SetActorLocation(GetActorLocation() + FVector(100, 0, 0));
}

void ABlocks::MoveDown(const FInputActionValue& Value)
{
	SetActorLocation(GetActorLocation() + FVector(-100, 0, 0));
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
	SetActorRotation(GetActorRotation() + FRotator(0, 90, 0));
}

void ABlocks::RandomBlock(const FInputActionValue& Value)
{
	FRandomStream RandomStream;
	RandomStream.GenerateNewSeed();
	int32 RandomNumber = RandomStream.RandRange(0, 6);
	BlockType = (EBlockType)RandomNumber;
	InitBlock();
}

void ABlocks::InitBlock()
{
	SetActorLocation(FVector(0, 0, 0));
	FName BlockTypeName = TEXT("");
	switch (BlockType)
	{
	case EBlockType::Z:
		BlockTypeName = TEXT("Z");
		break;
	case EBlockType::S:
		BlockTypeName = TEXT("S");
		break;
	case EBlockType::I:
		BlockTypeName = TEXT("I");
		break;
	case EBlockType::J:
		BlockTypeName = TEXT("J");
		break;
	case EBlockType::O:
		BlockTypeName = TEXT("O");
		break;
	case EBlockType::T:
		BlockTypeName = TEXT("T");
		break;
	case EBlockType::L:
		BlockTypeName = TEXT("L");
		break;
	}
	GetBlockOffset(BlockTypeName);
}

void ABlocks::GetBlockOffset(const FName& BlockTypeName)
{
	if (BlockOffsetTable)
	{

		FBlockOffSet* BlockOffsets = BlockOffsetTable->FindRow<FBlockOffSet>(BlockTypeName, nullptr);


		if (BlockOffsets)
		{
			BlockArray[0]->SetActorRelativeLocation(BlockOffsets->Offset1);
			BlockArray[1]->SetActorRelativeLocation(BlockOffsets->Offset2);
			BlockArray[2]->SetActorRelativeLocation(BlockOffsets->Offset3);
			BlockArray[3]->SetActorRelativeLocation(BlockOffsets->Offset4);
		}
	}
}





