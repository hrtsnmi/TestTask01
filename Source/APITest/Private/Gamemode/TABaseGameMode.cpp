// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/TABaseGameMode.h"
#include "QuestSystem/TAQuestManager.h"
#include "Data/FQuestData.h"

#include "Interfaces/InteractableInterface.h"
#include "Interfaces/QuestComponentOwnerInterface.h"
#include "Interfaces/HasInterfaceChecker.h"

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
    SetupDelegatesForQuestComponent(NewPlayer);
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
    else if (ATAPlayerController* TAPlayerController = Cast<ATAPlayerController>(QuestController))
    {
        TAPlayerController->OnQuestStart.BindUObject(this, &ATABaseGameMode::UpdateStartQuestProgress);
        TAPlayerController->OnQuestEnd.BindUObject(this, &ATABaseGameMode::UpdateEndQuestProgress);
    }
}

void ATABaseGameMode::SetNewQuestData(
    bool hasQuestComponentOwnerInterface, AActor* QuestComponentOwner, FQuestData NewQuestData, AActor* QuestTaker)
{
    if (!hasQuestComponentOwnerInterface)
    {
        return;
    }

    IQuestComponentOwnerInterface::Execute_SetDataInComponent(QuestComponentOwner, NewQuestData, QuestTaker);
}


void ATABaseGameMode::UpdateQuestFlow(AController* PlayerController, AController* NPCController, bool bIsStart)
{
    // Set Actors which interacts to start Quest
    static bool PlayerWantsToStartQuest{false};
    static AActor* NPC{nullptr};
    static AActor* Player{nullptr};

    if (PlayerWantsToStartQuest)  // Called by NPC - second time
    {
        if (!(Player == PlayerController->GetPawn()) || !(NPC == NPCController->GetPawn()))
        {
            return;
        }

        // can start quest with data in NPC
        FQuestData Buffer;
        bool canGetQuest = IInteractableInterface::Execute_UnderInteract(NPCController, Buffer);
        if (!canGetQuest)
        {
            return;
        }

        SetNewQuestData(HasInterfaceChecker::HasQuestComponentOwnerInterface(Player), Player, Buffer, NPC);

        // Set Empty Data for NPC
        SetNewQuestData(HasInterfaceChecker::HasQuestComponentOwnerInterface(NPC), NPC,
            bIsStart ? FQuestData() : TAQuestManager->GetAvailableQuest(), this);

        if (!bIsStart)
        {
            Player = nullptr;
            NPC = nullptr;
        }
    }
    else  // Called by Player - first time
    {
        if (bIsStart)
        {
            Player = PlayerController->GetPawn();
            NPC = NPCController->GetPawn();
        }
        else
        {
            //TODO: Check If Player Finish Quest

        }
    }

    PlayerWantsToStartQuest = !PlayerWantsToStartQuest;
}

void ATABaseGameMode::UpdateStartQuestProgress(AController* PlayerController, AController* NPCController)
{
    UpdateQuestFlow(PlayerController, NPCController);
}

void ATABaseGameMode::UpdateEndQuestProgress(AController* PlayerController, AController* NPCController)
{
    UpdateQuestFlow(PlayerController, NPCController, false);
}
