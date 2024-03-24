// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/FQuestData.h"
#include "InteractableInterface.generated.h"

// This class does not need to be modified.
class UTAQuestComponent;

UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class APITEST_API IInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) bool UnderInteract(FQuestData& OutData);

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) EInteractType GetInteractType() const;
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void SetInteractType(EInteractType InteractType);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void StartQuest(AController* PlayerController);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void EndQuest(AController* PlayerController);
};
