// Copyright Soccertitan 2025


#include "Action/ActionDebug.h"

#include "InputActionValue.h"
#include "Kismet/KismetSystemLibrary.h"

void UActionDebug::OnInputActionStarted(const FInputActionValue& Value)
{
	Super::OnInputActionStarted(Value);
	if (bPrintActionStarted)
	{
		const FString Message = FString::Printf(TEXT("[%s] - Action Started: Value [%s]"), *GetName(), *Value.ToString());
		UKismetSystemLibrary::PrintString(this, Message, bPrintToScreen, bPrintToLog, TextColor, Duration);
	}
}

void UActionDebug::OnInputActionTriggered(const FInputActionValue& Value)
{
	Super::OnInputActionTriggered(Value);
	if (bPrintActionTriggered)
	{
		const FString Message = FString::Printf(TEXT("[%s] - Action Triggered: Value [%s]"), *GetName(), *Value.ToString());
		UKismetSystemLibrary::PrintString(this, Message, bPrintToScreen, bPrintToLog, TextColor, Duration);
	}
}

void UActionDebug::OnInputActionOngoing(const FInputActionValue& Value)
{
	Super::OnInputActionOngoing(Value);
	if (bPrintActionOngoing)
	{
		const FString Message = FString::Printf(TEXT("[%s] - Action Ongoing: Value [%s]"), *GetName(), *Value.ToString());
		UKismetSystemLibrary::PrintString(this, Message, bPrintToScreen, bPrintToLog, TextColor, 0.f);
	}
}

void UActionDebug::OnInputActionCanceled(const FInputActionValue& Value)
{
	Super::OnInputActionCanceled(Value);
	if (bPrintActionCanceled)
	{
		const FString Message = FString::Printf(TEXT("[%s] - Action Canceled: Value [%s]"), *GetName(), *Value.ToString());
		UKismetSystemLibrary::PrintString(this, Message, bPrintToScreen, bPrintToLog, TextColor, Duration);
	}
}

void UActionDebug::OnInputActionCompleted(const FInputActionValue& Value)
{
	Super::OnInputActionCompleted(Value);
	if (bPrintActionCompleted)
	{
		const FString Message = FString::Printf(TEXT("[%s] - Action Completed: Value [%s]"), *GetName(), *Value.ToString());
		UKismetSystemLibrary::PrintString(this, Message, bPrintToScreen, bPrintToLog, TextColor, Duration);
	}
}
