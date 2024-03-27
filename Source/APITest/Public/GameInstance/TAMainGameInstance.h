// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TAMainGameInstance.generated.h"

class UTAQuestManager;

UCLASS()
class APITEST_API UTAMainGameInstance : public UGameInstance
{
    GENERATED_BODY()

 private:
    TUniquePtr<UTAQuestManager> QuestManager;

public:
    virtual void Init() override;

    virtual void Shutdown() override;

    public:
    void SetupDelegatesForGameMode(AGameModeBase* CurrentGM);
};
