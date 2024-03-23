// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/NPCAIController.h"
#include "Controllers/SetupQuestDataInPawn.h"

void ANPCAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (ATABaseGameMode* GM = Cast<ATABaseGameMode>(GetWorld()->GetAuthGameMode()))
    {
        ForControllerSetup::SetupQuestDataInPawn(GM, InPawn);
    }
}

FQuestData ANPCAIController::UnderInteract_Implementation()
{
    return FQuestData();
}

EInteractType ANPCAIController::GetInteractType_Implementation() const
{
    return CurrentInteractType;
}

void ANPCAIController::SetInteractType_Implementation(EInteractType InteractType)
{
    CurrentInteractType = InteractType;
}