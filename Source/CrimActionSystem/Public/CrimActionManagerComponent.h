// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "CrimActionTypes.h"
#include "CrimInputActionSet.h"
#include "Components/ActorComponent.h"
#include "CrimActionManagerComponent.generated.h"


class UCrimActionDefinition;
class UEnhancedInputLocalPlayerSubsystem;
class UCrimInputActionSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCrimActionManagerInputActionSignature, const FCrimInputActionItem&, InputActionItem);

/** 
 * Can assign different actions that can be triggered. Like an ActionBar, palette, or action slot. From using items, to activating abilities,
 * or other gameplay features. This is separate from the GAS AbilityInputManager as not all actions need to be routed 
 * through GAS or custom events need to be passed into an ability from client.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRIMACTIONSYSTEM_API UCrimActionManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCrimActionManagerComponent();
	
	/** When an InputAction has been bound to the EnhancedInputComponent. */
	UPROPERTY(BlueprintAssignable)
	FCrimActionManagerInputActionSignature OnInputActionAdded;
	/** When an InputAction bindings has been removed from the EnhancedInputComponent. */
	UPROPERTY(BlueprintAssignable)
	FCrimActionManagerInputActionSignature OnInputActionRemoved;
	
	UFUNCTION(BlueprintPure, Category = "CrimActionManager")
	UCrimAction* FindAction(UPARAM(meta = (Categories = "Input")) FGameplayTag InputTag) const;
	
	// Call this in the PlayerController during SetupInputComponent().
	virtual void InitActionManagerComponent();

	UFUNCTION(BlueprintCallable, Category = "CrimActionManager")
	void SetInputActionSet(UCrimInputActionSet* InputActionSet);
	UFUNCTION(BlueprintCallable, Category = "CrimActionManager")
	void SetInputAction(const FCrimInputAction& InputAction);
	
	UFUNCTION(BlueprintCallable, Category = "CrimActionManager")
	void SetAction(UPARAM(meta = (Categories = "Input")) FGameplayTag InputTag, UCrimActionDefinition* ActionDefinition);
	
protected:
	// Input Actions to bind to by default.
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UCrimInputActionSet>> InputActionSets;
	
private:
	/** Cached InputComponent from the player controller. */
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;
	
	UPROPERTY()
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputSubsystem;
	
	/** Cached reference of the PlayerController */
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;
	
	/** Runtime data for active InputActions. */
	UPROPERTY()
	TArray<FCrimInputActionItem> InputActionItems;
	
	void Internal_AddBinding(FCrimInputActionItem& InputActionItem, UCrimActionDefinition* ActionDefinition);
	void Internal_RemoveBinding(FCrimInputActionItem& InputActionItem);
};
