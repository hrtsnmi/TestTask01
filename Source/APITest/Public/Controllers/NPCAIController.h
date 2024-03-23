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
    FQuestData UnderInteract_Implementation();

public:
    EInteractType GetInteractType_Implementation() const;
    void SetInteractType_Implementation(EInteractType InteractType);

 public: //Delegates For Gamemode
    OnQuestStartSignature OnQuestStart;
    OnQuestEndSignature OnQuestEnd;

};
