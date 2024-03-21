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

UENUM() enum class EQuestProgress : uint8
{
    NONE    UMETA(DisplayName = "NONE"),
    Started UMETA(DisplayName = "Started"),
    Complited UMETA(DisplayName = "Complited")
};

UCLASS()
class APITEST_API ATAPlayerState : public APlayerState
{
	GENERATED_BODY()


 private:
    FQuestData CurrentQuestData;
    EQuestProgress OwnerHasActiveQuest;

protected:
    /** Overridable native event for when play begins for this actor. */
    virtual void BeginPlay() override;


private:
    void SetQuestData(FQuestData NewQusetData);
    FQuestData GetQuestData() const;

public:
    
    void SetupDelegatesForQuestComponent(UTAQuestComponent* QuestComponent);
    OnQuestEndSignature OnQuestEnd;
};
