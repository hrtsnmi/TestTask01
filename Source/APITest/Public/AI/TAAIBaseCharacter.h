// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interfaces/InteractableInterface.h"

#include "TAAIBaseCharacter.generated.h"


class UTAQuestComponent;

UCLASS()
class APITEST_API ATAAIBaseCharacter : public ACharacter, public IInteractableInterface
{
	GENERATED_BODY()

public:
	ATAAIBaseCharacter();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UTAQuestComponent> QuestComponent;

protected:  // InteractableInterface
    EInteractType CurrentInteractType;

    FQuestData UnderInteract_Implementation();

public:
    EInteractType GetInteractType_Implementation() const;
    // void SetInteractType_Implementation(EInteractType InteractType);
};
