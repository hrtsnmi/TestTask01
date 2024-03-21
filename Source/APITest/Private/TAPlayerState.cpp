// Fill out your copyright notice in the Description page of Project Settings.


#include "TAPlayerState.h"
#include "QuestSystem/TAQuestComponent.h"

void ATAPlayerState::BeginPlay()
{
    Super::BeginPlay();

    OwnerHasActiveQuest = EQuestProgress::NONE;
}

void ATAPlayerState::SetQuestData(FQuestData NewQusetData)
{
    switch (OwnerHasActiveQuest)
    {
        case EQuestProgress::NONE: 
            CurrentQuestData = NewQusetData;
            OwnerHasActiveQuest = EQuestProgress::Started;
            break;
        case EQuestProgress::Started: 

            break;
        case EQuestProgress::Complited:
            OnQuestEnd.ExecuteIfBound(CurrentQuestData);
            OwnerHasActiveQuest = EQuestProgress::NONE;
            break;
        default: break;
    }  
}

FQuestData ATAPlayerState::GetQuestData() const
{
    return CurrentQuestData;
}

void ATAPlayerState::SetupDelegatesForQuestComponent(UTAQuestComponent* QuestComponent)
{
    QuestComponent->OnGetQuestData.BindUObject(this, &ATAPlayerState::GetQuestData);
    QuestComponent->OnSetQuestData.AddUObject(this, &ATAPlayerState::SetQuestData);
}
