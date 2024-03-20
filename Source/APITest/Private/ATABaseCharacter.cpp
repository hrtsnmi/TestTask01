// Fill out your copyright notice in the Description page of Project Settings.


#include "ATABaseCharacter.h"
#include "QuestSystem/TAQuestComponent.h"

ATABaseCharacter::ATABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	QuestComponent = CreateDefaultSubobject<UTAQuestComponent>(TEXT("QuestComponent"));

}

void ATABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

