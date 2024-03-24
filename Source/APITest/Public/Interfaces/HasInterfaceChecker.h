#pragma once
#include "QuestComponentOwnerInterface.h"
#include "InteractableInterface.h"

namespace HasInterfaceChecker
{
bool HasInteractableInterface(AActor* Actor)
{
    return Actor ? Actor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()) : false;
}

bool HasQuestComponentOwnerInterface(AActor* Actor)
{
    return Actor ? Actor->GetClass()->ImplementsInterface(UQuestComponentOwnerInterface::StaticClass()) : false;
}

}  // namespace HasInterfaceChecker