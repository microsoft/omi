/* @migen@ */
#include <MI.h>
#include "ClassHierarchyTest.h"

#include "Derived.h"
#include <vector>
#include <stdlib.h>
#include <pal/strings.h>

#define EH_Check(x, result) { if (!(x)) { miResult = (result); goto EH_Finally; } }
#define EH_CheckMIResult(result) { miResult = (result); if (miResult != MI_RESULT_OK) { goto EH_Finally; } }
#define EH_Fail { goto EH_Finally; }
#define EH_UNWIND EH_Finally:

using std::vector;

vector<ClassHierarchyTest*> allTests;

/*
    Instance that verifies polymorphic reference and embedded instance.

    Structure of returned object (pseudo-code):

    instance of ClassHierarchyTest
    {
        object TestInstance : instance of Base
        {
            Base BaseInstance = instance of Derived { ... };        // Polymorphic embedded instance
            Base ref BaseReference = instance of Derived { ... };   // Polymorphic reference
            Separate = instance of Separate { ... };                // No polymorphism
            ...
        }
        ...
    }
*/
MI_Result AddTestWithPolymorphicInstance(_In_ MI_Context* pContext, vector<ClassHierarchyTest*>&  allTests)
{ 
    MI_Result           miResult    = MI_RESULT_OK;
    ClassHierarchyTest* pTest       = NULL;
    Base*               pBase       = NULL; 
    Derived*            pDerived1   = NULL;
    Derived*            pDerived2   = NULL;
    Separate*           pSeparate   = NULL;

    pTest = (ClassHierarchyTest*)PAL_Calloc(1, sizeof(ClassHierarchyTest));
    EH_Check(pTest != NULL, MI_RESULT_SERVER_LIMITS_EXCEEDED);
    EH_CheckMIResult(ClassHierarchyTest_Construct(pTest, pContext));
    EH_CheckMIResult(ClassHierarchyTest_Set_TestName(pTest, MI_T("PolymorphicInstance")));

    pBase = (Base*)PAL_Calloc(1, sizeof(Base));
    EH_Check(pBase != NULL, MI_RESULT_SERVER_LIMITS_EXCEEDED);
    EH_CheckMIResult(Base_Construct(pBase, pContext));
    EH_CheckMIResult(Base_Set_Uint32Property(pBase, 111));

    pDerived1 = (Derived*)PAL_Calloc(1, sizeof(Derived));
    EH_Check(pDerived1 != NULL, MI_RESULT_SERVER_LIMITS_EXCEEDED);
    EH_CheckMIResult(Derived_Construct(pDerived1, pContext));
    EH_CheckMIResult(Derived_Set_StringProperty(pDerived1, MI_T("This is set as instance")));
    EH_CheckMIResult(Derived_Set_Uint32Property(pDerived1, 123));

    pDerived2 = (Derived*)PAL_Calloc(1, sizeof(Derived));
    EH_Check(pDerived2 != NULL, MI_RESULT_SERVER_LIMITS_EXCEEDED);
    EH_CheckMIResult(Derived_Construct(pDerived2, pContext));
    EH_CheckMIResult(Derived_Set_StringProperty(pDerived2, MI_T("This is set as reference")));
    EH_CheckMIResult(Derived_Set_Uint32Property(pDerived2, 456));

    pSeparate = (Separate*)PAL_Calloc(1, sizeof(Separate));
    EH_Check(pSeparate != NULL, MI_RESULT_SERVER_LIMITS_EXCEEDED);
    EH_CheckMIResult(Separate_Construct(pSeparate, pContext));
    EH_CheckMIResult(Separate_Set_BooleanProperty(pSeparate, MI_TRUE));    
    
    EH_CheckMIResult(Base_SetPtr_BaseInstance(pBase, reinterpret_cast<const Base*>(pDerived1)));
    pDerived1 = NULL;

    EH_CheckMIResult(Base_SetPtr_RootReference(pBase, reinterpret_cast<const Root*>(pDerived2)));
    pDerived2 = NULL;

    EH_CheckMIResult(Base_SetPtr_SeparateReference(pBase, pSeparate));
    pSeparate = NULL;

    EH_CheckMIResult(ClassHierarchyTest_SetPtr_TestInstance(pTest, &pBase->__instance));
    pBase = NULL;

EH_UNWIND
    if (miResult != MI_RESULT_OK)
    {
        ClassHierarchyTest_Delete(pTest);
        Base_Delete(pBase);
        Derived_Delete(pDerived1);
        Derived_Delete(pDerived2);
        Separate_Delete(pSeparate);
    }
    else
        allTests.push_back(pTest);

    return miResult;
}

