// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TAAIBaseCharacter.h"
#include "QuestSystem/TAQuestComponent.h"
#include "TAPlayerState.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/NPCInfoWidget.h"

ATAAIBaseCharacter::ATAAIBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	QuestComponent = CreateDefaultSubobject<UTAQuestComponent>(TEXT("QuestComponent"));

	CurrentInteractType = EInteractType::Slave;

    WorldWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("World Widget"));
    WorldWidget->SetupAttachment(RootComponent);
    WorldWidget->SetVisibility(false);

    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Comp"));
    SphereComp->SetupAttachment(RootComponent);
}

void ATAAIBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    if (HUD)
    {
        CurrentWidget = CreateWidget<UNPCInfoWidget>(GetWorld(), HUD);
        WorldWidget->SetWidget(CurrentWidget);
        CurrentWidget->SetupQuestComponentDelegates(QuestComponent);
    }

    if (ATAPlayerState* PState = GetController()->GetPlayerState<ATAPlayerState>())
    {
        PState->SetupDelegatesForQuestComponent(QuestComponent);
        QuestComponent->SetupDelegatesForPlayerState(PState);
    }

    if (CurrentInteractType == EInteractType::Slave)
    {
        QuestComponent->SetOwnersQuest(UTAQuestManager::GetInstance()->GetAvailableQuest());
    }

    SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATAAIBaseCharacter::ComponentBeginOverlap);
    SphereComp->OnComponentEndOverlap.AddDynamic(this, &ATAAIBaseCharacter::ComponentEndOverlap);
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

void ATAAIBaseCharacter::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (this != OtherActor && OtherActor)
    {
        WatchActorInRangeToShowWidget(OtherActor, WorldWidget->IsVisible());
    }
}

void ATAAIBaseCharacter::ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (this != OtherActor && OtherActor)
    {
        WatchActorInRangeToShowWidget(OtherActor, WorldWidget->IsVisible());
    }
}

void ATAAIBaseCharacter::WatchActorInRangeToShowWidget(AActor* OtherActor, bool bIsWidgetVisible)
{
    if (!OtherActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
    {
        return;
    }

    static AActor* WatchedActor = nullptr;
    bool Visability = false;
    if (bIsWidgetVisible)
    {
        WorldWidget->SetVisibility(WatchedActor != OtherActor);
        
        WatchedActor = nullptr;
    }
    else
    {
        Visability = IInteractableInterface::Execute_GetInteractType(OtherActor) == EInteractType::Master;
        if (Visability)
        {
            WatchedActor = OtherActor;
        }
    }

    WorldWidget->SetVisibility(Visability);
}



