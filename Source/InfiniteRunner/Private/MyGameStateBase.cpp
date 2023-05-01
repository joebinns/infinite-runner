// Copyright 2023 Joe Binns, All Rights Reserved.


#include "MyGameStateBase.h"
#include "PlayablePlayerState.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
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
		ShowEnterName();
	}
}

void AMyGameStateBase::ShowEnterName()
{
	if (!IsValid(EnterNameWidgetClass)) return;
	
    UWidgetLayoutLibrary::RemoveAllWidgets(this);
	
    EnterNameWidget = Cast<UUserWidget>(CreateWidget(GetWorld(), EnterNameWidgetClass));
	if (!EnterNameWidget) return;
	
	EnterNameWidget->AddToViewport();
}


