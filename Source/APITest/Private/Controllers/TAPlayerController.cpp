// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TAPlayerController.h"
#include "Functions/Functions.h"
#include "Data/FQuestData.h"
#include "Interfaces/QuestComponentOwnerInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

//void ATAPlayerController::OnPossess(APawn* InPawn)
//{
//    Super::OnPossess(InPawn);
//
//    ControllersFunctions::OnPossess(InPawn);
//}

void ATAPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(DefaultMappingContext, 0);

    ControllersFunctions::BeginPlay(this);
}

bool ATAPlayerController::UnderInteract_Implementation(FQuestData& OutData, EQuestProgress& OutProgress)
{
    return ControllersFunctions::UnderInteract(this, OutData, OutProgress);
}

void ATAPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(ExitAction, ETriggerEvent::Started, this, &ATAPlayerController::ExitButtonPressed);
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ATAPlayerController::Interact);
    }
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
    return ControllersFunctions::CanPawnDoQuest(GetPawn(), CurrentInteractType);
}

bool ATAPlayerController::CanEndQuest_Implementation()
{
    return ControllersFunctions::CanPawnDoQuest(GetPawn(), CurrentInteractType, false);
}

void ATAPlayerController::PawnTryToStartNewQuest_Implementation(AController* OtherInteractController)
{
    ControllersFunctions::PawnTryToStartNewQuest(this, OtherInteractController, OnQuestStart);
}

void ATAPlayerController::PawnTryToEndQuest_Implementation(AController* OtherInteractController)
{
    ControllersFunctions::PawnTryToStartNewQuest(this, OtherInteractController, OnQuestEnd);
}


EQuestProgress ATAPlayerController::UpdateQuestProgress_Implementation(EQuestProgress CurrentProgress, AActor* QuestGiver)
{
    return ControllersFunctions::UpdateQuestProgress(this, CurrentProgress, QuestGiver);
}

void ATAPlayerController::PostProccessQuestProgress_Implementation(EQuestProgress QuestProgress)
{
    ControllersFunctions::PostProccessQuestProgress(this, QuestProgress);
}

void ATAPlayerController::Interact(const FInputActionValue& Value)
{
    bool bIsInteractStarts = Value.Get<bool>();

    if (!bIsInteractStarts)
    {
        return;
    }

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Yellow, FString::Printf(TEXT("E button pressed")));
    }

    APawn* ControlledPawn = GetPawn();

    TArray<AActor*> QuestOwnerActors;
    ControlledPawn->GetOverlappingActors(QuestOwnerActors, UQuestComponentOwnerInterface::StaticClass());

    for (AActor* QuestOwnerActor : QuestOwnerActors)
    {
        if (APawn* QuestOwnerPawn = Cast<APawn>(QuestOwnerActor))
        {
            
            if (QuestOwnerActor == ControlledPawn)
            {
                continue;
            }

            FVector DistanceToActorNorm = QuestOwnerActor->GetActorLocation() - ControlledPawn->GetActorLocation();
            DistanceToActorNorm.Normalize();
            if (FVector::DotProduct(ControlledPawn->GetActorForwardVector(), DistanceToActorNorm) < 0.6f)
            {
                continue;
            }

            if (ControllersFunctions::TryToSendRequestToStartEndQuest(this, QuestOwnerPawn->GetController()))
            {
                if (GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Blue,
                        FString::Printf(
                            TEXT("Interact %s and %s"), *GetName(), *QuestOwnerPawn->GetController()->GetName()));
                }

                break;
            }
            else
            {
                continue;
            }
        }
    }
}

void ATAPlayerController::ExitButtonPressed(const FInputActionValue& Value)
{
    UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit, false);
}