// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSystem/SpamActor.h"
#include "Components/SphereToShowWidgetComponent.h"
#include "Interfaces/QuestComponentOwnerInterface.h"

// Sets default values
ASpamActor::ASpamActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SphereComp = CreateDefaultSubobject<USphereToShowWidgetComponent>(TEXT("Sphere Comp"));
    SphereComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpamActor::BeginPlay()
{
    Super::BeginPlay();

    SphereComp->OnGotWidgetVisibility.BindLambda([]() -> bool 
        { 
            static bool boolean{true};
            boolean = !boolean;
            return boolean;
        });
    SphereComp->OnSetWidgetVisibility.BindLambda(
        [this](bool Visibility)
        {
            if (Visibility)
            {
                OnEndQuestConditionsReaching.ExecuteIfBound(SphereComp->GetWatchedActor());
                Destroy();
            }
        });

}

// Called every frame
void ASpamActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

