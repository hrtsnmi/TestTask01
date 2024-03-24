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
    bool UnderInteract(FQuestData& OutData);

public:
    EInteractType GetInteractType_Implementation() const;
    void SetInteractType_Implementation(EInteractType InteractType);

    void StartQuest_Implementation(AController* NPCController);
    void EndQuest_Implementation(AController* NPCController);

public:  // Delegates For Gamemode
    QuestFlowDelegates::OnQuestStartSignature OnQuestStart;
    QuestFlowDelegates::OnQuestEndSignature OnQuestEnd;
};
