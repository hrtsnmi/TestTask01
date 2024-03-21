// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestSystem/TAQuestManager.h"
#include "TAQuestComponent.generated.h"

DECLARE_DELEGATE_RetVal(FQuestData, OnGetQuestDataSignature)
DECLARE_DELEGATE_OneParam(OnSetQuestDataSignature, FQuestData)

class ATAPlayerState;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class APITEST_API UTAQuestComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	void StartMoveTo();
    void StartFindItem();

public:	
	UTAQuestComponent();

protected:

	void InitNewQuest(FQuestData QusetData);

	void MarkSuccessQuset(FQuestData QusetData);

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Delegates for proccesing info of quest in PlayerState
	OnGetQuestDataSignature OnGetQuestData;
    OnSetQuestDataSignature OnSetQuestData;

	bool GetOwnersQuest(FQuestData& OutQuestData) const;
    bool SetOwnersQuest(FQuestData NewQuestData);

	void SetupDelegatesForPlayerState(ATAPlayerState* PlayerState);

};
