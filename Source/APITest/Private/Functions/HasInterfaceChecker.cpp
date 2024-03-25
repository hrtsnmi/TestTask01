// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Functions.h"

#include "Interfaces/InteractableInterface.h"
#include "Interfaces/QuestComponentOwnerInterface.h"

bool HasInterfaceChecker::HasInteractableInterface(AActor* Actor)
{
    return Actor ? Actor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()) : false;
}

bool HasInterfaceChecker::HasQuestComponentOwnerInterface(AActor* Actor)
{
    return Actor ? Actor->GetClass()->ImplementsInterface(UQuestComponentOwnerInterface::StaticClass()) : false;
}