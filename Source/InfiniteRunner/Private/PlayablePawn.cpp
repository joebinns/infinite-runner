// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayablePawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

// Sets default values
APlayablePawn::APlayablePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create components
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	
	// Declare root
	RootComponent = Mesh;
	
	// Setup spring arm
	SpringArm->SetupAttachment(Mesh);
	SpringArm->SetRelativeLocation(FVector(-100.f, 0.f, 50.f));
	SpringArm->SetRelativeRotation(FRotator(0.f, -5.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 50.f;
	SpringArm->TargetArmLength = 200.f;

	// Setup camera
	Camera->SetupAttachment(SpringArm);
	Camera->FieldOfView = 60.f;

}

// Called when the game starts or when spawned
void APlayablePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayablePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	IsGrounded = GroundCheck();
}

// Called to bind functionality to input
void APlayablePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Make sure that we are using a UEnhancedInputComponent; if not, the project is not configured correctly.
	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// There are ways to bind a UInputAction* to a handler function and multiple types of ETriggerEvent that may be of interest.
		
		// This calls the handler function on the tick when MyInputAction starts, such as when pressing an action button.
		if (StrafeAction)
		{
			PlayerEnhancedInputComponent->BindAction(StrafeAction, ETriggerEvent::Triggered, this, &APlayablePawn::Strafe);
		}

		if (JumpAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayablePawn::Jump);
		}

		if (SlideAction)
		{
			PlayerEnhancedInputComponent->BindAction(SlideAction, ETriggerEvent::Started, this, &APlayablePawn::Slide);
		}
	}
}

void APlayablePawn::PawnClientRestart()
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

bool APlayablePawn::GroundCheck()
{
	// FHitResult will hold all data returned by our line collision query
	FHitResult Hit;

	// We set up a line trace from our current location to a point below
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation() + GetActorUpVector() * -TraceDistance;

	// You can use FCollisionQueryParams to further configure the query
	// Here we add ourselves to the ignored list so we won't block the trace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	// To run the query, you need a pointer to the current level, which you can get from an Actor with GetWorld()
	// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, GroundCheckTraceChannel, QueryParams);

	// You can use DrawDebug helpers and the log to help visualize and debug your trace queries.
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
	//UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());

	bool didTraceHit = (Hit.bBlockingHit && IsValid(Hit.GetActor()));
	
	// If the trace hit something, bBlockingHit will be true,
	// and its fields will be filled with detailed info about what was hit
	if (didTraceHit)
	{
		//UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
	}
	else {
		//UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}

	return didTraceHit;
}

void APlayablePawn::Strafe(const FInputActionValue& Value)
{
	float input = Value.Get<float>();
	if (input != 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Strafe: %f"), input);
		AddMovementInput(GetActorRightVector(), input);
	}
}

void APlayablePawn::Jump(const FInputActionValue& Value)
{
	if (IsGrounded)
	{
	    UE_LOG(LogTemp, Warning, TEXT("Jump"));
	}
}

void APlayablePawn::Slide(const FInputActionValue& Value)
{
	if (IsGrounded)
	{
		UE_LOG(LogTemp, Warning, TEXT("Slide"));
	}
}
