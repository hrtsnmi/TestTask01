// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TAAIBaseCharacter.h"
#include "QuestSystem/TAQuestComponent.h"

ATAAIBaseCharacter::ATAAIBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	QuestComponent = CreateDefaultSubobject<UTAQuestComponent>(TEXT("QuestComponent"));

	CurrentInteractType = EInteractType::Slave;
}

void ATAAIBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

FQuestData ATAAIBaseCharacter::UnderInteract_Implementation()
{
    return FQuestData();
}

EInteractType ATAAIBaseCharacter::GetInteractType_Implementation() const
{
    return CurrentInteractType;
}

void ATAAIBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


