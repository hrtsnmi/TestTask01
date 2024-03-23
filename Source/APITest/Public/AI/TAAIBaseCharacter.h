// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interfaces/InteractableInterface.h"
#include "../Interfaces/QuestComponentOwnerInterface.h"

#include "TAAIBaseCharacter.generated.h"

class UTAQuestComponent;
class USphereToShowWidgetComponent;
class UNPCWidgetComponent;

UCLASS()
class APITEST_API ATAAIBaseCharacter : public ACharacter, public IInteractableInterface, public IQuestComponentOwnerInterface
{
	GENERATED_BODY()

public:
	ATAAIBaseCharacter();

	virtual void Tick(float DeltaTime) override;


private: //Widget
    UPROPERTY(EditInstanceOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UNPCWidgetComponent> WorldWidget;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UTAQuestComponent> QuestComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<USphereToShowWidgetComponent> SphereComp;

protected:
    //void GetAvailableQuestDataFromGameMode();

protected:  // InteractableInterface
    EInteractType CurrentInteractType;

    FQuestData UnderInteract_Implementation();

public:
    EInteractType GetInteractType_Implementation() const;
    void SetInteractType_Implementation(EInteractType InteractType);

public:  // IQuestComponentOwnerInterface
    UTAQuestComponent* GetQuestComponent_Implementation() const { return QuestComponent; }
    void SetDataInComponent_Implementation(FQuestData NewQuestData);
};
