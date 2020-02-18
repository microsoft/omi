/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include <MI.h>
#include <common.h>
#include <base/paths.h>
#include <pal/dir.h>
#include <pal/strings.h>
#include <base/batch.h>
#include <base/strarr.h>
#include <base/stringarray.h>
#include <provmgr/provmgr.h>
#include "Identify.h"

extern MI_Server* __mi_server;

#define T MI_T

#define PROVIDER_ID MI_T("2FDB5542-5896-45D5-9BE9-DC04430AAABE")

MI_Char** Listdir(const char* path)
{
    Dir* dir;
    MI_Char** arr;

    dir = Dir_Open(path);
    if (!dir)
        return NULL;

    arr = ZArr();
    if (!arr)
    {
        Dir_Close(dir);
        return NULL;
    }

    for (;;)
    {
        DirEnt* ent = Dir_Read(dir);
        MI_Char path[PAL_MAX_PATH_SIZE];
        MI_Char** oldArr = arr;


        if (!ent)
            break;

        if (strcmp(ent->name, ".") == 0 || strcmp(ent->name, "..") == 0)
            continue;

        TcsStrlcpy(path, ent->name, MI_COUNT(path));
#ifdef _PREFAST_
    #pragma prefast(push)
    #pragma prefast(disable:26018) 
        /* Prefast is getting confused with the fact that ZArrCat can return NULL for first parameter */
#endif
        ZArrCat(&arr, path);
#ifdef _PREFAST_
    #pragma prefast(pop)
#endif        
        if (!arr)
        {
            ZArrFree(oldArr);
            Dir_Close(dir);
            return NULL;
        }
    }

    Dir_Close(dir);
    return arr;
}

static MI_Result _MakeInstance(Identify* inst, MI_Context* context)
{
    MI_Char buf[1024];

    ProvMgrFT* ft = (ProvMgrFT*)__mi_server->serverFT - 1;

    if (ft->magic != PROVMGRFT_MAGIC)
        return MI_RESULT_FAILED;

    Identify_Construct(inst, context);

    Identify_Set_InstanceID(inst, PROVIDER_ID);

    TcsStrlcpy(buf, CONFIG_PRODUCT, MI_COUNT(buf));
    Identify_Set_ProductName(inst, buf);

    Identify_Set_ProductVendor(inst, T("Microsoft"));

    Identify_Set_ProductVersionMajor(inst, CONFIG_MAJOR);

    Identify_Set_ProductVersionMinor(inst, CONFIG_MINOR);

    Identify_Set_ProductVersionRevision(inst, CONFIG_REVISION);

    TcsStrlcpy(buf, CONFIG_VERSION, MI_COUNT(buf));
    Identify_Set_ProductVersionString(inst, buf);

    TcsStrlcpy(buf, CONFIG_PLATFORM, MI_COUNT(buf));
    Identify_Set_Platform(inst, buf);

    TcsStrlcpy(buf, CONFIG_OS, MI_COUNT(buf));
    Identify_Set_OperatingSystem(inst, buf);

    TcsStrlcpy(buf, CONFIG_ARCH, MI_COUNT(buf));
    Identify_Set_Architecture(inst, buf);

    TcsStrlcpy(buf, CONFIG_COMPILER, MI_COUNT(buf));
    Identify_Set_Compiler(inst, buf);

    TcsStrlcpy(buf, CONFIG_COMPILER, MI_COUNT(buf));
    Identify_Set_ConfigPrefix(inst, buf);

    TcsStrlcpy(buf, CONFIG_LIBDIR, MI_COUNT(buf));
    Identify_Set_ConfigLibDir(inst, buf);

    TcsStrlcpy(buf, CONFIG_BINDIR, MI_COUNT(buf));
    Identify_Set_ConfigBinDir(inst, buf);

    TcsStrlcpy(buf, CONFIG_INCLUDEDIR, MI_COUNT(buf));
    Identify_Set_ConfigIncludeDir(inst, buf);

    TcsStrlcpy(buf, CONFIG_DATADIR, MI_COUNT(buf));
    Identify_Set_ConfigDataDir(inst, buf);

    TcsStrlcpy(buf, CONFIG_LOCALSTATEDIR, MI_COUNT(buf));
    Identify_Set_ConfigLocalStateDir(inst, buf);

    TcsStrlcpy(buf, CONFIG_SYSCONFDIR, MI_COUNT(buf));
    Identify_Set_ConfigSysConfDir(inst, buf);

    TcsStrlcpy(buf, CONFIG_SYSCONFDIR, MI_COUNT(buf));
    Identify_Set_ConfigProviderDir(inst, buf);

    TcsStrlcpy(buf, OMI_GetPath(ID_LOGFILE), MI_COUNT(buf));
    Identify_Set_ConfigLogFile(inst, buf);

    TcsStrlcpy(buf, OMI_GetPath(ID_PIDFILE), MI_COUNT(buf));
    Identify_Set_ConfigPIDFile(inst, buf);

    TcsStrlcpy(buf, OMI_GetPath(ID_REGISTERDIR), MI_COUNT(buf));
    Identify_Set_ConfigRegisterDir(inst, buf);

    TcsStrlcpy(buf, OMI_GetPath(ID_SCHEMADIR), MI_COUNT(buf));
    Identify_Set_ConfigSchemaDir(inst, buf);

    /* Identify.SystemName */
    {
        const MI_Char* systemName;
        if (MI_Server_GetSystemName(&systemName) == MI_RESULT_OK)
            Identify_Set_SystemName(inst, systemName);
    }

    /* Identify.ConfigNameSpaces */
    {
        typedef const char* (*GetPathFunc)(PathID id);
        GetPathFunc func;

        if ((func = (GetPathFunc)ft->FindSymbol("OMI_GetPath")))
        {
            MI_Char** data = Listdir(func(ID_REGISTERDIR));

            if (data)
            {
                Identify_Set_ConfigNameSpaces(
                    inst, (const MI_Char**)data, (MI_Uint32)ZArrLen(data));

                ZArrFree(data);
            }
        }
    }

    return MI_RESULT_OK;
}

void MI_CALL Identify_Load(
    Identify_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Identify_Unload(
    Identify_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Identify_EnumerateInstances(
    Identify_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Identify inst;
    _MakeInstance(&inst, context);
    Identify_Post(&inst, context);
    Identify_Destruct(&inst);
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Identify_GetInstance(
    Identify_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identify* instanceName,
    const MI_PropertySet* propertySet)
{
    if (!instanceName ||
        !instanceName->InstanceID.exists ||
        Tcscmp(PROVIDER_ID, instanceName->InstanceID.value) != 0)
    {
        MI_PostResult(context, MI_RESULT_NOT_FOUND);
        return;
    }

    {
        Identify inst;
        _MakeInstance(&inst, context);
        Identify_Post(&inst, context);
        Identify_Destruct(&inst);
        MI_PostResult(context, MI_RESULT_OK);
    }
}

void MI_CALL Identify_CreateInstance(
    Identify_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identify* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Identify_ModifyInstance(
    Identify_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identify* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Identify_DeleteInstance(
    Identify_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identify* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}
