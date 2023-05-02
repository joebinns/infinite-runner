// Copyright 2023 Joe Binns, All Rights Reserved.


#include "AIPlayerPawn.h"

// Called every frame
void AAIPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ObstacleCheck();
}

bool AAIPlayerPawn::ObstacleCheck()
{
	// FHitResult will hold all data returned by our line collision query
	FHitResult Hit;

	// We set up a line trace from our current location to a point below
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * ObstacleCheckTraceDistance;

	// You can use FCollisionQueryParams to further configure the query
	// Here we add ourselves to the ignored list so we won't block the trace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	// To run the query, you need a pointer to the current level, which you can get from an Actor with GetWorld()
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, GroundCheckTraceChannel, QueryParams);

	// You can use DrawDebug helpers and the log to help visualize and debug your trace queries.
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);

	return Hit.bBlockingHit && IsValid(Hit.GetActor());
}