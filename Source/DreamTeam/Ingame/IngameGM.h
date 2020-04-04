// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IngameGM.generated.h"

/**
 * 
 */
UCLASS()
class DREAMTEAM_API AIngameGM : public AGameModeBase
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int ClearItemNum;
};
