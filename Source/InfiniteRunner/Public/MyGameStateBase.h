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

		UPROPERTY(EditAnywhere, Category="Class Types")
		TSubclassOf<UUserWidget> EnterNameWidgetClass;

		UPROPERTY(VisibleInstanceOnly, Category="Runtime")
		UUserWidget* EnterNameWidget;

	private:
		UFUNCTION(BlueprintCallable, Category="Game")
		void GameOver();

		UFUNCTION(BlueprintCallable, Category="UI")
		void ShowEnterName();
	
};
