// Copyright 2023 Joe Binns, All Rights Reserved.


#include "MyGameStateBase.h"
#include "PlayablePlayerState.h"
#include "GameFramework/PlayerState.h"

void AMyGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	
	for (APlayerState* PlayerState : PlayerArray)
	{
		APlayablePlayerState* PlayablePlayerState = Cast<APlayablePlayerState>(PlayerState);
		PlayablePlayerState->OnHealthChanged.AddDynamic(this, &AMyGameStateBase::GameOver);
	}
}

void AMyGameStateBase::GameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over"));
	
	bool AreAllPlayersAlive = false;
	for (APlayerState* PlayerState : PlayerArray)
	{
		APlayablePlayerState* PlayablePlayerState = Cast<APlayablePlayerState>(PlayerState);
		AreAllPlayersAlive = PlayablePlayerState->IsAlive();
		if (!AreAllPlayersAlive)
		{
			break;
		}
	}

	if (AreAllPlayersAlive)
	{
		// TODO: Open enter name
		
	}
}
