// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SphereToShowWidgetComponent.h"
#include "Interfaces/InteractableInterface.h"
#include "Functions/Functions.h"

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

void USphereToShowWidgetComponent::WatchActorInRangeToShowWidget(AController* OtherActor, bool bIsWidgetVisible)
{
    if (!HasInterfaceChecker::HasInteractableInterface(OtherActor))
    {
        return;
    }

    bool Visibility = false;
    if (bIsWidgetVisible)
    {
        Visibility = WatchedActor.Get() != OtherActor->GetPawn();

       WatchedActor.Reset();
    }
    else
    {
        Visibility = IInteractableInterface::Execute_GetInteractType(OtherActor) == EInteractType::Master;
        if (Visibility)
        {
            WatchedActor = OtherActor->GetPawn();
        }
    }

    OnSetWidgetVisibility.ExecuteIfBound(Visibility);
}

void USphereToShowWidgetComponent::BeginPlay()
{
    Super::BeginPlay();

    OnComponentBeginOverlap.AddDynamic(this, &USphereToShowWidgetComponent::ComponentBeginOverlap);
    OnComponentEndOverlap.AddDynamic(this, &USphereToShowWidgetComponent::ComponentEndOverlap);
}
