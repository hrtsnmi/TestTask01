// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interfaces/InteractableInterface.h"

#include "TAAIBaseCharacter.generated.h"

class UTAQuestComponent;
class USphereComponent;
class UWidgetComponent;
class UNPCInfoWidget;

UCLASS()
class APITEST_API ATAAIBaseCharacter : public ACharacter, public IInteractableInterface
{
	GENERATED_BODY()

public:
	ATAAIBaseCharacter();

	virtual void Tick(float DeltaTime) override;

private:
    UFUNCTION()
    void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

   UFUNCTION()
    void ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

   void WatchActorInRangeToShowWidget(AActor* OtherActor, bool bIsWidgetVisible);


private: //Widget
    UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
    UNPCInfoWidget* CurrentWidget;
    UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UNPCInfoWidget> HUD;
    UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
    UWidgetComponent* WorldWidget;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UTAQuestComponent> QuestComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USphereComponent* SphereComp;

protected:
    //void GetAvailableQuestDataFromGameMode();

protected:  // InteractableInterface
    EInteractType CurrentInteractType;

    FQuestData UnderInteract_Implementation();

public:
    EInteractType GetInteractType_Implementation() const;
    // void SetInteractType_Implementation(EInteractType InteractType);
};
