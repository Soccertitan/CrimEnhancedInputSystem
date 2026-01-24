// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "CrimActionTypes.generated.h"

class UInputAction;
class UCrimAction;

// Struct used by the CrimActionManagerComponent to store runtime data for Input bindings and actions.
USTRUCT(BlueprintType)
struct FCrimInputActionItem
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCrimAction> CrimAction;

	FORCEINLINE bool operator ==(FGameplayTag const& Other) const
	{
		return InputTag == Other;
	}

	FORCEINLINE bool operator !=(FGameplayTag const& Other) const
	{
		return InputTag != Other;
	}

private:	
	uint32 TriggeredHandle = -1;
	uint32 StartedHandle = -1;
	uint32 OngoingHandle = -1;
	uint32 CanceledHandle = -1;
	uint32 CompletedHandle = -1;
	
	friend class UCrimActionManagerComponent;
};
