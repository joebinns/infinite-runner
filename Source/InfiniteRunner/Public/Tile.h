// Copyright 2023 Joe Binns, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class INFINITERUNNER_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region MESH

	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* Mesh;

#pragma endregion 
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
