// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSystem/TAQuestManager.h"
#include "Misc/Paths.h"
#include "QuestSystem/ReadJson.h"
#include "Data/FQuestData.h"

UTAQuestManager* UTAQuestManager::SingletonInstance = nullptr;

UTAQuestManager::UTAQuestManager()
{
    SingletonInstance = this;
}

UTAQuestManager* UTAQuestManager::GetInstance()
{
    if (!SingletonInstance)
    {
        SingletonInstance = NewObject<UTAQuestManager>();
        SingletonInstance->AddToRoot();

        FString JsonPath;
        FQuestData QuestData;
        JsonPath += FPaths::ProjectContentDir() + FString(TEXT("Json//questData.json"));
        
        SingletonInstance->QuestDataArray = MoveTempIfPossible(ReadToArrayFromJsonObject(ReadJSon(*JsonPath)));
    }
    return SingletonInstance;
}

FQuestData UTAQuestManager::GetAvailableQuest()
{
    FQuestData DataToTransfer;

    if (QuestDataArray.IsEmpty())
    {
        //Dont have any quests
        DataToTransfer.Id = -1;
        return MoveTemp(DataToTransfer);
    }

    DataToTransfer = QuestDataArray[index];
    ++index %= QuestDataArray.Num();

    return MoveTemp(DataToTransfer);
}
