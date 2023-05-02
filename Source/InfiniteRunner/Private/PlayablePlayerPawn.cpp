// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayablePlayerPawn.h"
#include "EngineUtils.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "InfiniteRunner/InfiniteRunnerGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayablePlayerPawn::APlayablePlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayablePlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayablePlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	IsGrounded = GroundCheck();
}

// Called to bind functionality to input
void APlayablePlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Make sure that we are using a UEnhancedInputComponent; if not, the project is not configured correctly.
	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// There are ways to bind a UInputAction* to a handler function and multiple types of ETriggerEvent that may be of interest.
		
		AInfiniteRunnerGameModeBase* GameMode = Cast<AInfiniteRunnerGameModeBase>(GetWorld()->GetAuthGameMode());
		const int NumPlayers = GameMode->GetNumPlayers();
		
		// This calls the handler function on the tick when MyInputAction starts, such as when pressing an action button.
		if (NumPlayers == 1)
		{
			if (StrafeP1Action)
			{
				PlayerEnhancedInputComponent->BindAction(StrafeP1Action, ETriggerEvent::Started, this, &APlayablePlayerPawn::Strafe);
				UE_LOG(LogTemp, Warning, TEXT("Assigned player 1 input"));
			}
			
			if (JumpAction)
            {
            	PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayablePlayerPawn::Jump);
            }
		}
		else if (NumPlayers == 2)
		{
			// TODO: Then make it an AI
			
			if (StrafeP2Action)
			{
				PlayerEnhancedInputComponent->BindAction(StrafeP2Action, ETriggerEvent::Started, this, &APlayablePlayerPawn::Strafe);
				UE_LOG(LogTemp, Warning, TEXT("Assigned player 2 input"));
			}

			if (SlideAction)
			{
				PlayerEnhancedInputComponent->BindAction(SlideAction, ETriggerEvent::Started, this, &APlayablePlayerPawn::Slide);
			}
		}
	}
}

void APlayablePlayerPawn::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (PlayerController == nullptr) PlayerController = Cast<APlayerController>(GetController());
	
	if (PlayerController != nullptr)
	{
		if (SubSystem == nullptr)
			SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		
		// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
		SubSystem->ClearAllMappings();

		// Add each mapping context, along with their priority values. Higher values out-prioritize lower values.
		SubSystem->AddMappingContext(GameMappingContext, GameMappingPriority);
	}
}

void APlayablePlayerPawn::Strafe(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Move"));
	
	float input = Value.Get<float>();
	Super::Strafe(input);
}

void APlayablePlayerPawn::Jump(const FInputActionValue& Value)
{
	if (IsGrounded)
	{
	    UE_LOG(LogTemp, Warning, TEXT("Jump"));
		// TODO: Jump using a curve
	}
}

void APlayablePlayerPawn::Slide(const FInputActionValue& Value)
{
	if (IsGrounded)
	{
		UE_LOG(LogTemp, Warning, TEXT("Slide"));
		// TODO: Slide using a curve
	}
}
