// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/NPCAIController.h"
#include "Controllers/SetupQuestDataInPawn.h"
#include "Interfaces/HasInterfaceChecker.h"
#include "Interfaces/QuestComponentOwnerInterface.h"

void ANPCAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (ATABaseGameMode* GM = Cast<ATABaseGameMode>(GetWorld()->GetAuthGameMode()))
    {
        ForControllerSetup::SetupQuestDataInPawn(GM, this);
    }
}

bool ANPCAIController::UnderInteract(FQuestData& OutData)
{
    bool canGetData = HasInterfaceChecker::HasQuestComponentOwnerInterface(GetPawn())
                          ? IQuestComponentOwnerInterface::Execute_GetDataFromComponent(GetPawn(), OutData)
                          : false;

    if (canGetData)
    {
        //Pawn can Give a quest
    }

    return canGetData;
}

EInteractType ANPCAIController::GetInteractType_Implementation() const
{
    return CurrentInteractType;
}

void ANPCAIController::SetInteractType_Implementation(EInteractType InteractType)
{
    CurrentInteractType = InteractType;
}

void ANPCAIController::StartQuest_Implementation(AController* PlayerController) 
{
    OnQuestStart.ExecuteIfBound(PlayerController, this);
}

void ANPCAIController::EndQuest_Implementation(AController* PlayerController) {}
