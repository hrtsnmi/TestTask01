// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestSystem/TAQuestComponent.h"

UTAQuestComponent::UTAQuestComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    
    //state without Quest
    CurrentQusetData.Id = -1;
}

void UTAQuestComponent::InitNewQuest(FQuestData QusetData)
{
    // TO DO function that is called when a new quest starts and launches one of the scripts depending on its type
    CurrentQusetData = QusetData;

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

    if (CurrentQusetData.Id != QusetData.Id)
    {
        return;
    }


    // state without Quest
    CurrentQusetData.Id = -1;
}

void UTAQuestComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UTAQuestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UTAQuestComponent::StartMoveTo()
{

}

void UTAQuestComponent::StartFindItem()
{

}