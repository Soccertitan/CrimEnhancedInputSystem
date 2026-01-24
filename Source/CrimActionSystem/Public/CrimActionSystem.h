// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

CRIMACTIONSYSTEM_API DECLARE_LOG_CATEGORY_EXTERN(LogCrimActionSystem, Log, All);

class FCrimActionSystemModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
