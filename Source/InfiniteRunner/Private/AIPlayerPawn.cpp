// Copyright 2023 Joe Binns, All Rights Reserved.


#include "AIPlayerPawn.h"

// Called every frame
void AAIPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO: Use 3 line traces to determine which lane to use, move to the lane by strafing with account to the current lane

	ObstacleCheck(-1);
	ObstacleCheck(0);
	ObstacleCheck(1);
	
}

bool AAIPlayerPawn::ObstacleCheck(int LaneIndex)
{
	// FHitResult will hold all data returned by our line collision query
	FHitResult Hit;

	// We set up a line trace from our current location to a point below
	FVector TraceStart = SpawnLocation + GetActorRightVector() * LaneWidth * LaneIndex;
	FVector TraceEnd = TraceStart + GetActorForwardVector() * ObstacleCheckTraceDistance;

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