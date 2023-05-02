// Copyright 2023 Joe Binns, All Rights Reserved.


#include "PlayerPawn.h"
#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
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
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocation = GetActorLocation();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool APlayerPawn::GroundCheck()
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

void APlayerPawn::Strafe(float Direction)
{
	if (Direction == 0.f) return;
	FHitResult hit;
	CurrentLane += Direction;
	CurrentLane = FMath::Clamp(CurrentLane, -1, 1);
	SetActorLocation(SpawnLocation + CurrentLane * GetActorRightVector() * LaneWidth, true, &hit, ETeleportType::TeleportPhysics);
}

