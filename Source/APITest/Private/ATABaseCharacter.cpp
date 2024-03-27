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
	
     if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

        // Subsystem->ClearAllMappings();
        Subsystem->AddMappingContext(DefaultMappingContext, 1);
    }
}

void ATABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            6, 0.5f, FColor::Blue, FString::Printf(TEXT("%s location: %s"), *GetName(), *GetActorLocation().ToString()));
    }
}

void ATABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATABaseCharacter::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATABaseCharacter::Look);
        //EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ATABaseCharacter::Interact);
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

    if (!Controller)
    {
        return;
    }

    // add yaw and pitch input to controller
    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(-LookAxisVector.Y);
}

