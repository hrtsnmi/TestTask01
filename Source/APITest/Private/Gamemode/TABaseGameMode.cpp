// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/TABaseGameMode.h"

#include "GameInstance/TAMainGameInstance.h"
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
    //TAQuestManager = UTAQuestManager::GetInstance();

}

void ATABaseGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (UTAMainGameInstance* GameInstance = GetGameInstance<UTAMainGameInstance>())
    {
        GameInstance->SetupDelegatesForGameMode(this);
    }
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


const FQuestData& ATABaseGameMode::GetAvailableQuest() const
{
    if (OnGameModeNeedsToGetQuest.IsBound())
    {
        return OnGameModeNeedsToGetQuest.Execute();
    }
    else
    {
        static FQuestData EmptyData;
        return EmptyData;
    }
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

void ATABaseGameMode::UpdateQuestFlow(AController* PlayerController, AController* NPCController, EQuestProgress GlobalProgress)
{
    // Set Actors which interacts to start Quest
    static bool PlayerWantsToStartQuest{true};
    static APawn* NPC{nullptr};
    static APawn* Player{nullptr};
    // static APawn* WhoCompletedQuest{nullptr};

    if (GlobalProgress == EQuestProgress::Get && GameModeFunctions::CheckIfGameModeCanProcessQuest(Player, PlayerController->GetPawn()))
    {
        GameModeProgressQuest(Player, NPC);
        return;
    }


    if (PlayerWantsToStartQuest)  // Called by Player - first time
    {
        if (!Player)
        {
            Player = PlayerController ? PlayerController->GetPawn() : nullptr;
        }
        if (!NPC)
        {
            NPC = NPCController ? NPCController->GetPawn() : nullptr;
        }
    }
    else  // Called by NPC - second time
    {
        if (GlobalProgress == EQuestProgress::NONE &&  // - Start Quest
            GameModeFunctions::CheckIfGameModeCanStartsQuest(Player, NPC, PlayerController, NPCController))
        {
            GameModeStartsQuest(Player, NPC);
        }
        else if (GlobalProgress == EQuestProgress::Done &&
                 GameModeFunctions::CheckIfGameModeCanEndsQuest(Player, NPC, PlayerController, NPCController))
        {
            GameModeEndsQuest(Player, NPC);

            Player = nullptr;
            NPC = nullptr;
            // WhoCompletedQuest = nullptr;
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
    UpdateQuestFlow(PlayerController, NPCController, EQuestProgress::Done);
}
