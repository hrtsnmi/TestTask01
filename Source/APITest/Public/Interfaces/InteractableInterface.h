// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/FQuestData.h"
#include "InteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
enum class EQuestProgress : uint8;

class APITEST_API IInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) bool UnderInteract(FQuestData& OutData, EQuestProgress& OutProgress);

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) EInteractType GetInteractType() const;
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void SetInteractType(EInteractType InteractType);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) bool CanStartQuest();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) bool CanEndQuest();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void PawnTryToStartNewQuest(AController* OtherInteractController);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void PawnTryToEndQuest(AController* OtherInteractController);

	// Controll Quest Progress
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) EQuestProgress UpdateQuestProgress(EQuestProgress CurrentProgress, AActor* QuestGiver);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void PostProccessQuestProgress(EQuestProgress QuestProgress);
};
