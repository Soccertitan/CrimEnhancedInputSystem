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
	virtual void InputActionTriggered(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable, Category = "InputActionListener")
	virtual void InputActionStarted(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable, Category = "InputActionListener")
	virtual void InputActionOngoing(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable, Category = "InputActionListener")
	virtual void InputActionCanceled(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable, Category = "InputActionListener")
	virtual void InputActionCompleted(const FInputActionValue& Value);

protected:
	/** Called by the CrimEnhancedInputComponent when setting up an InputActionListener for the first time. */
	virtual void Initialize();
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "Initialize")
	void K2_Initialize();
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "InputActionTriggered")
	void K2_InputActionTriggered(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "InputActionStarted")
	void K2_InputActionStarted(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "InputActionOngoing")
	void K2_InputActionOngoing(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "InputActionCanceled")
	void K2_InputActionCanceled(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "InputActionCompleted")
	void K2_InputActionCompleted(const FInputActionValue& Value);

private:
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;
	/** Cached pointer to the CrimEnhancedInputComponent that constructed the listener. */
	UPROPERTY()
	TObjectPtr<UCrimEnhancedInputComponent> EnhancedInputComponent;

	friend UCrimEnhancedInputComponent;
};
