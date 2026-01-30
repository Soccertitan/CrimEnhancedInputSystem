// Copyright Soccertitan 2025


#include "InputActionListener.h"

#include "CrimEnhancedInputComponent.h"


UInputActionListener::UInputActionListener()
{
}

void UInputActionListener::InputActionTriggered(const FInputActionValue& Value)
{
	OnInputActionTriggered(Value);
	K2_OnInputActionTriggered(Value);
}

void UInputActionListener::InputActionStarted(const FInputActionValue& Value)
{
	OnInputActionStarted(Value);
	K2_OnInputActionStarted(Value);
}

void UInputActionListener::InputActionOngoing(const FInputActionValue& Value)
{
	OnInputActionOngoing(Value);
	K2_OnInputActionOngoing(Value);
}

void UInputActionListener::InputActionCanceled(const FInputActionValue& Value)
{
	OnInputActionCanceled(Value);
	K2_OnInputActionCanceled(Value);
}

void UInputActionListener::InputActionCompleted(const FInputActionValue& Value)
{
	OnInputActionCompleted(Value);
	K2_OnInputActionCompleted(Value);
}

void UInputActionListener::InitializeListener()
{
	EnhancedInputComponent = Cast<UCrimEnhancedInputComponent>(GetOuter());
	ensure(EnhancedInputComponent);
	PlayerController = Cast<APlayerController>(EnhancedInputComponent->GetOwner());
	if (!PlayerController)
	{
		if (APawn* Pawn = Cast<APawn>(EnhancedInputComponent->GetOwner()))
		{
			PlayerController = Cast<APlayerController>(Pawn->GetController());		
		}
	}
	ensure(PlayerController);
	OnInitializeListener();
	K2_OnInitializeListener();
}
