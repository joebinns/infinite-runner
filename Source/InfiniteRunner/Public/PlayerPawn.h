// Copyright 2023 Joe Binns, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class INFINITERUNNER_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region MOVEMENT

	UPROPERTY(EditAnywhere, Category="Movement")
	int CurrentLane = 0;
	
	UPROPERTY(EditAnywhere, Category="Movement")
	float LaneWidth = 250.f;

	UFUNCTION()
	void Strafe(float Direction);

#pragma endregion

#pragma region MESH

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

#pragma endregion

#pragma region CAMERA
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

#pragma endregion

#pragma region GROUND_CHECK

	bool IsGrounded;
	
	UPROPERTY(EditAnywhere, Category="Ground Check")
	float TraceDistance = 100.f;
	
	UPROPERTY(EditAnywhere, Category="Ground Check")
	TEnumAsByte<ECollisionChannel> GroundCheckTraceChannel = ECC_Visibility;

	bool GroundCheck();

#pragma endregion

	FVector SpawnLocation;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
