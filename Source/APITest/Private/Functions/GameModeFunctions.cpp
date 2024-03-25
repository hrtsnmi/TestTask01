#include "Functions/Functions.h"

#include "Gamemode/TABaseGameMode.h"
#include "TAPlayerState.h"

#include "Interfaces/InteractableInterface.h"
#include "Interfaces/QuestComponentOwnerInterface.h"

bool GameModeFunctions::CheckIfGameModeCanStartsQuest(
    AActor* Player, AActor* NPC, AController* PlayerController, AController* NPCController)
{
    return (HasInterfaceChecker::HasInteractableInterface(PlayerController)
                   ? IInteractableInterface::Execute_GetInteractType(PlayerController) == EInteractType::Master
                   : false) &&
           IInteractableInterface::Execute_CanStartQuest(PlayerController) &&
           (HasInterfaceChecker::HasInteractableInterface(NPCController)
                   ? IInteractableInterface::Execute_GetInteractType(NPCController) == EInteractType::Slave
                   : false) &&
           IInteractableInterface::Execute_CanStartQuest(NPCController) && (Player == PlayerController->GetPawn()) &&
           (NPC == NPCController->GetPawn());
}

bool GameModeFunctions::CheckIfGameModeCanEndsQuest(AActor* Player, AActor* WhoCompletedQuest)
{
    return Player == WhoCompletedQuest;
}