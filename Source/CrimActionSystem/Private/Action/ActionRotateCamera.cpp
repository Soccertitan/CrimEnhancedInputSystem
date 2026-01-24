// Copyright Soccertitan 2025


#include "Action/ActionRotateCamera.h"

#include "InputActionValue.h"

void UActionRotateCamera::OnInputActionTriggered(const FInputActionValue& Value)
{
	if(APawn* ControlledPawn = GetPlayerController()->GetPawn())
	{
		ControlledPawn->AddControllerPitchInput(Value[1]);
		ControlledPawn->AddControllerYawInput(Value[0]);
	}
}
