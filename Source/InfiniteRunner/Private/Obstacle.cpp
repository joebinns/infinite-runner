// Copyright 2023 Joe Binns, All Rights Reserved.


#include "Obstacle.h"
#include "PlayablePlayerPawn.h"
#include "PlayablePlayerState.h"

// Sets default values for this component's properties
UObstacle::UObstacle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
	this->OnComponentBeginOverlap.AddDynamic(this, &UObstacle::OnOverlapBegin);
	this->OnComponentEndOverlap.AddDynamic(this, &UObstacle::OnOverlapEnd);

}

// Called when the game starts
void UObstacle::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UObstacle::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Obstacle Encountered"));

	const APlayablePlayerPawn* Player = Cast<APlayablePlayerPawn>(OtherActor);
	if (!Player) return;
	Player->GetController()->GetPlayerState<APlayablePlayerState>()->DecrementHealth();
	
	UE_LOG(LogTemp, Warning, TEXT("Lose Health"));
}

void UObstacle::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


// Called every frame
void UObstacle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

