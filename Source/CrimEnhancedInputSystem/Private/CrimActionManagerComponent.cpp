// Copyright Soccertitan 2025


#include "CrimActionManagerComponent.h"

#include "CrimAction.h"
#include "CrimEnhancedInputSystem.h"
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
		UE_LOG(LogCrimEnhancedInputSystem, Error, TEXT("[%s] expects to be added only to a PlayerController. Deactivating component"), *GetNameSafe(this));
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
		if (InputAction.ActionClass)
		{
			Internal_AddBinding(*ActionItem, InputAction.ActionClass);
		}
	}
	else
	{
		FCrimInputActionItem& NewActionItem = InputActionItems.AddDefaulted_GetRef();
		NewActionItem.InputTag = InputAction.InputTag;
		NewActionItem.InputAction = InputAction.InputAction;
		if (InputAction.ActionClass)
		{
			Internal_AddBinding(NewActionItem, InputAction.ActionClass);
		}
	}
}

void UCrimActionManagerComponent::SetAction(FGameplayTag InputTag, TSubclassOf<UCrimAction> ActionClass)
{
	if (!InputTag.IsValid())
	{
		return;
	}
	
	if (FCrimInputActionItem* ActionItem = InputActionItems.FindByKey(InputTag))
	{
		if (ActionItem->CrimAction)
		{
			Internal_RemoveBinding(*ActionItem);
		}
		if (ActionClass)
		{
			Internal_AddBinding(*ActionItem, ActionClass);
		}
	}
}

void UCrimActionManagerComponent::Internal_AddBinding(FCrimInputActionItem& InputActionItem, TSubclassOf<UCrimAction> ActionClass)
{
	bool bMakeNewAction = true;
	for (const FCrimInputActionItem& Item : InputActionItems)
	{
		if (Item.CrimAction && Item.CrimAction->GetClass() == ActionClass)
		{
			InputActionItem.CrimAction = Item.CrimAction;
			bMakeNewAction = false;
		}
	}
	
	if (bMakeNewAction)
	{
		UCrimAction* NewAction = NewObject<UCrimAction>(this, ActionClass);
		NewAction->PlayerController = PlayerController;
		NewAction->ActionManagerComponent = this;
		NewAction->InitializeAction();
		InputActionItem.CrimAction = NewAction;
	}
	
	InputActionItem.CrimAction->AddInputTag(InputActionItem.InputTag);
	
	//TODO: Figure out how to tell if the overriden functions are implements to avoid having to bind for each action when it's not necessary.
	InputActionItem.TriggeredHandle = EnhancedInputComponent->BindAction(InputActionItem.InputAction, ETriggerEvent::Triggered, InputActionItem.CrimAction.Get(), &UCrimAction::InputActionTriggered).GetHandle();
	InputActionItem.StartedHandle = EnhancedInputComponent->BindAction(InputActionItem.InputAction, ETriggerEvent::Started, InputActionItem.CrimAction.Get(), &UCrimAction::InputActionStarted).GetHandle();
	InputActionItem.OngoingHandle = EnhancedInputComponent->BindAction(InputActionItem.InputAction, ETriggerEvent::Ongoing, InputActionItem.CrimAction.Get(), &UCrimAction::InputActionOngoing).GetHandle();
	InputActionItem.CanceledHandle = EnhancedInputComponent->BindAction(InputActionItem.InputAction, ETriggerEvent::Canceled, InputActionItem.CrimAction.Get(), &UCrimAction::InputActionCanceled).GetHandle();
	InputActionItem.CompletedHandle = EnhancedInputComponent->BindAction(InputActionItem.InputAction, ETriggerEvent::Completed, InputActionItem.CrimAction.Get(), &UCrimAction::InputActionCompleted).GetHandle();
	
	OnActionAdded.Broadcast(InputActionItem);
}

void UCrimActionManagerComponent::Internal_RemoveBinding(FCrimInputActionItem& InputActionItem)
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

	OnInputActionRemoved.Broadcast(InputActionItem);
	
	InputActionItem.CrimAction->RemoveInputTag(InputActionItem.InputTag);
	if (InputActionItem.CrimAction->GetInputTagContainer().IsEmpty())
	{
		InputActionItem.CrimAction->DestroyAction();
		InputActionItem.CrimAction = nullptr;
	}
}

