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
	bool AreAllPlayersDead = true;
	for (APlayerState* PlayerState : PlayerArray)
	{
		APlayablePlayerState* PlayablePlayerState = Cast<APlayablePlayerState>(PlayerState);
		AreAllPlayersDead = !PlayablePlayerState->IsAlive();
		if (!AreAllPlayersDead)
		{
			break;
		}
	}

	if (AreAllPlayersDead)
	{
		// TODO: Open enter name
		
	}
}
