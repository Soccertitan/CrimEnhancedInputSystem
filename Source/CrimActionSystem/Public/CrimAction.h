// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "CrimAction.generated.h"

struct FInputActionValue;
class UCrimActionManagerComponent;

/**
 * An action that can be performed taking in input.
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class CRIMACTIONSYSTEM_API UCrimAction : public UObject
{
	GENERATED_BODY()
	
public:
	UCrimAction();

	UFUNCTION(BlueprintPure, Category = "CrimAction")
	APlayerController* GetPlayerController() const { return PlayerController; }
	UFUNCTION(BlueprintPure, Category = "CrimAction")
	UCrimActionManagerComponent* GetActionManagerComponent() const { return ActionManagerComponent; }
	UFUNCTION(BlueprintPure, Category = "CrimAction")
	FGameplayTag GetInputTag() const { return InputTag; }

	UFUNCTION(BlueprintCallable, Category = "CrimAction")
	void InputActionTriggered(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable, Category = "CrimAction")
	void InputActionStarted(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable, Category = "CrimAction")
	void InputActionOngoing(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable, Category = "CrimAction")
	void InputActionCanceled(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable, Category = "CrimAction")
	void InputActionCompleted(const FInputActionValue& Value);

protected:
	void InitializeAction();

	virtual void OnInitializeAction() {}
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnInitializeAction")
	void K2_OnInitializeAction();

	virtual void OnResetAction() {}
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnResetAction")
	void K2_OnResetAction();

	UFUNCTION()
	virtual void OnInputActionTriggered(const FInputActionValue& Value) {}
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnInputActionTriggered")
	void K2_OnInputActionTriggered(const FInputActionValue& Value);
	
	UFUNCTION()
	virtual void OnInputActionStarted(const FInputActionValue& Value) {}
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnInputActionStarted")
	void K2_OnInputActionStarted(const FInputActionValue& Value);
	
	UFUNCTION()
	virtual void OnInputActionOngoing(const FInputActionValue& Value) {}
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnInputActionOngoing")
	void K2_OnInputActionOngoing(const FInputActionValue& Value);
	
	UFUNCTION()
	virtual void OnInputActionCanceled(const FInputActionValue& Value) {}
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnInputActionCanceled")
	void K2_OnInputActionCanceled(const FInputActionValue& Value);
	
	UFUNCTION()
	virtual void OnInputActionCompleted(const FInputActionValue& Value) {}
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnInputActionCompleted")
	void K2_OnInputActionCompleted(const FInputActionValue& Value);

private:
	/** Input Tag that can activate and identify the action. */
	UPROPERTY()
	FGameplayTag InputTag;

	/** Cached pointer to the PlayerController. */
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	/** Cached pointer to the ActionManagerComponent. */
	UPROPERTY()
	TObjectPtr<UCrimActionManagerComponent> ActionManagerComponent;

	friend UCrimActionManagerComponent;
};
