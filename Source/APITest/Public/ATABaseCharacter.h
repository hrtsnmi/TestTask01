// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interfaces/InteractableInterface.h"
#include "Interfaces/QuestComponentOwnerInterface.h"

#include "ATABaseCharacter.generated.h"

class UTAQuestComponent;

UCLASS()
class APITEST_API ATABaseCharacter : public ACharacter, public IInteractableInterface, public IQuestComponentOwnerInterface
{
	GENERATED_BODY()

private:
    /** MappingContext */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputMappingContext* DefaultMappingContext;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* MoveAction;

    /** Look Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* LookAction;

    /** Interact Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* InteractAction;

private:
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void Interact(const FInputActionValue& Value);

public:
	ATABaseCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UTAQuestComponent> QuestComponent;

    
protected:        //InteractableInterface
    EInteractType CurrentInteractType;

    FQuestData UnderInteract_Implementation();

public: 
    EInteractType GetInteractType_Implementation() const;
    void SetInteractType_Implementation(EInteractType InteractType);

public:  // IQuestComponentOwnerInterface
    UTAQuestComponent* GetQuestComponent_Implementation() const { return QuestComponent; }
    void SetDataInComponent_Implementation(FQuestData NewQuestData);
};
