// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CrimActionDefinition.generated.h"

enum class ETriggerEvent : uint8;
class UCrimAction;

/**
 * Describes an action.
 */
UCLASS(Const)
class CRIMACTIONSYSTEM_API UCrimActionDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UCrimActionDefinition();
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Primary Asset")
	FPrimaryAssetType AssetType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action Definition")
	FName ActionName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action Definition")
	TSubclassOf<UCrimAction> ActionClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action Definition|UI", meta = (AssetBundles = "UI"))
	TSoftObjectPtr<UTexture2D> Icon;

	// Requires implementing a specific interface.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action Definition|UI", meta = (AssetBundles = "UI"))
	TSoftClassPtr<UUserWidget> WidgetClass;
	
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action Definition|UI", meta = (AssetBundles = "UI"))
	// TSoftClassPtr<> ViewModelClass;
};
