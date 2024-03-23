// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "TAQuestManager.generated.h"

struct FQuestData;

UCLASS()
class APITEST_API UTAQuestManager : public UObject
{
    GENERATED_BODY()

private:
    UPROPERTY()
    TArray<FQuestData> QuestDataArray;
    int32 index{0};

protected:
    UTAQuestManager();

    static UTAQuestManager* SingletonInstance;

public:

    static UTAQuestManager* GetInstance();

    FQuestData GetAvailableQuest();
};