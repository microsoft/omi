/* @migen@ */
#include <MI.h>
#include "CommonUtils.h"
#include "Test_PhysicalDisk.h"

#include <vector>

std::vector<Test_PhysicalDisk*> physicalDiskInstanceStore;

void CreatePhysicalDiskInstances(MI_Context* context, std::vector<Test_PhysicalDisk*>& phyStore)
{
	Test_PhysicalDisk* instance = NULL;
	Test_PhysicalDisk temp; 

	Test_PhysicalDisk_Construct(&temp, context);
	Test_PhysicalDisk_Clone(&temp, &instance);

	Test_PhysicalDisk_Set_serialNumber(instance, MI_T("10000"));
	Test_PhysicalDisk_Set_sectorSize(instance, 512);
	Test_PhysicalDisk_Set_numSectors(instance, 488281250);	
	phyStore.push_back(instance);

	Test_PhysicalDisk_Destruct(&temp);	

	Test_PhysicalDisk_Construct(&temp, context);
	Test_PhysicalDisk_Clone(&temp, &instance);

	Test_PhysicalDisk_Set_serialNumber(instance, MI_T("10001"));
	Test_PhysicalDisk_Set_sectorSize(instance, 512);
	Test_PhysicalDisk_Set_numSectors(instance, 488281250);	
	phyStore.push_back(instance);

	Test_PhysicalDisk_Destruct(&temp);	
}

void MI_CALL Test_PhysicalDisk_Load(
    Test_PhysicalDisk_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;

	if(physicalDiskInstanceStore.size() == 0)
	{
		CreatePhysicalDiskInstances(context, physicalDiskInstanceStore);
	}

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_PhysicalDisk_Unload(
    Test_PhysicalDisk_Self* self,
    MI_Context* context)
{
	for(unsigned int i=0; i < physicalDiskInstanceStore.size(); i++)
	{	
		Test_PhysicalDisk_Delete(physicalDiskInstanceStore[i]);
	}

	physicalDiskInstanceStore.clear();

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_PhysicalDisk_EnumerateInstances(
    Test_PhysicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Result result = MI_RESULT_FAILED;

	for(MI_Uint32 i = 0; i < physicalDiskInstanceStore.size(); ++i)
	{
		result = Test_PhysicalDisk_Post(physicalDiskInstanceStore[i], context);

		if(result != MI_RESULT_OK)
			break;
	}

    MI_PostResult(context, result);
}

void MI_CALL Test_PhysicalDisk_GetInstance(
    Test_PhysicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_PhysicalDisk* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_Result result = MI_RESULT_FAILED;
	MI_Boolean instanceFound = MI_FALSE;

	if(instanceName->serialNumber.exists == MI_FALSE)
	{
		MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
		return;
	}
		
	for(MI_Uint32 i = 0; i < physicalDiskInstanceStore.size(); ++i)
	{
#if(MI_CHAR_TYPE == 1)
		if(strcasecmp(physicalDiskInstanceStore[i]->serialNumber.value, instanceName->serialNumber.value) == 0)
#else
		if(wcasecmp(physicalDiskInstanceStore[i]->serialNumber.value, instanceName->serialNumber.value) == 0)
#endif		
		{
			instanceFound = MI_TRUE;

			result = Test_PhysicalDisk_Post(physicalDiskInstanceStore[i], context);

			if(result != MI_RESULT_OK)
				break;
		}
	}

	if(instanceFound == MI_FALSE)
		result = MI_RESULT_NOT_FOUND;

    MI_PostResult(context, result);
}

void MI_CALL Test_PhysicalDisk_CreateInstance(
    Test_PhysicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_PhysicalDisk* newInstance)
{
    MI_Result result = MI_RESULT_FAILED;

	if(newInstance->serialNumber.exists == MI_FALSE)
	{
		result = MI_RESULT_INVALID_PARAMETER;
	}
	else
	{
		Test_PhysicalDisk *temp;
		result = Test_PhysicalDisk_Clone(newInstance, &temp);

		if(result != MI_RESULT_OK)
		{
			MI_PostResult(context, result);
			return;
		}

		physicalDiskInstanceStore.push_back(temp);
		
		result = Test_PhysicalDisk_Post(newInstance, context);
	}

    MI_PostResult(context, result);
}

void MI_CALL Test_PhysicalDisk_ModifyInstance(
    Test_PhysicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_PhysicalDisk* modifiedInstance,
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
		
	for(MI_Uint32 i = 0; i < physicalDiskInstanceStore.size(); ++i)
	{

#if(MI_CHAR_TYPE == 1)
		if(strcasecmp(physicalDiskInstanceStore[i]->serialNumber.value, modifiedInstance->serialNumber.value) == 0)
#else
		if(wcasecmp(physicalDiskInstanceStore[i]->serialNumber.value, modifiedInstance->serialNumber.value) == 0)
#endif
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
					result = MI_Instance_SetElementAt(&physicalDiskInstanceStore[i]->__instance, j, &val, type, flags);		
					if(result != MI_RESULT_OK)
						break;
				}
			}
			
			if(result != MI_RESULT_OK)
				break;
			
			result = Test_PhysicalDisk_Post(physicalDiskInstanceStore[i], context);

			break;
		}
	}

	if(instanceFound == MI_FALSE)
		result = MI_RESULT_NOT_FOUND;

    MI_PostResult(context, result);
}

void MI_CALL Test_PhysicalDisk_DeleteInstance(
    Test_PhysicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_PhysicalDisk* instanceName)
{
    MI_Result result = MI_RESULT_FAILED;

	MI_Boolean instanceFound = MI_FALSE;

	if(instanceName->serialNumber.exists == MI_FALSE)
	{
		MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
		return;
	}
		
	std::vector<Test_PhysicalDisk*>::iterator it;
		
	for(it = physicalDiskInstanceStore.begin(); it != physicalDiskInstanceStore.end(); it++)
	{
#if(MI_CHAR_TYPE == 1)
		if(strcasecmp((*it)->serialNumber.value, instanceName->serialNumber.value) == 0)
#else
		if(wcasecmp((*it)->serialNumber.value, instanceName->serialNumber.value) == 0)
#endif	
		{
			instanceFound = MI_TRUE;

			result = Test_PhysicalDisk_Post((*it), context);

			Test_PhysicalDisk_Delete((*it));
			physicalDiskInstanceStore.erase(it);

			if(result != MI_RESULT_OK)
				break;
		}
	}

	if(instanceFound == MI_FALSE)
		result = MI_RESULT_NOT_FOUND;

    MI_PostResult(context, result);
}

