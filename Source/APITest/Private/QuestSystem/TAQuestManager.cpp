// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSystem/TAQuestManager.h"
#include "Misc/Paths.h"
#include "QuestSystem/ReadJson.h"
#include "Data/FQuestData.h"

//UTAQuestManager* UTAQuestManager::SingletonInstance = nullptr;

UTAQuestManager::UTAQuestManager()
{
    FString JsonPath;
    FQuestData QuestData;
    JsonPath += FPaths::ProjectContentDir() + FString(TEXT("Json//questData.json"));

    QuestDataArray = MoveTempIfPossible(ReadToArrayFromJsonObject(ReadJSon(*JsonPath)));

    //SingletonInstance = this;

    AddToRoot();
}

//UTAQuestManager::~UTAQuestManager()
//{
//    QuestDataArray.Empty();
//    SingletonInstance->RemoveFromRoot();
//}

UTAQuestManager* UTAQuestManager::GetInstance()
{
    static UTAQuestManager* SingletonInstance = NewObject<UTAQuestManager>();
    
    return SingletonInstance;
}

const FQuestData& UTAQuestManager::GetAvailableQuest() const
{
    if (QuestDataArray.IsEmpty())
    {
        static FQuestData EmptyData;
        return EmptyData;
    }
    else
    {
        const FQuestData& DataToTransfer{QuestDataArray[index++]};
        index %= QuestDataArray.Num();

        return DataToTransfer;
    }
}
