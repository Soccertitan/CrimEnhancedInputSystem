// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CrimInputActionSet.generated.h"

class UCrimAction;
class UInputMappingContext;
class UInputAction;

USTRUCT(BlueprintType)
struct FCrimInputAction
{
	GENERATED_BODY()

	// The InputTag to map to the InputAction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Input"))
	FGameplayTag InputTag = FGameplayTag();
	// The InputAction to activate the CrimAction.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputAction> InputAction = nullptr;
	// The Action to call when the InputAction is activated. Can be empty and set at runtime.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCrimAction> ActionClass;
	
	bool IsValid() const;
};

/**
 * Maps a GameplayTag to an InputAction. Also defines an InputMappingContext and priority to grant.
 */
UCLASS()
class CRIMENHANCEDINPUTSYSTEM_API UCrimInputActionSet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 InputMappingContextPriority = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (NoResetToDefault, TitleProperty=InputTag))
	TArray<FCrimInputAction> InputActions;
};
