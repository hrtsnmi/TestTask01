// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interfaces/QuestComponentOwnerInterface.h"

#include "CharacterWithQuestComponent.generated.h"

class UTAQuestComponent;

UCLASS(Abstract)
class APITEST_API ACharacterWithQuestComponent : public ACharacter, public IQuestComponentOwnerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterWithQuestComponent();

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<UTAQuestComponent> QuestComponent;

   

public:  // IQuestComponentOwnerInterface
    UTAQuestComponent* GetQuestComponent_Implementation() const { return QuestComponent; }

    bool SetDataInComponent_Implementation(const FQuestData& NewQuestData, EQuestProgress NewQuestProgress, AActor* QuestGiver);
    bool GetDataFromComponent_Implementation(FQuestData& OutQuestData, EQuestProgress& OutQuestProgress);

};
