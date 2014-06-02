/* @migen@ */
#include <MI.h>
#include <pal/strings.h>
#include "Test_AssociationPhysicalLogicalDisk.h"
#include "CommonUtils.h"
#include <vector>

std::vector<Test_PhysicalDisk*> physicalDiskForAssocInstanceStore;
std::vector<Test_LogicalDisk*> logicalDiskForAssocInstanceStore;

void CreatePhysicalLogicalAssociations(MI_Context* context)
{
    if(physicalDiskForAssocInstanceStore.size() == 0)
        CreatePhysicalDiskInstances(context, physicalDiskForAssocInstanceStore);    

    if(logicalDiskForAssocInstanceStore.size() == 0)
        CreateLogicalDiskInstances(context, logicalDiskForAssocInstanceStore);    
}

MI_Result PostPhysicalToLogicalAssociation(MI_Context* context, const Test_PhysicalDisk* instanceName, MI_Boolean isReference)
{
    MI_Result result = MI_RESULT_OK;

    if(instanceName->serialNumber.exists == MI_FALSE)
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }
    else
    {    
        if(Tcscasecmp(instanceName->serialNumber.value, MI_T("10000")) == 0)
        {
            for(MI_Uint32 i = 0; i < logicalDiskForAssocInstanceStore.size(); i++)
            {
                if(logicalDiskForAssocInstanceStore[i]->diskID.value == 0 && (Tcscasecmp(logicalDiskForAssocInstanceStore[i]->driveLetter.value, MI_T("C")) == 0))
                {
                    if(isReference == MI_TRUE)
                    {
                        Test_AssociationPhysicalLogicalDisk assocLogical;
                        Test_AssociationPhysicalLogicalDisk_Construct(&assocLogical, context);
                        Test_AssociationPhysicalLogicalDisk_Set_antecedent(&assocLogical, instanceName);
                        Test_AssociationPhysicalLogicalDisk_Set_dependent(&assocLogical, logicalDiskForAssocInstanceStore[i]);
                        result = Test_AssociationPhysicalLogicalDisk_Post(&assocLogical, context);

                        Test_AssociationPhysicalLogicalDisk_Destruct(&assocLogical);

                        if(result != MI_RESULT_OK)
                            break;
                    }
                    else
                    {
                        result = Test_LogicalDisk_Post(logicalDiskForAssocInstanceStore[i], context);

                        if(result != MI_RESULT_OK)
                            break;
                    }
                }
                
                if(logicalDiskForAssocInstanceStore[i]->diskID.value == 1 && (Tcscasecmp(logicalDiskForAssocInstanceStore[i]->driveLetter.value, MI_T("D")) == 0) )
                {
                    if(isReference == MI_TRUE)
                    {
                        Test_AssociationPhysicalLogicalDisk assocLogical;
                        Test_AssociationPhysicalLogicalDisk_Construct(&assocLogical, context);
                        Test_AssociationPhysicalLogicalDisk_Set_antecedent(&assocLogical, instanceName);
                        Test_AssociationPhysicalLogicalDisk_Set_dependent(&assocLogical, logicalDiskForAssocInstanceStore[i]);
                        result = Test_AssociationPhysicalLogicalDisk_Post(&assocLogical, context);

                        Test_AssociationPhysicalLogicalDisk_Destruct(&assocLogical);

                        if(result != MI_RESULT_OK)
                            break;
                    }
                    else
                    {
                        result = Test_LogicalDisk_Post(logicalDiskForAssocInstanceStore[i], context);

                        if(result != MI_RESULT_OK)
                            break;
                    }
                }
            }
        }
        else if(Tcscasecmp(instanceName->serialNumber.value, MI_T("10001")) == 0)
        {
            for(MI_Uint32 i = 0; i < logicalDiskForAssocInstanceStore.size(); i++)
            {
                if(logicalDiskForAssocInstanceStore[i]->diskID.value == 2 && (Tcscasecmp(logicalDiskForAssocInstanceStore[i]->driveLetter.value, MI_T("E")) == 0) )
                {
                    if(isReference == MI_TRUE)
                    {
                        Test_AssociationPhysicalLogicalDisk assocLogical;
                        Test_AssociationPhysicalLogicalDisk_Construct(&assocLogical, context);
                        Test_AssociationPhysicalLogicalDisk_Set_antecedent(&assocLogical, instanceName);
                        Test_AssociationPhysicalLogicalDisk_Set_dependent(&assocLogical, logicalDiskForAssocInstanceStore[i]);
                        result = Test_AssociationPhysicalLogicalDisk_Post(&assocLogical, context);

                        Test_AssociationPhysicalLogicalDisk_Destruct(&assocLogical);

                        if(result != MI_RESULT_OK)
                            break;
                    }
                    else
                    {
                        result = Test_LogicalDisk_Post(logicalDiskForAssocInstanceStore[i], context);                    
                        break;
                    }
                }
            }
        }
    }

    return result;
}

