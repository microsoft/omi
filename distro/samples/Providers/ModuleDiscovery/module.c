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

/* @migen@ */
#include <MI.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <base/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <base/strings.h>
#include "util.h"


PSModuleFile mModuleFiles[FILECOUNT];
PS_ModuleFile psmodulefiles[MFILECOUNT];
MI_Boolean psmodulefilesConstructed[MFILECOUNT];

PS_Module psmodule;
MI_Boolean psmoduleConstructed = MI_FALSE;

MI_Boolean loadfile = MI_FALSE;

MI_EXTERN_C MI_SchemaDecl schemaDecl;

const char * Filenames[] = {
    "/omi/etc/TorSwitchManagement/TorSwitchManagement.psd1",
    "/omi/etc/TorSwitchManagement/CIM_ComputerSystem.cdxml",
    "/omi/etc/TorSwitchManagement/CIM_ComputerSystem.format.ps1xml",
    "/omi/etc/TorSwitchManagement/CIM_ComputerSystem.types.ps1xml",
    "/omi/etc/TorSwitchManagement/CIM_EthernetPort.cdxml",
    "/omi/etc/TorSwitchManagement/CIM_EthernetPort.format.ps1xml",
    "/omi/etc/TorSwitchManagement/CIM_EthernetPort.types.ps1xml",
    "/omi/etc/TorSwitchManagement/CIM_VLANEndpoint.cdxml",
    "/omi/etc/TorSwitchManagement/CIM_VLANEndpoint.format.ps1xml",
    "/omi/etc/TorSwitchManagement/CIM_VLANEndpoint.types.ps1xml"
};

unsigned int Filelengths [] = {
    736,
    4340,
    1366,
    2452,
    2333,
    2532,
    2328,
    1203,
    1092,
    2165
};

MI_Result LoadFile(PSModuleFile * f, unsigned int fileLength)
{
    if (!f)
    {
        return MI_RESULT_FAILED;
    }
    {
        //struct stat st;
        FILE * fp = Fopen(f->filename, "rb");
        if (!fp)
        {
            return MI_RESULT_FAILED;
        }
        f->datalength = fileLength + 4;
        fseek(fp, 0L, SEEK_SET);
        f->data = (unsigned char *)malloc(sizeof(unsigned char) * f->datalength);
        if (!f->data)
        {
            fclose(fp);
            return MI_RESULT_FAILED;
        }
        {
            // put length to the data
            unsigned int len = f->datalength;
            f->data[3] = (unsigned char) len & 0xFF;
            len = len >> 8;
            f->data[2] = (unsigned char) len & 0xFF;
            len = len >> 8;
            f->data[1] = (unsigned char) len & 0xFF;
            len = len >> 8;
            f->data[0] = (unsigned char) len & 0xFF;
        }
        fread(f->data + 4, 1, fileLength, fp);
        fclose(fp);
    }
    return MI_RESULT_OK;
}

MI_Result ConstructModuleInstances(_In_ struct _MI_Context* context)
{
    // construct module instance
    MI_Result r = MI_RESULT_FAILED;
    if (loadfile == MI_FALSE) return r;

    r = PS_Module_Construct(&psmodule, context);
    if (r != MI_RESULT_OK) return r;
    psmoduleConstructed = MI_TRUE;

    r = PS_Module_Set_InstanceID(&psmodule, MI_T("/omi/etc/TorSwitchManagement"));
    if (r != MI_RESULT_OK) return r;

    r = PS_Module_Set_ModuleName(&psmodule, MI_T("TorSwitchManagement"));
    if (r != MI_RESULT_OK) return r;

    r = PS_Module_Set_moduleManifestFileData(&psmodule, mModuleFiles[0].data, mModuleFiles[0].datalength);
    if (r != MI_RESULT_OK) return r;

    r = PS_Module_Set_moduleType(&psmodule, 1);
    return r;
}

MI_Result ConstructModuleFileInstances(_In_ struct _MI_Context* context)
{
    // construct moduleFile instance
    int i;
    int prefixlength = strlen("/omi/etc/TorSwitchManagement/");
    MI_Result r = MI_RESULT_FAILED;
    if (loadfile == MI_FALSE) return r;

    for (i = 0; i < MFILECOUNT; i++)
    {
        r = PS_ModuleFile_Construct(&psmodulefiles[i], context);
        if (r != MI_RESULT_OK) return r;
        psmodulefilesConstructed[i] = MI_TRUE;

        r = PS_ModuleFile_Set_InstanceID(&psmodulefiles[i], mModuleFiles[i+1].filename);
        if (r != MI_RESULT_OK) return r;

        r = PS_ModuleFile_Set_FileName(&psmodulefiles[i], Filenames[i+1] + prefixlength);
        if (r != MI_RESULT_OK) return r;

        r = PS_ModuleFile_Set_FileData(&psmodulefiles[i], mModuleFiles[i+1].data, mModuleFiles[i+1].datalength);
    }
    return r;
}

void DestructModuleInstances()
{
    if (psmoduleConstructed == MI_TRUE) PS_Module_Destruct(&psmodule);
    psmoduleConstructed = MI_FALSE;
}

void DestructModuleFileInstances()
{
    int i;
    for (i = 0; i < MFILECOUNT; i++)
    {
        if (psmodulefilesConstructed[i] == MI_TRUE) PS_ModuleFile_Destruct(&psmodulefiles[i]);
        psmodulefilesConstructed[i] = MI_FALSE;
    }
}

void CleanUp()
{
    int i;
    for (i = 0; i < FILECOUNT; i++)
    {
        if (mModuleFiles[i].data) free(mModuleFiles[i].data);
    }
}

void MI_CALL Load(_Outptr_result_maybenull_ MI_Module_Self** self, _In_ struct _MI_Context* context)
{
    int i;
    MI_Result r;
    *self = NULL;

    loadfile = MI_TRUE;
    for (i = 0; i < FILECOUNT; i++)
    {
        mModuleFiles[i].filename = Filenames[i];
        mModuleFiles[i].data = 0;
        mModuleFiles[i].datalength = 0;
        r = LoadFile(&mModuleFiles[i], Filelengths[i]);
        if ( i < MFILECOUNT)
            psmodulefilesConstructed[i] = MI_FALSE;
    }
    MI_Context_PostResult(context, r);
}

void MI_CALL Unload(_In_opt_ MI_Module_Self* self, _In_ struct _MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(context);
    CleanUp();
    MI_Context_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C MI_EXPORT MI_Module* MI_MAIN_CALL MI_Main(_In_ MI_Server* server)
{
    /* WARNING: THIS FUNCTION AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT. */
    static MI_Module module;
    MI_EXTERN_C MI_Server* __mi_server;
    __mi_server = server;
    module.flags |= MI_MODULE_FLAG_DESCRIPTIONS;
    module.flags |= MI_MODULE_FLAG_VALUES;
    module.flags |= MI_MODULE_FLAG_BOOLEANS;
    module.flags |= MI_MODULE_FLAG_LOCALIZED;
    module.charSize = sizeof(MI_Char);
    module.version = MI_VERSION;
    module.generatorVersion = MI_MAKE_VERSION(1,0,0);
    module.schemaDecl = &schemaDecl;
    module.Load = Load;
    module.Unload = Unload;
    return &module;
}
