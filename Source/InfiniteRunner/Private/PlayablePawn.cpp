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
	
	// Declare root
	RootComponent = Mesh;
	
	// Setup spring arm
	SpringArm->SetupAttachment(Mesh);
	SpringArm->SetRelativeLocation(FVector(-100.f, 0.f, 50.f));
	SpringArm->SetRelativeRotation(FRotator(-10.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 200.f;
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
			PlayerEnhancedInputComponent->BindAction(StrafeAction, ETriggerEvent::Started, this, &APlayablePawn::Strafe);
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
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, GroundCheckTraceChannel, QueryParams);

	// You can use DrawDebug helpers and the log to help visualize and debug your trace queries.
	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);

	return Hit.bBlockingHit && IsValid(Hit.GetActor());
}

void APlayablePawn::Strafe(const FInputActionValue& Value)
{
	float input = Value.Get<float>();
	if (input != 0.f)
	{
		FHitResult hit;
		CurrentLane += input;
		CurrentLane = FMath::Clamp(CurrentLane, -1, 1);
		SetActorLocation(CurrentLane * GetActorRightVector() * LaneWidth, true, &hit, ETeleportType::TeleportPhysics);
	}
}

void APlayablePawn::Jump(const FInputActionValue& Value)
{
	if (IsGrounded)
	{
	    UE_LOG(LogTemp, Warning, TEXT("Jump"));
		// TODO: Jump using a curve
	}
}

void APlayablePawn::Slide(const FInputActionValue& Value)
{
	if (IsGrounded)
	{
		UE_LOG(LogTemp, Warning, TEXT("Slide"));
		// TODO: Slide using a curve
	}
}
