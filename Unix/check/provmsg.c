#include <stdio.h>

#include <base/messages.h>

void PrintProviderMsg( _In_ Message* msg)
{
    MessagePrint(msg, stdout);
}
