#pragma once

#include "QuestSystem/TAQuestManager.h"
#include "Dom/JsonObject.h"
#include "JsonObjectConverter.h"

TSharedPtr<FJsonObject> ReadJSon(const FName& JsonPath)
{
    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*JsonPath.ToString()))
    {
        return nullptr;
    }

    FString AfterJsonIsReadAsString;
    if (!FFileHelper::LoadFileToString(AfterJsonIsReadAsString, *JsonPath.ToString()))
    {
        return nullptr;
    }

    auto Reader = TJsonReaderFactory<>::Create(AfterJsonIsReadAsString);
    TSharedPtr<FJsonObject> AfterJsonIsReadAsObject;
    //Try to convert string to JSonObj
    if (!FJsonSerializer::Deserialize(Reader, AfterJsonIsReadAsObject))
    {
        nullptr;
    }

    return AfterJsonIsReadAsObject;
}

TArray<FQuestData> ReadToArrayFromJsonObject(TSharedPtr<FJsonObject> JSonObject)
{
    TArray<TSharedPtr<FJsonValue>> JsonValues = JSonObject->GetArrayField(TEXT("questArray"));

    TArray<FQuestData> Result;
    for (TSharedPtr<FJsonValue>& JsonValue : JsonValues)
    {
        if (JsonValue.IsValid())
        {
            FQuestData ReadQuestData;

            if (FJsonObjectConverter::JsonObjectToUStruct<FQuestData>(JsonValue->AsObject().ToSharedRef(), &ReadQuestData))
            {
                ReadQuestData.TargetLocation = (FVector(
                    JsonValue->AsObject()->TryGetField(TEXT("locationX"))->AsNumber(),
                    JsonValue->AsObject()->TryGetField(TEXT("locationY"))->AsNumber(),
                    JsonValue->AsObject()->TryGetField(TEXT("locationZ"))->AsNumber()
                ));
                Result.Emplace(MoveTemp(ReadQuestData));
            }
        }
    }
    
    return Result;
}