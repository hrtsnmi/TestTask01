// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TAAIBaseCharacter.h"
#include "QuestSystem/TAQuestComponent.h"
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
    static FQuestData TMPQuestData;
    QuestComponent->GetOwnersQuest(TMPQuestData);
    
    return TMPQuestData;
}

EInteractType ATAAIBaseCharacter::GetInteractType_Implementation() const
{
    return CurrentInteractType;
}

void ATAAIBaseCharacter::SetInteractType_Implementation(EInteractType InteractType)
{
    CurrentInteractType = InteractType;
}

void ATAAIBaseCharacter::SetDataInComponent_Implementation(FQuestData NewQuestData)
{
    QuestComponent->SetOwnersQuest(NewQuestData);
}

void ATAAIBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}