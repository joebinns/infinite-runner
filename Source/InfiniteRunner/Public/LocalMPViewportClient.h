// Copyright 2023 Joe Binns, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "LocalMPViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class INFINITERUNNER_API ULocalMPViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

	public:
		virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;
};
