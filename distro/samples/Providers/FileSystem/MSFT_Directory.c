/* @migen@ */
#include <MI.h>
#include <stdlib.h>
#include <base/strings.h>
#include "MSFT_Directory.h"
#include "dir.h"

MI_Boolean ConstructDirectory(
    MSFT_Directory* self,
    const MI_Char* name,
    MI_Context* context)
{
    Dir* dir;
    MI_Uint32 count = 0;
    MI_Uint32 i;
    char** names = NULL;
    char buf[MAX_PATH_SIZE];

    /* Reject if key is null */

    if (!name)
        return MI_FALSE;

    /* Try to open this directory */

    dir = Dir_Open(ZToStr(buf, MI_COUNT(buf), name));

    if (!dir)
        return MI_FALSE;

    /* Build a list of file names in this directory */

    for (;;)
    {
        DirEnt* ent = Dir_Read(dir);

        if (!ent)
            break;

        if (strcmp(ent->name, ".") == 0 || strcmp(ent->name, "..") == 0)
            continue;

        names = (char**)realloc(names, (count+1) * sizeof(char*));

        if (!names)
        {
            free(names);
            return MI_FALSE;
        }

        names[count] = strdup(ent->name);

        if (!names[count])
        {
            for (i = 0; i < count; i++)
                free(names[i]);

            return MI_FALSE;
        }

        count++;
    }

    /* Close this directory */

    Dir_Close(dir);

    /* Build and post the instance */
    {
        MSFT_Directory_Construct(self, context);
        MSFT_Directory_Set_Name(self, name);
        MSFT_Directory_Set_Count(self, count);
        MSFT_Directory_Set_FileNames(self, (const MI_Char**)names, count);
    }

    /* Free the names */

    for (i = 0; i < count; i++)
        free(names[i]);

    return MI_TRUE;
}

void MI_CALL MSFT_Directory_Load(
    MSFT_Directory_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_Directory_Unload(
    MSFT_Directory_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_Directory_EnumerateInstances(
    MSFT_Directory_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_Directory_GetInstance(
    MSFT_Directory_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Directory* instanceName,
    const MI_PropertySet* propertySet)
{
    MSFT_Directory inst;

    /* Reject if key is null */

    if (!instanceName->Name.value)
    {
        MI_PostResult(context, MI_RESULT_NOT_FOUND);
        return;
    }

    if (!ConstructDirectory(&inst, instanceName->Name.value, context))
    {
        MI_PostResult(context, MI_RESULT_FAILED);
        return;
    }

    MSFT_Directory_Post(&inst, context);
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_Directory_CreateInstance(
    MSFT_Directory_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Directory* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_Directory_ModifyInstance(
    MSFT_Directory_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Directory* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_Directory_DeleteInstance(
    MSFT_Directory_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Directory* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

