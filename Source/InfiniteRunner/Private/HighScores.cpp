// Copyright 2023 Joe Binns, All Rights Reserved.


#include "HighScores.h"

UHighScores::UHighScores()
{
	// TODO: Load high scores from GameSave
	HighScores = {
		FNamedScore(FText::FromString("Joe"), 0),
		FNamedScore(FText::FromString("Bob"), 1),
		FNamedScore(FText::FromString("Tom"), 2),
		FNamedScore(FText::FromString("Fred"), 3),
		FNamedScore(FText::FromString("Steve"), 4)
	};
}

/*
 * Places the named score appropriately within the high scores.
 */
void UHighScores::AddScore(FNamedScore NamedScore)
{
	HighScores.Add(NamedScore);
	HighScores.Sort( 
		[](const FNamedScore& a, const FNamedScore& b)
		{
			return a.Score > b.Score;
		}); // Sort in descending order
	if (HighScores.Num() > MAX_NUM_HIGH_SCORES) HighScores.RemoveAt(HighScores.Num()-1);
}
