// Fill out your copyright notice in the Description page of Project Settings.


#include "ATABaseCharacter.h"
#include "QuestSystem/TAQuestComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "TAPlayerState.h"


ATABaseCharacter::ATABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	QuestComponent = CreateDefaultSubobject<UTAQuestComponent>(TEXT("QuestComponent"));

    //InteractableInterface
    CurrentInteractType = EInteractType::Master;
}

void ATABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	if (ATAPlayerState* PState = GetController()->GetPlayerState<ATAPlayerState>())
    {
        PState->SetupDelegatesForQuestComponent(QuestComponent);
        QuestComponent->SetupDelegatesForPlayerState(PState);
    }
}

FQuestData ATABaseCharacter::UnderInteract_Implementation()
{
    return FQuestData();
}

EInteractType ATABaseCharacter::GetInteractType_Implementation() const
{
    return CurrentInteractType;
}

void ATABaseCharacter::Interact(const FInputActionValue& Value)
{
    bool bIsInteractStartes = Value.Get<bool>();
    
    if (bIsInteractStartes)
    {
        TArray<AActor*> QuestOwnerActors;
        GetOverlappingActors(QuestOwnerActors, UInteractableInterface::StaticClass());

        for (AActor* QuestOwnerActor : QuestOwnerActors)
        {
            FVector DistanceToActorNorm = QuestOwnerActor->GetActorLocation() - GetActorLocation();
            DistanceToActorNorm.Normalize();
            if (FVector::DotProduct(GetActorForwardVector(), DistanceToActorNorm) < 0.6f)
            {
                continue;
            }

            // this is pointed to Actor
            if (CurrentInteractType == EInteractType::Slave ||
                IInteractableInterface::Execute_GetInteractType(QuestOwnerActor) == EInteractType::Master)
            {
                continue;
            }

            // TODO: Get QuestData
            IInteractableInterface::Execute_UnderInteract(QuestOwnerActor);
        }
    }
}

void ATABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    APlayerController* PlayerController = Cast<APlayerController>(GetController());

    UEnhancedInputLocalPlayerSubsystem* Subsystem =
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(DefaultMappingContext, 0);

    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATABaseCharacter::Move);
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATABaseCharacter::Look);
    EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ATABaseCharacter::Interact);
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