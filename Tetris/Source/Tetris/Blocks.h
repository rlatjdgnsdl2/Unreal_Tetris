// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Blocks.generated.h"


class ABlock;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class TETRIS_API ABlocks : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABlocks();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveUp(const FInputActionValue& Value);
	void MoveDown(const FInputActionValue& Value);
	void MoveLeft(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);

	void RotateLeft(const FInputActionValue& Value);
	void RotateRight(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveUpAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveDownAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveLeftAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveRightAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* RotateLeftAction;
	UPROPERTY(EditDefaultsOnly)
	UInputAction* RotateRightAction;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tetris")
	TArray<ABlock*> Blocks;

};
