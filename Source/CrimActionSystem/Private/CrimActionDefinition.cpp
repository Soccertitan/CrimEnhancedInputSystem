// Copyright Soccertitan 2025


#include "CrimActionDefinition.h"

UCrimActionDefinition::UCrimActionDefinition()
{
	AssetType = TEXT("CrimInputActionDefinition");
}

FPrimaryAssetId UCrimActionDefinition::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(AssetType, GetFName());
}
