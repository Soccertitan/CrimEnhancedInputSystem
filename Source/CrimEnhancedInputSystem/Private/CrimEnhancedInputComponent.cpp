// Copyright Soccertitan 2025


#include "CrimEnhancedInputComponent.h"

#include "InputActionListener.h"
#include "EnhancedInputComponent.h"


UCrimEnhancedInputComponent::UCrimEnhancedInputComponent()
{

}

FCrimEnhancedInputActionBinding UCrimEnhancedInputComponent::CreateActionBinding(UInputAction* InputAction, const TSubclassOf<UInputActionListener>& ListenerClass)
{
	FCrimEnhancedInputActionBinding Result;
	
	if (InputAction && ListenerClass)
	{
		UInputActionListener* NewListener = NewObject<UInputActionListener>(this, ListenerClass);
		NewListener->EnhancedInputComponent = this;
		NewListener->InitializeListener();
		Result.InputAction = InputAction;
		Result.Listener = NewListener;

		//TODO: Figure out how to tell if the overriden functions are implements to avoid having to bind for each action when it's not necessary.
		Result.TriggeredHandle = BindAction(InputAction, ETriggerEvent::Triggered, NewListener, &UInputActionListener::InputActionTriggered).GetHandle();
		Result.StartedHandle = BindAction(InputAction, ETriggerEvent::Started, NewListener, &UInputActionListener::InputActionStarted).GetHandle();
		Result.OngoingHandle = BindAction(InputAction, ETriggerEvent::Ongoing, NewListener, &UInputActionListener::InputActionOngoing).GetHandle();
		Result.CanceledHandle = BindAction(InputAction, ETriggerEvent::Canceled, NewListener, &UInputActionListener::InputActionCanceled).GetHandle();
		Result.CompletedHandle = BindAction(InputAction, ETriggerEvent::Completed, NewListener, &UInputActionListener::InputActionCompleted).GetHandle();
	}

	return Result;
}

void UCrimEnhancedInputComponent::SetListener(UInputAction* InputAction, const TSubclassOf<UInputActionListener>& ListenerClass)
{
	if (InputAction)
	{
		if (FCrimEnhancedInputActionBinding* CurrentBinding = CrimEnhancedInputActionBindings.FindByKey(InputAction))
		{
			Internal_RemoveListener(*CurrentBinding);
		}

		const FCrimEnhancedInputActionBinding Result = CreateActionBinding(InputAction, ListenerClass);
		if (Result.IsValid())
		{
			Internal_AddListener(Result);
		}
	}
}

void UCrimEnhancedInputComponent::ClearListeners()
{
	for (int32 Idx = CrimEnhancedInputActionBindings.Num() -1; Idx >= 0; Idx--)
	{
		FCrimEnhancedInputActionBinding TempCopy = CrimEnhancedInputActionBindings[Idx];
		RemoveBindingByHandle(TempCopy.StartedHandle);
		TempCopy.StartedHandle = INDEX_NONE;
		RemoveBindingByHandle(TempCopy.TriggeredHandle);
		TempCopy.TriggeredHandle = INDEX_NONE;
		RemoveBindingByHandle(TempCopy.OngoingHandle);
		TempCopy.OngoingHandle = INDEX_NONE;
		RemoveBindingByHandle(TempCopy.CanceledHandle);
		TempCopy.CanceledHandle = INDEX_NONE;
		RemoveBindingByHandle(TempCopy.CompletedHandle);
		TempCopy.CompletedHandle = INDEX_NONE;
		OnListenerRemoved.Broadcast(TempCopy);
	}
	CrimEnhancedInputActionBindings.Reset();
}

UInputActionListener* UCrimEnhancedInputComponent::FindListener(UInputAction* InputAction) const
{
	if (InputAction)
	{
		for (const FCrimEnhancedInputActionBinding& Item : CrimEnhancedInputActionBindings)
		{
			if (Item == InputAction)
			{
				return Item.Listener;
			}
		}
	}
	return nullptr;
}

const TArray<FCrimEnhancedInputActionBinding>& UCrimEnhancedInputComponent::GetListeners() const
{
	return CrimEnhancedInputActionBindings;
}

void UCrimEnhancedInputComponent::ClearActionBindings()
{
	Super::ClearActionBindings();
	
	ClearListeners();
}

void UCrimEnhancedInputComponent::ClearBindingsForObject(UObject* InOwner)
{
	Super::ClearBindingsForObject(InOwner);
	
	if (InOwner == this)
	{
		ClearListeners();
	}
	else if (InOwner && InOwner->IsA(UInputActionListener::StaticClass()))
	{
		for (FCrimEnhancedInputActionBinding& Item : CrimEnhancedInputActionBindings)
		{
			if (Item.Listener == InOwner)
			{
				Internal_RemoveListener(Item);
				continue;
			}
		}
	}
}

void UCrimEnhancedInputComponent::Internal_AddListener(const FCrimEnhancedInputActionBinding& Binding)
{
	CrimEnhancedInputActionBindings.Add(Binding);
	OnListenerAdded.Broadcast(Binding);
}

void UCrimEnhancedInputComponent::Internal_RemoveListener(FCrimEnhancedInputActionBinding& Binding)
{
	RemoveBindingByHandle(Binding.StartedHandle);
	Binding.StartedHandle = INDEX_NONE;
	RemoveBindingByHandle(Binding.TriggeredHandle);
	Binding.TriggeredHandle = INDEX_NONE;
	RemoveBindingByHandle(Binding.OngoingHandle);
	Binding.OngoingHandle = INDEX_NONE;
	RemoveBindingByHandle(Binding.CanceledHandle);
	Binding.CanceledHandle = INDEX_NONE;
	RemoveBindingByHandle(Binding.CompletedHandle);
	Binding.CompletedHandle = INDEX_NONE;

	for (int32 Idx = CrimEnhancedInputActionBindings.Num() -1; Idx >= 0; Idx--)
	{
		if (CrimEnhancedInputActionBindings[Idx] == Binding.InputAction)
		{
			const FCrimEnhancedInputActionBinding TempCopy = CrimEnhancedInputActionBindings[Idx];
			CrimEnhancedInputActionBindings.RemoveAtSwap(Idx);
			OnListenerRemoved.Broadcast(TempCopy);
			return;
		}
	}
}

