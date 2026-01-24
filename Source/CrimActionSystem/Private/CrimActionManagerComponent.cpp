// Copyright Soccertitan 2025


#include "CrimActionManagerComponent.h"

#include "CrimAction.h"
#include "CrimActionDefinition.h"
#include "CrimActionSystem.h"
#include "CrimInputActionSet.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


UCrimActionManagerComponent::UCrimActionManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(false);
}

UCrimAction* UCrimActionManagerComponent::FindAction(FGameplayTag InputTag) const
{
	if (InputTag.IsValid())
	{
		return nullptr;
	}
	
	if (const FCrimInputActionItem* ActionItem = InputActionItems.FindByKey(InputTag))
	{
		return ActionItem->CrimAction;
	}
	
	return nullptr;
}

void UCrimActionManagerComponent::InitActionManagerComponent()
{
	PlayerController = Cast<APlayerController>(GetOwner());
	if (!PlayerController)
	{
		UE_LOG(LogCrimActionSystem, Error, TEXT("[%s] expects to be added only to a PlayerController. Deactivating component"), *GetNameSafe(this));
		Deactivate();
		return;
	}
	
	EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	check(EnhancedInputSubsystem);
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
	check(EnhancedInputComponent);

	
	for (const TObjectPtr<UCrimInputActionSet>& InputSet : InputActionSets)
	{
		SetInputActionSet(InputSet);
	}
}

void UCrimActionManagerComponent::SetInputActionSet(UCrimInputActionSet* InputActionSet)
{
	if (!EnhancedInputComponent || !EnhancedInputSubsystem || !InputActionSet)
	{
		return;
	}
	
	if (InputActionSet->InputMappingContext)
	{
		EnhancedInputSubsystem->AddMappingContext(InputActionSet->InputMappingContext, InputActionSet->InputMappingContextPriority);
	}
	
	for (const FCrimInputAction& StartupInputAction : InputActionSet->InputActions)
	{
		SetInputAction(StartupInputAction);
	}
}

void UCrimActionManagerComponent::SetInputAction(const FCrimInputAction& InputAction)
{
	if (!InputAction.IsValid())
	{
		return;
	}
		
	if (FCrimInputActionItem* ActionItem = InputActionItems.FindByKey(InputAction.InputTag))
	{
		Internal_RemoveBinding(*ActionItem);
		ActionItem->InputAction = InputAction.InputAction;
		if (InputAction.ActionDefinition && InputAction.ActionDefinition->ActionClass)
		{
			Internal_AddBinding(*ActionItem, InputAction.ActionDefinition);
		}
	}
	else
	{
		FCrimInputActionItem& NewActionItem = InputActionItems.AddDefaulted_GetRef();
		NewActionItem.InputTag = InputAction.InputTag;
		NewActionItem.InputAction = InputAction.InputAction;
		if (InputAction.ActionDefinition && InputAction.ActionDefinition->ActionClass)
		{
			Internal_AddBinding(NewActionItem, InputAction.ActionDefinition);
		}
	}
}

void UCrimActionManagerComponent::SetAction(FGameplayTag InputTag, UCrimActionDefinition* ActionDefinition)
{
	if (!InputTag.IsValid())
	{
		return;
	}
	
	if (FCrimInputActionItem* ActionItem = InputActionItems.FindByKey(InputTag))
	{
		Internal_RemoveBinding(*ActionItem);
		if (ActionDefinition && ActionDefinition->ActionClass)
		{
			Internal_AddBinding(*ActionItem, ActionDefinition);
		}
	}
}

void UCrimActionManagerComponent::Internal_AddBinding(FCrimInputActionItem& InputActionItem, UCrimActionDefinition* ActionDefinition)
{
	UCrimAction* NewAction = NewObject<UCrimAction>(this, ActionDefinition->ActionClass);
	NewAction->InputTag = InputActionItem.InputTag;
	NewAction->ActionDefinition = ActionDefinition;
	NewAction->PlayerController = PlayerController;
	NewAction->ActionManagerComponent = this;
	NewAction->InitializeAction();
	
	InputActionItem.CrimAction = NewAction;
	
	//TODO: Figure out how to tell if the overriden functions are implements to avoid having to bind for each action when it's unecessary.
	InputActionItem.TriggeredHandle = EnhancedInputComponent->BindAction(InputActionItem.InputAction, ETriggerEvent::Triggered, NewAction, &UCrimAction::InputActionTriggered).GetHandle();
	InputActionItem.StartedHandle = EnhancedInputComponent->BindAction(InputActionItem.InputAction, ETriggerEvent::Started, NewAction, &UCrimAction::InputActionStarted).GetHandle();
	InputActionItem.OngoingHandle = EnhancedInputComponent->BindAction(InputActionItem.InputAction, ETriggerEvent::Ongoing, NewAction, &UCrimAction::InputActionOngoing).GetHandle();
	InputActionItem.CanceledHandle = EnhancedInputComponent->BindAction(InputActionItem.InputAction, ETriggerEvent::Canceled, NewAction, &UCrimAction::InputActionCanceled).GetHandle();
	InputActionItem.CompletedHandle = EnhancedInputComponent->BindAction(InputActionItem.InputAction, ETriggerEvent::Completed, NewAction, &UCrimAction::InputActionCompleted).GetHandle();
	
	OnInputActionAdded.Broadcast(InputActionItem);
}

void UCrimActionManagerComponent::Internal_RemoveBinding(FCrimInputActionItem& InputActionItem)
{
	if (InputActionItem.CrimAction)
	{
		EnhancedInputComponent->RemoveBindingByHandle(InputActionItem.StartedHandle);
		InputActionItem.StartedHandle = INDEX_NONE;
		EnhancedInputComponent->RemoveBindingByHandle(InputActionItem.TriggeredHandle);
		InputActionItem.TriggeredHandle = INDEX_NONE;
		EnhancedInputComponent->RemoveBindingByHandle(InputActionItem.OngoingHandle);
		InputActionItem.OngoingHandle = INDEX_NONE;
		EnhancedInputComponent->RemoveBindingByHandle(InputActionItem.CanceledHandle);
		InputActionItem.CanceledHandle = INDEX_NONE;
		EnhancedInputComponent->RemoveBindingByHandle(InputActionItem.CompletedHandle);
		InputActionItem.CompletedHandle = INDEX_NONE;
		
		InputActionItem.CrimAction->ResetAction();
		OnInputActionRemoved.Broadcast(InputActionItem);
		InputActionItem.CrimAction = nullptr;
	}
}

