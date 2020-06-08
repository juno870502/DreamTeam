// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SlateBasics.h"
#include "Interfaces/OnlineLeaderboardInterface.h"

/**
 * 
 */
class DREAMTEAM_API SDTLeaderboard : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDTLeaderboard)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	int a;

	FOnlineLeaderboardReadPtr ReadObject;

	FOnLeaderboardReadCompleteDelegate LeaderboardReadCompleteDelegate;
	void OnLeaderboardReadComplete(bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void ReadLeaderboard();

	UFUNCTION(BlueprintCallable)
	void WriteLeaderboard();
};
