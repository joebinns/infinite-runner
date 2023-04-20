// Copyright 2023 Joe Binns, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HighScores.generated.h"

USTRUCT(BlueprintType)
struct FNamedScore
{
	GENERATED_BODY();
			
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Named Score")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Named Score")
	int Score;

	FNamedScore()
	{
		Name = FText::FromString("Joe");
		Score = 0;
	}
	
	FNamedScore(FText name, int score)
	{
		Name = name;
		Score = score;
	}

	bool operator <(const FNamedScore& Other) const
	{
		return Score < Other.Score;
	}
};

UCLASS()
class INFINITERUNNER_API UHighScores : public USaveGame
{
	GENERATED_BODY()

	public:
		UHighScores();
	
		UFUNCTION(BlueprintCallable, Category="HighScores")
		void Score(FNamedScore NamedScore);

	protected: 
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HighScores")
		TArray<FNamedScore> HighScores;

		const int MAX_NUM_HIGH_SCORES = 5;
	
};
