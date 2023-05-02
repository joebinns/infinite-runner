// Copyright 2023 Joe Binns, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerPawn.h"
#include "AIPlayerPawn.generated.h"

/**
 * 
 */
UCLASS()
class INFINITERUNNER_API AAIPlayerPawn : public APlayerPawn
{
	GENERATED_BODY()

protected:
#pragma region OBSTACLE_CHECK
		
		UPROPERTY(EditAnywhere, Category="Obstacle Check")
		float ObstacleCheckTraceDistance = 200.f;
		
		UPROPERTY(EditAnywhere, Category="Obstacle Check")
		TEnumAsByte<ECollisionChannel> ObstacleCheckTraceChannel = ECC_Visibility;

		bool ObstacleCheck(int LaneIndex);

#pragma endregion

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
