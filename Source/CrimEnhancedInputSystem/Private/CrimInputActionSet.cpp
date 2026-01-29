// Copyright Soccertitan 2025


#include "CrimInputActionSet.h"

bool FCrimInputAction::IsValid() const
{
	if (!InputTag.IsValid())
	{
		return false;
	}
	
	if (!InputAction)
	{
		return false;
	}
	
	return true;
}
