// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SphereToShowWidgetComponent.h"
#include "Interfaces/InteractableInterface.h"

void USphereToShowWidgetComponent::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (GetOwner() == OtherActor || !OtherActor)
    {
        return;
    }

    if (OnGotWidgetVisibility.IsBound())
    {
        WatchActorInRangeToShowWidget(OtherActor, OnGotWidgetVisibility.Execute());
    }
}

void USphereToShowWidgetComponent::ComponentEndOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (GetOwner() == OtherActor || !OtherActor)
    {
        return;
    }

    if (OnGotWidgetVisibility.IsBound())
    {
        WatchActorInRangeToShowWidget(OtherActor, OnGotWidgetVisibility.Execute());
    }
}

void USphereToShowWidgetComponent::WatchActorInRangeToShowWidget(AActor* OtherActor, bool bIsWidgetVisible)
{
    if (!OtherActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
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
