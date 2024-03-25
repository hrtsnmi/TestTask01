// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "../Functions/Functions.h"

#include "TABaseGameMode.generated.h"

/**
 * 
 */
class UTAQuestManager;
struct FQuestData;

UCLASS()
class APITEST_API ATABaseGameMode : public AGameMode
{
	GENERATED_BODY()
	
private:
    UTAQuestManager* TAQuestManager{nullptr};

    friend void ControllersFunctions::OnPossess(APawn* InPawn);

    void InitQuestData(AController* InController, bool bIsMasterInteract);
    void GameModeStartsQuest(APawn* Player, APawn* APAwn);
    void GameModeEndsQuest(APawn* Player, APawn* NPC);

private:
    void UpdateQuestFlow(AController* PlayerController, AController* NPCController, bool bIsStart = true);
    void UpdateStartQuestProgress(AController* PlayerController, AController* NPCController);
    void UpdateEndQuestProgress(AController* PlayerController, AController* NPCController);

public:
    ATABaseGameMode();

    virtual void StartPlay() override;

protected:
    virtual void PostLogin(APlayerController* NewPlayer) override;

    void SetInteractType(AController* InController, bool bIsMasterInteract);

    void SetNewQuestData(AController* QuestController, const FQuestData& NewQuestData, EQuestProgress NewQuestProgress, AActor* QuestTaker);

 public:
    FQuestData GetAvailableQuest() const;

    void SetupDelegatesForQuestComponent(AController* PlayerController);

};
