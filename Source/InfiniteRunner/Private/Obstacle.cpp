// Copyright 2023 Joe Binns, All Rights Reserved.


#include "Obstacle.h"

#include "PlayablePawn.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Begin"));

	const APlayablePawn* Player = Cast<APlayablePawn>(OtherActor);
	// TODO: Move BP player controller to C++...
		// TODO: Health (PLAYER STATE)
		// TODO: Die (transition to next scene) (GAME STATE)
	
	
	// TODO: Decrease health
	// TODO: Copy this script to target, which then needs to be adapted for triggering upcoming obstacles (and triggers) to dissapear
}

void UObstacle::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("End"));
}


// Called every frame
void UObstacle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

