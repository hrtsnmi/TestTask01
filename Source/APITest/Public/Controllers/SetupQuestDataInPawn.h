#pragma once
#include "../Interfaces/QuestComponentOwnerInterface.h"
#include "../Interfaces/InteractableInterface.h"
#include "../Interfaces/HasInterfaceChecker.h"
#include "../Gamemode/TABaseGameMode.h"
#include "../Data/FQuestData.h"
#include "../TAPlayerState.h"

namespace ForControllerSetup
{
void SetupQuestDataInPawn(ATABaseGameMode* GM, AController* InController, bool bIsMasterInteract = false)
{
    // TODO: Set Quest Data to QuestComponent
    if (!bIsMasterInteract)
    {
        GM->SetupDelegatesForQuestComponent(InController);
    }

    if (!HasInterfaceChecker::HasInteractableInterface(InController))
    {
        return;
    }

    IInteractableInterface::Execute_SetInteractType(InController, bIsMasterInteract ? EInteractType::Master : EInteractType::Slave);

    APawn* InPawn = InController->GetPawn();
    bool hasQuestComponentOwnerInterface = HasInterfaceChecker::HasQuestComponentOwnerInterface(InPawn);
    if (!hasQuestComponentOwnerInterface)
    {
        return;
    }

    // SetDelegate
    // TODO: Connecct Delegates in Quest Component
    //      To StartQuest, End Quest

    if (ATAPlayerState* PState = InController->GetPlayerState<ATAPlayerState>())
    {
        PState->SetupDelegatesForQuestComponent(IQuestComponentOwnerInterface::Execute_GetQuestComponent(InPawn));
    }

    // Set Data
    FQuestData QuestData;
    GM->SetNewQuestData(hasQuestComponentOwnerInterface, InPawn, bIsMasterInteract ? QuestData : GM->GetAvailableQuest(), GM);
}
}  // namespace ForControllerSetup