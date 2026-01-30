// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "CrimEnhancedInputActionTypes.generated.h"

class UInputAction;
class UInputActionListener;

// Struct used by the CrimEnhancedInputComponent to store runtime data for Input bindings.
USTRUCT(BlueprintType)
struct FCrimEnhancedInputActionBinding
{
	GENERATED_BODY()

	UInputAction* GetInputAction() const { return InputAction;}
	UInputActionListener* GetListener() const { return Listener; }
	
	bool IsValid() const;

	FORCEINLINE bool operator ==(UInputAction* const& Other) const
	{
		return InputAction == Other;
	}

	FORCEINLINE bool operator !=(UInputAction* const& Other) const
	{
		return InputAction != Other;
	}

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	TObjectPtr<UInputActionListener> Listener;
	
	uint32 TriggeredHandle = -1;
	uint32 StartedHandle = -1;
	uint32 OngoingHandle = -1;
	uint32 CanceledHandle = -1;
	uint32 CompletedHandle = -1;

	friend class UCrimEnhancedInputComponent;
};
