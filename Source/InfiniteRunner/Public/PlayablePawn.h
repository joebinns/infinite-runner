// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInput/Public/InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PlayablePawn.generated.h"

// Forward declarations
class UInputAction;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS()
class INFINITERUNNER_API APlayablePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayablePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PawnClientRestart() override;

#pragma region MOVEMENT

	UPROPERTY(EditAnywhere, Category="Movement")
	float LaneWidth = 250.f;

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

#pragma region INPUT
	
	// Input Actions
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Actions")
	UInputAction* StrafeAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Actions")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Actions")
	UInputAction* SlideAction;

	// Input Mappings
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Mappings")
	UInputMappingContext* GameMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Mappings")
	int32 GameMappingPriority = 0;
	
	// Input Functions
	void Strafe(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void Slide(const FInputActionValue& Value);

#pragma endregion

private:
	APlayerController* PlayerController;
	UEnhancedInputLocalPlayerSubsystem* SubSystem;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
