// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/NPCAIController.h"
#include "Functions/Functions.h"
#include "Interfaces/QuestComponentOwnerInterface.h"

void ANPCAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    ControllersFunctions::OnPossess(InPawn);
}

bool ANPCAIController::UnderInteract_Implementation(FQuestData& OutData, EQuestProgress& OutProgress)
{
    return ControllersFunctions::UnderInteract(this, OutData, OutProgress);
}

EInteractType ANPCAIController::GetInteractType_Implementation() const
{
    return CurrentInteractType;
}

void ANPCAIController::SetInteractType_Implementation(EInteractType InteractType)
{
    CurrentInteractType = InteractType;
}

bool ANPCAIController::CanStartQuest_Implementation()
{
    return ControllersFunctions::CanPawnStartQuest(GetPawn(), CurrentInteractType);
}

bool ANPCAIController::CanEndQuest_Implementation()
{
    return false;
}

void ANPCAIController::PawnTryToStartNewQuest_Implementation(AController* OtherInteractController)
{
    OnQuestStart.ExecuteIfBound(OtherInteractController, this);
}

void ANPCAIController::PawnTryToEndQuest_Implementation(AController* OtherInteractPawn) {}

EQuestProgress ANPCAIController::UpdateQuestProgress_Implementation(EQuestProgress CurrentProgress, AActor* QuestGiver)
{
    return ControllersFunctions::UpdateQuestProgress(this, CurrentProgress, QuestGiver);
}

void ANPCAIController::PostProccessQuestProgress_Implementation(EQuestProgress QuestProgress)
{
    ControllersFunctions::PostProccessQuestProgress(this, QuestProgress);
}

