// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NPCInfoWidget.h"
#include "Components/TextBlock.h"
#include "AI/TAAIBaseCharacter.h"
#include "QuestSystem/TAQuestComponent.h"

void UNPCInfoWidget::UpdateQuestInfo(const FQuestData& NewQuestData, EQuestProgress NewQuestProgress, AActor* QuestGiver)
{
    
    if (NewQuestData.Id == -1)
    {
        static const FName NoQuest = FName(TEXT("Quest is unavailable "));
        TB_ID->SetText(FText::FromName(NoQuest));

        TB_QuestDesc->SetText(FText());
        TB_QuestType->SetText(FText());
        TB_TargetLocation->SetText(FText());
    }
    else
    {
        static const FName ID = FName(TEXT("ID: "));
        static const FName QuestDesc = FName(TEXT("Quest Desc: "));
        static const FName QuestType = FName(TEXT("Quest Type: "));
        static const FName TargetLocation = FName(TEXT("Target Location: "));
        static const FName FindItem = FName(TEXT("FindItem"));
        static const FName MoveTo = FName(TEXT("MoveTo"));

        FString tmpString = ID.ToString() + FString::FromInt(NewQuestData.Id);
        TB_ID->SetText(FText::FromString(tmpString));

        tmpString = QuestDesc.ToString() + NewQuestData.QuestDesc;
        TB_QuestDesc->SetText(FText::FromString(tmpString));

        tmpString = QuestType.ToString() + (NewQuestData.QuestType == EQuestType::FindItem ? (FindItem.ToString()) : (MoveTo.ToString()));
        TB_QuestType->SetText(FText::FromString(tmpString));

        tmpString = TargetLocation.ToString() + NewQuestData.TargetLocation.ToString();
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
