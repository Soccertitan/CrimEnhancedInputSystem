// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "CrimAction.h"
#include "ActionMovePawn.generated.h"

/**
 * 
 */
UCLASS()
class CRIMENHANCEDINPUTSYSTEM_API UActionMovePawn : public UCrimAction
{
	GENERATED_BODY()
	
public:
	
protected:
	virtual void OnInputActionTriggered(const FInputActionValue& Value) override;
};
