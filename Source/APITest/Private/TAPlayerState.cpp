// Fill out your copyright notice in the Description page of Project Settings.


#include "TAPlayerState.h"
#include "QuestSystem/TAQuestComponent.h"

void ATAPlayerState::BeginPlay()
{
    Super::BeginPlay();

    CurrentQusetData.Id = -1;
}

void ATAPlayerState::SetQusetData(FQuestData NewQusetData)
{
    CurrentQusetData = NewQusetData;
}

FQuestData ATAPlayerState::GetQusetData() const
{
    return CurrentQusetData;
}

void ATAPlayerState::SetupDelegatesForQuestComponent(UTAQuestComponent* QuestComponent)
{
    QuestComponent->OnGetQuestData.BindUObject(this, &ATAPlayerState::GetQusetData);
    QuestComponent->OnSetQuestData.BindUObject(this, &ATAPlayerState::SetQusetData);
}
