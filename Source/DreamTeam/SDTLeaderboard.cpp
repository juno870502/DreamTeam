// Fill out your copyright notice in the Description page of Project Settings.


#include "SDTLeaderboard.h"
#include "SlateOptMacros.h"
#include "Engine/Engine.h"
#include "Leaderboards.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Kismet/GameplayStatics.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

FLeaderboardRow::FLeaderboardRow(const FOnlineStatsRow& Row)
	: Rank(FString::FromInt(Row.Rank))
	, PlayerName(Row.NickName)
	, PlayerId(Row.PlayerId)
{
	if (const FVariantData* KillData = Row.Columns.Find(LEADERBOARD_STAT_KILLS))
	{
		int32 Val;
		KillData->GetValue(Val);
		Kills = FString::FromInt(Val);
	}

	if (const FVariantData* DeathData = Row.Columns.Find(LEADERBOARD_STAT_DEATHS))
	{
		int32 Val;
		DeathData->GetValue(Val);
		Deaths = FString::FromInt(Val);
	}

	if (const FVariantData* TimeData = Row.Columns.Find(LEADERBOARD_STAT_TIME))
	{
		int32 Val;
		TimeData->GetValue(Val);
		Time = FString::FromInt(Val);
	}
}

void SDTLeaderboard::Construct(const FArguments& InArgs)
{
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
	LeaderboardReadCompleteDelegate = FOnLeaderboardReadCompleteDelegate::CreateRaw(this, &SDTLeaderboard::OnLeaderboardReadComplete);
}

void SDTLeaderboard::OnLeaderboardReadComplete(bool bWasSuccessful)
{
	// It's possible for another read request to happen while another one is ongoing (such as when the player leaves the menu and
	// re-enters quickly). We only want to process a leaderboard read if our read object is done.
	if (!IsLeaderboardReadInProgress())
	{
		ClearOnLeaderboardReadCompleteDelegate();

		if (bWasSuccessful)
		{
			for (int Idx = 0; Idx < ReadObject->Rows.Num(); ++Idx)
			{
				TSharedPtr<FLeaderboardRow> NewLeaderboardRow = MakeShareable(new FLeaderboardRow(ReadObject->Rows[Idx]));

				StatRows.Add(NewLeaderboardRow);

				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Emerald, FString::Printf(TEXT("Score : %s"), &(StatRows[Idx]->Time)));
			}

			//RowListWidget->RequestListRefresh();
		}

		bReadingStats = false;
	}
}

void SDTLeaderboard::ReadLeaderboard()
{
	ReadObject = MakeShareable(new FDreamTeamLeaderboardRead());

	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);

	if (SubSystem)
	{
		IOnlineIdentityPtr Identity = SubSystem->GetIdentityInterface();
		if (Identity.IsValid())
		{
			TSharedPtr<const FUniqueNetId> UserIdPtr = Identity->GetUniquePlayerId(0);
			TSharedRef<const FUniqueNetId> UserIdRef = UserIdPtr.ToSharedRef();

			IOnlineLeaderboardsPtr Leaderboards = SubSystem->GetLeaderboardsInterface();

			if (Leaderboards.IsValid())
			{
				FOnlineLeaderboardReadRef ReadRef = ReadObject.ToSharedRef();
				Leaderboards->OnLeaderboardReadCompleteDelegates.AddUObject(this, &SDTLeaderboard::OnLeaderboardReadComplete);
				if (Leaderboards->ReadLeaderboardsAroundRank(10, 10, ReadRef))
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Black, FString::Printf(TEXT("ReadSuccess")));
					for (size_t i = 0; i < ReadRef->Rows.Num(); i++)
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Black, FString::Printf(TEXT("Score : %d"), ReadRef->Rows[i].Rank));
					}
				}
			}
		}
	}
}
void SDTLeaderboard::WriteLeaderboard()
{
	FDreamTeamLeaderboardWrite WriteLeaderboard;
	Time++;
	WriteLeaderboard.SetIntStat(TEXT("Time"), Time);

	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
	if (SubSystem)
	{
		IOnlineIdentityPtr Identity = SubSystem->GetIdentityInterface();
		if (Identity.IsValid())
		{
			TSharedPtr<const FUniqueNetId> UserIdPtr = Identity->GetUniquePlayerId(0);
			if (UserIdPtr.IsValid())
			{
				IOnlineLeaderboardsPtr Leaderboards = SubSystem->GetLeaderboardsInterface();
				if (Leaderboards.IsValid())
				{
					Leaderboards->WriteLeaderboards(WriteLeaderboard.LeaderboardNames[0], (*UserIdPtr), WriteLeaderboard);
					bool bFlush = Leaderboards->FlushLeaderboards(WriteLeaderboard.LeaderboardNames[0]);
					if (bFlush)
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Score : %d"), Time));
					}
					else
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Failure")));
					}
				}
			}
		}
	}
}

void SDTLeaderboard::ClearOnLeaderboardReadCompleteDelegate()
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
	if (OnlineSub)
	{
		IOnlineLeaderboardsPtr Leaderboards = OnlineSub->GetLeaderboardsInterface();
		if (Leaderboards.IsValid())
		{
			Leaderboards->ClearOnLeaderboardReadCompleteDelegate_Handle(LeaderboardReadCompleteDelegateHandle);
		}
	}
}

bool SDTLeaderboard::IsLeaderboardReadInProgress()
{
	return ReadObject.IsValid() && (ReadObject->ReadState == EOnlineAsyncTaskState::InProgress || ReadObject->ReadState == EOnlineAsyncTaskState::NotStarted);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
