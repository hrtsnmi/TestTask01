#include "Gamemode/TABaseGameMode.h"
#include "Interfaces/InteractableInterface.h"
#include "Data/FQuestData.h"
#include "QuestSystem/SpamActor.h"

void ATABaseGameMode::GameModeStartsQuest(APawn* Player, APawn* NPC)
{
    // can start quest with data in NPC
    FQuestData QuestToStart, placeholder;
    EQuestProgress NewNPCProgress, NewPlayerProgress;

    GetCurrentQuestDataFor(Player, NPC, placeholder, QuestToStart, NewPlayerProgress, NewNPCProgress);

    // Set For player data from NPC, and NPC with empty data
    SetNewQuestDataFor(Player, NPC, QuestToStart, FQuestData(), NewPlayerProgress, NewNPCProgress, false);

    const TSubclassOf<ASpamActor>& tmp = QuestToStart.QuestType == EQuestType::FindItem ? FindItemSubClass : MoveToSubClass;

    if (tmp)
    {
        ASpamActor*  SpamActor = GetWorld()->SpawnActor<ASpamActor>(tmp, QuestToStart.TargetLocation, FRotator());
        SpamActor->OnEndQuestConditionsReaching.BindLambda(
            [this](APawn* Player)
            {
                // WhoCompletedQuest = Player;
                UpdateQuestFlow(Player->GetController(), nullptr, EQuestProgress::Get);
            });
    }
}

void ATABaseGameMode::GameModeProgressQuest(APawn* Player, APawn* NPC)
{
    FQuestData CurrentPlayerData, CurrentNPCData;
    EQuestProgress CurrentNPCProgress, CurrentPlayerProgress;

    GetCurrentQuestDataFor(Player, NPC, CurrentPlayerData, CurrentNPCData, CurrentPlayerProgress, CurrentNPCProgress);

    SetNewQuestDataFor(Player, NPC, CurrentPlayerData, CurrentNPCData, CurrentPlayerProgress, CurrentNPCProgress, true);
}

void ATABaseGameMode::GameModeEndsQuest(APawn* Player, APawn* NPC)
{
    // Get New Progres Type
    FQuestData Placeholder1, Placeholder2;
    EQuestProgress NewNPCProgress, NewPlayerProgress;

    GetCurrentQuestDataFor(Player, NPC, Placeholder1, Placeholder2, NewPlayerProgress, NewNPCProgress);

    SetNewQuestDataFor(Player, NPC, FQuestData(), GetAvailableQuest(), NewPlayerProgress, NewNPCProgress, false);
}


void ATABaseGameMode::GetCurrentQuestDataFor(APawn* Player, APawn* NPC, FQuestData& CurrentPlayerData, FQuestData& CurrentNPCData,
    EQuestProgress& NewPlayerProgress, EQuestProgress& NewNPCProgress)
{
    IInteractableInterface::Execute_UnderInteract(Player->GetController(), CurrentPlayerData, NewPlayerProgress);
    IInteractableInterface::Execute_UnderInteract(NPC->GetController(), CurrentNPCData, NewNPCProgress);
}

void ATABaseGameMode::SetNewQuestDataFor(APawn* Player, APawn* NPC, const FQuestData& NewPlayerData, const FQuestData& NewNPCData,
    EQuestProgress NewPlayerProgress, EQuestProgress NewNPCProgress, bool bIsGameModeSender)
{
    AActor* QuestSenderForPlayer = nullptr;
    AActor* QuestSenderForNPC = nullptr;

    if (bIsGameModeSender)
    {
        QuestSenderForNPC = QuestSenderForPlayer = this;
    }
    else
    {
        QuestSenderForPlayer = NPC->GetController();
        QuestSenderForNPC = Player->GetController();
    }

    NewPlayerProgress =
        IInteractableInterface::Execute_UpdateQuestProgress(Player->GetController(), NewPlayerProgress, QuestSenderForPlayer);
    NewNPCProgress = IInteractableInterface::Execute_UpdateQuestProgress(NPC->GetController(), NewNPCProgress, QuestSenderForNPC);

    // Set Data to player
    SetNewQuestData(Player->GetController(), NewPlayerData, NewPlayerProgress, QuestSenderForPlayer);

    // Set Data for NPC
    SetNewQuestData(NPC->GetController(), NewNPCData, NewNPCProgress, QuestSenderForNPC);
}