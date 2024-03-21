// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/TABaseGameMode.h"
#include "QuestSystem/TAQuestManager.h"
//#include "Interfaces/InteractableInterface.h"
//#include "TAPlayerState.h"


ATABaseGameMode::ATABaseGameMode()
{
    UTAQuestManager::GetInstance();
}


void ATABaseGameMode::StartPlay()
{
    Super::StartPlay();

}
