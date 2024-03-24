// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../Data/FQuestData.h"
#include "../Gamemode/DeclaringDelegatesForQuestFlow.h"

#include "NPCAIController.generated.h"

/**
 * 
 */
class UTAQuestComponent;

UCLASS()
class APITEST_API ANPCAIController : public AAIController, public IInteractableInterface
{
	GENERATED_BODY()
	

protected:
    virtual void OnPossess(APawn* InPawn) override;

protected:  // InteractableInterface
    EInteractType CurrentInteractType;
    bool UnderInteract(FQuestData& OutData);

public:
    EInteractType GetInteractType_Implementation() const;
    void SetInteractType_Implementation(EInteractType InteractType);

    void StartQuest_Implementation(AController* PlayerController);
    void EndQuest_Implementation(AController* PlayerController);

 public: //Delegates For Gamemode
    QuestFlowDelegates::OnQuestStartSignature OnQuestStart;
    QuestFlowDelegates::OnQuestEndSignature OnQuestEnd;

};