// Copyright Soccertitan 2025


#include "CrimAction.h"


UCrimAction::UCrimAction()
{
}

void UCrimAction::InputActionTriggered(const FInputActionValue& Value)
{
	OnInputActionTriggered(Value);
	K2_OnInputActionTriggered(Value);
}

void UCrimAction::InputActionStarted(const FInputActionValue& Value)
{
	OnInputActionStarted(Value);
	K2_OnInputActionStarted(Value);
}

void UCrimAction::InputActionOngoing(const FInputActionValue& Value)
{
	OnInputActionOngoing(Value);
	K2_OnInputActionOngoing(Value);
}

void UCrimAction::InputActionCanceled(const FInputActionValue& Value)
{
	OnInputActionCanceled(Value);
	K2_OnInputActionCanceled(Value);
}

void UCrimAction::InputActionCompleted(const FInputActionValue& Value)
{
	OnInputActionCompleted(Value);
	K2_OnInputActionCompleted(Value);
}

void UCrimAction::InitializeAction()
{
	OnInitializeAction();
	K2_OnInitializeAction();
}
