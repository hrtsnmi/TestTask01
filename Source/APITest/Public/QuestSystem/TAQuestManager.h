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

    friend struct TDefaultDelete<UTAQuestManager>;

private:
    UPROPERTY()
    TArray<FQuestData> QuestDataArray;
    mutable int32 index{0};

protected:
    UTAQuestManager();
    ~UTAQuestManager();

    //static UTAQuestManager* SingletonInstance;

public:

    static UTAQuestManager* GetInstance();

    const FQuestData& GetAvailableQuest() const;
};