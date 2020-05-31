// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemSteam.h"
#include "OnlineStats.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineLeaderboardInterface.h"

UProjectGameInstance::UProjectGameInstance()
{
}

void UProjectGameInstance::ReadLeaderboard()
{
	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
	IOnlineLeaderboardsPtr LBInterface;
	IOnlineLeaderboards* LB;
	LBInterface = SubSystem->GetLeaderboardsInterface();
	
	if (LBInterface.IsValid())
	{
		LB = LBInterface.Get();
		TArray< TSharedRef<const FUniqueNetId> > Players;
		
		
		//FOnlineLeaderboardReadRef ReadObject;
		FOnlineSubsystemSteamPtr OSS;

		FName SessionName = TEXT("TimeRank");
		TSharedPtr<const FUniqueNetId> Player = IOnlineSubsystem::Get()->GetIdentityInterface()->GetUniquePlayerId(0);
		FOnlineLeaderboardWrite OLW;
		
		OSS->GetLeaderboardsInterface()->WriteLeaderboards(SessionName, *Player.Get(), OLW);
	}
	
	
}

void UProjectGameInstance::WriteLeaderboard()
{
	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
	IOnlineLeaderboardsPtr LBInterface;
	IOnlineLeaderboards* LB;
	LBInterface = SubSystem->GetLeaderboardsInterface();

	if (LBInterface.IsValid())
	{
		LB = LBInterface.Get();
	}
}

void UProjectGameInstance::LoginLeaderboard()
{
	//if (!OnLoginCompleteDelegateHandle.IsValid())
	//{
	//	//IOnlineSubsystem* const OnlineSub = Online::GetSubsystem(GetWorld());
	//	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
	//	if (OnlineSub)
	//	{
	//		IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();
	//		if (Identity.IsValid())
	//		{
	//			OnLoginCompleteDelegateHandle = Identity->AddOnLoginCompleteDelegate_Handle(0, FOnLoginCompleteDelegate::CreateRaw(this, &UProjectGameInstance::OnLoginCompleteReadStats));
	//			Identity->Login(0, FOnlineAccountCredentials());
	//		}
	//	}
	//}
}

void UProjectGameInstance::OnLoginCompleteReadStats(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	//Online::GetIdentityInterface(GetWorld())->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, OnLoginCompleteDelegateHandle);
	//IOnlineSubsystem::Get(STEAM_SUBSYSTEM)->GetIdentityInterface()->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, OnLoginCompleteDelegateHandle);
	//if (bWasSuccessful)
	//{
	//	ReadStats();
	//}
}

void UProjectGameInstance::ReadStats()
{
	//StatRows.Reset();

	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
	if (OnlineSub)
	{
		IOnlineLeaderboardsPtr Leaderboards = OnlineSub->GetLeaderboardsInterface();
		if (Leaderboards.IsValid())
		{
			// We are about to read the stats. The delegate will set this to false once the read is complete.
			//LeaderboardReadCompleteDelegateHandle = Leaderboards->AddOnLeaderboardReadCompleteDelegate_Handle(LeaderboardReadCompleteDelegate);
			bReadingStats = true;

			// There's no reason to request leaderboard requests while one is in progress, so only do it if there isn't one active.
			//if (!IsLeaderboardReadInProgress())
			//{
			//	ReadObject = MakeShareable(new FShooterAllTimeMatchResultsRead());
			//	FOnlineLeaderboardReadRef ReadObjectRef = ReadObject.ToSharedRef();
			//	bReadingStats = Leaderboards->ReadLeaderboardsForFriends(0, ReadObjectRef);
			//}
		}
		else
		{
			// TODO: message the user?
		}
	}
}
