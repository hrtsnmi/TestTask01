// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWithQuestComponent/CharacterWithQuestComponent.h"
#include "QuestSystem/TAQuestComponent.h"

// Sets default values
ACharacterWithQuestComponent::ACharacterWithQuestComponent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    QuestComponent = CreateDefaultSubobject<UTAQuestComponent>(TEXT("QuestComponent"));
}

bool ACharacterWithQuestComponent::SetDataInComponent_Implementation(
    const FQuestData& NewQuestData, EQuestProgress NewQuestProgress, AActor* QuestGiver)
{
    return QuestComponent->SetOwnersQuest(NewQuestData, NewQuestProgress, QuestGiver);
}

bool ACharacterWithQuestComponent::GetDataFromComponent_Implementation(FQuestData& OutQuestData, EQuestProgress& OutQuestProgress)
{
    return QuestComponent->GetOwnersQuest(OutQuestData, OutQuestProgress);
}

