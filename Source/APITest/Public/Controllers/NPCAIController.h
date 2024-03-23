// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../Data/FQuestData.h"
#include "NPCAIController.generated.h"

/**
 * 
 */
class UTAQuestComponent;

UCLASS()
class APITEST_API ANPCAIController : public AAIController
{
	GENERATED_BODY()
	

protected:
    virtual void OnPossess(APawn* InPawn) override;
};
