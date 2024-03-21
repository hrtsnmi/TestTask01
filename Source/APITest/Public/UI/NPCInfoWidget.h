// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../QuestSystem/TAQuestManager.h"
#include "NPCInfoWidget.generated.h"

/**
 * 
 */

class UTextBlock;
class UTAQuestComponent;

UCLASS()
class APITEST_API UNPCInfoWidget : public UUserWidget
{
    GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI|ID")
    UTextBlock* TB_ID;

    UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI|Quest Desc")
    UTextBlock* TB_QuestDesc;

    UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI|Quest Type")
    UTextBlock* TB_QuestType;

    UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI|Target Location")
    UTextBlock* TB_TargetLocation;

private:
    UFUNCTION()
    void UpdateQuestInfo(FQuestData QuestData);

public:
    void SetupQuestComponentDelegates(UTAQuestComponent* QuestComponent);
};
