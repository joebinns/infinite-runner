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

	SpawnRandomTile();
}

void ATreadmill::SpawnTile(TSubclassOf<ATile> Tile)
{
	if (!Tile) return;
	
	FTransform Transform = GetTransform();
	const float SpawnDistanceCorrection = NumTilesTravelled * TileLength - DistanceTravelled;
	Transform.SetLocation(Transform.GetLocation() + (TileLength + SpawnDistanceCorrection) * GetActorForwardVector() + TileSpawnOffset);
	Tiles.Add(GetWorld()->SpawnActor<ATile>(Tile, Transform, SpawnParameters));
}

void ATreadmill::SpawnRandomTile()
{
	const int Index = FMath::RandRange(0, TilesToPick.Num() - 1);
	SpawnTile(TilesToPick[Index]);
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
		if (Tile)
		{
			Tile->GetRootComponent()->SetRelativeLocation(Tile->GetActorLocation() + -GetActorForwardVector() * Speed * DeltaTime);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("A tile is a nullptr."));
		}
	}
	DistanceTravelled += Speed * DeltaTime;
	
	if (DistanceTravelled / TileLength > NumTilesTravelled)
	{
		SpawnRandomTile();
		NumTilesTravelled++;
	}
}



