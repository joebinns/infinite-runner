// Copyright 2023 Joe Binns, All Rights Reserved.


#include "Obstacle.h"
#include "PlayablePlayerPawn.h"
#include "PlayablePlayerState.h"

UObstacle::UObstacle()
{
	this->OnComponentBeginOverlap.AddDynamic(this, &UObstacle::OnOverlapBegin);
}

void UObstacle::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Obstacle Encountered"));

	const APlayablePlayerPawn* Player = Cast<APlayablePlayerPawn>(OtherActor);
	if (!Player) return;
	Player->GetController()->GetPlayerState<APlayablePlayerState>()->DecrementHealth();
	
	UE_LOG(LogTemp, Warning, TEXT("Lose Health"));
}

