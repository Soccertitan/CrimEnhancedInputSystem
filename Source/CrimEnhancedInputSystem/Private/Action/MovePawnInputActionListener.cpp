// Copyright Soccertitan 2025


#include "Action/MovePawnInputActionListener.h"

#include "CrimEnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"

void UMovePawnInputActionListener::OnInitializeListener()
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

void UMovePawnInputActionListener::OnInputActionTriggered(const FInputActionValue& Value)
{
	if (Controller)
	{
		if(APawn* ControlledPawn = Controller->GetPawn())
		{
			const FRotator Rotation = ControlledPawn->GetControlRotation();
			const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0,Rotation.Yaw,0));
			const FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0,Rotation.Yaw,0));
			ControlledPawn->AddMovementInput(ForwardVector, Value[1], false);
			ControlledPawn->AddMovementInput(RightVector, Value[0], false);
		}
	}
}
