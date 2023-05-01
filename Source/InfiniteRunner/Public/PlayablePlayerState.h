// Copyright 2023 Joe Binns, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayablePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class INFINITERUNNER_API APlayablePlayerState : public APlayerState
{
	GENERATED_BODY()
	
	public:
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health")
		int Health = 3;

		UFUNCTION(BlueprintCallable, Category="Health")
		void DecrementHealth();

		UFUNCTION(BlueprintCallable, Category="Health")
		bool IsAlive();
	
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthChangedSignature);
	
		FHealthChangedSignature OnHealthChanged;
	
};
