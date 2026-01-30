// Copyright Soccertitan 2025


#include "CrimEnhancedInputActionTypes.h"


bool FCrimEnhancedInputActionBinding::IsValid() const
{
	if (InputAction && Listener)
	{
		return true;
	}
	return false;
}
