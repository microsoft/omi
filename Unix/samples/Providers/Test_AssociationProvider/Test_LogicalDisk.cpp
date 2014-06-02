/* @migen@ */
#include <MI.h>
#include "CommonUtils.h"
#include "Test_LogicalDisk.h"
#include <pal/strings.h>

#include <vector>

std::vector<Test_LogicalDisk*> logicalDiskInstanceStore;

void CreateLogicalDiskInstances(MI_Context* context, std::vector<Test_LogicalDisk*>& logStore)
{
    Test_LogicalDisk* instance = NULL;
    Test_LogicalDisk temp; 

    Test_LogicalDisk_Construct(&temp, context);
    Test_LogicalDisk_Clone(&temp, &instance);
    Test_LogicalDisk_Set_diskID(instance, 0);
    Test_LogicalDisk_Set_driveLetter(instance, MI_T("C"));
    Test_LogicalDisk_Set_sizeInGb(instance, 100);    
    logStore.push_back(instance);
    Test_LogicalDisk_Destruct(&temp);    

    Test_LogicalDisk_Construct(&temp, context);
    Test_LogicalDisk_Clone(&temp, &instance);
    Test_LogicalDisk_Set_diskID(instance, 1);
    Test_LogicalDisk_Set_driveLetter(instance, MI_T("D"));
    Test_LogicalDisk_Set_sizeInGb(instance, 100);    
    logStore.push_back(instance);
    Test_LogicalDisk_Destruct(&temp);    

    Test_LogicalDisk_Construct(&temp, context);
    Test_LogicalDisk_Clone(&temp, &instance);
    Test_LogicalDisk_Set_diskID(instance, 2);
    Test_LogicalDisk_Set_driveLetter(instance, MI_T("E"));
    Test_LogicalDisk_Set_sizeInGb(instance, 100);    
    logStore.push_back(instance);
    Test_LogicalDisk_Destruct(&temp);    
}

void MI_CALL Test_LogicalDisk_Load(
    Test_LogicalDisk_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;

    if(logicalDiskInstanceStore.size() == 0)
    {
        CreateLogicalDiskInstances(context, logicalDiskInstanceStore);
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_LogicalDisk_Unload(
    Test_LogicalDisk_Self* self,
    MI_Context* context)
{
    for(unsigned int i=0; i < logicalDiskInstanceStore.size(); i++)
    {    
        Test_LogicalDisk_Delete(logicalDiskInstanceStore[i]);
    }

    logicalDiskInstanceStore.clear();

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_LogicalDisk_EnumerateInstances(
    Test_LogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Result result = MI_RESULT_FAILED;

    for(MI_Uint32 i = 0; i < logicalDiskInstanceStore.size(); ++i)
    {
        result = Test_LogicalDisk_Post(logicalDiskInstanceStore[i], context);

        if(result != MI_RESULT_OK)
            break;
    }

    MI_PostResult(context, result);
}

void MI_CALL Test_LogicalDisk_GetInstance(
    Test_LogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_Result result = MI_RESULT_FAILED;
    MI_Boolean instanceFound = MI_FALSE;

    if(instanceName->diskID.exists == MI_FALSE || instanceName->driveLetter.exists == MI_FALSE)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }
        
    for(MI_Uint32 i = 0; i < logicalDiskInstanceStore.size(); ++i)
    {
        if(logicalDiskInstanceStore[i]->diskID.value == instanceName->diskID.value && (Tcscasecmp(logicalDiskInstanceStore[i]->driveLetter.value, instanceName->driveLetter.value) == 0) )
        {
            instanceFound = MI_TRUE;

            result = Test_LogicalDisk_Post(logicalDiskInstanceStore[i], context);

            if(result != MI_RESULT_OK)
                break;
        }
    }

    if(instanceFound == MI_FALSE)
        result = MI_RESULT_NOT_FOUND;

    MI_PostResult(context, result);
}

void MI_CALL Test_LogicalDisk_CreateInstance(
    Test_LogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* newInstance)
{
    MI_Result result = MI_RESULT_FAILED;

    if(newInstance->diskID.exists == MI_FALSE || newInstance->driveLetter.exists == MI_FALSE)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }
    else
    {
        Test_LogicalDisk *temp;
        result = Test_LogicalDisk_Clone(newInstance, &temp);

        if(result != MI_RESULT_OK)
        {
            MI_PostResult(context, result);
            return;
        }

        logicalDiskInstanceStore.push_back(temp);
        
        result = Test_LogicalDisk_Post(newInstance, context);
    }

    MI_PostResult(context, result);
}

void MI_CALL Test_LogicalDisk_ModifyInstance(
    Test_LogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_Result result = MI_RESULT_FAILED;
    MI_Boolean instanceFound = MI_FALSE;

    MI_Value val;
    MI_Type type;
    MI_Uint32 flags;
    const MI_Char* propertyName;

    if(modifiedInstance->diskID.exists == MI_FALSE || modifiedInstance->driveLetter.exists == MI_FALSE)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }
        
    for(MI_Uint32 i = 0; i < logicalDiskInstanceStore.size(); ++i)
    {
        if(logicalDiskInstanceStore[i]->diskID.value == modifiedInstance->diskID.value && (Tcscasecmp(logicalDiskInstanceStore[i]->driveLetter.value, modifiedInstance->driveLetter.value) == 0) )
        {
            instanceFound = MI_TRUE;

            // check each property here for modification
            MI_Uint32 numProperties = 0;
            
            result = MI_Instance_GetElementCount(&modifiedInstance->__instance, &numProperties);
            if(result != MI_RESULT_OK)
                break;

            for(MI_Uint32 j = 0; j < numProperties; ++j)
            {
                result = MI_Instance_GetElementAt(&modifiedInstance->__instance, j, &propertyName, &val, &type, &flags);
                if(result != MI_RESULT_OK)
                    break;

                if((flags & MI_FLAG_NOT_MODIFIED) != 0)
                {
                    result = MI_Instance_SetElementAt(&logicalDiskInstanceStore[i]->__instance, j, &val, type, flags);        
                    if(result != MI_RESULT_OK)
                        break;
                }
            }
            
            if(result != MI_RESULT_OK)
                break;
            
            result = Test_LogicalDisk_Post(logicalDiskInstanceStore[i], context);

            break;
        }
    }

    if(instanceFound == MI_FALSE)
        result = MI_RESULT_NOT_FOUND;

    MI_PostResult(context, result);
}

void MI_CALL Test_LogicalDisk_DeleteInstance(
    Test_LogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* instanceName)
{
    MI_Result result = MI_RESULT_FAILED;
    MI_Boolean instanceFound = MI_FALSE;

    if(instanceName->diskID.exists == MI_FALSE || instanceName->driveLetter.exists == MI_FALSE)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }
        
    std::vector<Test_LogicalDisk*>::iterator it;
        
    for(it = logicalDiskInstanceStore.begin(); it != logicalDiskInstanceStore.end(); it++)
    {        
        if((*it)->diskID.value == instanceName->diskID.value && (Tcscasecmp((*it)->driveLetter.value, instanceName->driveLetter.value) == 0) )     
        {
            instanceFound = MI_TRUE;

            result = Test_LogicalDisk_Post((*it), context);

            Test_LogicalDisk_Delete((*it));
            logicalDiskInstanceStore.erase(it);

            if(result != MI_RESULT_OK)
                break;
        }
    }

    if(instanceFound == MI_FALSE)
        result = MI_RESULT_NOT_FOUND;

    MI_PostResult(context, result);   
}

