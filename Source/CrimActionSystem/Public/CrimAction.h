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
	FGameplayTagContainer GetInputTagContainer() const { return InputTagContainer; }

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

	void DestroyAction();
	virtual void OnDestroyAction() {}
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnDestroyAction")
	void K2_OnDestroyAction();

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
	
	void AddInputTag(const FGameplayTag& InputTag);
	virtual void OnInputTagAdded(const FGameplayTag& InputTag) {}
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnInputTagAdded")
	void K2_OnInputTagAdded(const FGameplayTag& InputTag);
	
	void RemoveInputTag(const FGameplayTag& InputTag);
	virtual void OnInputTagRemoved(const FGameplayTag& InputTag) {}
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnInputTagRemoved")
	void K2_OnInputTagRemoved(const FGameplayTag& InputTag);

private:
	/** Input Tag that can activate and identify the action. */
	UPROPERTY()
	FGameplayTagContainer InputTagContainer;

	/** Cached pointer to the PlayerController. */
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	/** Cached pointer to the ActionManagerComponent. */
	UPROPERTY()
	TObjectPtr<UCrimActionManagerComponent> ActionManagerComponent;

	friend UCrimActionManagerComponent;
};
