// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "SphereToShowWidgetComponent.generated.h"

DECLARE_DELEGATE_RetVal(bool, OnGotWidgetVisibilitySignature)
DECLARE_DELEGATE_OneParam(OnSetWidgetVisibilitySignature, bool)
    /**
 * 
 */
UCLASS()
class APITEST_API USphereToShowWidgetComponent : public USphereComponent
{
	GENERATED_BODY()
	
private:
    AActor* WatchedActor{nullptr};
 
private:
    UFUNCTION()
    void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void ComponentEndOverlap(
        UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    void WatchActorInRangeToShowWidget(AActor* OtherActor, bool bIsWidgetVisible);

protected:
    virtual void BeginPlay() override;

public:
    OnGotWidgetVisibilitySignature OnGotWidgetVisibility;
    OnSetWidgetVisibilitySignature OnSetWidgetVisibility;
};
