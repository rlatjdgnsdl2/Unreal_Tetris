// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPawn.h"
#include "Block.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ACheckPawn::ACheckPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACheckPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACheckPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACheckPawn::CheckLine(int Width)
{
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + FVector(0, Width * 100.0f, 0);

	FCollisionQueryParams QueryParams;
	TArray<FHitResult> HitResults;
	GetWorld()->LineTraceMultiByObjectType(
		HitResults,
		StartLocation,
		EndLocation,
		FCollisionObjectQueryParams(ECC_WorldDynamic),
		QueryParams
		
	);

	// ����� ���� �߰� (Ʈ���̽� Ȯ��)
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 1.0f, 0, 2.0f);
	DrawDebugSphere(GetWorld(), StartLocation, 10.0f, 12, FColor::Blue, false, 1.0f);  // �������� ���Ǿ�
	DrawDebugSphere(GetWorld(), EndLocation, 10.0f, 12, FColor::Red, false, 1.0f);    // ������ ���Ǿ�

	CurCount = 0;  // Count �ʱ�ȭ ��ġ ����
	TArray<AActor*> ProcessedActors;  // �̹� ó���� Actor�� ������ �迭

	for (FHitResult& HitResult : HitResults)
	{
		if (HitResult.GetActor() && HitResult.GetActor()->IsA<ABlock>())
		{
			ABlock* Block = Cast<ABlock>(HitResult.GetActor());
			if (Block && !ProcessedActors.Contains(Block)) // �̹� ó���� ����� ����
			{
				ProcessedActors.Add(Block);  // ó���� ����� �߰�
				CurCount++;
			}
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("CurCount : %d"), CurCount));

	if (CurCount == Width)
	{
		// ���� �� ä�����ٸ� �ش� �� ����
		for (FHitResult& HitResult : HitResults)
		{
			ABlock* Block = Cast<ABlock>(HitResult.GetActor());
			if (Block)
			{
				Block->Destroy();
			}
		}
	}
}



