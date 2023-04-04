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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region TILES
	
	UPROPERTY(EditAnywhere, Category="Tiles")
	TArray<TSubclassOf<ATile>> TilesToPick;

	UPROPERTY(EditAnywhere, Category="Tiles")
	ATile* StartTile;
	
	TArray<ATile*> Tiles;
	
#pragma endregion

#pragma region MOVEMENT

	UPROPERTY(EditAnywhere, Category="Movement")
	float Speed = 1000.f;

	void Move(float DeltaTime);

#pragma endregion

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
