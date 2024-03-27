// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "../Functions/Functions.h"
#include "DeclaringDelegatesForQuestFlow.h"

#include "TABaseGameMode.generated.h"

/**
 * 
 */
class ASpamActor;

struct FQuestData;

UCLASS()
class APITEST_API ATABaseGameMode : public AGameMode
{
    GENERATED_BODY()
 
private:     
    TUniquePtr<ASpamActor> SpawnedActor;

    void SpawnItem(const TSubclassOf<ASpamActor>& tmp, const FVector SpawnLocation);
    void DestroyItem(TUniquePtr<ASpamActor>& ToDestroy);
     
private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpamActors|For Move To Quest", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<ASpamActor> MoveToSubClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpamActors|For Find Item Quest", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<ASpamActor> FindItemSubClass;

private:

    friend void ControllersFunctions::BeginPlay(AController* Controller);

    void InitQuestData(AController* InController, bool bIsMasterInteract);

    void GetCurrentQuestDataFor(APawn* Player, APawn* NPC, FQuestData& CurrentPlayerData, FQuestData& CurrentNPCData,
        EQuestProgress& NewPlayerProgress, EQuestProgress& NewNPCProgress);
    void SetNewQuestDataFor(APawn* Player, APawn* NPC, const FQuestData& NewPlayerData, const FQuestData& NewNPCData,
        EQuestProgress NewPlayerProgress, EQuestProgress NewNPCProgress, bool bIsGameModeSender);

    void GameModeStartsQuest(APawn* Player, APawn* NPC);
    void GameModeProgressQuest(APawn* Player, APawn* NPC);
    void GameModeEndsQuest(APawn* Player, APawn* NPC);

private:
    void UpdateQuestFlow(AController* PlayerController, AController* NPCController, EQuestProgress GlobalProgress = EQuestProgress::NONE);
    void UpdateStartQuestProgress(AController* PlayerController, AController* NPCController);
    void UpdateEndQuestProgress(AController* PlayerController, AController* NPCController);

public:
    ATABaseGameMode();

protected:
    virtual void PostLogin(APlayerController* NewPlayer) override;

    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

    void SetInteractType(AController* InController, bool bIsMasterInteract);

    void SetNewQuestData(AController* QuestController, const FQuestData& NewQuestData, EQuestProgress NewQuestProgress, AActor* QuestTaker);

public:
    const FQuestData& GetAvailableQuest() const;

    void SetupDelegatesForQuestComponent(AController* PlayerController);

    QuestFlowDelegates::OnGameModeNeedsToGetQuestSignature OnGameModeNeedsToGetQuest;
};
