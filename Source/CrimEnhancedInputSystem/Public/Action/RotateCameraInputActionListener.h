// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "InputActionListener.h"
#include "RotateCameraInputActionListener.generated.h"

/**
 * 
 */
UCLASS()
class CRIMENHANCEDINPUTSYSTEM_API URotateCameraInputActionListener : public UInputActionListener
{
	GENERATED_BODY()
	
protected:
	virtual void OnInitializeListener() override;
	
	virtual void OnInputActionTriggered(const FInputActionValue& Value) override;
	
private:
	UPROPERTY()
	TObjectPtr<AController> Controller;
};
