// Fill out your copyright notice in the Description page of Project Settings.


#include "ATABaseCharacter.h"
#include "QuestSystem/TAQuestComponent.h"
#include "Interfaces/InteractableInterface.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


ATABaseCharacter::ATABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	QuestComponent = CreateDefaultSubobject<UTAQuestComponent>(TEXT("QuestComponent"));

}

void ATABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATABaseCharacter::AvailableToBeginQuest(APawn* QuestOwnerPawn)
{
    AController* QuestOwnerController = QuestOwnerPawn->GetController();
    if (!GetController()->GetClass()->ImplementsInterface(UQuestComponentOwnerInterface::StaticClass()) ||
        !QuestOwnerController->GetClass()->ImplementsInterface(UQuestComponentOwnerInterface::StaticClass()))
    {
        return;
    }

    if (IInteractableInterface::Execute_GetInteractType(GetController()) == EInteractType::Slave ||
        IInteractableInterface::Execute_GetInteractType(QuestOwnerController) == EInteractType::Master)
    {
        return;
    }

    // TODO: Ask GameMode for starting New Quest

    SetDataInComponent_Implementation(IInteractableInterface::Execute_UnderInteract(QuestOwnerPawn), QuestOwnerPawn);
}

void ATABaseCharacter::SetDataInComponent_Implementation(FQuestData NewQuestData, AActor* QuestGiver)
{
    QuestComponent->SetOwnersQuest(NewQuestData, QuestGiver);
}

void ATABaseCharacter::Interact(const FInputActionValue& Value)
{
    bool bIsInteractStartes = Value.Get<bool>();

    if (!bIsInteractStartes)
    {
        return;
    }

    TArray<AActor*> QuestOwnerActors;
    GetOverlappingActors(QuestOwnerActors, UQuestComponentOwnerInterface::StaticClass());

    for (AActor* QuestOwnerActor : QuestOwnerActors)
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

        if (APawn* QuestOwnerPawn = Cast<APawn>(QuestOwnerActor))
        {
            AvailableToBeginQuest(QuestOwnerPawn);

            break;
        }
    }
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