// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TAMainGameInstance.generated.h"

UCLASS()
class APITEST_API UTAMainGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    virtual void Init() override;
};
