// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TAPlayerController.h"
#include "Functions/Functions.h"
#include "Data/FQuestData.h"


void ATAPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    ControllersFunctions::OnPossess(InPawn);
}

bool ATAPlayerController::UnderInteract_Implementation(FQuestData& OutData, EQuestProgress& OutProgress)
{
    return ControllersFunctions::UnderInteract(this, OutData, OutProgress);
}

EInteractType ATAPlayerController::GetInteractType_Implementation() const
{
    return CurrentInteractType;
}

void ATAPlayerController::SetInteractType_Implementation(EInteractType InteractType)
{
    CurrentInteractType = InteractType;
}

bool ATAPlayerController::CanStartQuest_Implementation()
{
    return ControllersFunctions::CanPawnStartQuest(GetPawn(), CurrentInteractType);
}

bool ATAPlayerController::CanEndQuest_Implementation()
{
    return false;
}

void ATAPlayerController::PawnTryToStartNewQuest_Implementation(AController* OtherInteractController)
{
    ControllersFunctions::PawnTryToStartNewQuest(this, OtherInteractController, OnQuestStart);
}

void ATAPlayerController::PawnTryToEndQuest_Implementation(AController* OtherInteractController) {}

   

EQuestProgress ATAPlayerController::UpdateQuestProgress_Implementation(EQuestProgress CurrentProgress, AActor* QuestGiver)
{
    return ControllersFunctions::UpdateQuestProgress(this, CurrentProgress, QuestGiver);
}

void ATAPlayerController::PostProccessQuestProgress_Implementation(EQuestProgress QuestProgress)
{
    ControllersFunctions::PostProccessQuestProgress(this, QuestProgress);
}



