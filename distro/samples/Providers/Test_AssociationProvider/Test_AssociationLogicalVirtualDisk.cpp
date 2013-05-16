/* @migen@ */
#include <MI.h>
#include "Test_AssociationLogicalVirtualDisk.h"
#include "CommonUtils.h"

std::vector<Test_VirtualDisk*> virtualDiskForAssocInstanceStore;
std::vector<Test_LogicalDisk*> logicalDiskForVirtualAssocInstanceStore;

void CreateLogicalVirtualAssociations(MI_Context* context)
{
	CreateVirtualDiskInstances(context, virtualDiskForAssocInstanceStore);	
	CreateLogicalDiskInstances(context, logicalDiskForVirtualAssocInstanceStore);	
}

MI_Result PostVirtualToLogicalAssociation(MI_Context* context, const Test_VirtualDisk* instanceName, MI_Boolean isReference)
{
	MI_Result result = MI_RESULT_OK;

	if(instanceName->serialNumber.exists == MI_FALSE)
	{
		result = MI_RESULT_INVALID_PARAMETER;
	}
	else
	{	
#if(MI_CHAR_TYPE == 1)
		if(strcasecmp(instanceName->serialNumber.value, MI_T("11000")) == 0)
#else
		if(wcasecmp(instanceName->serialNumber.value, MI_T("11000")) == 0)
#endif
		{
			for(MI_Uint32 i = 0; i < logicalDiskForVirtualAssocInstanceStore.size(); ++i)
			{	
#if(MI_CHAR_TYPE == 1)
				if(logicalDiskForVirtualAssocInstanceStore[i]->diskID.value == 2 && (strcasecmp(logicalDiskForVirtualAssocInstanceStore[i]->driveLetter.value, MI_T("E")) == 0))
#else
				if(logicalDiskForVirtualAssocInstanceStore[i]->diskID.value == 2 && (wcasecmp(logicalDiskForVirtualAssocInstanceStore[i]->driveLetter.value, MI_T("E")) == 0))
#endif
				{
					if(isReference == MI_TRUE)
					{
						Test_AssociationLogicalVirtualDisk assocInstance;
						Test_AssociationLogicalVirtualDisk_Construct(&assocInstance, context);
						Test_AssociationLogicalVirtualDisk_Set_antecedent(&assocInstance, logicalDiskForVirtualAssocInstanceStore[i]);
						Test_AssociationLogicalVirtualDisk_Set_dependent(&assocInstance, instanceName);
						result = Test_AssociationLogicalVirtualDisk_Post(&assocInstance, context);

						Test_AssociationLogicalVirtualDisk_Destruct(&assocInstance);

						if(result != MI_RESULT_OK)
							break;
					}
					else
					{
						result = Test_LogicalDisk_Post(logicalDiskForVirtualAssocInstanceStore[i], context);

						if(result != MI_RESULT_OK)
							break;
					}
				}
			}
		}
	}

	return result;
}

MI_Result PostLogicalToVirtualAssociation(MI_Context* context, const Test_LogicalDisk* instanceName, MI_Boolean isReference)
{
	MI_Result result = MI_RESULT_OK;

	if(instanceName->diskID.exists == MI_FALSE && instanceName->driveLetter.exists == MI_FALSE)
	{
		result = MI_RESULT_INVALID_PARAMETER;
	}
	else
	{	
#if(MI_CHAR_TYPE == 1)
		if(instanceName->diskID.value == 2 && (strcasecmp(instanceName->driveLetter.value, MI_T("E")) == 0))
#else
		if(instanceName->diskID.value == 2 && (wcasecmp(instanceName->driveLetter.value, MI_T("E")) == 0))
#endif
		{
			for(MI_Uint32 i = 0; i < virtualDiskForAssocInstanceStore.size(); ++i)
			{				
#if(MI_CHAR_TYPE == 1)
				if(strcasecmp(virtualDiskForAssocInstanceStore[i]->serialNumber.value, MI_T("11000")) == 0)
#else
				if(wcasecmp(virtualDiskForAssocInstanceStore[i]->serialNumber.value, MI_T("11000")) == 0)
#endif
				{
					if(isReference == MI_TRUE)
					{
						Test_AssociationLogicalVirtualDisk assocInstance;
						Test_AssociationLogicalVirtualDisk_Construct(&assocInstance, context);
						Test_AssociationLogicalVirtualDisk_Set_antecedent(&assocInstance, instanceName);
						Test_AssociationLogicalVirtualDisk_Set_dependent(&assocInstance, virtualDiskForAssocInstanceStore[i]);
						result = Test_AssociationLogicalVirtualDisk_Post(&assocInstance, context);

						Test_AssociationLogicalVirtualDisk_Destruct(&assocInstance);

						if(result != MI_RESULT_OK)
							break;
					}
					else
					{
						result = Test_VirtualDisk_Post(virtualDiskForAssocInstanceStore[i], context);
						break;					
					}
				}
			}
		}
	}

	return result;
}

void MI_CALL Test_AssociationLogicalVirtualDisk_Load(
    Test_AssociationLogicalVirtualDisk_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
	CreateLogicalVirtualAssociations(context);
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_AssociationLogicalVirtualDisk_Unload(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_AssociationLogicalVirtualDisk_EnumerateInstances(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Test_AssociationLogicalVirtualDisk_GetInstance(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationLogicalVirtualDisk* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Test_AssociationLogicalVirtualDisk_CreateInstance(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationLogicalVirtualDisk* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Test_AssociationLogicalVirtualDisk_ModifyInstance(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationLogicalVirtualDisk* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Test_AssociationLogicalVirtualDisk_DeleteInstance(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationLogicalVirtualDisk* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Test_AssociationLogicalVirtualDisk_AssociatorInstancesantecedent(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{    
	MI_PostResult(context, PostLogicalToVirtualAssociation(context, instanceName, MI_FALSE));
}

void MI_CALL Test_AssociationLogicalVirtualDisk_AssociatorInstancesdependent(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_VirtualDisk* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
	MI_PostResult(context, PostVirtualToLogicalAssociation(context, instanceName, MI_FALSE));
}

void MI_CALL Test_AssociationLogicalVirtualDisk_ReferenceInstancesantecedent(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, PostLogicalToVirtualAssociation(context, instanceName, MI_TRUE));
}

void MI_CALL Test_AssociationLogicalVirtualDisk_ReferenceInstancesdependent(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_VirtualDisk* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, PostVirtualToLogicalAssociation(context, instanceName, MI_TRUE));
}

