/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
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
