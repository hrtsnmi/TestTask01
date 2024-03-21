// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestComponentOwnerInterface.generated.h"

class UTAQuestComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UQuestComponentOwnerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class APITEST_API IQuestComponentOwnerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) UTAQuestComponent* GetQuestComponent() const;
};
