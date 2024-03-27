// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NPCInfoWidget.h"
#include "Components/TextBlock.h"
#include "QuestSystem/TAQuestComponent.h"

void UNPCInfoWidget::UpdateQuestInfo(const FQuestData& NewQuestData, EQuestProgress NewQuestProgress, AActor* QuestGiver)
{
    static const FString QuestProgress = FString(TEXT("QuestProgress: "));
    static const FString NoneProgress = FString(TEXT("None"));
    static const FString GetProgress = FString(TEXT("Get"));
    static const FString DoneProgress = FString(TEXT("Done"));

    FString tmpString = QuestProgress;
    switch (NewQuestProgress)
    {
        case EQuestProgress::NONE: tmpString += NoneProgress; break;
        case EQuestProgress::Get: tmpString += GetProgress; break;
        default: tmpString += DoneProgress; break;
    }
    TB_QuestProgress->SetText(FText::FromString(tmpString));

    if (NewQuestData.Id == -1)
    {
        static const FString NoQuest = FString(TEXT("Quest is unavailable "));
        TB_ID->SetText(FText::FromString(NoQuest));

        TB_QuestDesc->SetText(FText());
        TB_QuestType->SetText(FText());
        TB_TargetLocation->SetText(FText());
    }
    else
    {

        static const FString ID = FString(TEXT("ID: "));
        static const FString QuestDesc = FString(TEXT("Quest Desc: "));
        static const FString QuestType = FString(TEXT("Quest Type: "));
        static const FString TargetLocation = FString(TEXT("Target Location: "));
        static const FString FindItem = FString(TEXT("FindItem"));
        static const FString MoveTo = FString(TEXT("MoveTo"));

        tmpString = ID + FString::FromInt(NewQuestData.Id);
        TB_ID->SetText(FText::FromString(tmpString));

        tmpString = QuestDesc + NewQuestData.QuestDesc;
        TB_QuestDesc->SetText(FText::FromString(tmpString));

        tmpString = QuestType + (NewQuestData.QuestType == EQuestType::FindItem ? FindItem : MoveTo);
        TB_QuestType->SetText(FText::FromString(tmpString));

        tmpString = TargetLocation + NewQuestData.TargetLocation.ToString();
        TB_TargetLocation->SetText(FText::FromString(tmpString));
    }
}

void UNPCInfoWidget::SetupQuestComponentDelegates(UTAQuestComponent* QuestComponent)
{
    QuestComponent->OnSetQuestData.AddUObject(this, &UNPCInfoWidget::UpdateQuestInfo);

    FQuestData QuestData;
    EQuestProgress EQuestProgress;
    
    if (QuestComponent->GetOwnersQuest(QuestData, EQuestProgress))
    {
        UpdateQuestInfo(QuestData, EQuestProgress, nullptr);
    }
}
