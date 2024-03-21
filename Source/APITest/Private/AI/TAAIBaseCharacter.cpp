// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TAAIBaseCharacter.h"
#include "QuestSystem/TAQuestComponent.h"
#include "TAPlayerState.h"
#include "Components/SphereToShowWidgetComponent.h"
#include "Components/NPCWidgetComponent.h"


ATAAIBaseCharacter::ATAAIBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	QuestComponent = CreateDefaultSubobject<UTAQuestComponent>(TEXT("QuestComponent"));

	CurrentInteractType = EInteractType::Slave;

    WorldWidget = CreateDefaultSubobject<UNPCWidgetComponent>(TEXT("World Widget"));
    WorldWidget->SetupAttachment(RootComponent);
    WorldWidget->SetVisibility(false);

    SphereComp = CreateDefaultSubobject<USphereToShowWidgetComponent>(TEXT("Sphere Comp"));
    SphereComp->SetupAttachment(RootComponent);
}

void ATAAIBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    

    if (ATAPlayerState* PState = GetController()->GetPlayerState<ATAPlayerState>())
    {
        PState->SetupDelegatesForQuestComponent(QuestComponent);
        QuestComponent->SetupDelegatesForPlayerState(PState);
    }

    if (CurrentInteractType == EInteractType::Slave)
    {
        QuestComponent->SetOwnersQuest(UTAQuestManager::GetInstance()->GetAvailableQuest());
    }

    SphereComp->OnGotWidgetVisibility.BindLambda([this]() -> bool
        {
            return WorldWidget ? (WorldWidget->IsVisible()) : (false);
        });

    SphereComp->OnSetWidgetVisibility.BindLambda([this](bool Visibility)
        { 
            WorldWidget->SetVisibility(Visibility);
        });
}

FQuestData ATAAIBaseCharacter::UnderInteract_Implementation()
{
    FQuestData TMPQuestData;
    TMPQuestData.Id = -1;
    QuestComponent->GetOwnersQuest(TMPQuestData);
    
    return TMPQuestData;
}

EInteractType ATAAIBaseCharacter::GetInteractType_Implementation() const
{
    return CurrentInteractType;
}

void ATAAIBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}