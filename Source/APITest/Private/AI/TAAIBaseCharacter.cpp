// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TAAIBaseCharacter.h"
#include "Components/SphereToShowWidgetComponent.h"
#include "Components/NPCWidgetComponent.h"

ATAAIBaseCharacter::ATAAIBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    WorldWidget = CreateDefaultSubobject<UNPCWidgetComponent>(TEXT("World Widget"));
    WorldWidget->SetupAttachment(RootComponent);
    WorldWidget->SetVisibility(false);

    SphereComp = CreateDefaultSubobject<USphereToShowWidgetComponent>(TEXT("Sphere Comp"));
    SphereComp->SetupAttachment(RootComponent);
}

void ATAAIBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    SphereComp->OnGotWidgetVisibility.BindLambda([this]() -> bool
        {
            return WorldWidget ? (WorldWidget->IsVisible()) : (false);
        });

    SphereComp->OnSetWidgetVisibility.BindLambda([this](bool Visibility)
        { 
            WorldWidget->SetVisibility(Visibility);
        });
}

void ATAAIBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}