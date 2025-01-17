// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/OnlineLeaderboardInterface.h"
#include "Leaderboards.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FLeaderboardRowData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Rank = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Nickname = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Time = 0;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//FString Country = "";
};

UCLASS()
class DREAMTEAM_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void OnLeaderboardReadComplete(bool bWasSuccessful);

	/** Internal. Reads the stats from the platform backend to sync online status with local */
	FOnlineLeaderboardReadPtr ReadObject;
	FDelegateHandle LeaderboardReadCompleteDelegateHandle;
	void ClearLeaderboardDelegate();

	/* WriteLeaderboard Variable */
	FDreamTeamLeaderboardWrite WriteLeaderboardVariable;

	/** Updates leaderboard stats, force */
	UFUNCTION(BlueprintCallable)
	void WriteLeaderboard();

	/** Updates leaderboard stats, compare */
	UFUNCTION(BlueprintCallable)
	void ReadLeaderboardToWrite();

	UFUNCTION()
	void OnLeaderboardReadCompleteToWrite(bool bWasSuccessful);

	int32 TimeToWrite = 0;

	/** Read leaderboard */
	UFUNCTION(BlueprintCallable)
	void ReadLeaderboard();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FLeaderboardRowData> BPDataArray;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateWidget();
};
