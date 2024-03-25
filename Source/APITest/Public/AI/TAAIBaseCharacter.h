// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CharacterWithQuestComponent/CharacterWithQuestComponent.h"

#include "TAAIBaseCharacter.generated.h"

class USphereToShowWidgetComponent;
class UNPCWidgetComponent;

UCLASS()
class APITEST_API ATAAIBaseCharacter : public ACharacterWithQuestComponent
{
	GENERATED_BODY()

public:
	ATAAIBaseCharacter();

	virtual void Tick(float DeltaTime) override;

private: //Widget
    UPROPERTY(EditInstanceOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UNPCWidgetComponent> WorldWidget;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<USphereToShowWidgetComponent> SphereComp;

protected:

	virtual void BeginPlay() override;
    
};
