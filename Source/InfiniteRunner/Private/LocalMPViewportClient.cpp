// Copyright 2023 Joe Binns, All Rights Reserved.


#include "LocalMPViewportClient.h"

bool ULocalMPViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	if (EventArgs.IsGamepad())
	{
		// Map the gamepad to the next player index (so 1st controller is player index 1, etc.)
		const FInputKeyEventArgs NextPlayerEventArgs = FInputKeyEventArgs(EventArgs.Viewport, EventArgs.ControllerId + 1, EventArgs.Key, EventArgs.Event, EventArgs.AmountDepressed, EventArgs.IsGamepad());
		return Super::InputKey(NextPlayerEventArgs);
	}
	else
	{
		return Super::InputKey(EventArgs);
	}
}