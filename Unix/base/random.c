/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <stdlib.h>
#include <time.h>
#include "random.h"

int GenerateRandomString(char *buffer, int bufLen)
{
    const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    time_t t;
    int i;
    unsigned int availableLetters = sizeof(letters) - 1;

    srand((unsigned) time(&t));
    
    for (i = 0; i < bufLen - 1; ++i)
    {
        buffer[i] = letters[rand() % availableLetters];
    }

    buffer[bufLen - 1] = '\0';
    return 0;
}
