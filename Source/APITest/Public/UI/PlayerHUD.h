// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
class UNPCInfoWidget;

UCLASS()
class APITEST_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
private:  // Widget
    UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
    UNPCInfoWidget* CurrentWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UNPCInfoWidget> HUD;

protected:
    virtual void BeginPlay() override;
};
