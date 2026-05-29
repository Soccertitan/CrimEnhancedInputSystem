// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "InputActionListener.h"
#include "InputActionListener_Debug.generated.h"

/**
 * An action that prints debug strings for the different Input Action triggers.
 */
UCLASS()
class CRIMENHANCEDINPUTSYSTEM_API UInputActionListener_Debug : public UInputActionListener
{
	GENERATED_BODY()

public:
	virtual void InputActionStarted(const FInputActionValue& Value) override;
	virtual void InputActionTriggered(const FInputActionValue& Value) override;
	virtual void InputActionOngoing(const FInputActionValue& Value) override;
	virtual void InputActionCanceled(const FInputActionValue& Value) override;
	virtual void InputActionCompleted(const FInputActionValue& Value) override;
	
protected:
	UPROPERTY(EditAnywhere)
	bool bPrintToScreen = true;
	UPROPERTY(EditAnywhere)
	bool bPrintToLog = true;
	UPROPERTY(EditAnywhere)
	FLinearColor TextColor = FLinearColor(0.0f, 0.66f, 1.0f);
	UPROPERTY(EditAnywhere)
	float Duration = 2.f;
	
	UPROPERTY(EditAnywhere)
	bool bPrintActionStarted = true;
	UPROPERTY(EditAnywhere)
	bool bPrintActionTriggered = true;
	UPROPERTY(EditAnywhere)
	bool bPrintActionOngoing = true;
	UPROPERTY(EditAnywhere)
	bool bPrintActionCanceled = true;
	UPROPERTY(EditAnywhere)
	bool bPrintActionCompleted = true;
};
