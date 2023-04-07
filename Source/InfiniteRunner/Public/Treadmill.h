// Copyright 2023 Joe Binns, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "Treadmill.generated.h"

UCLASS()
class INFINITERUNNER_API ATreadmill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreadmill();

#pragma region TILES
	
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	float DistanceTravelled;

#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region TILES

	UPROPERTY(EditAnywhere, Category="Tiles")
	float TileLength = 10000.f;

	UPROPERTY(EditAnywhere, Category="Tiles")
	FVector TileSpawnOffset = FVector(0.f, 0.f, -100.f);
	
	UPROPERTY(EditAnywhere, Category="Tiles")
	int TilesPerLevel = 10;
	
	UPROPERTY(EditAnywhere, Category="Tiles")
	TArray<TSubclassOf<ATile>> TilesToPick;

	UPROPERTY(EditAnywhere, Category="Tiles")
	ATile* StartTile;
	
	UPROPERTY(EditAnywhere, Category="Tiles")
	TSubclassOf<ATile> LevelUpTile;
	
	TArray<ATile*> Tiles;
	
	int NumTilesTravelled = 0;

	FActorSpawnParameters SpawnParameters;

	void SpawnTile(TSubclassOf<ATile> Tile);
	void SpawnRandomTile();
	
#pragma endregion

#pragma region MOVEMENT

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	float Speed = 1000.f;

	void Move(float DeltaTime);

#pragma endregion

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};