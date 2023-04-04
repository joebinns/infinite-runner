// Copyright 2023 Joe Binns, All Rights Reserved.


#include "Treadmill.h"

// Sets default values
ATreadmill::ATreadmill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ATreadmill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATreadmill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
	
}

void ATreadmill::Move(float DeltaTime)
{
	for (ATile* Tile : Tiles)
	{
		Tile->GetRootComponent()->SetRelativeLocation(Tile->GetActorLocation() + -GetActorForwardVector() * Speed * DeltaTime);
	}

	// TODO: Trigger 'recycle' when a mesh has surpassed a certain distance
	
}


