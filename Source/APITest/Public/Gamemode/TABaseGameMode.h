// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TABaseGameMode.generated.h"

/**
 * 
 */
class UTAQuestManager;
class UTAQuestComponent;

UCLASS()
class APITEST_API ATABaseGameMode : public AGameMode
{
	GENERATED_BODY()
	
private:
    UTAQuestManager* TAQuestManager{nullptr};

private:
    AActor* NPC{nullptr};
    AActor* Player{nullptr};

private:
    void UpdateStartQuestProgress(UTAQuestComponent* PlayerComponent, UTAQuestComponent* NPCComponent);
    void UpdateEndQuestProgress(UTAQuestComponent* PlayerComponent, UTAQuestComponent* NPCComponent);

public:
    ATABaseGameMode();

    virtual void StartPlay() override;

protected:
    virtual void PostLogin(APlayerController* NewPlayer) override;

 public:
    FQuestData GetAvailableQuest() const;

    void SetupDelegatesForQuestComponent(AController* QuestController);

    void SetNewQuestData(bool hasQuestComponentOwnerInterface, APawn* QuestComponentOwner, FQuestData NewQuestData, AActor* QuestTaker);
};
