// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "NPCWidgetComponent.generated.h"

/**
 * 
 */
class UNPCInfoWidget;

UCLASS()
class APITEST_API UNPCWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
private:  // Widget
    UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
    UNPCInfoWidget* CurrentWidget;
    UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UNPCInfoWidget> HUD;

public:
    /** UActorComponent Interface */
    virtual void BeginPlay() override;
};
