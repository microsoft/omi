/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifdef _MSC_VER
    #include <sal.h>
#endif

#ifdef _MSC_VER
# define CDECLAPI __cdecl
#else
# define CDECLAPI
#endif

#include <stdlib.h>
#include <stdio.h>
#include "Frog.h"

int CDECLAPI main(int argc, _In_reads_(argc) char *argv[])
{
	int i, length, flys, depth, time;
    (argc); 
    (argv); 

	system("logman.exe start Frog -p {F93D404F-F291-496E-9D8D-56D8C6F8F650} 0xff -o NativeFrog.etl -ets");

	for(i=0; i<10; i++)
	{
		if (rand() % 2 == 0)
		{
			length = 1 + rand() % 10;
			Frog_Jump(length);
		}

		if (rand() % 2 == 0)
		{
		    flys = 1 + rand() % 3;
		    Frog_EatFlys(flys);
		}

		if (rand() % 2 == 0)
		{
			depth = 1 + rand() % 12;
                        time = 1 + rand() % 20;
			Frog_Dive(depth, time);
		}
	}

	printf("Done. Press any key to exit");
#pragma prefast(suppress: 6031)
	getchar();

	system("logman.exe stop Frog -ets");
    	return 0;
}
