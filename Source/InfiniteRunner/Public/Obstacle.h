// Copyright 2023 Joe Binns, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Obstacle.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INFINITERUNNER_API UObstacle : public UBoxComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:	
	UObstacle();
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
