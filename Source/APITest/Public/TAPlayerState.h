// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "QuestSystem/TAQuestManager.h"
#include "TAPlayerState.generated.h"

class UTAQuestComponent;

DECLARE_DELEGATE_OneParam(OnQuestEndSignature, FQuestData)

    /**
 * 
 */
UCLASS()
class APITEST_API ATAPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
    /** Overridable native event for when play begins for this actor. */
    virtual void BeginPlay() override;


private:
    FQuestData CurrentQusetData;
    void SetQusetData(FQuestData NewQusetData);
    FQuestData GetQusetData() const;

public:

    void SetupDelegatesForQuestComponent(UTAQuestComponent* QuestComponent);
    OnQuestEndSignature OnQuestEnd;
};
