// Copyright Soccertitan 2025


#include "Action/RotateCameraInputActionListener.h"

#include "CrimEnhancedInputComponent.h"
#include "InputActionValue.h"

void URotateCameraInputActionListener::OnInitializeListener()
{
	Super::OnInitializeListener();
	
	Controller = Cast<AController>(GetEnhancedInputManagerComponent()->GetOwner());
	if (Controller)
	{
		return;
	}
	
	if (const APawn* Pawn = Cast<APawn>(GetEnhancedInputManagerComponent()->GetOwner()))
	{
		Controller = Pawn->GetController();
	}
}

void URotateCameraInputActionListener::OnInputActionTriggered(const FInputActionValue& Value)
{
	if (Controller)
	{
		if(APawn* ControlledPawn = Controller->GetPawn())
		{
			ControlledPawn->AddControllerPitchInput(Value[1]);
			ControlledPawn->AddControllerYawInput(Value[0]);
		}
	}
}
