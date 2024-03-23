// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/FQuestData.h"
#include "TAPlayerState.h"

UTAQuestComponent::UTAQuestComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
 
}

void UTAQuestComponent::InitNewQuest(FQuestData QusetData)
{
    // TO DO function that is called when a new quest starts and launches one of the scripts depending on its type
    switch (QusetData.QuestType)
    {
        case EQuestType::FindItem: 
            StartFindItem();
            break;
        case EQuestType::MoveTo: 
            StartMoveTo();
            break;
        default: break;
    }

}

void UTAQuestComponent::MarkSuccessQuset(FQuestData QusetData)
{
    // TO DO function that is called when a quest is completed and ATAPlayerState is notified about the successful completion of the quest

    FQuestData CurrentQusetData;
    if (!GetOwnersQuest(CurrentQusetData) || CurrentQusetData.Id != QusetData.Id)
    {
        return;
    }

    // state without Quest
    if (!SetOwnersQuest(CurrentQusetData, nullptr))
    {
        return;
    }
}

void UTAQuestComponent::BeginPlay()
{
    Super::BeginPlay();

}

void UTAQuestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UTAQuestComponent::GetOwnersQuest(FQuestData& OutQuestData) const
{
    bool bCanGetQuestInfo = OnGetQuestData.IsBound();
    if (bCanGetQuestInfo)
    {
        OutQuestData = OnGetQuestData.Execute();
    }

    return bCanGetQuestInfo;
}

bool UTAQuestComponent::SetOwnersQuest(FQuestData NewQuestData, AActor* QuestGiver)
{
    bool bCanSetQuestInfo = OnSetQuestData.IsBound();
    if (bCanSetQuestInfo)
    {
        OnSetQuestData.Broadcast(NewQuestData, QuestGiver);
    }
    
    return bCanSetQuestInfo;
}

//void UTAQuestComponent::SetupDelegatesForPlayerState(ATAPlayerState* PlayerState)
//{
//    PlayerState->OnQuestEnd.BindUObject(this, &UTAQuestComponent::MarkSuccessQuset);
//}


void UTAQuestComponent::StartMoveTo()
{

}

void UTAQuestComponent::StartFindItem()
{

}