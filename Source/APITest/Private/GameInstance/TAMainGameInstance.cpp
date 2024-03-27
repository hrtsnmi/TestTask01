// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/TAMainGameInstance.h"
#include "QuestSystem/TAQuestManager.h"
#include "Gamemode/TABaseGameMode.h"
#include "Data/FQuestData.h"

void UTAMainGameInstance::Init()
{
    Super::Init();

    // TO DO Create QuestManager object and call a function to convert .json the file into an array of struct
    QuestManager.Reset(UTAQuestManager::GetInstance());

}

void UTAMainGameInstance::Shutdown()
{
    Super::Shutdown();

    QuestManager.Release();
}

void UTAMainGameInstance::SetupDelegatesForGameMode(AGameModeBase* CurrentGM)
{
    if (ATABaseGameMode* TAGM = Cast<ATABaseGameMode>(CurrentGM))
    {
        const TUniquePtr<UTAQuestManager>& QuestManagerRef = QuestManager;

        TAGM->OnGameModeNeedsToGetQuest.BindLambda(
            [&QuestManagerRef]() -> const FQuestData&
            {
                if (QuestManagerRef.IsValid())
                {
                    return QuestManagerRef->GetAvailableQuest();
                }
                else
                {
                    static FQuestData EmptyData;
                    return EmptyData;
                }
            });
    }
}
