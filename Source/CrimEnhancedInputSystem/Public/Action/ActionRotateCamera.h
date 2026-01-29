// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "CrimAction.h"
#include "ActionRotateCamera.generated.h"

/**
 * 
 */
UCLASS()
class CRIMENHANCEDINPUTSYSTEM_API UActionRotateCamera : public UCrimAction
{
	GENERATED_BODY()
	
protected:
	virtual void OnInputActionTriggered(const FInputActionValue& Value) override;
};
