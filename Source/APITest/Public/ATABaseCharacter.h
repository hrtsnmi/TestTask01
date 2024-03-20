// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ATABaseCharacter.generated.h"

class UTAQuestComponent;

UCLASS()
class APITEST_API ATABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATABaseCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UTAQuestComponent> QuestComponent;

};
