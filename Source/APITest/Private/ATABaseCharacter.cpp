// Fill out your copyright notice in the Description page of Project Settings.


#include "ATABaseCharacter.h"
#include "Interfaces/InteractableInterface.h"
#include "Functions/Functions.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


ATABaseCharacter::ATABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATABaseCharacter::Interact(const FInputActionValue& Value)
{
    bool bIsInteractStartes = Value.Get<bool>();

    if (!bIsInteractStartes)
    {
        return;
    }

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Blue, FString::Printf(TEXT("E button pressed")));
    }

    TArray<AActor*> QuestOwnerActors;
    GetOverlappingActors(QuestOwnerActors, UQuestComponentOwnerInterface::StaticClass());

    for (AActor* QuestOwnerActor : QuestOwnerActors)
    {
        if (APawn* QuestOwnerPawn = Cast<APawn>(QuestOwnerActor))
        {
            if (QuestOwnerActor == this)
            {
                continue;
            }

            FVector DistanceToActorNorm = QuestOwnerActor->GetActorLocation() - GetActorLocation();
            DistanceToActorNorm.Normalize();
            if (FVector::DotProduct(GetActorForwardVector(), DistanceToActorNorm) < 0.6f)
            {
                continue;
            }

            if (TryToSendRequestToStartEndQuest(QuestOwnerPawn->GetController()))
            {
                break;
            }
            else
            {
                continue;
            }
        }
    }
}
bool ATABaseCharacter::TryToSendRequestToStartEndQuest(AController* NPCController)
{
    bool ControllersHasInteractableInterface =
        HasInterfaceChecker::HasInteractableInterface(GetController()) && HasInterfaceChecker::HasInteractableInterface(NPCController);

    if (!ControllersHasInteractableInterface)
    {
        return ControllersHasInteractableInterface;
    }

    if (IInteractableInterface::Execute_CanEndQuest(NPCController))
    {
        IInteractableInterface::Execute_PawnTryToEndQuest(GetController(), NPCController);
        IInteractableInterface::Execute_PawnTryToEndQuest(NPCController, GetController());
        return ControllersHasInteractableInterface;
    }

    if (IInteractableInterface::Execute_CanStartQuest(NPCController))
    {
        IInteractableInterface::Execute_PawnTryToStartNewQuest(GetController(), NPCController);
        IInteractableInterface::Execute_PawnTryToStartNewQuest(NPCController, GetController());
        return ControllersHasInteractableInterface;
    }

    return ControllersHasInteractableInterface;
}



void ATABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

        Subsystem->ClearAllMappings();
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATABaseCharacter::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATABaseCharacter::Look);
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ATABaseCharacter::Interact);
    }
}

void ATABaseCharacter::Move(const FInputActionValue& Value)
{
    if (!Controller)
    {
        return;
    }

    const FVector2D MovementVector = Value.Get<FVector2D>();
    const FRotator YawRotation(0, GetControlRotation().Yaw, 0);
    FVector MoveDirection;

    if (MoveDirection.Y != 0.f)
    {
        MoveDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(MoveDirection, MovementVector.Y);
    }
    if (MoveDirection.X != 0.f)
    {
        MoveDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(MoveDirection, MovementVector.X);
    }
}

void ATABaseCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // add yaw and pitch input to controller
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(-LookAxisVector.Y);
    }
}