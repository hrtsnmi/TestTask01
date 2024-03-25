// Fill out your copyright notice in the Description page of Project Settings.


#include "TAPlayerState.h"
#include "QuestSystem/TAQuestComponent.h"
#include "Interfaces/InteractableInterface.h"
#include "Functions/Functions.h"

void ATAPlayerState::BeginPlay()
{
    Super::BeginPlay();

}

void ATAPlayerState::SetQuestData(const FQuestData& NewQuestData, EQuestProgress NewQuestProgress, AActor* QuestGiver)
{
    CurrentQuestData = NewQuestData;
    CurrentQuestProgress = NewQuestProgress;
}

const FQuestData& ATAPlayerState::GetQuestData() const
{
    return CurrentQuestData;
}

void ATAPlayerState::SetupDelegatesForQuestComponent(UTAQuestComponent* QuestComponent)
{
    QuestComponent->OnGetQuestData.BindUObject(this, &ATAPlayerState::GetQuestData);
    QuestComponent->OnSetQuestData.AddUObject(this, &ATAPlayerState::SetQuestData);

    QuestComponent->OnGetQuestProgress.BindLambda([this]() -> EQuestProgress { return CurrentQuestProgress; });
}
