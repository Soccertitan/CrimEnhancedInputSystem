// Copyright Soccertitan 2025


#include "Action/ActionMovePawn.h"

#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"

void UActionMovePawn::OnInputActionTriggered(const FInputActionValue& Value)
{
	if(APawn* ControlledPawn = GetPlayerController()->GetPawn())
	{
		FRotator Rotation = ControlledPawn->GetControlRotation();
		FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0,Rotation.Yaw,0));
		FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0,Rotation.Yaw,0));
		ControlledPawn->AddMovementInput(ForwardVector, Value[1], false);
		ControlledPawn->AddMovementInput(RightVector, Value[0], false);
	}
}
