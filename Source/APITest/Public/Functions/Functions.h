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

void BeginPlay(AController* Controller);

bool UnderInteract(AController* Controller, FQuestData& OutData, EQuestProgress& OutProgress);

bool CanPawnDoQuest(APawn* Pawn, EInteractType InteractType, bool isStarting = true);

void PawnTryToStartNewQuest(
    AController* PlayerController, AController* NPCController, QuestFlowDelegates::OnQuestStartSignature& OnQuestStart);

void PawnTryToEndQuest(
    AController* PlayerController, AController* NPCController, QuestFlowDelegates::OnQuestEndSignature& OnQuestEnd);

// Control Quest Progress
EQuestProgress UpdateQuestProgress(AController* FuncCaller, EQuestProgress CurrentProgress, AActor* QuestGiver);
void PostProccessQuestProgress(AController* FuncCaller, EQuestProgress QuestProgress);

}  // namespace ControllerFunctions

class ATABaseGameMode;

namespace GameModeFunctions
{

bool CheckIfGameModeCanStartsQuest(AActor* Player, AActor* NPC, AController* PlayerController, AController* NPCController);
bool CheckIfGameModeCanEndsQuest(AActor* Player, AActor* NPC, AController* PlayerController, AController* NPCController);
bool CheckIfGameModeCanProcessQuest(APawn* Player, APawn* WhoCompletedQuest);

}

class UTAQuestComponent;

namespace CharactersFunctions
{
//bool SetDataInComponent(UTAQuestComponent* QuestComponent, const FQuestData& NewQuestData, AActor* QuestGiver);
//bool GetDataFromComponent(UTAQuestComponent* QuestComponent, FQuestData& OutData);

}