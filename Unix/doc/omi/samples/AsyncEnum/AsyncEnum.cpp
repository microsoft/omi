/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <cstdio>
#include <omiclient/client.h>

#define T MI_T

using namespace mi;

class MyHandler : public Handler
{
public:

    MyHandler() : done(false)
    {
    }

    virtual void HandleConnect()
    {
        printf("==== MyHandler::HandleConnect()\n");
    }

    virtual void HandleNoOp(Uint64 operationId)
    {
        printf("==== MyHandler::HandleNoOp()\n");
    }

    virtual void HandleConnectFailed()
    {
        printf("==== MyHandler::HandleConnectFailed()\n");

        // Handler error!
        done = true;
    }

    virtual void HandleDisconnect()
    {
        printf("==== MyHandler::HandleDisconnect()\n");
        done = true;
    }

    virtual void HandleInstance(Uint64 operationId, const DInstance& instance)
    {
        printf("==== MyHandler::HandleInstance()\n");

        instance.Print();
    }

    virtual void HandleResult(Uint64 operationId, MI_Result result)
    {
        printf("==== MyHandler::HandleResult()\n");
        done = true;
    }

    bool done;
};

int main(int argc, const char* argv[])
{
    int r = 0;

    // Create handler:
    MyHandler* handler = new MyHandler;

    // Construct client:
    Client client(handler);

    String locator;
    String username;
    String password;

    if (!client.ConnectAsync(locator, username, password))
    {
        // Handle error!
    }

    const String nameSpace = "root/omi";
    const String className = "OMI_Identify";
    const bool deep = true;
    Uint64 operationId;

    if (!client.EnumerateInstancesAsync(nameSpace, className, deep, operationId))
    {
        // Handle error!
    }

    // Wait here for 5 seconds for operation to finish.
    while (!handler->done)
    {
        client.Run(1000);
    }

    return r;
}
