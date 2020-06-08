// Fill out your copyright notice in the Description page of Project Settings.


#include "SDTLeaderboard.h"
#include "SlateOptMacros.h"
#include "Engine/Engine.h"
#include "Leaderboards.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Kismet/GameplayStatics.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
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
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, ReadObject->Rows[0].NickName);
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

			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, UserIdRef->ToString());

			if (Leaderboards.IsValid())
			{
				FOnlineLeaderboardReadRef ReadRef = ReadObject.ToSharedRef();
				Leaderboards->ReadLeaderboardsAroundRank(10, 10, ReadRef);
			}
		}
	}
}
void SDTLeaderboard::WriteLeaderboard()
{
	FDreamTeamLeaderboardWrite WriteLeaderboard;
	float Time = 100.f;
	WriteLeaderboard.SetFloatStat(LEADERBOARD_STAT_TIME, Time);

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
					
					Leaderboards->WriteLeaderboards(WriteLeaderboard.LeaderboardNames[0], *UserIdPtr, WriteLeaderboard);
					bool bFlush = Leaderboards->FlushLeaderboards(WriteLeaderboard.LeaderboardNames[0]);
					if (bFlush)
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Score : %f"), Time));
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
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
