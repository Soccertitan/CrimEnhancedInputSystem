// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "CrimAction.h"
#include "ActionDebug.generated.h"

/**
 * An action that prints debug strings for the different Input Action triggers.
 */
UCLASS()
class CRIMACTIONSYSTEM_API UActionDebug : public UCrimAction
{
	GENERATED_BODY()

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
	
	virtual void OnInputActionStarted(const FInputActionValue& Value) override;
	virtual void OnInputActionTriggered(const FInputActionValue& Value) override;
	virtual void OnInputActionOngoing(const FInputActionValue& Value) override;
	virtual void OnInputActionCanceled(const FInputActionValue& Value) override;
	virtual void OnInputActionCompleted(const FInputActionValue& Value) override;
};
