// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestSystem/TAQuestManager.h"
#include "TAQuestComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class APITEST_API UTAQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTAQuestComponent();

protected:

	void InitNewQuest(FQuestData QusetData);

	void MarkSuccessQuset(FQuestData QusetData);

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
