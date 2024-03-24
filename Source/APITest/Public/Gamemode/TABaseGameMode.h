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

private:
    void UpdateQuestFlow(AController* PlayerController, AController* NPCController, bool bIsStart = true);
    void UpdateStartQuestProgress(AController* PlayerController, AController* NPCController);
    void UpdateEndQuestProgress(AController* PlayerController, AController* NPCController);

public:
    ATABaseGameMode();

    virtual void StartPlay() override;

protected:
    virtual void PostLogin(APlayerController* NewPlayer) override;

 public:
    FQuestData GetAvailableQuest() const;

    void SetupDelegatesForQuestComponent(AController* PlayerController);

    void SetNewQuestData(bool hasQuestComponentOwnerInterface, AActor* QuestComponentOwner, FQuestData NewQuestData, AActor* QuestTaker);
};