MI_Result PostLogicalToPhysicalAssociation(MI_Context* context, const Test_LogicalDisk* instanceName, MI_Boolean isReference)
{
    MI_Result result = MI_RESULT_OK;

    if(instanceName->diskID.exists == MI_FALSE && instanceName->driveLetter.exists == MI_FALSE)
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }
    else
    {    
        if( (instanceName->diskID.value == 0 && (Tcscasecmp(instanceName->driveLetter.value, MI_T("C")) == 0)) ||  (instanceName->diskID.value == 1 && (Tcscasecmp(instanceName->driveLetter.value, MI_T("D")) == 0)))
        {
            for(MI_Uint32 i = 0; i < physicalDiskForAssocInstanceStore.size(); i++)
            {
                if(Tcscasecmp(physicalDiskForAssocInstanceStore[i]->serialNumber.value, MI_T("10000")) == 0)
                {
                    if(isReference == MI_TRUE)
                    {
                        Test_AssociationPhysicalLogicalDisk assocPhysical;
                        Test_AssociationPhysicalLogicalDisk_Construct(&assocPhysical, context);
                        Test_AssociationPhysicalLogicalDisk_Set_antecedent(&assocPhysical, physicalDiskForAssocInstanceStore[i]);
                        Test_AssociationPhysicalLogicalDisk_Set_dependent(&assocPhysical, instanceName);
                        result = Test_AssociationPhysicalLogicalDisk_Post(&assocPhysical, context);

                        Test_AssociationPhysicalLogicalDisk_Destruct(&assocPhysical);

                        if(result != MI_RESULT_OK)
                            break;                            
                    }
                    else
                    {
                        result = Test_PhysicalDisk_Post(physicalDiskForAssocInstanceStore[i], context);

                        if(result != MI_RESULT_OK)
                            break;
                    }
                }
            }
        }
        else if(instanceName->diskID.value == 2 && (Tcscasecmp(instanceName->driveLetter.value, MI_T("E")) == 0))
        {
            for(MI_Uint32 i = 0; i < physicalDiskForAssocInstanceStore.size(); i++)
            {
                if(Tcscasecmp(physicalDiskForAssocInstanceStore[i]->serialNumber.value, MI_T("10001")) == 0)
                {
                    if(isReference == MI_TRUE)
                    {
                        Test_AssociationPhysicalLogicalDisk assocPhysical;
                        Test_AssociationPhysicalLogicalDisk_Construct(&assocPhysical, context);
                        Test_AssociationPhysicalLogicalDisk_Set_antecedent(&assocPhysical, physicalDiskForAssocInstanceStore[i]);
                        Test_AssociationPhysicalLogicalDisk_Set_dependent(&assocPhysical, instanceName);
                        result = Test_AssociationPhysicalLogicalDisk_Post(&assocPhysical, context);

                        Test_AssociationPhysicalLogicalDisk_Destruct(&assocPhysical);

                        if(result != MI_RESULT_OK)
                            break;
                    }
                    else
                    {
                        result = Test_PhysicalDisk_Post(physicalDiskForAssocInstanceStore[i], context);

                        if(result != MI_RESULT_OK)
                            break;
                    }
                }
            }
        }
    }

    return result;
}

void MI_CALL Test_AssociationPhysicalLogicalDisk_Load(
    Test_AssociationPhysicalLogicalDisk_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    CreatePhysicalLogicalAssociations(context);
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_AssociationPhysicalLogicalDisk_Unload(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context)
{
    for(MI_Uint32 i=0; i < physicalDiskForAssocInstanceStore.size(); i++)
    {
        Test_PhysicalDisk_Delete(physicalDiskForAssocInstanceStore[i]);
    }
    
    for(MI_Uint32 i=0; i < logicalDiskForAssocInstanceStore.size(); i++)
    {
        Test_LogicalDisk_Delete(logicalDiskForAssocInstanceStore[i]);
    }

    physicalDiskForAssocInstanceStore.clear();
    logicalDiskForAssocInstanceStore.clear();

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_AssociationPhysicalLogicalDisk_EnumerateInstances(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Test_AssociationPhysicalLogicalDisk_GetInstance(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationPhysicalLogicalDisk* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Test_AssociationPhysicalLogicalDisk_CreateInstance(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationPhysicalLogicalDisk* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Test_AssociationPhysicalLogicalDisk_ModifyInstance(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationPhysicalLogicalDisk* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Test_AssociationPhysicalLogicalDisk_DeleteInstance(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationPhysicalLogicalDisk* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Test_AssociationPhysicalLogicalDisk_AssociatorInstancesantecedent(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_PhysicalDisk* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, PostPhysicalToLogicalAssociation(context, instanceName,MI_FALSE));
}

void MI_CALL Test_AssociationPhysicalLogicalDisk_AssociatorInstancesdependent(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, PostLogicalToPhysicalAssociation(context, instanceName, MI_FALSE));
}

void MI_CALL Test_AssociationPhysicalLogicalDisk_ReferenceInstancesantecedent(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_PhysicalDisk* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, PostPhysicalToLogicalAssociation(context, instanceName, MI_TRUE));
}

void MI_CALL Test_AssociationPhysicalLogicalDisk_ReferenceInstancesdependent(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, PostLogicalToPhysicalAssociation(context, instanceName, MI_TRUE));
}

