// Copyright Soccertitan 2025


#include "InputActionListener.h"

#include "CrimEnhancedInputComponent.h"


UInputActionListener::UInputActionListener()
{
}

void UInputActionListener::InputActionTriggered(const FInputActionValue& Value)
{
	K2_InputActionTriggered(Value);
}

void UInputActionListener::InputActionStarted(const FInputActionValue& Value)
{
	K2_InputActionStarted(Value);
}

void UInputActionListener::InputActionOngoing(const FInputActionValue& Value)
{
	K2_InputActionOngoing(Value);
}

void UInputActionListener::InputActionCanceled(const FInputActionValue& Value)
{
	K2_InputActionCanceled(Value);
}

void UInputActionListener::InputActionCompleted(const FInputActionValue& Value)
{
	K2_InputActionCompleted(Value);
}

void UInputActionListener::Initialize()
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

	K2_Initialize();
}
