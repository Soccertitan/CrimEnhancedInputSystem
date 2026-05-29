// Copyright Soccertitan 2025


#include "Action/InputActionListener_MovePawn.h"

#include "CrimEnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"


void UInputActionListener_MovePawn::InputActionTriggered(const FInputActionValue& Value)
{
	if (GetPlayerController())
	{
		if(APawn* ControlledPawn = GetPlayerController()->GetPawn())
		{
			const FRotator Rotation = ControlledPawn->GetControlRotation();
			const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0,Rotation.Yaw,0));
			const FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0,Rotation.Yaw,0));
			ControlledPawn->AddMovementInput(ForwardVector, Value[1], false);
			ControlledPawn->AddMovementInput(RightVector, Value[0], false);
		}
	}
}
