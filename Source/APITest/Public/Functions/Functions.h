// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */

namespace HasInterfaceChecker
{
bool HasInteractableInterface(AActor* Actor);

bool HasQuestComponentOwnerInterface(AActor* Actor);

}  // namespace HasInterfaceChecker

struct FQuestData;
enum class EInteractType : uint8;
enum class EQuestProgress : uint8;


namespace ControllersFunctions
{
void OnPossess(APawn* InPawn);

bool UnderInteract(AController* Controller, FQuestData& OutData, EQuestProgress& OutProgress);

bool CanPawnStartQuest(APawn* Pawn, EInteractType InteractType);

void PawnTryToStartNewQuest(
    AController* PlayerController, AController* NPCController, QuestFlowDelegates::OnQuestStartSignature& OnQuestStart);

// Control Quest Progress
EQuestProgress UpdateQuestProgress(AController* FuncCaller, EQuestProgress CurrentProgress, AActor* QuestGiver);
void PostProccessQuestProgress(AController* FuncCaller, EQuestProgress QuestProgress);

}  // namespace ControllerFunctions

class ATABaseGameMode;

namespace GameModeFunctions
{

bool CheckIfGameModeCanStartsQuest(AActor* Player, AActor* NPC, AController* PlayerController, AController* NPCController);
bool CheckIfGameModeCanEndsQuest(AActor* Player, AActor* NPC, AController* PlayerController, AController* NPCController);

}

class UTAQuestComponent;

namespace CharactersFunctions
{
//bool SetDataInComponent(UTAQuestComponent* QuestComponent, const FQuestData& NewQuestData, AActor* QuestGiver);
//bool GetDataFromComponent(UTAQuestComponent* QuestComponent, FQuestData& OutData);

}