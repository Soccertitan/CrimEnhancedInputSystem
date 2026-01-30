// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InputActionListener.generated.h"

struct FInputActionValue;
class UCrimEnhancedInputComponent;

/**
 * An action that can be performed taking in input.
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class CRIMENHANCEDINPUTSYSTEM_API UInputActionListener : public UObject
{
	GENERATED_BODY()
	
public:
	UInputActionListener();

	UFUNCTION(BlueprintPure, Category = "InputActionListener")
	APlayerController* GetPlayerController() const { return PlayerController; }
	UFUNCTION(BlueprintPure, Category = "InputActionListener")
	UCrimEnhancedInputComponent* GetEnhancedInputManagerComponent() const { return EnhancedInputComponent; }

	UFUNCTION(BlueprintCallable, Category = "InputActionListener")
	void InputActionTriggered(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable, Category = "InputActionListener")
	void InputActionStarted(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable, Category = "InputActionListener")
	void InputActionOngoing(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable, Category = "InputActionListener")
	void InputActionCanceled(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable, Category = "InputActionListener")
	void InputActionCompleted(const FInputActionValue& Value);

protected:
	void InitializeListener();
	virtual void OnInitializeListener() {}
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnInitializeListener")
	void K2_OnInitializeListener();

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
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;
	/** Cached pointer to the CrimEnhancedInputComponent that constructed the listener. */
	UPROPERTY()
	TObjectPtr<UCrimEnhancedInputComponent> EnhancedInputComponent;

	friend UCrimEnhancedInputComponent;
};
