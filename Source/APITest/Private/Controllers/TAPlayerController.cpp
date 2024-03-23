// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TAPlayerController.h"
#include "Controllers/SetupQuestDataInPawn.h"


void ATAPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (ATABaseGameMode* GM = Cast<ATABaseGameMode>(InPawn->GetWorld()->GetAuthGameMode()))
    {
        ForControllerSetup::SetupQuestDataInPawn(GM, InPawn, true);
    }
}

FQuestData ATAPlayerController::UnderInteract_Implementation()
{
    return FQuestData();
}

EInteractType ATAPlayerController::GetInteractType_Implementation() const
{
    return CurrentInteractType;
}

void ATAPlayerController::SetInteractType_Implementation(EInteractType InteractType)
{
    CurrentInteractType = InteractType;
}
