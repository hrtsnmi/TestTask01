#include "Gamemode/TABaseGameMode.h"
#include "Interfaces/InteractableInterface.h"
#include "Data/FQuestData.h"


void ATABaseGameMode::GameModeStartsQuest(APawn* Player, APawn* NPC)
{
    // can start quest with data in NPC
    FQuestData QuestToStart;
    EQuestProgress NewNPCProgress, NewPlayerProgress;
    
    IInteractableInterface::Execute_UnderInteract(Player->GetController(), QuestToStart, NewPlayerProgress);
    
    bool canGetQuest = IInteractableInterface::Execute_UnderInteract(NPC->GetController(), QuestToStart, NewNPCProgress);
    if (!canGetQuest)
    {
        return;
    }
    //Get New Progres Type
    NewPlayerProgress =
        IInteractableInterface::Execute_UpdateQuestProgress(Player->GetController(), NewPlayerProgress, NPC->GetController());
    NewNPCProgress = IInteractableInterface::Execute_UpdateQuestProgress(NPC->GetController(), NewNPCProgress, Player->GetController());

    //Set Data to player
    SetNewQuestData(Player->GetController(), QuestToStart, NewPlayerProgress, NPC);

    // Set Empty Data for NPC
    SetNewQuestData(NPC->GetController(), FQuestData(), NewNPCProgress, Player);

    //Start Mission with QuestToStart data
    IInteractableInterface::Execute_PostProccessQuestProgress(Player->GetController(), NewPlayerProgress);
    IInteractableInterface::Execute_PostProccessQuestProgress(NPC->GetController(), NewNPCProgress);
}

void ATABaseGameMode::GameModeEndsQuest(APawn* Player, APawn* NPC) {}