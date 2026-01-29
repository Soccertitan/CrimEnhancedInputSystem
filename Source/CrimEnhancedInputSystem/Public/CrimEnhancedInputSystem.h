// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

CRIMENHANCEDINPUTSYSTEM_API DECLARE_LOG_CATEGORY_EXTERN(LogCrimEnhancedInputSystem, Log, All);

class FCrimEnhancedInputSystemModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
