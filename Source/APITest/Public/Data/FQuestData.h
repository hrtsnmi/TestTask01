// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FQuestData.generated.h"

UENUM() enum class EQuestProgress : uint8
{
    NONE UMETA(DisplayName = "NONE"),
    Get UMETA(DisplayName = "Get From Manager or NPC, depends on Interact State"),
    Done UMETA(DisplayName = "Done, NPC when give Quest, Player when complete"),
    Max UMETA(DisplayName = "Max")
};

UENUM()
enum class EQuestType : uint8
{
    MoveTo UMETA(DisplayName = "MoveTo"),
    FindItem UMETA(DisplayName = "FindItem")
};

UENUM()
enum class EInteractType : uint8
{
    Master UMETA(DisplayName = "Can Interact"),
    Slave UMETA(DisplayName = "Can Be Interact")
};

USTRUCT(BlueprintType)
struct FQuestData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Id = -1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestDesc;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EQuestType QuestType = EQuestType::MoveTo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector TargetLocation;
};
