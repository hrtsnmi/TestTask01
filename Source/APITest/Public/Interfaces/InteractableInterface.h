// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../QuestSystem/TAQuestManager.h"
#include "InteractableInterface.generated.h"


UENUM()
enum class EInteractType : uint8
{
    Master  UMETA(DisplayName = "Can Interact"),
    Slave   UMETA(DisplayName = "Can Be Interact")
};

// This class does not need to be modified.
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
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) FQuestData UnderInteract();

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) EInteractType GetInteractType() const;
    
    //UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void SetInteractType(EInteractType InteractType);
};
