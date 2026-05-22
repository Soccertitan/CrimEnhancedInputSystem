// Copyright Soccertitan 2025


#include "Action/InputActionListener_RotateControl.h"

#include "CrimEnhancedInputComponent.h"
#include "InputActionValue.h"

void UInputActionListener_RotateControl::OnInitializeListener()
{
	Super::OnInitializeListener();
	
	PlayerController = Cast<APlayerController>(GetEnhancedInputManagerComponent()->GetOwner());
}

void UInputActionListener_RotateControl::OnInputActionTriggered(const FInputActionValue& Value)
{
	if (PlayerController)
	{
		PlayerController->AddPitchInput(Value[1]);
		PlayerController->AddYawInput(Value[2]);
		PlayerController->AddRollInput(Value[3]);
	}
}
