// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TABaseGameMode.generated.h"

/**
 * 
 */
class UTAQuestManager;
UCLASS()
class APITEST_API ATABaseGameMode : public AGameMode
{
	GENERATED_BODY()
	
private:
    UTAQuestManager* TAQuestManager{nullptr};

public:
    ATABaseGameMode();

    virtual void StartPlay() override;

protected:
    virtual void PostLogin(APlayerController* NewPlayer) override;

 public:
    FQuestData GetAvailableQuest() const;
};
