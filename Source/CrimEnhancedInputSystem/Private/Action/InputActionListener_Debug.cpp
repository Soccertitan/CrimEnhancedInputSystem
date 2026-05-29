// Copyright Soccertitan 2025


#include "Action/InputActionListener_Debug.h"

#include "InputActionValue.h"
#include "Kismet/KismetSystemLibrary.h"

void UInputActionListener_Debug::InputActionStarted(const FInputActionValue& Value)
{
	Super::InputActionStarted(Value);
	if (bPrintActionStarted)
	{
		const FString Message = FString::Printf(TEXT("[%s] - Action Started: Value [%s]"), *GetName(), *Value.ToString());
		UKismetSystemLibrary::PrintString(this, Message, bPrintToScreen, bPrintToLog, TextColor, Duration);
	}
}

void UInputActionListener_Debug::InputActionTriggered(const FInputActionValue& Value)
{
	Super::InputActionTriggered(Value);
	if (bPrintActionTriggered)
	{
		const FString Message = FString::Printf(TEXT("[%s] - Action Triggered: Value [%s]"), *GetName(), *Value.ToString());
		UKismetSystemLibrary::PrintString(this, Message, bPrintToScreen, bPrintToLog, TextColor, Duration);
	}
}

void UInputActionListener_Debug::InputActionOngoing(const FInputActionValue& Value)
{
	Super::InputActionOngoing(Value);
	if (bPrintActionOngoing)
	{
		const FString Message = FString::Printf(TEXT("[%s] - Action Ongoing: Value [%s]"), *GetName(), *Value.ToString());
		UKismetSystemLibrary::PrintString(this, Message, bPrintToScreen, bPrintToLog, TextColor, 0.f);
	}
}

void UInputActionListener_Debug::InputActionCanceled(const FInputActionValue& Value)
{
	Super::InputActionCanceled(Value);
	if (bPrintActionCanceled)
	{
		const FString Message = FString::Printf(TEXT("[%s] - Action Canceled: Value [%s]"), *GetName(), *Value.ToString());
		UKismetSystemLibrary::PrintString(this, Message, bPrintToScreen, bPrintToLog, TextColor, Duration);
	}
}

void UInputActionListener_Debug::InputActionCompleted(const FInputActionValue& Value)
{
	Super::InputActionCompleted(Value);
	if (bPrintActionCompleted)
	{
		const FString Message = FString::Printf(TEXT("[%s] - Action Completed: Value [%s]"), *GetName(), *Value.ToString());
		UKismetSystemLibrary::PrintString(this, Message, bPrintToScreen, bPrintToLog, TextColor, Duration);
	}
}
