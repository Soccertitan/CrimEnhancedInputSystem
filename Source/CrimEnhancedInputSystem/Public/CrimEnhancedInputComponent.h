// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "CrimEnhancedInputActionTypes.h"
#include "EnhancedInputComponent.h"
#include "CrimEnhancedInputComponent.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UCrimInputActionSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCrimEnhancedInputSignature, const FCrimEnhancedInputActionBinding&, InputActionItem);

/** 
 * Provides a centralized location to dynamically bind/unbind listeners to an InputAction.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRIMENHANCEDINPUTSYSTEM_API UCrimEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UCrimEnhancedInputComponent();
	
	/** When an InputActionListener has been added and is tracked. */
	UPROPERTY(BlueprintAssignable)
	FCrimEnhancedInputSignature OnListenerAdded;
	/** When an InputActionListener that is tracked had its bindings removed. */
	UPROPERTY(BlueprintAssignable)
	FCrimEnhancedInputSignature OnListenerRemoved;
	
	/** 
	 * Creates a new binding with the ListenerClass. 
	 * Does not add it to the tracked action bindings. @see SetListener
	 */
	UFUNCTION(BlueprintCallable, Category = "CrimEnhancedInputComponent")
	FCrimEnhancedInputActionBinding CreateActionBinding(UInputAction* InputAction, const TSubclassOf<UInputActionListener>& ListenerClass);

	/**
	 * Clears and then creates a new listener bound to the InputAction.
	 * @param InputAction The InputAction to update.
	 * @param ListenerClass The class to construct as the listener bound to the InputAction.
	 */
	UFUNCTION(BlueprintCallable, Category = "CrimEnhancedInputComponent")
	void SetListener(UInputAction* InputAction, const TSubclassOf<UInputActionListener>& ListenerClass = nullptr);
	
	UFUNCTION(BlueprintCallable, Category = "CrimEnhancedInputComponent")
	void ClearListeners();
	UFUNCTION(BlueprintPure, Category = "CrimEnhancedInputComponent")
	UInputActionListener* FindListener(UInputAction* InputAction) const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "CrimEnhancedInputComponent")
	const TArray<FCrimEnhancedInputActionBinding>& GetListeners() const;
	
	virtual void ClearActionBindings() override;
	virtual void ClearBindingsForObject(UObject* InOwner) override;
	
protected:
	
private:
	/** Runtime data for tracked bindings. */
	UPROPERTY()
	TArray<FCrimEnhancedInputActionBinding> CrimEnhancedInputActionBindings;
	
	void Internal_AddListener(const FCrimEnhancedInputActionBinding& Binding);
	void Internal_RemoveListener(FCrimEnhancedInputActionBinding& Binding);
};
