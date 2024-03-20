// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TAQuestManager.generated.h"

UENUM()
enum class EQuestType : uint8
{
    MoveTo UMETA(DisplayName = "MoveTo"),
    FindItem UMETA(DisplayName = "FindItem")
};

USTRUCT(BlueprintType)
struct FQuestData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Id = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestDesc;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EQuestType QuestType = EQuestType::MoveTo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector TargetLocation;
};

UCLASS()
class APITEST_API UTAQuestManager : public UObject
{
    GENERATED_BODY()

private:
    UPROPERTY()
    TArray<FQuestData> QuestDataArray;
};
