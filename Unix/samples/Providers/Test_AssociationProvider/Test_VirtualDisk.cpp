/* @migen@ */
#include <MI.h>
#include "Test_VirtualDisk.h"
#include "CommonUtils.h"
#include <vector>

#include <pal/strings.h>

std::vector<Test_VirtualDisk*> virtualDiskInstanceStore;

void CreateVirtualDiskInstances(MI_Context* context, std::vector<Test_VirtualDisk*>& virtualStore)
{
    Test_VirtualDisk* instance = NULL;
    Test_VirtualDisk temp; 

    Test_VirtualDisk_Construct(&temp, context);
    Test_VirtualDisk_Clone(&temp, &instance);

    Test_VirtualDisk_Set_serialNumber(instance, MI_T("11000"));
    Test_VirtualDisk_Set_sectorSize(instance, 512);
    Test_VirtualDisk_Set_numSectors(instance, 100000);
    Test_VirtualDisk_Set_filePath(instance, MI_T("\\vhd\\TestVhd.vhd"));
    virtualStore.push_back(instance);

    Test_VirtualDisk_Destruct(&temp);    
}

void MI_CALL Test_VirtualDisk_Load(
    Test_VirtualDisk_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;

    if(virtualDiskInstanceStore.size() == 0)
    {
        CreateVirtualDiskInstances(context, virtualDiskInstanceStore);        
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_VirtualDisk_Unload(
    Test_VirtualDisk_Self* self,
    MI_Context* context)
{
    for(unsigned int i=0; i < virtualDiskInstanceStore.size(); i++)
    {    
        Test_VirtualDisk_Delete(virtualDiskInstanceStore[i]);
    }

    virtualDiskInstanceStore.clear();

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_VirtualDisk_EnumerateInstances(
    Test_VirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Result result = MI_RESULT_FAILED;

    for(MI_Uint32 i = 0; i < virtualDiskInstanceStore.size(); ++i)
    {
        result = Test_VirtualDisk_Post(virtualDiskInstanceStore[i], context);

        if(result != MI_RESULT_OK)
            break;
    }

    MI_PostResult(context, result);
}

void MI_CALL Test_VirtualDisk_GetInstance(
    Test_VirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_VirtualDisk* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_Result result = MI_RESULT_FAILED;
    MI_Boolean instanceFound = MI_FALSE;

    if(instanceName->serialNumber.exists == MI_FALSE)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }
        
    for(MI_Uint32 i = 0; i < virtualDiskInstanceStore.size(); ++i)
    {
        if(Tcscasecmp(virtualDiskInstanceStore[i]->serialNumber.value, instanceName->serialNumber.value) == 0)          
        {
            instanceFound = MI_TRUE;

            result = Test_VirtualDisk_Post(virtualDiskInstanceStore[i], context);

            if(result != MI_RESULT_OK)
                break;
        }
    }

    if(instanceFound == MI_FALSE)
        result = MI_RESULT_NOT_FOUND;

    MI_PostResult(context, result);
}

void MI_CALL Test_VirtualDisk_CreateInstance(
    Test_VirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_VirtualDisk* newInstance)
{
    MI_Result result = MI_RESULT_FAILED;

    if(newInstance->serialNumber.exists == MI_FALSE)
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }
    else
    {
        Test_VirtualDisk *temp;
        result = Test_VirtualDisk_Clone(newInstance, &temp);

        if(result != MI_RESULT_OK)
        {
            MI_PostResult(context, result);
            return;
        }

        virtualDiskInstanceStore.push_back(temp);
        
        result = Test_VirtualDisk_Post(newInstance, context);
    }

    MI_PostResult(context, result);
}

void MI_CALL Test_VirtualDisk_ModifyInstance(
    Test_VirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_VirtualDisk* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_Result result = MI_RESULT_FAILED;
    MI_Boolean instanceFound = MI_FALSE;

    MI_Value val;
    MI_Type type;
    MI_Uint32 flags;
    const MI_Char* propertyName;

    if(modifiedInstance->serialNumber.exists == MI_FALSE)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }
        
    for(MI_Uint32 i = 0; i < virtualDiskInstanceStore.size(); ++i)
    {
        if(Tcscasecmp(virtualDiskInstanceStore[i]->serialNumber.value, modifiedInstance->serialNumber.value) == 0)
        {
            instanceFound = MI_TRUE;

            // check each proprty here for modification
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
                    result = MI_Instance_SetElementAt(&virtualDiskInstanceStore[i]->__instance, j, &val, type, flags);        
                    if(result != MI_RESULT_OK)
                        break;
                }
            }
            
            if(result != MI_RESULT_OK)
                break;
            
            result = Test_VirtualDisk_Post(virtualDiskInstanceStore[i], context);

            break;
        }
    }

    if(instanceFound == MI_FALSE)
        result = MI_RESULT_NOT_FOUND;

    MI_PostResult(context, result);
}

void MI_CALL Test_VirtualDisk_DeleteInstance(
    Test_VirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_VirtualDisk* instanceName)
{
    MI_Result result = MI_RESULT_FAILED;

    MI_Boolean instanceFound = MI_FALSE;

    if(instanceName->serialNumber.exists == MI_FALSE)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }
        
    std::vector<Test_VirtualDisk*>::iterator it;

    //for(MI_Uint32 i = 0; i < virtualDiskInstanceStore.size(); ++i)
    for(it = virtualDiskInstanceStore.begin(); it != virtualDiskInstanceStore.end(); it++)
    {
        if(Tcscasecmp((*it)->serialNumber.value, instanceName->serialNumber.value) == 0)
        {
            instanceFound = MI_TRUE;

            result = Test_VirtualDisk_Post((*it), context);

            Test_VirtualDisk_Delete((*it));
            virtualDiskInstanceStore.erase(it);

            if(result != MI_RESULT_OK)
                break;
        }
    }

    if(instanceFound == MI_FALSE)
        result = MI_RESULT_NOT_FOUND;

    MI_PostResult(context, result);
}

