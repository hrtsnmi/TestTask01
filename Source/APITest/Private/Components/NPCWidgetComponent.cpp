// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NPCWidgetComponent.h"
#include "Interfaces/QuestComponentOwnerInterface.h"
#include "UI/NPCInfoWidget.h"

void UNPCWidgetComponent::BeginPlay()
{
    Super::BeginPlay();

    if (HUD && GetOwner()->GetClass()->ImplementsInterface(UQuestComponentOwnerInterface::StaticClass()))
    {
        CurrentWidget = CreateWidget<UNPCInfoWidget>(GetWorld(), HUD);
        SetWidget(CurrentWidget);
        CurrentWidget->SetupQuestComponentDelegates(IQuestComponentOwnerInterface::Execute_GetQuestComponent(GetOwner()));
    }
}
