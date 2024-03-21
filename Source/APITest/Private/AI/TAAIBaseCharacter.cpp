// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TAAIBaseCharacter.h"
#include "QuestSystem/TAQuestComponent.h"
#include "TAPlayerState.h"

ATAAIBaseCharacter::ATAAIBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	QuestComponent = CreateDefaultSubobject<UTAQuestComponent>(TEXT("QuestComponent"));

	CurrentInteractType = EInteractType::Slave;
}

void ATAAIBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    if (ATAPlayerState* PState = GetController()->GetPlayerState<ATAPlayerState>())
    {
        PState->SetupDelegatesForQuestComponent(QuestComponent);
        QuestComponent->SetupDelegatesForPlayerState(PState);
    }
}

FQuestData ATAAIBaseCharacter::UnderInteract_Implementation()
{
    FQuestData TMPQuestData;
    TMPQuestData.Id = -1;
    QuestComponent->GetOwnersQuest(TMPQuestData);
    
    return TMPQuestData;
}

EInteractType ATAAIBaseCharacter::GetInteractType_Implementation() const
{
    return CurrentInteractType;
}

void ATAAIBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


