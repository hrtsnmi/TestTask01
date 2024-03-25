// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Data/FQuestData.h"
#include "TAPlayerState.generated.h"

class UTAQuestComponent;

/**
 * 
 */

UCLASS()
class APITEST_API ATAPlayerState : public APlayerState
{
	GENERATED_BODY()

 private:
    FQuestData CurrentQuestData;
    EQuestProgress CurrentQuestProgress;

protected:
    /** Overridable native event for when play begins for this actor. */
    virtual void BeginPlay() override;

private:
    void SetQuestData(const FQuestData& NewQuestData, EQuestProgress NewQuestProgress, AActor* QuestGiver);
    const FQuestData& GetQuestData() const;
    //void PostProccessProgress(AActor* QuestGiver);

public:
    void SetupDelegatesForQuestComponent(UTAQuestComponent* QuestComponent);

};
