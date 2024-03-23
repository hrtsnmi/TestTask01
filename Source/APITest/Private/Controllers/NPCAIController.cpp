// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/NPCAIController.h"
#include "Controllers/SetupQuestDataInPawn.h"

void ANPCAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    SetupQuestDataInPawn(InPawn);
}
