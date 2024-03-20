// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestSystem/TAQuestComponent.h"

UTAQuestComponent::UTAQuestComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

void UTAQuestComponent::InitNewQuest(FQuestData QusetData)
{
    // TO DO function that is called when a new quest starts and launches one of the scripts depending on its type
}

void UTAQuestComponent::MarkSuccessQuset(FQuestData QusetData)
{
    // TO DO function that is called when a quest is completed and ATAPlayerState is notified about the successful completion of the quest
}

void UTAQuestComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UTAQuestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
