// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Functions.h"
#include "Gamemode/TABaseGameMode.h"
#include "Gamemode/DeclaringDelegatesForQuestFlow.h"
#include "Interfaces/InteractableInterface.h"
#include "Interfaces/QuestComponentOwnerInterface.h"
#include "Controllers/TAPlayerController.h"
#include "Data/FQuestData.h"


void ControllersFunctions::OnPossess(APawn* InPawn)
{
}

void ControllersFunctions::BeginPlay(AController* Controller)
{
    APawn* InPawn = Controller->GetPawn();

    check(InPawn);

    if (ATABaseGameMode* GM = Cast<ATABaseGameMode>(InPawn->GetWorld()->GetAuthGameMode()))
    {
        GM->SetInteractType(Controller, (bool)Cast<ATAPlayerController>(Controller));
        GM->InitQuestData(Controller, (HasInterfaceChecker::HasInteractableInterface(Controller)
                                              ? IInteractableInterface::Execute_GetInteractType(Controller) == EInteractType::Master
                                              : false));
    }
}

bool ControllersFunctions::UnderInteract(AController* Controller, FQuestData& OutData, EQuestProgress& OutProgress)
{
    return HasInterfaceChecker::HasQuestComponentOwnerInterface(Controller->GetPawn())
               ? IQuestComponentOwnerInterface::Execute_GetDataFromComponent(Controller->GetPawn(), OutData, OutProgress)
           : false && HasInterfaceChecker::HasInteractableInterface(Controller)
               ? IInteractableInterface::Execute_GetInteractType(Controller) == EInteractType::Slave
               : false;
}

bool ControllersFunctions::CanPawnDoQuest(APawn* Pawn, EInteractType InteractType, bool isStarting)
{
    EQuestProgress ProgressToCompare;
    switch (InteractType)
    {
        case EInteractType::Master: ProgressToCompare = isStarting ? EQuestProgress::NONE : EQuestProgress::Done; break;
        default: ProgressToCompare = isStarting ? EQuestProgress::Get : EQuestProgress::Done; break;
    }

    if (!HasInterfaceChecker::HasQuestComponentOwnerInterface(Pawn))
    {
        return false;
    }
    EQuestProgress CurentQuestProgress;
    FQuestData PlaceholderVar;
    IQuestComponentOwnerInterface::Execute_GetDataFromComponent(Pawn, PlaceholderVar, CurentQuestProgress);
    
    return CurentQuestProgress == ProgressToCompare;         
}

void ControllersFunctions::PawnTryToStartNewQuest(
    AController* PlayerController, AController* NPCController, QuestFlowDelegates::OnQuestStartSignature& OnQuestStart)
{
    OnQuestStart.ExecuteIfBound(PlayerController, NPCController);
}

void ControllersFunctions::PawnTryToEndQuest(
    AController* PlayerController, AController* NPCController, QuestFlowDelegates::OnQuestEndSignature& OnQuestEnd)
{
    OnQuestEnd.ExecuteIfBound(PlayerController, NPCController);
}

EQuestProgress ControllersFunctions::UpdateQuestProgress(AController* FuncCaller, EQuestProgress CurrentProgress, AActor* QuestGiver)
{
    if (!HasInterfaceChecker::HasInteractableInterface(FuncCaller))
    {
        return EQuestProgress::Max;
    }

   
    static bool (*HasQuestGiverAnInteractType)(
        EInteractType CompareType, AActor * QuestGiver) = [](EInteractType CompareType, AActor* QuestGiver) -> bool
    {
        return HasInterfaceChecker::HasInteractableInterface(QuestGiver)
                   ? IInteractableInterface::Execute_GetInteractType(QuestGiver) == CompareType
                   : false;
    };

    bool ControllerHasMasterInteract = IInteractableInterface::Execute_GetInteractType(FuncCaller) == EInteractType::Master;

    static bool forCompare;
    forCompare = HasQuestGiverAnInteractType(ControllerHasMasterInteract ? EInteractType::Slave : EInteractType::Master, QuestGiver);

    if (forCompare)
    {
        uint8 Result = ((uint8)CurrentProgress + 1U) % (uint8)EQuestProgress::Max;
        if (!ControllerHasMasterInteract && !Result)
        {
            Result++;
        }

        return (EQuestProgress)Result;
    }
    else
    {
        return ControllerHasMasterInteract ? EQuestProgress::Done : CurrentProgress;
    }
}

void ControllersFunctions::PostProccessQuestProgress(AController* FuncCaller, EQuestProgress QuestProgress)
{
    /*if (!HasInterfaceChecker::HasInteractableInterface(FuncCaller))
    {
        return;
    }

    switch (QuestProgress)
    {
        case EQuestProgress::NONE: break;
        case EQuestProgress::Get: 
            OnQuestStart.ExecuteIfBound()
            break;
        case EQuestProgress::Max: break;
        default: break;
    }*/
}

// if (CurrentQuestProgress == EQuestProgress::NONE)
//     {
//         CurrentQuestData = NewQuestData;
//         CurrentQuestProgress = NewQuestData.Id > -1 ? EQuestProgress::Get : EQuestProgress::NONE;
//         if ((HasInterfaceChecker::HasInteractableInterface(QuestGiver)
//                     ? IInteractableInterface::Execute_GetInteractType(QuestGiver) == EInteractType::Slave
//                     : NewQuestData.Id > -1))
//         {
//         }
//
//         CurrentQuestProgress = HasInterfaceChecker::HasInteractableInterface(QuestGiver)
//                                    ? IInteractableInterface::Execute_GetInteractType(QuestGiver) == EInteractType::Slave
//                                    : (NewQuestData.Id > -1 ? EQuestProgress::Get : EQuestProgress::NONE;);
//     }
//     else
//     {
//         uint8 intProgress = (uint8)CurrentQuestProgress;
//         ++intProgress %= (uint8)EQuestProgress::Max;
//
//         CurrentQuestProgress = (EQuestProgress)intProgress;
//     }
//
//     PostProccessProgress(QuestGiver);