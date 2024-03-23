// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TAPlayerController.h"
#include "Controllers/SetupQuestDataInPawn.h"


void ATAPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    SetupQuestDataInPawn(InPawn, true);
}
