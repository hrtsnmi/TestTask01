#pragma once
#include "../Interfaces/QuestComponentOwnerInterface.h"
#include "../Interfaces/InteractableInterface.h"
#include "../Gamemode/TABaseGameMode.h"
#include "../Data/FQuestData.h"
#include "../TAPlayerState.h"
#include "../QuestSystem/TAQuestComponent.h"

namespace ForControllerSetup
{
void SetupQuestDataInPawn(ATABaseGameMode* GM, APawn* InPawn, bool bIsMasterInteract = false)
{
    // TODO: Set Quest Data to QuestComponent
    if (!bIsMasterInteract)
    {
        GM->SetupDelegatesForQuestComponent(InPawn->GetController());
    }

    bool hasInterface = InPawn->GetController()->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass());

    if (!hasInterface)
    {
        return;
    }

    IInteractableInterface::Execute_SetInteractType(
        InPawn->GetController(), bIsMasterInteract ? EInteractType::Master : EInteractType::Slave);

    hasInterface = InPawn->GetClass()->ImplementsInterface(UQuestComponentOwnerInterface::StaticClass());
    if (!hasInterface)
    {
        return;
    }

    // SetDelegate
    // TODO: Connecct Delegates in Quest Component
    //      To StartQuest, End Quest
    UTAQuestComponent* QuestComponent = IQuestComponentOwnerInterface::Execute_GetQuestComponent(InPawn);

    if (ATAPlayerState* PState = InPawn->GetController()->GetPlayerState<ATAPlayerState>())
    {
        PState->SetupDelegatesForQuestComponent(QuestComponent);
    }

    // Set Data
    FQuestData QuestData;
    GM->SetNewQuestData(hasInterface, InPawn, bIsMasterInteract ? QuestData : GM->GetAvailableQuest(), GM);
}
}  // namespace ForControllerSetup