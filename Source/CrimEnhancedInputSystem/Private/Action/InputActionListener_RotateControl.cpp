// Copyright Soccertitan 2025


#include "Action/InputActionListener_RotateControl.h"

#include "InputActionValue.h"


void UInputActionListener_RotateControl::OnInputActionTriggered(const FInputActionValue& Value)
{
	if (GetPlayerController())
	{
		GetPlayerController()->AddYawInput(Value[0]);
		GetPlayerController()->AddPitchInput(Value[1]);
		GetPlayerController()->AddRollInput(Value[2]);
	}
}
