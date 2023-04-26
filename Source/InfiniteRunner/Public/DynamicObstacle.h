// Copyright 2023 Joe Binns, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DynamicObstacle.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INFINITERUNNER_API UDynamicObstacle : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDynamicObstacle();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void Hide();

	UPROPERTY(EditAnywhere, Category="Movement")
	UCurveFloat* HideCurve;

	FTimerHandle HideTimerHandle;
	FDateTime TimerStartTime;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
