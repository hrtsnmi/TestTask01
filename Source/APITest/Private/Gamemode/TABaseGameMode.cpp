// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/TABaseGameMode.h"
#include "QuestSystem/TAQuestManager.h"
#include "QuestSystem/TAQuestComponent.h"
#include "Data/FQuestData.h"
#include "Interfaces/InteractableInterface.h"
#include "Interfaces/QuestComponentOwnerInterface.h"

#include "Controllers/TAPlayerController.h"
#include "Controllers/NPCAIController.h"
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

    //Controller takes data delegates
    if (ANPCAIController* TAPlayerController = Cast<ANPCAIController>(NewPlayer))
    {
        TAPlayerController->OnQuestStart.BindUObject(this, &ATABaseGameMode::UpdateStartQuestProgress);
        TAPlayerController->OnQuestEnd.BindUObject(this, &ATABaseGameMode::UpdateEndQuestProgress);
    }  
}

FQuestData ATABaseGameMode::GetAvailableQuest() const
{
    static FQuestData NewQuestData;

    return TAQuestManager ? (TAQuestManager->GetAvailableQuest()) : (NewQuestData);
}

void ATABaseGameMode::SetupDelegatesForQuestComponent(AController* QuestController)
{
    if (ANPCAIController* NPCController = Cast<ANPCAIController>(QuestController))
    {
        NPCController->OnQuestStart.BindUObject(this, &ATABaseGameMode::UpdateStartQuestProgress);
        NPCController->OnQuestEnd.BindUObject(this, &ATABaseGameMode::UpdateEndQuestProgress);
    }
}

void ATABaseGameMode::SetNewQuestData(
    bool hasQuestComponentOwnerInterface, APawn* QuestComponentOwner, FQuestData NewQuestData, AActor* QuestTaker)
{
    if (!hasQuestComponentOwnerInterface)
    {
        return;
    }

    IQuestComponentOwnerInterface::Execute_SetDataInComponent(QuestComponentOwner, NewQuestData, QuestTaker);
}


void ATABaseGameMode::UpdateStartQuestProgress(UTAQuestComponent* PlayerComponent, UTAQuestComponent* NPCComponent) {}

void ATABaseGameMode::UpdateEndQuestProgress(UTAQuestComponent* PlayerComponent, UTAQuestComponent* NPCComponent) {}
