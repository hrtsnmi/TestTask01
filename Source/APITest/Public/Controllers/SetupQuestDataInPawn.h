#pragma once
#include "../Interfaces/QuestComponentOwnerInterface.h"
#include "../Interfaces/InteractableInterface.h"
#include "../Gamemode/TABaseGameMode.h"
#include "../Data/FQuestData.h"
#include "../TAPlayerState.h"
#include "../QuestSystem/TAQuestComponent.h"

void SetupQuestDataInPawn(APawn* InPawn, bool bIsMasterInteract = false)
{
    // TODO: Set Quest Data to QuestComponent
    bool hasQuestComponentOwnerInterface = InPawn->GetClass()->ImplementsInterface(UQuestComponentOwnerInterface::StaticClass());
    
    if (!hasQuestComponentOwnerInterface)
    {
        return;
    }

    if (ATAPlayerState* PState = InPawn->GetController()->GetPlayerState<ATAPlayerState>())
    {
        auto* QuestComponent = IQuestComponentOwnerInterface::Execute_GetQuestComponent(InPawn);
        PState->SetupDelegatesForQuestComponent(QuestComponent);
        QuestComponent->SetupDelegatesForPlayerState(PState);
    }

    bool hasInteractableInterface = InPawn->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass());

    if (!hasInteractableInterface)
    {
        return;
    }

    IInteractableInterface::Execute_SetInteractType(InPawn, bIsMasterInteract ? EInteractType::Master : EInteractType::Slave);

    if (ATABaseGameMode* GM = Cast<ATABaseGameMode>(InPawn->GetWorld()->GetAuthGameMode()))
    {
        FQuestData QuestData;
        IQuestComponentOwnerInterface::Execute_SetDataInComponent(InPawn, bIsMasterInteract ? QuestData : GM->GetAvailableQuest());
    }
}