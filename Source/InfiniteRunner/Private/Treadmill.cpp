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

	if (StartTile != nullptr)
	{
		Tiles.Add(StartTile);
	}
	
}

// Called every frame
void ATreadmill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
	
}

void ATreadmill::Move(float DeltaTime)
{
	for (const ATile* Tile : Tiles)
	{
		if (Tile != nullptr)
		{
			Tile->GetRootComponent()->SetRelativeLocation(Tile->GetActorLocation() + -GetActorForwardVector() * Speed * DeltaTime);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("A tile is a nullptr."));
		}
	}
	
}


