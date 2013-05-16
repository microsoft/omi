/* @migen@ */
#include <MI.h>
#include "DemoTest.h"

void MI_CALL DemoTest_Load(
    DemoTest_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL DemoTest_Unload(
    DemoTest_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL DemoTest_EnumerateInstances(
    DemoTest_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    DemoTest demoTest;
	DemoTest_Construct(&demoTest,context);
	DemoTest_Set_Name(&demoTest,MI_T("EnumeratteInstances has been implemented in original files."));
	DemoTest_Post(&demoTest, context);
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL DemoTest_GetInstance(
    DemoTest_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const DemoTest* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL DemoTest_CreateInstance(
    DemoTest_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const DemoTest* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL DemoTest_ModifyInstance(
    DemoTest_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const DemoTest* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL DemoTest_DeleteInstance(
    DemoTest_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const DemoTest* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

