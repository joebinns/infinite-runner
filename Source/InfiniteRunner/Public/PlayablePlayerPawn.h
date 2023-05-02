// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInput/Public/InputActionValue.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PlayerPawn.h"
#include "PlayablePlayerPawn.generated.h"

// Forward declarations
class UInputAction;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS()
class INFINITERUNNER_API APlayablePlayerPawn : public APlayerPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayablePlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PawnClientRestart() override;

#pragma region INPUT
	
	// Input Actions
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Actions")
	UInputAction* StrafeP1Action;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Actions")
	UInputAction* StrafeP2Action;
	
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

	APlayerController* PlayerController;

private:
	UEnhancedInputLocalPlayerSubsystem* SubSystem;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
