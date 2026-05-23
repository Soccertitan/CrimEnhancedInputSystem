// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "InputActionListener.h"
#include "InputActionListener_RotateControl.generated.h"

/**
 * 
 */
UCLASS()
class CRIMENHANCEDINPUTSYSTEM_API UInputActionListener_RotateControl : public UInputActionListener
{
	GENERATED_BODY()
	
protected:
	virtual void OnInputActionTriggered(const FInputActionValue& Value) override;
};
