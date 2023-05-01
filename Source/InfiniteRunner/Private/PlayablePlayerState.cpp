// Copyright 2023 Joe Binns, All Rights Reserved.


#include "PlayablePlayerState.h"

void APlayablePlayerState::DecrementHealth() // TODO: Hook this up in BP OnCollisionOverlap
{
	Health--;
	OnHealthChanged.Broadcast();
}

bool APlayablePlayerState::IsAlive()
{
	return Health > 0;
}