/*
    Instance that verifies polymorphic arrays.

    Structure of returned object (pseudo-code):

    instance of ClassHierarchyTest
    {
        object TestInstance : instance of Base
        {
            Base[] BaseInstanceArray = 
            {
                instance of Derived { ... },
                instance of Base { ... }
            };
        }
    }
*/
MI_Result AddTestWithPolymorphicArray(_In_ MI_Context* pContext, vector<ClassHierarchyTest*>& allTests)
{
    MI_Result           miResult    = MI_RESULT_OK;
    ClassHierarchyTest* pTest       = NULL;
    Base*               pBase       = NULL;
    Derived*            pFirstItem  = NULL;
    Base*               pSecondItem = NULL;

    Base**              baseArray   = NULL;

    pTest = (ClassHierarchyTest*)PAL_Calloc(1, sizeof(ClassHierarchyTest));
    EH_Check(pTest != NULL, MI_RESULT_SERVER_LIMITS_EXCEEDED);
    EH_CheckMIResult(ClassHierarchyTest_Construct(pTest, pContext));
    EH_CheckMIResult(ClassHierarchyTest_Set_TestName(pTest, MI_T("PolymorphicArrays")));

    pBase = (Base*)PAL_Calloc(1, sizeof(Base));
    EH_Check(pBase != NULL, MI_RESULT_SERVER_LIMITS_EXCEEDED);
    EH_CheckMIResult(Base_Construct(pBase, pContext));
    EH_CheckMIResult(Base_Set_Uint32Property(pBase, 111));

    pFirstItem = (Derived*)PAL_Calloc(1, sizeof(Derived));
    EH_Check(pFirstItem != NULL, MI_RESULT_SERVER_LIMITS_EXCEEDED);
    EH_CheckMIResult(Derived_Construct(pFirstItem, pContext));
    EH_CheckMIResult(Derived_Set_StringProperty(pFirstItem, MI_T("First item in the array")));
    EH_CheckMIResult(Derived_Set_Uint32Property(pFirstItem, 123));

    pSecondItem = (Base*)PAL_Calloc(1, sizeof(Base));
    EH_Check(pSecondItem != NULL, MI_RESULT_SERVER_LIMITS_EXCEEDED);
    EH_CheckMIResult(Base_Construct(pSecondItem, pContext));
    EH_CheckMIResult(Base_Set_Uint32Property(pSecondItem, 456));
    
    baseArray = reinterpret_cast<Base**>(PAL_Calloc(2, sizeof(Base*)));
    EH_Check(baseArray != NULL, MI_RESULT_SERVER_LIMITS_EXCEEDED);
    baseArray[0] = reinterpret_cast<Base*>(pFirstItem);
    baseArray[1] = pSecondItem;

    EH_CheckMIResult(Base_SetPtr_BaseInstanceArray(pBase, baseArray, 2));
    baseArray = NULL;
    pFirstItem = NULL;
    pSecondItem = NULL;
    
    EH_CheckMIResult(ClassHierarchyTest_SetPtr_TestInstance(pTest, &pBase->__instance));
    pBase = NULL;

EH_UNWIND
    if (miResult != MI_RESULT_OK)
    {
        ClassHierarchyTest_Delete(pTest);
        Base_Delete(pBase);
        Derived_Delete(pFirstItem);
        Base_Delete(pSecondItem);
        PAL_Free(baseArray);
    }
    else
        allTests.push_back(pTest);

    return miResult;
}

void MI_CALL ClassHierarchyTest_Load(
    _Outptr_result_maybenull_ ClassHierarchyTest_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* pContext)
{
    MI_Result miResult = MI_RESULT_OK;
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = NULL;
    
    EH_CheckMIResult(AddTestWithPolymorphicInstance(pContext, allTests));
    EH_CheckMIResult(AddTestWithPolymorphicArray(pContext, allTests));

EH_UNWIND
    MI_Context_PostResult(pContext, miResult);
}

void MI_CALL ClassHierarchyTest_Unload(
    _In_opt_ ClassHierarchyTest_Self* self,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);

    for (vector<ClassHierarchyTest*>::iterator it = allTests.begin(); it != allTests.end(); ++it) 
        ClassHierarchyTest_Delete(*it);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ClassHierarchyTest_EnumerateInstances(
    _In_opt_ ClassHierarchyTest_Self* self,
    _In_ MI_Context* pContext,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(propertySet);
    MI_UNREFERENCED_PARAMETER(keysOnly);
    MI_UNREFERENCED_PARAMETER(filter);

    MI_Result miResult = MI_RESULT_OK;

    if (Tcscasecmp(className, ClassHierarchyTest_rtti.name) == 0)
    {
        for (vector<ClassHierarchyTest*>::iterator it = allTests.begin(); it != allTests.end(); ++it)
        {
            EH_CheckMIResult(MI_PostInstance(pContext, reinterpret_cast<const MI_Instance*>(*it)));
        }
    }

EH_UNWIND
    MI_PostResult(pContext, miResult);
}

void MI_CALL ClassHierarchyTest_GetInstance(
    _In_opt_ ClassHierarchyTest_Self* self,
    _In_ MI_Context* pContext,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ClassHierarchyTest* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_Result miResult = MI_RESULT_OK;
    
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(propertySet);

    if (Tcscasecmp(className, ClassHierarchyTest_rtti.name) == 0)
    {
        for (vector<ClassHierarchyTest*>::iterator it = allTests.begin(); it != allTests.end(); ++it)
        {
            if (Tcscasecmp(instanceName->TestName.value, (*it)->TestName.value) == 0)
            {
                EH_CheckMIResult(MI_PostInstance(pContext, reinterpret_cast<const MI_Instance*>(*it)));
            }
        }
    }

EH_UNWIND
    MI_Context_PostResult(pContext, miResult);
}

void MI_CALL ClassHierarchyTest_CreateInstance(
    _In_opt_ ClassHierarchyTest_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ClassHierarchyTest* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ClassHierarchyTest_ModifyInstance(
    _In_opt_ ClassHierarchyTest_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ClassHierarchyTest* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ClassHierarchyTest_DeleteInstance(
    _In_opt_ ClassHierarchyTest_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ClassHierarchyTest* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

