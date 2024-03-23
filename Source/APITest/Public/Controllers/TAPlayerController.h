// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TAPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class APITEST_API ATAPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
    virtual void OnPossess(APawn* InPawn) override;
};
