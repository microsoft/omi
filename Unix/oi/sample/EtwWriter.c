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


