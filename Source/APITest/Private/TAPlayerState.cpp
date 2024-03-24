// Fill out your copyright notice in the Description page of Project Settings.


#include "TAPlayerState.h"
#include "QuestSystem/TAQuestComponent.h"
#include "Interfaces/InteractableInterface.h"
#include "Interfaces/HasInterfaceChecker.h"

void ATAPlayerState::BeginPlay()
{
    Super::BeginPlay();

}

void ATAPlayerState::SetQuestData(const FQuestData& NewQuestData, AActor* QuestGiver)
{
    // TODO:
    
    const bool bIsSlaveInteractType = HasInterfaceChecker::HasInteractableInterface(QuestGiver)
                                          ? IInteractableInterface::Execute_GetInteractType(QuestGiver) == EInteractType::Slave
                                          : false;
                                                 
    switch (CurrentQuestProggres)
    {
        case EQuestProgress::NONE:
            CurrentQuestData = NewQuestData;
            CurrentQuestProggres = bIsSlaveInteractType ? (EQuestProgress::Get) : (EQuestProgress::Done);
            break;
        case EQuestProgress::Get: CurrentQuestProggres = bIsSlaveInteractType ? (EQuestProgress::Done) : (EQuestProgress::Get); break;
        case EQuestProgress::Done: CurrentQuestProggres = EQuestProgress::NONE; break;
        case EQuestProgress::Max: break;
        default: break;
    }
}

const FQuestData& ATAPlayerState::GetQuestData() const
{
    return CurrentQuestData;
}

void ATAPlayerState::SetupDelegatesForQuestComponent(UTAQuestComponent* QuestComponent)
{
    QuestComponent->OnGetQuestData.BindUObject(this, &ATAPlayerState::GetQuestData);
    QuestComponent->OnSetQuestData.AddUObject(this, &ATAPlayerState::SetQuestData);
}
