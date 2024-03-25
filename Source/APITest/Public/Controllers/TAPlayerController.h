// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Gamemode/DeclaringDelegatesForQuestFlow.h"
#include "../Interfaces/InteractableInterface.h"
#include "TAPlayerController.generated.h"

/**
 * 
 */

UCLASS()
class APITEST_API ATAPlayerController : public APlayerController, public IInteractableInterface
{
    GENERATED_BODY()

protected:
    virtual void OnPossess(APawn* InPawn) override;


protected:  // InteractableInterface
    EInteractType CurrentInteractType;
    bool UnderInteract_Implementation(FQuestData& OutData, EQuestProgress& OutProgress);

public:
    EInteractType GetInteractType_Implementation() const;
    void SetInteractType_Implementation(EInteractType InteractType);

    bool CanStartQuest_Implementation();
    bool CanEndQuest_Implementation();

    void PawnTryToStartNewQuest_Implementation(AController* OtherInteractController);
    void PawnTryToEndQuest_Implementation(AController* OtherInteractController);

    // Control Quest Progress
    EQuestProgress UpdateQuestProgress_Implementation(EQuestProgress CurrentProgress, AActor* QuestGiver);
    void PostProccessQuestProgress_Implementation(EQuestProgress QuestProgress);

public:  // Delegates For Gamemode
    QuestFlowDelegates::OnQuestStartSignature OnQuestStart;
    QuestFlowDelegates::OnQuestEndSignature OnQuestEnd;

};
