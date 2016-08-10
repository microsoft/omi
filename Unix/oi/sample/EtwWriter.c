/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <oi_etw.h>

REGHANDLE RegistrationHandle = 0;

void EtwInitProvider()
{
	if (0 != RegistrationHandle)
		return;

	EventRegister(
			&ProviderGuid,      // GUID that identifies the provider
			NULL,               // Callback not used
			NULL,               // Context noot used
			&RegistrationHandle // Used when calling EventWrite and EventUnregister
			);
}


