/* @migen@ */
#include <MI.h>
#include <base/strings.h>
#include "dir.h"
#include "MSFT_DirectoryContainsFile.h"
#include "MSFT_DataFile.h"

#define T MI_T

MI_Boolean ConstructDirectory(
    MSFT_Directory* self,
    const MI_Char* name,
    MI_Context* context);

void MI_CALL MSFT_DirectoryContainsFile_Load(
    MSFT_DirectoryContainsFile_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_DirectoryContainsFile_Unload(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_DirectoryContainsFile_EnumerateInstances(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_DirectoryContainsFile_GetInstance(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_DirectoryContainsFile* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_DirectoryContainsFile_CreateInstance(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_DirectoryContainsFile* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_DirectoryContainsFile_ModifyInstance(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_DirectoryContainsFile* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_DirectoryContainsFile_DeleteInstance(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_DirectoryContainsFile* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_DirectoryContainsFile_AssociatorInstancesGroupComponent(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Directory* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Dir* dir;
    char buf[MAX_PATH_SIZE];

    /* Try to open this directory */

    dir = Dir_Open(ZToStr(buf, MI_COUNT(buf), instanceName->Name.value));

    if (!dir)
    {
        MI_PostResult(context, MI_RESULT_NOT_FOUND);
        return;
    }

    /* Visit associated files and directories */

    for (;;)
    {
        DirEnt* ent;
        MI_Char path[MAX_PATH_SIZE];
        MI_Char zbuf[MAX_PATH_SIZE];

        ent = Dir_Read(dir);

        if (!ent)
            break;

        if (strcmp(ent->name, "..") == 0 || strcmp(ent->name, ".") == 0)
            continue;

        /* Form full path to directory or file */

        Zlcpy(path, instanceName->Name.value, MAX_PATH_SIZE);

        if (Zcmp(instanceName->Name.value, T("/")) != 0)
            Zlcat(path, T("/"), MAX_PATH_SIZE);

        Zlcat(path, StrToZ(zbuf, MI_COUNT(buf), ent->name), MAX_PATH_SIZE);

        if (ent->isDir)
        {
            if (!resultClass || Zcasecmp(resultClass, T("MSFT_Directory")) == 0)
            {
                MSFT_Directory inst;

                if (ConstructDirectory(&inst, path, context))
                {
                    MSFT_Directory_Post(&inst, context);
                }
            }
        }
        else
        {
            if (!resultClass || Zcasecmp(resultClass, T("MSFT_DataFile")) == 0)
            {
                MSFT_DataFile inst;
                MSFT_DataFile_Construct(&inst, context);
                MSFT_DataFile_Set_Name(&inst, path);
                MSFT_DataFile_Post(&inst, context);
            }
        }
    }

    /* Close this directory */

    Dir_Close(dir);

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_DirectoryContainsFile_AssociatorInstancesPartComponent(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_LogicalFile* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_DirectoryContainsFile_ReferenceInstancesGroupComponent(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Directory* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_DirectoryContainsFile_ReferenceInstancesPartComponent(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_LogicalFile* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

