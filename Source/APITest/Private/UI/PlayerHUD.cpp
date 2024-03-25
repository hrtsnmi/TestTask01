// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD.h"
#include "UI/NPCInfoWidget.h"
#include "Interfaces/QuestComponentOwnerInterface.h"
#include "Functions/Functions.h"

void APlayerHUD::BeginPlay()
{
    Super::BeginPlay();

    CurrentWidget = CreateWidget<UNPCInfoWidget>(GetWorld(), HUD);
    CurrentWidget->AddToViewport();

    if (HasInterfaceChecker::HasQuestComponentOwnerInterface(GetOwningPawn()))
    {
        CurrentWidget->SetupQuestComponentDelegates(IQuestComponentOwnerInterface::Execute_GetQuestComponent(GetOwningPawn()));
    }
}
