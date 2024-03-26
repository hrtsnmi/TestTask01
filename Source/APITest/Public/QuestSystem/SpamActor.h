// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpamActor.generated.h"

class USphereToShowWidgetComponent;

DECLARE_DELEGATE_OneParam(OnEndQuestConditionsReachingSignature, APawn*);

UCLASS()
class APITEST_API ASpamActor : public AActor
{
	GENERATED_BODY()
	
private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<USphereToShowWidgetComponent> SphereComp;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    bool bIsFindItem{true};

public:	
	// Sets default values for this actor's properties
	ASpamActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	OnEndQuestConditionsReachingSignature OnEndQuestConditionsReaching;
};
