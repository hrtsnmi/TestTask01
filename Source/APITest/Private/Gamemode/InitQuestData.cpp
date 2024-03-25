#include "Gamemode/TABaseGameMode.h"
#include "TAPlayerState.h"

#include "Interfaces/InteractableInterface.h"
#include "Interfaces/QuestComponentOwnerInterface.h"
#include "Functions/Functions.h"

void ATABaseGameMode::InitQuestData(AController* InController, bool bIsMasterInteract)
{
    // TODO: Set Quest Data to QuestComponent
    if (!bIsMasterInteract)
    {
        SetupDelegatesForQuestComponent(InController);
    }

    APawn* InPawn = InController->GetPawn();
    bool hasQuestComponentOwnerInterface = HasInterfaceChecker::HasQuestComponentOwnerInterface(InPawn);
    if (!hasQuestComponentOwnerInterface)
    {
        return;
    }

    // SetDelegate
    // TODO: Connecct Delegates in Quest Component
    //      To StartQuest, End Quest


    //Set Delegates in PlayerState
    if (ATAPlayerState* PState = InController->GetPlayerState<ATAPlayerState>())
    {
        PState->SetupDelegatesForQuestComponent(IQuestComponentOwnerInterface::Execute_GetQuestComponent(InPawn));
    }

    // Set Data
    FQuestData QuestData;
    EQuestProgress NewQuestProgress = bIsMasterInteract ? EQuestProgress::NONE : EQuestProgress::Get;
    SetNewQuestData(InController, bIsMasterInteract ? QuestData : GetAvailableQuest(), NewQuestProgress, this);
}