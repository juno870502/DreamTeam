// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Interfaces/OnlineLeaderboardInterface.h"

// these are normally exported from platform-specific tools
#define LEADERBOARD_STAT_TIME				"Time"
#define LEADERBOARD_STAT_KILLS				"Frags"
#define LEADERBOARD_STAT_DEATHS				"Deaths"
#define LEADERBOARD_STAT_MATCHESPLAYED		"MatchesPlayed"

/**
 *	'AllTime' leaderboard read object
 */
class FDreamTeamLeaderboardRead : public FOnlineLeaderboardRead
{
public:

	FDreamTeamLeaderboardRead()
	{
		// Default properties
		LeaderboardName = FName(TEXT("TimeRecord"));
		SortedColumn = LEADERBOARD_STAT_TIME;

		// Define default columns
		new (ColumnMetadata) FColumnMetaData(LEADERBOARD_STAT_TIME, EOnlineKeyValuePairDataType::Float);
		//new (ColumnMetadata) FColumnMetaData(LEADERBOARD_STAT_KILLS, EOnlineKeyValuePairDataType::Int32);
		//new (ColumnMetadata) FColumnMetaData(LEADERBOARD_STAT_DEATHS, EOnlineKeyValuePairDataType::Int32);
		//new (ColumnMetadata) FColumnMetaData(LEADERBOARD_STAT_MATCHESPLAYED, EOnlineKeyValuePairDataType::Int32);
	}
};

/**
 *	'AllTime' leaderboard write object
 */
class FDreamTeamLeaderboardWrite : public FOnlineLeaderboardWrite
{
public:

	FDreamTeamLeaderboardWrite()
	{
		// Default properties
		new (LeaderboardNames) FName(TEXT("TimeRecord"));
		RatedStat = LEADERBOARD_STAT_TIME;
		DisplayFormat = ELeaderboardFormat::Number;
		SortMethod = ELeaderboardSort::Descending;
		UpdateMethod = ELeaderboardUpdateMethod::KeepBest;
	}
};

