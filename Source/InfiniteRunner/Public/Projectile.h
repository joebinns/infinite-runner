// Copyright 2023 Joe Binns, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "Projectile.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INFINITERUNNER_API UProjectile : public UObstacle
{
	GENERATED_BODY()

public:	
	UProjectile();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
#pragma region MOVEMENT
	
	UPROPERTY(EditAnywhere, Category="Movement")
	float Amplitude = 50.f;

	UPROPERTY(EditAnywhere, Category="Movement")
	float Frequency = 1.5f;
	
	void Move(float DeltaTime);

#pragma endregion

private:
	float TimeElapsed;
	
};
