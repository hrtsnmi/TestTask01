// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SphereToShowWidgetComponent.h"
#include "Interfaces/InteractableInterface.h"
#include "Interfaces/HasInterfaceChecker.h"

void USphereToShowWidgetComponent::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (GetOwner() == OtherActor)
    {
        return;
    }

    if (!OnGotWidgetVisibility.IsBound())
    {
        return;
    }

    if (APawn* OtherPawn = Cast<APawn>(OtherActor))
    {
        WatchActorInRangeToShowWidget(OtherPawn->GetController(), OnGotWidgetVisibility.Execute());
    }
}

void USphereToShowWidgetComponent::ComponentEndOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (GetOwner() == OtherActor)
    {
        return;
    }

    if (!OnGotWidgetVisibility.IsBound())
    {
        return;
    }
    
    if (APawn* OtherPawn = Cast<APawn>(OtherActor))
    {
        WatchActorInRangeToShowWidget(OtherPawn->GetController(), OnGotWidgetVisibility.Execute());
    }
}

void USphereToShowWidgetComponent::WatchActorInRangeToShowWidget(AActor* OtherActor, bool bIsWidgetVisible)
{
    if (!HasInterfaceChecker::HasInteractableInterface(OtherActor))
    {
        return;
    }

    bool Visability = false;
    if (bIsWidgetVisible)
    {
        Visability = WatchedActor != OtherActor;

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

    OnSetWidgetVisibility.ExecuteIfBound(Visability);
}

void USphereToShowWidgetComponent::BeginPlay()
{
    Super::BeginPlay();

    OnComponentBeginOverlap.AddDynamic(this, &USphereToShowWidgetComponent::ComponentBeginOverlap);
    OnComponentEndOverlap.AddDynamic(this, &USphereToShowWidgetComponent::ComponentEndOverlap);
}
