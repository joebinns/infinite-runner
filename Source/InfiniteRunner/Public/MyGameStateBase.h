// Copyright 2023 Joe Binns, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class INFINITERUNNER_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
	protected:
		virtual void BeginPlay() override;

	private:
		UFUNCTION(BlueprintCallable, Category="Game")
		void GameOver();
};