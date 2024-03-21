// Fill out your copyright notice in the Description page of Project Settings.


#include "ATABaseCharacter.h"
#include "QuestSystem/TAQuestComponent.h"
#include "TAPlayerState.h"

ATABaseCharacter::ATABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	QuestComponent = CreateDefaultSubobject<UTAQuestComponent>(TEXT("QuestComponent"));

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

void ATABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

