// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/TABaseGameMode.h"
#include "QuestSystem/TAQuestManager.h"
#include "Data/FQuestData.h"
#include "Interfaces/InteractableInterface.h"
//#include "Interfaces/ControllerBindDelegatesInterface.h"
//#include "Interfaces/ControllerGetQuestDataInterface.h"



ATABaseGameMode::ATABaseGameMode()
{
    TAQuestManager = UTAQuestManager::GetInstance();
}


void ATABaseGameMode::StartPlay()
{
    Super::StartPlay();

    //GetWorld()->GetPlayerControllerIterator
}

void ATABaseGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    //GetPlayerController

    //Controller takes data delegates

    //if has custom player state
    //if (ATAPlayerState* PS = NewPlayer->GetPlayerState<ATAPlayerState>())
    //{
    //    if (!NewPlayer->GetClass()->ImplementsInterface(UControllerBindDelegatesInterface::StaticClass()))
    //    {
    //        return;
    //    }

    //    IControllerBindDelegatesInterface::Execute_SetDataForBinding(NewPlayer, PS);

    //    //Send NewAvailableQuest

    //    if (!TAQuestManager || !NewPlayer->GetClass()->ImplementsInterface(UControllerGetQuestDataInterface::StaticClass()))
    //    {
    //        return;
    //    }

    //    IControllerGetQuestDataInterface::Execute_SetQuestData(NewPlayer, TAQuestManager->GetAvailableQuest());
    //}    
}

FQuestData ATABaseGameMode::GetAvailableQuest() const
{
    static FQuestData NewQuestData;

    return TAQuestManager ? (TAQuestManager->GetAvailableQuest()) : (NewQuestData);
}
