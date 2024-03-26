// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/TABaseGameMode.h"

#include "QuestSystem/TAQuestManager.h"
#include "Data/FQuestData.h"
#include "TAPlayerState.h"

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

}

void ATABaseGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    //Controller takes data delegates
    SetupDelegatesForQuestComponent(NewPlayer);
}

void ATABaseGameMode::SetInteractType(AController* InController, bool bIsMasterInteract)
{
    if (!HasInterfaceChecker::HasInteractableInterface(InController))
    {
        return;
    }

    IInteractableInterface::Execute_SetInteractType(InController, bIsMasterInteract ? EInteractType::Master : EInteractType::Slave);
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
    AController* QuestController, const FQuestData& NewQuestData, EQuestProgress NewQuestProgress, AActor* QuestTaker)
{
    // Set New Progress Type for pawn
    if (!HasInterfaceChecker::HasQuestComponentOwnerInterface(QuestController->GetPawn()))
    {
        return;
    }

    IQuestComponentOwnerInterface::Execute_SetDataInComponent(QuestController->GetPawn(), NewQuestData, NewQuestProgress, QuestTaker);
}

void ATABaseGameMode::UpdateQuestFlow(AController* PlayerController, AController* NPCController, bool bIsStart)
{
    // Set Actors which interacts to start Quest
    static bool PlayerWantsToStartQuest{false};
    static APawn* NPC{nullptr};
    static APawn* Player{nullptr};

    if (PlayerWantsToStartQuest)  // Called by NPC - second time
    {
        if (GameModeFunctions::CheckIfGameModeCanStartsQuest(Player, NPC, PlayerController, NPCController))
        {
            GameModeStartsQuest(Player, NPC);
        }
    }
    else if (bIsStart)  // Called by Player - first time
    {
        Player = PlayerController->GetPawn();
        NPC = NPCController->GetPawn();
    }
    else
    {
        // TODO: Check If Player Finish Quest
        if (GameModeFunctions::CheckIfGameModeCanEndsQuest(Player, WhoCompletedQuest))
        {
            GameModeEndsQuest(Player, NPC);
        }

        Player = nullptr;
        NPC = nullptr;
        WhoCompletedQuest = nullptr;

        return;
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
