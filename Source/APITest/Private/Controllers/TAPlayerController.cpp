// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TAPlayerController.h"
#include "Controllers/SetupQuestDataInPawn.h"
#include "Interfaces/QuestComponentOwnerInterface.h"
#include "Interfaces/HasInterfaceChecker.h"


void ATAPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (ATABaseGameMode* GM = Cast<ATABaseGameMode>(InPawn->GetWorld()->GetAuthGameMode()))
    {
        ForControllerSetup::SetupQuestDataInPawn(GM, this, true);
    }
}

bool ATAPlayerController::UnderInteract(FQuestData& OutData)
{
    return false;
}

EInteractType ATAPlayerController::GetInteractType_Implementation() const
{
    return CurrentInteractType;
}

void ATAPlayerController::SetInteractType_Implementation(EInteractType InteractType)
{
    CurrentInteractType = InteractType;
}

void ATAPlayerController::StartQuest_Implementation(AController* NPCController)
{
    OnQuestStart.ExecuteIfBound(this, NPCController);
}

void ATAPlayerController::EndQuest_Implementation(AController* NPCController) {}

