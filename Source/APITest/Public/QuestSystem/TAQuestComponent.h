// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Gamemode/DeclaringDelegatesForQuestFlow.h"
#include "Data/FQuestData.h"
#include "TAQuestComponent.generated.h"

class ATAPlayerState;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class APITEST_API UTAQuestComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	//void StartMoveTo();
    //void StartFindItem();

public:	
	UTAQuestComponent();

protected:

	void InitNewQuest(FQuestData QusetData);

	void MarkSuccessQuset(FQuestData QusetData);

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Delegates for proccesing info of quest in PlayerState
    QuestFlowDelegates::OnGetQuestDataSignature OnGetQuestData;
    QuestFlowDelegates::OnSetQuestDataSignature OnSetQuestData;
    QuestFlowDelegates::OnGetQuestProgressSignature OnGetQuestProgress;

	bool GetOwnersQuest(FQuestData& OutQuestData, EQuestProgress& OutQuestProgress) const;
    bool SetOwnersQuest(const FQuestData& NewQuestData, EQuestProgress NewQuestProgress, AActor* QuestGiver);
   
};
