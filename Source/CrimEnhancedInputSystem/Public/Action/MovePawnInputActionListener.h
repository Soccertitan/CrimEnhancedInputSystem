// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "InputActionListener.h"
#include "MovePawnInputActionListener.generated.h"

/**
 * 
 */
UCLASS()
class CRIMENHANCEDINPUTSYSTEM_API UMovePawnInputActionListener : public UInputActionListener
{
	GENERATED_BODY()
	
public:
	
protected:
	virtual void OnInitializeListener() override;
	
	virtual void OnInputActionTriggered(const FInputActionValue& Value) override;
	
private:
	UPROPERTY()
	TObjectPtr<AController> Controller;
};
