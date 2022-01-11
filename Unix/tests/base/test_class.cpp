/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <ut/ut.h>
#include <MI.h>
#include <base/batch.h>
#include <base/class.h>
#include <base/schemadecl.h>
#include "MSFT_AllTypes.h"
//#include <common\scx\schemadecl.h>

extern "C" 
{
extern MI_SchemaDecl test_repos_classDecl;
}

void DoRecurseClass(const MI_ClassDecl *classDecl);


NitsTest(Test_Class_New_InvalidParameters)
{
    MI_Class *newClass = NULL;
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_AllTypes"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        NitsCompare(Class_New(NULL, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_INVALID_PARAMETER, PAL_T("should return invalid parameter"));
        NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("should return invalid parameter"));
    }
}
NitsEndTest


NitsTest(Test_Class_New)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_AllTypes"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"), &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetParentClass)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("CIM_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"), &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_Class *parentClass = NULL;
            if (NitsCompare(newClass->ft->GetParentClass(newClass, &parentClass), MI_RESULT_OK, PAL_T("GetParentClass succeed")))
                MI_Class_Delete(parentClass);
            NitsCompare(newClass->ft->GetParentClass(NULL, &parentClass), MI_RESULT_INVALID_PARAMETER, PAL_T("GetParentClass should fail"));
            NitsCompare(newClass->ft->GetParentClass(newClass, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("GetParentClass should fail"));
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetClassName)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_AllTypes"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"), &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            const MI_Char *className = NULL;
            if (NitsCompare(MI_Class_GetClassName(newClass, &className), MI_RESULT_OK, PAL_T("Getting classname should not fail")))
            {
                NitsCompareString(className, PAL_T("MSFT_AllTypes"), PAL_T("class name should be MSFT_AllTypes"));
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetClassName_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_AllTypes"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            const MI_Char *className = NULL;
            NitsCompare(newClass->ft->GetClassName(NULL, &className), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting classname should fail due to invalid parameter"));
            NitsCompare(MI_Class_GetClassName(NULL, &className), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting classname should fail due to invalid parameter"));
            NitsCompare(MI_Class_GetClassName(newClass, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting classname should fail due to invalid parameter"));
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetServerName)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_AllTypes"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"), &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            const MI_Char *serverName = NULL;
            if (NitsCompare(MI_Class_GetServerName(newClass, &serverName), MI_RESULT_OK, PAL_T("Getting serverName should not fail")))
            {
                NitsCompareString(serverName, PAL_T("server"), PAL_T("server name should be server"));
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetServerName_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_AllTypes"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"), &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            const MI_Char *serverName = NULL;
            NitsCompare(newClass->ft->GetServerName(NULL, &serverName), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting serverName should fail due to invalid parameter"));
            NitsCompare(MI_Class_GetServerName(NULL, &serverName), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting serverName should fail due to invalid parameter"));
            NitsCompare(MI_Class_GetServerName(newClass, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting serverName should fail due to invalid parameter"));
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetNamespaceName)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_AllTypes"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"), &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            const MI_Char *namespaceName = NULL;
            if (NitsCompare(MI_Class_GetNameSpace(newClass, &namespaceName), MI_RESULT_OK, PAL_T("Getting namespaceName should not fail")))
            {
                NitsCompareString(namespaceName, PAL_T("namespace"), PAL_T("namespace name should be namespace"));
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetNamespaceName_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_AllTypes"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            const MI_Char *namespaceName = NULL;
            NitsCompare(newClass->ft->GetNameSpace(NULL, &namespaceName), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting namespaceName should fail due to invalid parameter"));
            NitsCompare(MI_Class_GetNameSpace(NULL, &namespaceName), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting namespaceName should fail due to invalid parameter"));
            NitsCompare(MI_Class_GetNameSpace(newClass, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting namespaceName should fail due to invalid parameter"));
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetParentClassName)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            const MI_Char * parentClassName = NULL;
            if (NitsCompare(MI_Class_GetParentClassName(newClass, &parentClassName), MI_RESULT_OK, PAL_T("Getting parentClassName should not fail")))
            {
                NitsCompareString(parentClassName, PAL_T("CIM_Process"), PAL_T("parent name on MSFT_Process should be CIM_Process"));
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetParentClassName_None)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_AllTypes"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_Class *parentClass;
            const MI_Char * parentClassName = NULL;
            if (NitsCompare(MI_Class_GetParentClassName(newClass, &parentClassName), MI_RESULT_INVALID_SUPERCLASS, PAL_T("Getting parentClassName should fail")))
            {
                NitsCompareString(parentClassName, NULL, PAL_T("parent name on parentClassName should be null"));
            }
            NitsCompare(MI_Class_GetParentClass(newClass, &parentClass), MI_RESULT_INVALID_SUPERCLASS, PAL_T("Getting parentClassName should fail"));
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetParentClassName_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            const MI_Char * parentClassName = NULL;
            NitsCompare(newClass->ft->GetParentClassName(NULL, &parentClassName), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting parentClassName count should fail"));
            NitsCompare(MI_Class_GetParentClassName(NULL, &parentClassName), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting parentClassName count should fail"));
            NitsCompare(MI_Class_GetParentClassName(newClass, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting parentClassName count should fail"));
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetElementCount)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_AllTypes"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_Uint32 count = 0;
            if (NitsCompare(MI_Class_GetElementCount(newClass, &count), MI_RESULT_OK, PAL_T("Getting element count should not fail")))
            {
                NitsCompare(count, 30, PAL_T("element count on MSFT_AllTypes should be 30"));
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetElementCount_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_AllTypes"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_Uint32 count = 0;
            NitsCompare(newClass->ft->GetElementCount(NULL, &count), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting element count should fail"));
            NitsCompare(MI_Class_GetElementCount(NULL, &count), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting element count should fail"));
            NitsCompare(MI_Class_GetElementCount(newClass, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting element count should fail"));
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetElementAt_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_AllTypes"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_Uint32 count = 0;
            const MI_Char *name = NULL;
            MI_Value value;
            MI_Boolean valueExists;
            MI_Type type;
            MI_Uint32 flags;
            MI_QualifierSet qs;

            NitsCompare(MI_Class_GetElementCount(newClass, &count), MI_RESULT_OK, PAL_T("count should be 30 for MSFT_AllTypes"));
            NitsCompare(MI_Class_GetElementAt(newClass, count, &name, &value, &valueExists, &type, NULL, &qs, &flags), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("Getting MI_Class_GetElementAt should fail"));
            NitsCompare(newClass->ft->GetElementAt(NULL, 0, &name, &value, &valueExists, &type, NULL, &qs, &flags), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting MI_Class_GetElementAt should fail"));
            NitsCompare(MI_Class_GetElementAt(NULL, 0, &name, &value, &valueExists, &type, NULL, &qs, &flags), MI_RESULT_INVALID_PARAMETER, PAL_T("Getting MI_Class_GetElementAt should fail"));
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetElementAt)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_AllTypes"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"), &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_Uint32 count = 0;
            const MI_Char *name = NULL;
            MI_Value value;
            MI_Boolean valueExists;
            MI_Type type;
            MI_Uint32 flags;
            MI_QualifierSet qs;

            NitsCompare(MI_Class_GetElementCount(newClass, &count), MI_RESULT_OK, PAL_T("count should be 30 for MSFT_AllTypes"));
            NitsCompare(MI_Class_GetElementAt(newClass, count-1, &name, &value, &valueExists, &type, NULL, &qs, &flags), MI_RESULT_OK, PAL_T("Getting MI_Class_GetElementAt should succeed"));
            NitsCompare(MI_Class_GetElementAt(newClass, 0, &name, &value, &valueExists, &type, NULL, &qs, &flags), MI_RESULT_OK, PAL_T("Getting MI_Class_GetElementAt should succeed"));
            NitsCompareString(name, PAL_T("Key"), PAL_T("param 0 of AllTypes should be Key"));
            NitsCompare(type, MI_UINT32, PAL_T("param 0 of AllTypes should be UINT32"));
            NitsCompare(flags, MI_FLAG_PROPERTY|MI_FLAG_KEY, PAL_T("param 0 of AllTypes should have MI_FLAG_PROPERTY|MI_FLAG_KEY flags"));
            NitsCompare(MI_Class_GetElementAt(newClass, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL), MI_RESULT_OK, PAL_T("Getting MI_Class_GetElementAt should succeed with only mandatory parameters"));
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetElement)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_AllTypes"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_Uint32 count = 0;
            const MI_Char *atName = NULL;
            MI_Value atValue, nameValue;
            MI_Boolean atValueExists, nameValueExists;
            MI_Type atType, nameType;
            MI_Uint32 atFlags, nameFlags;
            MI_QualifierSet atQs, nameQs;
            MI_Uint32 nameIndex;

            NitsCompare(MI_Class_GetElementCount(newClass, &count), MI_RESULT_OK, PAL_T("count should be 30 for MSFT_AllTypes"));
            
            if (NitsCompare(MI_Class_GetElementAt(newClass, count-1, &atName, &atValue, &atValueExists, &atType, NULL, &atQs, &atFlags), MI_RESULT_OK, PAL_T("Getting MI_Class_GetElementAt should succeed")) &&
                NitsCompare(MI_Class_GetElement(newClass, atName, &nameValue, &nameValueExists, &nameType, NULL, &nameQs, &nameFlags, &nameIndex), MI_RESULT_OK, PAL_T("MI_Class_GetElement should succeed")))
            {
                NitsCompare(count-1, nameIndex, PAL_T("GetElement by name and element should have same index"));
                //TODO NitsCompare(atValue, nameValue, PAL_T("values should be same"));
                NitsCompare(atValueExists, nameValueExists, PAL_T("valueExists should be same"));
                NitsCompare(atType, nameType, PAL_T("nameType should be same"));
                NitsCompare(atFlags, nameFlags, PAL_T("nameFlags should be same"));
                NitsAssert(atQs.reserved1 == nameQs.reserved1, PAL_T("nameQs should be same"));
                NitsAssert(atQs.reserved2 == nameQs.reserved2, PAL_T("nameQs should be same"));
            }

            if (NitsCompare(MI_Class_GetElementAt(newClass, 0, &atName, &atValue, &atValueExists, &atType, NULL, &atQs, &atFlags), MI_RESULT_OK, PAL_T("Getting MI_Class_GetElementAt should succeed")) &&
                NitsCompare(MI_Class_GetElement(newClass, atName, &nameValue, &nameValueExists, &nameType, NULL, &nameQs, &nameFlags, &nameIndex), MI_RESULT_OK, PAL_T("MI_Class_GetElement should succeed")))
            {
                NitsCompare(0, nameIndex, PAL_T("GetElement by name and element should have same index"));
                //TODO NitsCompare(atValue, nameValue, PAL_T("values should be same"));
                NitsCompare(atValueExists, nameValueExists, PAL_T("valueExists should be same"));
                NitsCompare(atType, nameType, PAL_T("nameType should be same"));
                NitsCompare(atFlags, nameFlags, PAL_T("nameFlags should be same"));
                NitsAssert(atQs.reserved1 == nameQs.reserved1, PAL_T("nameQs should be same"));
                NitsAssert(atQs.reserved2 == nameQs.reserved2, PAL_T("nameQs should be same"));
            }

            NitsCompare(MI_Class_GetElement(newClass, PAL_T("Key"), NULL, NULL, NULL, NULL, NULL, NULL, NULL), MI_RESULT_OK, PAL_T("Getting MI_Class_GetElement should succeed with only mandatory parameters"));
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetElement_InvalidParameters)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_AllTypes"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"), &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_Value nameValue;
            MI_Boolean nameValueExists;
            MI_Type nameType;
            MI_Uint32 nameFlags;
            MI_QualifierSet nameQs;
            MI_Uint32 nameIndex;

            NitsCompare(newClass->ft->GetElement(NULL, PAL_T("fofofo"), &nameValue, &nameValueExists, &nameType, NULL, &nameQs, &nameFlags, &nameIndex), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Class_GetElement should succeed"));
            NitsCompare(MI_Class_GetElement(NULL, PAL_T("fofofo"), &nameValue, &nameValueExists, &nameType, NULL, &nameQs, &nameFlags, &nameIndex), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Class_GetElement should succeed"));
            NitsCompare(MI_Class_GetElement(newClass, PAL_T("fofofo"), &nameValue, &nameValueExists, &nameType, NULL, &nameQs, &nameFlags, &nameIndex), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("MI_Class_GetElement should succeed"));
            NitsCompare(MI_Class_GetElement(newClass, NULL, &nameValue, &nameValueExists, &nameType, NULL, &nameQs, &nameFlags, &nameIndex), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Class_GetElement should succeed"));

            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetClassQualifierSet)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_QualifierSet qs;
            if (NitsCompare(MI_Class_GetClassQualifierSet(newClass, &qs), MI_RESULT_OK, PAL_T("MI_Class_GetClassQualifierSet should not fail")))
            {
                NitsCompare((int)qs.reserved1, 2, PAL_T("MSFT_Process has 1 class qualifier"));
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetClassQualifierSet_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_QualifierSet qs;

            NitsCompare(newClass->ft->GetClassQualifierSet(NULL, &qs), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Class_GetClassQualifierSet should fail"));
            NitsCompare(MI_Class_GetClassQualifierSet(NULL, &qs), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Class_GetClassQualifierSet should fail"));
            NitsCompare(MI_Class_GetClassQualifierSet(newClass, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Class_GetClassQualifierSet should fail"));
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetMethodCount)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_Uint32 count;
            if (NitsCompare(MI_Class_GetMethodCount(newClass, &count), MI_RESULT_OK, PAL_T("MI_Class_GetMethodCount should not fail")))
            {
                NitsCompare(count, 1, PAL_T("MSFT_Process has 1 method"));
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetMethodCount_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_Uint32 count;

            NitsCompare(newClass->ft->GetMethodCount(NULL, &count), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Class_GetMethodCount should fail"));
            NitsCompare(MI_Class_GetMethodCount(NULL, &count), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Class_GetMethodCount should fail"));
            NitsCompare(MI_Class_GetMethodCount(newClass, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Class_GetMethodCount should fail"));
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetMethodAt)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            const MI_Char *name = PAL_T("");
            MI_QualifierSet qs;
            MI_ParameterSet ps;

            if (NitsCompare(MI_Class_GetMethodAt(newClass, 0, &name, &qs, &ps), MI_RESULT_OK, PAL_T("MI_Class_GetMethodAt should notfail")))
            {
                NitsCompareString(name, PAL_T("RequestStateChange"), PAL_T("method name should be MSFT_Process::RequestStateChange"));
                NitsCompare((int)qs.reserved1, 4, PAL_T("1 qualifier on method MSFT_Process::RequestStateChange"));
                NitsCompare((int)ps.reserved1, 4, PAL_T("1 parameter on method MSFT_Process::RequestStateChange"));
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetMethodAt_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            const MI_Char *name;
            MI_QualifierSet qs;
            MI_ParameterSet ps;

            NitsCompare(newClass->ft->GetMethodAt(NULL, 0, &name, &qs, &ps), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Class_GetMethodAt should fail"));
            NitsCompare(MI_Class_GetMethodAt(NULL, 0, &name, &qs, &ps), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Class_GetMethodAt should fail"));
            NitsCompare(MI_Class_GetMethodAt(newClass, 22, &name, &qs, &ps), MI_RESULT_METHOD_NOT_FOUND, PAL_T("MI_Class_GetMethodAt should fail"));
            NitsCompare(MI_Class_GetMethodAt(newClass, 0, NULL, NULL, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Class_GetMethodAt should fail"));
            
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetMethod)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;

            if (NitsCompare(MI_Class_GetMethod(newClass, PAL_T("RequestStateChange"), &qs, &ps, &index), MI_RESULT_OK, PAL_T("MI_Class_GetMethodAt should not fail")))
            {
                NitsCompare(index, 0, PAL_T("method index should be 0 for MSFT_Process::RequestStateChange"));
                NitsCompare((int)qs.reserved1, 4, PAL_T("1 qualifier on method MSFT_Process::RequestStateChange"));
                NitsCompare((int)ps.reserved1, 4, PAL_T("1 parameter on method MSFT_Process::RequestStateChange"));
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_GetMethod_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"), &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;

            NitsCompare(newClass->ft->GetMethod(NULL, PAL_T("fofofoof"), &qs, &ps, &index), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Class_GetMethod should fail"));
            NitsCompare(MI_Class_GetMethod(NULL, PAL_T("fofofoof"), &qs, &ps, &index), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Class_GetMethod should fail"));
            NitsCompare(MI_Class_GetMethod(newClass, PAL_T("fofofoof"), &qs, &ps, &index), MI_RESULT_METHOD_NOT_FOUND, PAL_T("MI_Class_GetMethod should fail"));
            NitsCompare(MI_Class_GetMethod(newClass, NULL, &qs, &ps, &index), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Class_GetMethod should fail"));
            
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_Class_Clone)
{
    const MI_Char *classes[] = 
    {
        PAL_T("MSFT_AllTypes")
    };
    for (int i = 0; i != sizeof(classes)/sizeof(MI_Char*);i++)
    {
        MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, classes[i]);

        if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
        {
            MI_Class *originalClass = NULL;
            if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"), &originalClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
            {
                MI_Class *newClass = NULL;
                if (NitsCompare(MI_Class_Clone(originalClass, &newClass), MI_RESULT_OK, PAL_T("Clone should work")))
                {
                    if (newClass && (newClass->classDecl!=NULL))
                        DoRecurseClass(newClass->classDecl);

                    MI_Class_Delete(newClass);
                }
                MI_Class_Delete(originalClass);
            }
        }
    }
}
NitsEndTest

NitsTest(Test_Class_Clone_Clone)
{
    const MI_Char *classes[] = 
    {
        PAL_T("MSFT_AllTypes"),
    };
    for (int i = 0; i != sizeof(classes)/sizeof(MI_Char*);i++)
    {
        MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, classes[i]);

        if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_AllTypes")))
        {
            MI_Class *originalClass = NULL;
            if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &originalClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
            {
                MI_Class *newClass = NULL;
                if (NitsCompare(MI_Class_Clone(originalClass, &newClass), MI_RESULT_OK, PAL_T("Clone should work")))
                {
                    MI_Class *cloneOfClone = NULL;
                    if (NitsCompare(MI_Class_Clone(newClass, &cloneOfClone), MI_RESULT_OK, PAL_T("Clone of clone should work")))
                    {
                        if (cloneOfClone && (cloneOfClone->classDecl!=NULL))
                            DoRecurseClass(cloneOfClone->classDecl);
                        MI_Class_Delete(cloneOfClone);
                    }

                    MI_Class_Delete(newClass);
                }
                MI_Class_Delete(originalClass);
            }
        }
    }
}
NitsEndTest

NitsTest(Test_ParameterSet_GetParameterCount)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;

            if (NitsCompare(MI_Class_GetMethod(newClass, PAL_T("RequestStateChange"), &qs, &ps, &index), MI_RESULT_OK, PAL_T("MI_Class_GetMethod should succeed")))
            {
                MI_Uint32 paramCount = 0;
                NitsCompare(MI_ParameterSet_GetParameterCount(&ps, &paramCount), MI_RESULT_OK, PAL_T("MI_ParameterSet_GetParameterCount should succeed"));
                NitsCompare(paramCount, 3, PAL_T("MSFT_Process::RequestStateChange should have 3 parameters, not including return type"));
            }
            
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_ParameterSet_GetParameterCount_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;

            if (NitsCompare(MI_Class_GetMethod(newClass, PAL_T("RequestStateChange"), &qs, &ps, &index), MI_RESULT_OK, PAL_T("MI_Class_GetMethod should succeed")))
            {
                MI_Uint32 paramCount = 0;
                NitsCompare(ps.ft->GetParameterCount(NULL, &paramCount), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameterCount should fail"));
                NitsCompare(MI_ParameterSet_GetParameterCount(NULL, &paramCount), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameterCount should fail"));
                NitsCompare(MI_ParameterSet_GetParameterCount(&ps, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameterCount should fail"));
            }
            
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_ParameterSet_GetMethodReturnType)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;

            if (NitsCompare(MI_Class_GetMethod(newClass, PAL_T("RequestStateChange"), &qs, &ps, &index), MI_RESULT_OK, PAL_T("MI_Class_GetMethod should succeed")))
            {
                MI_Type returnType;
                MI_QualifierSet qualifierSet;
                NitsCompare(MI_ParameterSet_GetMethodReturnType(&ps, &returnType, &qualifierSet), MI_RESULT_OK, PAL_T("MI_ParameterSet_GetParameterCount should succeed"));
            }
            
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_ParameterSet_GetMethodReturnType_InvalidParameters)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;

            if (NitsCompare(MI_Class_GetMethod(newClass, PAL_T("RequestStateChange"), &qs, &ps, &index), MI_RESULT_OK, PAL_T("MI_Class_GetMethod should succeed")))
            {
                MI_Type returnType;
                MI_QualifierSet qualifierSet;

                NitsCompare(ps.ft->GetMethodReturnType(NULL, &returnType, &qualifierSet), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameterCount should fail"));
                NitsCompare(MI_ParameterSet_GetMethodReturnType(NULL, &returnType, &qualifierSet), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameterCount should fail"));
                NitsCompare(MI_ParameterSet_GetMethodReturnType(&ps, NULL, &qualifierSet), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameterCount should fail"));
                NitsCompare(MI_ParameterSet_GetMethodReturnType(&ps, &returnType, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameterCount should fail"));
            }
            
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_ParameterSet_GetParameterAt)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            const MI_Char *name;
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;
            MI_Uint32 paramCount = 0;
            MI_Type type;

            if (NitsCompare(MI_Class_GetMethod(newClass, PAL_T("RequestStateChange"), &qs, &ps, &index), MI_RESULT_OK, PAL_T("MI_Class_GetMethod should succeed")) &&
                NitsCompare(MI_ParameterSet_GetParameterCount(&ps, &paramCount), MI_RESULT_OK, PAL_T("MI_ParameterSet_GetParameterCount should succeed")))
            {
                for (MI_Uint32 index = 0; index != paramCount; index++)
                {
                    NitsCompare(MI_ParameterSet_GetParameterAt(&ps, index, &name, &type, NULL, &qs), MI_RESULT_OK, PAL_T("MI_ParameterSet_GetParameterAt should succeed"));
                }
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_ParameterSet_GetParameterAt_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            const MI_Char *name;
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;
            MI_Uint32 paramCount = 0;
            MI_Type type;

            if (NitsCompare(MI_Class_GetMethod(newClass, PAL_T("RequestStateChange"), &qs, &ps, &index), MI_RESULT_OK, PAL_T("MI_Class_GetMethod should succeed")) &&
                NitsCompare(MI_ParameterSet_GetParameterCount(&ps, &paramCount), MI_RESULT_OK, PAL_T("MI_ParameterSet_GetParameterCount should succeed")))
            {
                NitsCompare(ps.ft->GetParameterAt(NULL, 0, &name, &type, NULL, &qs), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameterAt should fail, index past parameter count"));
                NitsCompare(MI_ParameterSet_GetParameterAt(NULL, 0, &name, &type, NULL, &qs), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameterAt should fail, index past parameter count"));
                NitsCompare(MI_ParameterSet_GetParameterAt(&ps, paramCount, &name, &type, NULL, &qs), MI_RESULT_NOT_FOUND, PAL_T("MI_ParameterSet_GetParameterAt should fail, index past parameter count"));
                NitsCompare(MI_ParameterSet_GetParameterAt(&ps, 0, NULL, &type, NULL, &qs), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameterAt should fail"));
                NitsCompare(MI_ParameterSet_GetParameterAt(&ps, 0, &name, NULL, NULL, &qs), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameterAt should fail"));
                NitsCompare(MI_ParameterSet_GetParameterAt(&ps, 0, &name, &type, NULL, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameterAt should fail"));
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_ParameterSet_GetParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;
            MI_Uint32 paramCount = 0;

            if (NitsCompare(MI_Class_GetMethod(newClass, PAL_T("RequestStateChange"), &qs, &ps, &index), MI_RESULT_OK, PAL_T("MI_Class_GetMethod should succeed")) &&
                NitsCompare(MI_ParameterSet_GetParameterCount(&ps, &paramCount), MI_RESULT_OK, PAL_T("MI_ParameterSet_GetParameterCount should succeed")))
            {
                MI_Type type;
                MI_QualifierSet qs;

                if (NitsCompare(MI_ParameterSet_GetParameter(&ps, PAL_T("RequestedState"), &type, NULL, &qs, &index), MI_RESULT_OK, PAL_T("MI_ParameterSet_GetParameter should succeed")))
                {
                    NitsCompare(type, MI_UINT16, PAL_T("type of MSFT_Process::RequestStateChange(RequestedState rs, ...) should be UINT16"));
                    NitsCompare((int)qs.reserved1, 4, PAL_T("MSFT_Process::RequestStateChange(RequestedState rs, ...) has 1 qualifier"));
                    NitsCompare(index, 0, PAL_T("MSFT_Process::RequestStateChange(RequestedState rs, ...) should be the first (0) index"));
                }
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_ParameterSet_GetParameter_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;
            MI_Uint32 paramCount = 0;

            if (NitsCompare(MI_Class_GetMethod(newClass, PAL_T("RequestStateChange"), &qs, &ps, &index), MI_RESULT_OK, PAL_T("MI_Class_GetMethod should succeed")) &&
                NitsCompare(MI_ParameterSet_GetParameterCount(&ps, &paramCount), MI_RESULT_OK, PAL_T("MI_ParameterSet_GetParameterCount should succeed")))
            {
                MI_Type type;
                MI_QualifierSet qs;

                NitsCompare(ps.ft->GetParameter(NULL,  PAL_T("RequestedState"), &type, NULL, &qs, &index), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameter should fail"));
                NitsCompare(MI_ParameterSet_GetParameter(NULL,  PAL_T("RequestedState"), &type, NULL, &qs, &index), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameter should fail"));
                NitsCompare(MI_ParameterSet_GetParameter(&ps, NULL, &type, NULL, &qs, &index), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameter should fail"));
                NitsCompare(MI_ParameterSet_GetParameter(&ps, PAL_T("RequestedState"), NULL, NULL, &qs, &index), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameter should fail"));
                NitsCompare(MI_ParameterSet_GetParameter(&ps, PAL_T("RequestedState"), &type, NULL, NULL, &index), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameter should fail"));
                NitsCompare(MI_ParameterSet_GetParameter(&ps, PAL_T("RequestedState"), &type, NULL, &qs, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_ParameterSet_GetParameter should fail"));
                NitsCompare(MI_ParameterSet_GetParameter(&ps, PAL_T("fofofofo"), &type, NULL, &qs, &index), MI_RESULT_NOT_FOUND, PAL_T("MI_ParameterSet_GetParameter should fail"));
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_QualifierSet_GetQualifierCount)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;

            if (NitsCompare(MI_Class_GetMethod(newClass, PAL_T("RequestStateChange"), &qs, &ps, &index), MI_RESULT_OK, PAL_T("MI_Class_GetMethod should succeed")))
            {
                MI_Uint32 qualifierCount = 0;
                NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qualifierCount), MI_RESULT_OK, PAL_T("MI_QualifierSet_GetQualifierCount should succeed"));
                NitsCompare(qualifierCount, 4, PAL_T("MSFT_Process::RequestStateChange should have 1 qualifier"));
            }
            
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_QualifierSet_GetQualifierCount_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;

            if (NitsCompare(MI_Class_GetMethod(newClass, PAL_T("RequestStateChange"), &qs, &ps, &index), MI_RESULT_OK, PAL_T("MI_Class_GetMethod should succeed")))
            {
                MI_Uint32 qualifierCount = 0;
                NitsCompare(qs.ft->GetQualifierCount(NULL, &qualifierCount), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifierCount should fail"));
                NitsCompare(MI_QualifierSet_GetQualifierCount(NULL, &qualifierCount), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifierCount should fail"));
                NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifierCount should fail"));
            }
            
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_QualifierSet_GetQualifierAt)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"), &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            const MI_Char *name;
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;
            MI_Uint32 qualCount = 0;
            MI_Type type;
            MI_Value qualValue;
            MI_Uint32 flags;

            if (NitsCompare(MI_Class_GetMethod(newClass, PAL_T("RequestStateChange"), &qs, &ps, &index), MI_RESULT_OK, PAL_T("MI_Class_GetMethod should succeed")) &&
                NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qualCount), MI_RESULT_OK, PAL_T("MI_QualifierSet_GetQualifierCount should succeed")))
            {
                for (MI_Uint32 index = 0; index != qualCount; index++)
                {
                    NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, index, &name, &type, &flags, &qualValue), MI_RESULT_OK, PAL_T("MI_QualifierSet_GetQualifierAt should succeed"));
                }
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_QualifierSet_GetQualifierAt_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"), &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            const MI_Char *name;
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;
            MI_Uint32 qualCount = 0;
            MI_Type type;
            MI_Value qualValue;
            MI_Uint32 flags;

            if (NitsCompare(MI_Class_GetMethod(newClass, PAL_T("RequestStateChange"), &qs, &ps, &index), MI_RESULT_OK, PAL_T("MI_Class_GetMethod should succeed")) &&
                NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qualCount), MI_RESULT_OK, PAL_T("MI_QualifierSet_GetQualifierCount should succeed")))
            {
                NitsCompare(qs.ft->GetQualifierAt(NULL, 0, &name, &type, &flags, &qualValue), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifierAt should fail"));
                NitsCompare(MI_QualifierSet_GetQualifierAt(NULL, 0, &name, &type, &flags, &qualValue), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifierAt should fail"));
                NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, qualCount, &name, &type, &flags, &qualValue), MI_RESULT_NOT_FOUND, PAL_T("MI_QualifierSet_GetQualifierAt should fail, index past parameter count"));
                NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, NULL, &type, &flags, &qualValue), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifierAt should fail"));
                NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, &name, NULL, &flags, &qualValue), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifierAt should fail"));
                NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, &name, &type, NULL, &qualValue), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifierAt should fail"));
                NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, &name, &type, &flags, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifierAt should fail"));
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_QualifierSet_GetQualifier)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"), &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;

            if (NitsCompare(MI_Class_GetMethod(newClass, PAL_T("RequestStateChange"), &qs, &ps, &index), MI_RESULT_OK, PAL_T("MI_Class_GetMethod should succeed")))
            {
                MI_Type type;
                MI_Value qualValue;
                MI_Uint32 flags;

                if (NitsCompare(MI_QualifierSet_GetQualifier(&qs, PAL_T("ModelCorrespondence"), &type, &flags, &qualValue, &index), MI_RESULT_OK, PAL_T("MI_QualifierSet_GetQualifier should succeed")))
                {
                    NitsCompare(type, MI_STRINGA, PAL_T("type of MSFT_Process::RequestStateChange(RequestedState rs, ...) should be UINT16"));
                    NitsCompare((int)qs.reserved1, 4, PAL_T("MSFT_Process::RequestStateChange(RequestedState rs, ...) has 1 qualifier"));
                    NitsCompare(index, 3, PAL_T("MSFT_Process::RequestStateChange(RequestedState rs, ...) should be the first (3) index"));
                }
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

NitsTest(Test_QualifierSet_GetQualifier_InvalidParameter)
{
    MI_ClassDecl* cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));

    if (NitsAssert(cd != NULL, PAL_T("Failed to find MSFT_Process")))
    {
        MI_Class *newClass = NULL;
        if (NitsCompare(Class_New(cd, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
        {
            MI_QualifierSet qs;
            MI_ParameterSet ps;
            MI_Uint32 index;

            if (NitsCompare(MI_Class_GetMethod(newClass, PAL_T("RequestStateChange"), &qs, &ps, &index), MI_RESULT_OK, PAL_T("MI_Class_GetMethod should succeed")))
            {
                MI_Type type;
                MI_Value qualValue;
                MI_Uint32 flags;

                NitsCompare(qs.ft->GetQualifier(NULL, PAL_T("fofofofof"), &type, &flags, &qualValue, &index), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifier should succeed"));
                NitsCompare(MI_QualifierSet_GetQualifier(NULL, PAL_T("fofofofof"), &type, &flags, &qualValue, &index), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifier should succeed"));
                NitsCompare(MI_QualifierSet_GetQualifier(&qs, PAL_T("fofofofof"), &type, &flags, &qualValue, &index), MI_RESULT_NOT_FOUND, PAL_T("MI_QualifierSet_GetQualifier should succeed"));
                NitsCompare(MI_QualifierSet_GetQualifier(&qs, NULL, &type, &flags, &qualValue, &index), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifier should succeed"));
                NitsCompare(MI_QualifierSet_GetQualifier(&qs, PAL_T("ModelCorrespondence"), NULL, &flags, &qualValue, &index), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifier should succeed"));
                NitsCompare(MI_QualifierSet_GetQualifier(&qs, PAL_T("ModelCorrespondence"), &type, NULL, &qualValue, &index), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifier should succeed"));
                NitsCompare(MI_QualifierSet_GetQualifier(&qs, PAL_T("ModelCorrespondence"), &type, &flags, NULL, &index), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifier should succeed"));
                NitsCompare(MI_QualifierSet_GetQualifier(&qs, PAL_T("ModelCorrespondence"), &type, &flags, &qualValue, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_QualifierSet_GetQualifier should succeed"));
            }
            MI_Class_Delete(newClass);
        }
    }
}
NitsEndTest

void IterateQualifierSet(MI_QualifierSet *qs)
{
    MI_Uint32 qualCount = 0;
    if (NitsCompare(MI_QualifierSet_GetQualifierCount(qs, &qualCount), MI_RESULT_OK, PAL_T("MI_QualifierSet_GetQualifierCount should succeed")))
    {
        for (MI_Uint32 index = 0; index != qualCount; index++)
        {
            const MI_Char *name;
            MI_Type type;
            MI_Uint32 flags;
            MI_Value qualValue;

            NitsCompare(MI_QualifierSet_GetQualifierAt(qs, index, &name, &type, &flags, &qualValue), MI_RESULT_OK, PAL_T("MI_QualifierSet_GetQualifierAt should succeed"));
        }
    }
}

void IterateParameterSet(MI_ParameterSet *ps)
{
    MI_Type type;
    MI_QualifierSet qs;
    MI_Uint32 count=0;

    if (NitsCompare(MI_ParameterSet_GetMethodReturnType(ps, &type, &qs), MI_RESULT_OK, PAL_T("GetMethodReturnType should succeed")))
    {
        IterateQualifierSet(&qs);
    }
    if (NitsCompare(MI_ParameterSet_GetParameterCount(ps, &count), MI_RESULT_OK, PAL_T("GetParameterCount should succeed")))
    {
        for (MI_Uint32 index = 0; index != count; index++)
        {
            const MI_Char *name;
            MI_Type type;
            
            if (NitsCompare(MI_ParameterSet_GetParameterAt(ps, index, &name, &type, NULL, &qs), MI_RESULT_OK, PAL_T("GetParameterAt should succeed")))
            {
                IterateQualifierSet(&qs);
            }
        }
    }
}


void DoRecurseClass(const MI_ClassDecl *classDecl)
{
    MI_Class *newClass = NULL;

    if (NitsCompare(Class_New(classDecl, PAL_T("namespace"), PAL_T("server"),  &newClass), MI_RESULT_OK, PAL_T("Class declaration should succeed")))
    {
        MI_QualifierSet qs;
        MI_Uint32 count=0, iter;
        MI_Class *superClass;
        MI_Result result;

        result = MI_Class_GetParentClass(newClass, &superClass);
        //Get parent class... may fail if there is no parent
       if ( result == MI_RESULT_OK)
       {
           MI_Class_Delete(superClass);
           superClass = NULL;
       }
       else 
       {
           NitsAssert(result != MI_RESULT_SERVER_LIMITS_EXCEEDED, PAL_T("may not have a parent class"));
       }

        //Get class qualifiers
        if (NitsCompare(MI_Class_GetClassQualifierSet(newClass, &qs), MI_RESULT_OK, PAL_T("GetClassQualifierSet should succeed")))
        {
            IterateQualifierSet(&qs);
        }

        //Get parameters
        if (NitsCompare(MI_Class_GetElementCount(newClass, &count), MI_RESULT_OK, PAL_T("GetElementCount should succeed")))
        {
            for (iter = 0; iter != count; iter++)
            {
                const MI_Char* name;
                MI_Value value;
                MI_Boolean valueExists;
                MI_Type type;
                MI_Uint32 flags;
                MI_Char *referenceName = NULL;

                if (NitsCompare(MI_Class_GetElementAt(newClass, iter, &name, &value, &valueExists, &type, &referenceName, &qs, &flags), MI_RESULT_OK, PAL_T("GetElementAt should succeed")))
                {
                    IterateQualifierSet(&qs);
                }
            }
        }

        //Get methods
        if (NitsCompare(MI_Class_GetMethodCount(newClass, &count), MI_RESULT_OK, PAL_T("GetMethodCount should succeed")))
        {
            for (iter = 0; iter != count; iter++)
            {
                const MI_Char* name;
                MI_ParameterSet ps;

                if (NitsCompare(MI_Class_GetMethodAt(newClass, iter, &name, &qs, &ps), MI_RESULT_OK, PAL_T("GetElementAt should succeed")))
                {
                    IterateQualifierSet(&qs);
                    IterateParameterSet(&ps);
                }
            }
        }
    }
}

NitsTest(Test_Class_RecurseClass)
{
    MI_Uint32 loop;
    for (loop = 0; loop != test_repos_classDecl.numClassDecls;loop++)
    {
        DoRecurseClass(test_repos_classDecl.classDecls[loop]);
    }
}
NitsEndTest

/*===========================================================================================================================
 *
 * Class Creation library
 *
 *===========================================================================================================================
 */
NitsTest(Class_New_NoParent)
{
    MI_Class *newClass = NULL;
    MI_Result res;
    
    res = ClassConstructor_New(
        NULL,           /* Parent RC_Class */
        PAL_T("root"),        /* Not needed if parentClass is passed in */
        PAL_T("localhost"),   /* Not needed if parentClass is passed in */
        PAL_T("MyClass"),     /* class name */
        0,              /* number of extra class qualifiers you want to create.  Allows us to pre-create array of correct size */
        0,              /* number of extra properties you want to create.  Allows us to pre-create array of correct size */
        0,              /* number of extra methods you want to create. Allows us to pre-create array of correct size */
        &newClass       /* Object that is ready to receive new qualifiers/properties/methods */
        );
    if (NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Creation should succeed")))
    {
        res = newClass->ft->Delete(newClass);
        NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Deletion should succeed"));
    }
}
NitsEndTest

NitsTest(Class_New_ClassQualifiers_NoParent)
{
    MI_Class *newClass = NULL;
    MI_Result res;
    
    res = ClassConstructor_New(
        NULL,           /* Parent RC_Class */
        PAL_T("root"),        /* Not needed if parentClass is passed in */
        PAL_T("localhost"),   /* Not needed if parentClass is passed in */
        PAL_T("MyClass"),     /* class name */
        2,              /* number of extra class qualifiers you want to create.  Allows us to pre-create array of correct size */
        0,              /* number of extra properties you want to create.  Allows us to pre-create array of correct size */
        0,              /* number of extra methods you want to create. Allows us to pre-create array of correct size */
        &newClass       /* Object that is ready to receive new qualifiers/properties/methods */
        );
    if (NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Creation should succeed")))
    {
        MI_Value valueTrue;
        valueTrue.boolean = MI_TRUE;

        NitsCompare(Class_AddClassQualifier(newClass, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed"));
        NitsCompare(Class_AddClassQualifier(newClass, PAL_T("Qual2"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed"));
        res = newClass->ft->Delete(newClass);
        NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Deletion should succeed"));
    }
}
NitsEndTest

NitsTest(Class_New_Methods_NoParent)
{
    MI_Class *newClass = NULL;
    MI_Result res;
    
    res = ClassConstructor_New(
        NULL,           /* Parent RC_Class */
        PAL_T("root"),        /* Not needed if parentClass is passed in */
        PAL_T("localhost"),   /* Not needed if parentClass is passed in */
        PAL_T("MyClass"),     /* class name */
        0,              /* number of extra class qualifiers you want to create.  Allows us to pre-create array of correct size */
        0,              /* number of extra properties you want to create.  Allows us to pre-create array of correct size */
        1,              /* number of extra methods you want to create. Allows us to pre-create array of correct size */
        &newClass       /* Object that is ready to receive new qualifiers/properties/methods */
        );
    if (NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Creation should succeed")))
    {
        MI_Uint32 methodId = 0;
        MI_Uint32 parameterId = 0;
        MI_Value valueTrue;
        valueTrue.boolean = MI_TRUE;

        if (NitsCompare(Class_AddMethod(newClass, PAL_T("Method1"), 0, 1, 1, &methodId), MI_RESULT_OK, PAL_T("Add method should succeed")))
        {
            NitsCompare(Class_AddMethodQualifier(newClass, methodId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed"));
            if (NitsCompare(Class_AddMethodParameter(newClass, methodId, PAL_T("Parameter1"), NULL, MI_BOOLEAN, 0, 0, 1, &parameterId), MI_RESULT_OK, PAL_T("Add method parameter should succeed")))
            {
                NitsCompare(Class_AddMethodParameterQualifier(newClass, methodId, parameterId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed"));
            }
        }
        res = newClass->ft->Delete(newClass);
        NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Deletion should succeed"));
    }
}
NitsEndTest

NitsTest(Class_New_EverythingWithValidation_NoParent)
{
    MI_Class *baseClass = NULL;
    MI_Result res;
    MI_Uint32 elementId, methodId, parameterId;
    MI_Value valueTrue;

    valueTrue.boolean = MI_TRUE;
    
    res = ClassConstructor_New(
        NULL,           /* Parent RC_Class */
        PAL_T("root"),        /* Not needed if parentClass is passed in */
        PAL_T("localhost"),   /* Not needed if parentClass is passed in */
        PAL_T("BaseClass"),   /* class name */
        1,              /* number of extra class qualifiers you want to create.  Allows us to pre-create array of correct size */
        1,              /* number of extra properties you want to create.  Allows us to pre-create array of correct size */
        1,              /* number of extra methods you want to create. Allows us to pre-create array of correct size */
        &baseClass       /* Object that is ready to receive new qualifiers/properties/methods */
        );

    if (NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Creation should succeed")) &&
        /* Class qualifier */
        NitsCompare(Class_AddClassQualifier(baseClass, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, MI_FLAG_TOSUBCLASS), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&

        /* Element */
        NitsCompare(Class_AddElement(baseClass, PAL_T("Elem1"), MI_BOOLEAN, valueTrue, 0, NULL, MI_FALSE, PAL_T("BaseClass"), 1, &elementId), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&
        NitsCompare(Class_AddElementQualifier(baseClass, elementId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&

        /* Method */
        NitsCompare(Class_AddMethod(baseClass, PAL_T("Method1"), 0, 1, 1, &methodId), MI_RESULT_OK, PAL_T("Add method should succeed")) &&
        NitsCompare(Class_AddMethodQualifier(baseClass, methodId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&
        NitsCompare(Class_AddMethodParameter(baseClass, methodId, PAL_T("Parameter1"), NULL, MI_BOOLEAN, 0, 0, 1, &parameterId), MI_RESULT_OK, PAL_T("Add method parameter should succeed")) &&
        NitsCompare(Class_AddMethodParameterQualifier(baseClass, methodId, parameterId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")))
    {
        if (NitsCompare((int)baseClass->reserved[1], 1, PAL_T("reserved[1] should be 1")) &&
            NitsAssert(baseClass->namespaceName != 0, PAL_T("should be a namespace name")) &&
            NitsCompareString(baseClass->namespaceName, PAL_T("root"), PAL_T("namespace should be 'root'")) &&
            NitsAssert(baseClass->serverName != 0, PAL_T("should be a server name")) &&
            NitsCompareString(baseClass->serverName, PAL_T("localhost"), PAL_T("server should be 'localhost'")) &&
            NitsAssert(baseClass->classDecl != 0, PAL_T("Should have class decl")) &&
            NitsAssert(baseClass->classDecl->name != NULL, PAL_T("should have class name")) &&
            NitsCompareString(baseClass->classDecl->name, PAL_T("BaseClass"), PAL_T("class name should be 'DerivedClass'")) &&
            NitsCompareString(baseClass->classDecl->superClass, 0, PAL_T("should not have superClass")) &&
            NitsAssert(baseClass->classDecl->superClassDecl == NULL, PAL_T("Superclass class decl should be null")) &&
            NitsCompare(baseClass->classDecl->numQualifiers, 1, PAL_T("Should have 1 qualifiers")) &&
            NitsAssert(baseClass->classDecl->qualifiers != NULL, PAL_T("Should have qualifier array")) &&
            NitsCompareString(baseClass->classDecl->qualifiers[0]->name, PAL_T("Qual1"), PAL_T("Qualifier 1 should exist")) &&
            NitsCompare(baseClass->classDecl->numProperties, 1, PAL_T("Should have 1 properties")) &&
            NitsAssert(baseClass->classDecl->properties != NULL, PAL_T("Should have properties array")) &&
            NitsCompareString(baseClass->classDecl->properties[0]->name, PAL_T("Elem1"), PAL_T("'Elem1' should exist")) &&
            NitsCompare(baseClass->classDecl->properties[0]->numQualifiers, 1, PAL_T("Elem1 should have 1 qualifier")) &&
            NitsAssert(baseClass->classDecl->properties[0]->qualifiers != 0, PAL_T("Elem1 should have qualifier list")) &&
            NitsCompareString(baseClass->classDecl->properties[0]->qualifiers[0]->name, PAL_T("Qual1"), PAL_T("Elem1 should have Qual1 qualifier")) &&
            NitsCompare(baseClass->classDecl->numMethods, 1, PAL_T("should have 1 methods")) &&
            NitsAssert(baseClass->classDecl->methods != NULL, PAL_T("Should have methods array")) &&
            NitsCompareString(baseClass->classDecl->methods[0]->name, PAL_T("Method1"), PAL_T("Method1 should exist")) &&
            NitsCompare(baseClass->classDecl->methods[0]->numQualifiers, 1, PAL_T("Method1 should have 1 qualifier")) &&
            NitsAssert(baseClass->classDecl->methods[0]->qualifiers != 0, PAL_T("Method1 qualifier list should exist")) &&
            NitsCompareString(baseClass->classDecl->methods[0]->qualifiers[0]->name, PAL_T("Qual1"), PAL_T("Method1 should have Qual1 qualifier")) &&
            NitsCompare(baseClass->classDecl->methods[0]->numParameters, 1, PAL_T("Method1 should have 1 parameters")) &&
            NitsAssert(baseClass->classDecl->methods[0]->parameters != 0, PAL_T("Method1 parameter list should exist")) &&
            NitsCompareString(baseClass->classDecl->methods[0]->parameters[0]->name, PAL_T("Parameter1"), PAL_T("Method1 should have Parameter1 parameter")) &&
            NitsAssert(baseClass->classDecl->methods[0]->parameters[0]->className == NULL, PAL_T("Parameter class name should be NULL")) &&
            NitsCompare(baseClass->classDecl->methods[0]->parameters[0]->numQualifiers, 1, PAL_T("Method1 parameter1 should have 1 qualifier")) &&
            NitsAssert(baseClass->classDecl->methods[0]->parameters[0]->qualifiers != 0, PAL_T("Method1 parameter1 qualifier list should exist")) &&
            NitsCompareString(baseClass->classDecl->methods[0]->parameters[0]->qualifiers[0]->name, PAL_T("Qual1"), PAL_T("Method1 parameter1 should have Qual1 qualifier"))
            )
        {
            // Yeah!  Validation complete!
        }

        res = baseClass->ft->Delete(baseClass);
        NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Deletion should succeed"));
    }
}
NitsEndTest

NitsTest(Class_New_ClassElement_NoParent)
{
    MI_Class *newClass = NULL;
    MI_Result res;
    
    res = ClassConstructor_New(
        NULL,           /* Parent RC_Class */
        PAL_T("root"),        /* Not needed if parentClass is passed in */
        PAL_T("localhost"),   /* Not needed if parentClass is passed in */
        PAL_T("MyClass"),     /* class name */
        0,              /* number of extra class qualifiers you want to create.  Allows us to pre-create array of correct size */
        1,              /* number of extra properties you want to create.  Allows us to pre-create array of correct size */
        0,              /* number of extra methods you want to create. Allows us to pre-create array of correct size */
        &newClass       /* Object that is ready to receive new qualifiers/properties/methods */
        );
    if (NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Creation should succeed")))
    {
        MI_Uint32 elementId;
        MI_Value valueTrue;
        valueTrue.boolean = MI_TRUE;

        /* Element */
        if (NitsCompare(Class_AddElement(newClass, PAL_T("Elem1"), MI_BOOLEAN, valueTrue, 0, NULL, MI_FALSE, PAL_T("MyClass"), 1, &elementId), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")))
            NitsCompare(Class_AddElementQualifier(newClass, elementId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed"));

        res = newClass->ft->Delete(newClass);
        NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Deletion should succeed"));
    }
}
NitsEndTest

NitsTest(Class_New_WithParent)
{
    MI_Class *baseClass = NULL;
    MI_Result res;
    MI_Uint32 elementId, methodId, parameterId;
    MI_Value valueTrue;
    MI_Class *derivedClass = NULL;

    valueTrue.boolean = MI_TRUE;
    
    res = ClassConstructor_New(
        NULL,           /* Parent RC_Class */
        PAL_T("root"),        /* Not needed if parentClass is passed in */
        PAL_T("localhost"),   /* Not needed if parentClass is passed in */
        PAL_T("BaseClass"),   /* class name */
        1,              /* number of extra class qualifiers you want to create.  Allows us to pre-create array of correct size */
        1,              /* number of extra properties you want to create.  Allows us to pre-create array of correct size */
        1,              /* number of extra methods you want to create. Allows us to pre-create array of correct size */
        &baseClass       /* Object that is ready to receive new qualifiers/properties/methods */
        );
    if (NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Creation should succeed")) &&
        /* Class qualifier */
        NitsCompare(Class_AddClassQualifier(baseClass, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, MI_FLAG_TOSUBCLASS), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&

        /* Element */
        NitsCompare(Class_AddElement(baseClass, PAL_T("Elem1"), MI_BOOLEAN, valueTrue, 0, NULL, MI_FALSE, PAL_T("BaseClass"), 1, &elementId), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&
        NitsCompare(Class_AddElementQualifier(baseClass, elementId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, MI_FLAG_TOSUBCLASS | MI_FLAG_ENABLEOVERRIDE), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&

        /* Method */
        NitsCompare(Class_AddMethod(baseClass, PAL_T("Method1"), 0, 1, 1, &methodId), MI_RESULT_OK, PAL_T("Add method should succeed")) &&
        NitsCompare(Class_AddMethodQualifier(baseClass, methodId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, MI_FLAG_TOSUBCLASS | MI_FLAG_ENABLEOVERRIDE), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&
        NitsCompare(Class_AddMethodParameter(baseClass, methodId, PAL_T("Parameter1"), NULL, MI_BOOLEAN, 0, 0, 1, &parameterId), MI_RESULT_OK, PAL_T("Add method parameter should succeed")) &&

        NitsCompare(Class_AddMethodParameterQualifier(baseClass, methodId, parameterId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")))
    {
        /* Have child class, now work on derived class */
        res = ClassConstructor_New(
            baseClass,      /* Parent RC_Class */
            NULL,           /* Not needed if parentClass is passed in */
            NULL,           /* Not needed if parentClass is passed in */
            PAL_T("DerivedClass"),/* class name */
            1,              /* number of extra class qualifiers you want to create.  Allows us to pre-create array of correct size */
            1,              /* number of extra properties you want to create.  Allows us to pre-create array of correct size */
            1,              /* number of extra methods you want to create. Allows us to pre-create array of correct size */
            &derivedClass   /* Object that is ready to receive new qualifiers/properties/methods */
            );
        if (NitsCompare(res, MI_RESULT_OK, PAL_T("RC derived Class Creation should succeed")) &&
            /* Class qualifier */
            NitsCompare(Class_AddClassQualifier(derivedClass, PAL_T("Qual2"), MI_BOOLEAN, valueTrue, MI_FLAG_TOSUBCLASS | MI_FLAG_ENABLEOVERRIDE), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&

            /* Element */
            NitsCompare(Class_AddElement(derivedClass, PAL_T("Elem2"), MI_BOOLEAN, valueTrue, 0, NULL, MI_FALSE, PAL_T("DerivedClass"), 1, &elementId), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&
            NitsCompare(Class_AddElementQualifier(derivedClass, elementId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&

            /* Method */
            NitsCompare(Class_AddMethod(derivedClass, PAL_T("Method2"), 0, 1, 1, &methodId), MI_RESULT_OK, PAL_T("Add method should succeed")) &&
            NitsCompare(Class_AddMethodQualifier(derivedClass, methodId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, MI_FLAG_TOSUBCLASS | MI_FLAG_ENABLEOVERRIDE), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&
            NitsCompare(Class_AddMethodParameter(derivedClass, methodId, PAL_T("Parameter1"), NULL, MI_BOOLEAN, 0, 0, 1, &parameterId), MI_RESULT_OK, PAL_T("Add method parameter should succeed")) &&
            NitsCompare(Class_AddMethodParameterQualifier(derivedClass, methodId, parameterId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, MI_FLAG_TOSUBCLASS | MI_FLAG_ENABLEOVERRIDE), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")))
        {
            if (NitsCompare((int)derivedClass->reserved[1], 1, PAL_T("reserved[1] should be 1")) &&
                NitsAssert(derivedClass->namespaceName != 0, PAL_T("should be a namespace name")) &&
                NitsCompareString(derivedClass->namespaceName, PAL_T("root"), PAL_T("namespace should be 'root'")) &&
                NitsAssert(derivedClass->serverName != 0, PAL_T("should be a server name")) &&
                NitsCompareString(derivedClass->serverName, PAL_T("localhost"), PAL_T("server should be 'localhost'")) &&
                NitsAssert(derivedClass->classDecl != 0, PAL_T("Should have class decl")) &&
                NitsAssert(derivedClass->classDecl->name != NULL, PAL_T("should have class name")) &&
                NitsCompareString(derivedClass->classDecl->name, PAL_T("DerivedClass"), PAL_T("class name should be 'DerivedClass'")) &&
                NitsAssert(derivedClass->classDecl->superClass != 0, PAL_T("should have superClass")) &&
                NitsCompareString(derivedClass->classDecl->superClass, PAL_T("BaseClass"), PAL_T("superclass name should be 'BaseClass'")) &&
                NitsAssert(derivedClass->classDecl->superClassDecl != NULL, PAL_T("Superclass class decl should exist")) &&
                NitsCompare((int)baseClass->reserved[1], 2, PAL_T("Superclass reserved[1] should be 2")) &&
                NitsCompare(derivedClass->classDecl->numQualifiers, 2, PAL_T("Should have 2 qualifiers")) &&
                NitsAssert(derivedClass->classDecl->qualifiers != NULL, PAL_T("Should have qualifier array")) &&
                NitsCompareString(derivedClass->classDecl->qualifiers[0]->name, PAL_T("Qual1"), PAL_T("Qualifier 1 should inherit from parent")) &&
                NitsCompareString(derivedClass->classDecl->qualifiers[1]->name, PAL_T("Qual2"), PAL_T("Qualifier 2 should be added")) &&
                NitsCompare(derivedClass->classDecl->numProperties, 2, PAL_T("Should have 2 properties")) &&
                NitsAssert(derivedClass->classDecl->properties != NULL, PAL_T("Should have properties array")) &&
                NitsCompareString(derivedClass->classDecl->properties[0]->name, PAL_T("Elem1"), PAL_T("Should inherit 'Elem1' from parent")) &&
                NitsCompare(derivedClass->classDecl->properties[0]->numQualifiers, 1, PAL_T("Elem1 should have 1 qualifier")) &&
                NitsAssert(derivedClass->classDecl->properties[0]->qualifiers != 0, PAL_T("Elem1 should have qualifier list")) &&
                NitsCompareString(derivedClass->classDecl->properties[0]->qualifiers[0]->name, PAL_T("Qual1"), PAL_T("Elem1 should have Qual1 qualifier")) &&
                NitsCompareString(derivedClass->classDecl->properties[1]->name, PAL_T("Elem2"), PAL_T("Should have added 'Elem2'")) &&
                NitsCompare(derivedClass->classDecl->properties[1]->numQualifiers, 1, PAL_T("Elem2 should have 1 qualifier")) &&
                NitsAssert(derivedClass->classDecl->properties[1]->qualifiers != 0, PAL_T("Elem2 should have qualifier list")) &&
                NitsCompareString(derivedClass->classDecl->properties[1]->qualifiers[0]->name, PAL_T("Qual1"), PAL_T("Elem2 should have Qual1 qualifier")) &&
                NitsCompare(derivedClass->classDecl->numMethods, 2, PAL_T("should have 2 methods")) &&
                NitsAssert(derivedClass->classDecl->methods != NULL, PAL_T("Should have methods array")) &&
                NitsCompareString(derivedClass->classDecl->methods[0]->name, PAL_T("Method1"), PAL_T("Method1 should inherit from parent")) &&
                NitsCompare(derivedClass->classDecl->methods[0]->numQualifiers, 1, PAL_T("Method1 should have 1 qualifier")) &&
                NitsAssert(derivedClass->classDecl->methods[0]->qualifiers != 0, PAL_T("Method1 qualifier list should exist")) &&
                NitsCompareString(derivedClass->classDecl->methods[0]->qualifiers[0]->name, PAL_T("Qual1"), PAL_T("Method1 should have Qual1 qualifier")) &&
                NitsCompare(derivedClass->classDecl->methods[0]->numParameters, 1, PAL_T("Method1 should have 1 parameters")) &&
                NitsAssert(derivedClass->classDecl->methods[0]->parameters != 0, PAL_T("Method1 parameter list should exist")) &&
                NitsCompareString(derivedClass->classDecl->methods[0]->parameters[0]->name, PAL_T("Parameter1"), PAL_T("Method1 should have Parameter1 parameter")) &&
                NitsAssert(derivedClass->classDecl->methods[0]->parameters[0]->className == NULL, PAL_T("Parameter class name should be NULL")) &&
                NitsCompare(derivedClass->classDecl->methods[0]->parameters[0]->numQualifiers, 1, PAL_T("Method1 parameter1 should have 1 qualifier")) &&
                NitsAssert(derivedClass->classDecl->methods[0]->parameters[0]->qualifiers != 0, PAL_T("Method1 parameter1 qualifier list should exist")) &&
                NitsCompareString(derivedClass->classDecl->methods[0]->parameters[0]->qualifiers[0]->name, PAL_T("Qual1"), PAL_T("Method1 parameter1 should have Qual1 qualifier"))
                )
            {
                // Yeah!  Validation complete!
            }

            res = derivedClass->ft->Delete(derivedClass);
            NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Deletion should succeed"));
        }

        res = baseClass->ft->Delete(baseClass);
        NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Deletion should succeed"));
    }
}
NitsEndTest

NitsTest(Class_New_WithParent_ButOverridden)
{
    MI_Class *baseClass = NULL;
    MI_Result res;
    MI_Uint32 elementId, methodId, parameterId;
    MI_Value valueTrue;
    MI_Class *derivedClass = NULL;

    valueTrue.boolean = MI_TRUE;
    
    res = ClassConstructor_New(
        NULL,           /* Parent RC_Class */
        PAL_T("root"),        /* Not needed if parentClass is passed in */
        PAL_T("localhost"),   /* Not needed if parentClass is passed in */
        PAL_T("BaseClass"),   /* class name */
        1,              /* number of extra class qualifiers you want to create.  Allows us to pre-create array of correct size */
        1,              /* number of extra properties you want to create.  Allows us to pre-create array of correct size */
        1,              /* number of extra methods you want to create. Allows us to pre-create array of correct size */
        &baseClass       /* Object that is ready to receive new qualifiers/properties/methods */
        );
    if (NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Creation should succeed")) &&
        /* Class qualifier */
        NitsCompare(Class_AddClassQualifier(baseClass, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, MI_FLAG_TOSUBCLASS), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&

        /* Element */
        NitsCompare(Class_AddElement(baseClass, PAL_T("Elem1"), MI_BOOLEAN, valueTrue, 0, NULL, MI_FALSE, PAL_T("BaseClass"), 1, &elementId), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&
        NitsCompare(Class_AddElementQualifier(baseClass, elementId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&

        /* Method */
        NitsCompare(Class_AddMethod(baseClass, PAL_T("Method1"), 0, 1, 1, &methodId), MI_RESULT_OK, PAL_T("Add method should succeed")) &&
        NitsCompare(Class_AddMethodQualifier(baseClass, methodId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&
        NitsCompare(Class_AddMethodParameter(baseClass, methodId, PAL_T("Parameter1"), NULL, MI_BOOLEAN, 0, 0, 1, &parameterId), MI_RESULT_OK, PAL_T("Add method parameter should succeed")) &&

        NitsCompare(Class_AddMethodParameterQualifier(baseClass, methodId, parameterId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")))
    {
        /* Have child class, now work on derived class */
        res = ClassConstructor_New(
            baseClass,      /* Parent RC_Class */
            NULL,           /* Not needed if parentClass is passed in */
            NULL,           /* Not needed if parentClass is passed in */
            PAL_T("DerivedClass"),/* class name */
            1,              /* number of extra class qualifiers you want to create.  Allows us to pre-create array of correct size */
            1,              /* number of extra properties you want to create.  Allows us to pre-create array of correct size */
            1,              /* number of extra methods you want to create. Allows us to pre-create array of correct size */
            &derivedClass   /* Object that is ready to receive new qualifiers/properties/methods */
            );
        if (NitsCompare(res, MI_RESULT_OK, PAL_T("RC derived Class Creation should succeed")) &&
            /* Class qualifier */
            NitsCompare(Class_AddClassQualifier(derivedClass, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&

            /* Element */
            NitsCompare(Class_AddElement(derivedClass, PAL_T("Elem1"), MI_BOOLEAN, valueTrue, 0, NULL, MI_TRUE, PAL_T("BaseClass"), 1, &elementId), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&
            NitsCompare(Class_AddElementQualifier(derivedClass, elementId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&

            /* Method */
            NitsCompare(Class_AddMethod(derivedClass, PAL_T("Method1"), 0, 1, 1, &methodId), MI_RESULT_OK, PAL_T("Add method should succeed")) &&
            NitsCompare(Class_AddMethodQualifier(derivedClass, methodId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")) &&
            NitsCompare(Class_AddMethodParameter(derivedClass, methodId, PAL_T("Parameter1"), NULL, MI_BOOLEAN, 0, 0, 1, &parameterId), MI_RESULT_OK, PAL_T("Add method parameter should succeed")) &&
            NitsCompare(Class_AddMethodParameterQualifier(derivedClass, methodId, parameterId, PAL_T("Qual1"), MI_BOOLEAN, valueTrue, 0), MI_RESULT_OK, PAL_T("Add Qualifier should succeed")))
        {
            if (NitsCompare((int)derivedClass->reserved[1], 1, PAL_T("reserved[1] should be 1")) &&
                NitsAssert(derivedClass->namespaceName != 0, PAL_T("should be a namespace name")) &&
                NitsCompareString(derivedClass->namespaceName, PAL_T("root"), PAL_T("namespace should be 'root'")) &&
                NitsAssert(derivedClass->serverName != 0, PAL_T("should be a server name")) &&
                NitsCompareString(derivedClass->serverName, PAL_T("localhost"), PAL_T("server should be 'localhost'")) &&
                NitsAssert(derivedClass->classDecl != 0, PAL_T("Should have class decl")) &&
                NitsAssert(derivedClass->classDecl->name != NULL, PAL_T("should have class name")) &&
                NitsCompareString(derivedClass->classDecl->name, PAL_T("DerivedClass"), PAL_T("class name should be 'DerivedClass'")) &&
                NitsAssert(derivedClass->classDecl->superClass != 0, PAL_T("should have superClass")) &&
                NitsCompareString(derivedClass->classDecl->superClass, PAL_T("BaseClass"), PAL_T("superclass name should be 'BaseClass'")) &&
                NitsAssert(derivedClass->classDecl->superClassDecl != NULL, PAL_T("Superclass class decl should exist")) &&
                NitsCompare((int)baseClass->reserved[1], 2, PAL_T("Superclass reserved[1] should be 2")) &&
                NitsCompare(derivedClass->classDecl->numQualifiers, 1, PAL_T("Should have 1 qualifiers")) &&
                NitsAssert(derivedClass->classDecl->qualifiers != NULL, PAL_T("Should have qualifier array")) &&
                NitsCompareString(derivedClass->classDecl->qualifiers[0]->name, PAL_T("Qual1"), PAL_T("Qualifier 1 should be overridden")) &&
                NitsCompare(derivedClass->classDecl->qualifiers[0]->flavor, 0, PAL_T("Qualifier 1 should be overridden")) &&
                NitsCompare(derivedClass->classDecl->numProperties, 1, PAL_T("Should have 1 properties")) &&
                NitsAssert(derivedClass->classDecl->properties != NULL, PAL_T("Should have properties array")) &&
                NitsCompareString(derivedClass->classDecl->properties[0]->name, PAL_T("Elem1"), PAL_T("Should be overridden 'Elem1' from parent")) &&
                NitsCompare(derivedClass->classDecl->properties[0]->numQualifiers, 1, PAL_T("Elem1 should have 1 qualifier")) &&
                NitsAssert(derivedClass->classDecl->properties[0]->qualifiers != 0, PAL_T("Elem1 should have qualifier list")) &&
                NitsCompareString(derivedClass->classDecl->properties[0]->qualifiers[0]->name, PAL_T("Qual1"), PAL_T("Elem1 should have Qual1 qualifier")) &&
                NitsCompare(derivedClass->classDecl->numMethods, 1, PAL_T("should have 2 methods")) &&
                NitsAssert(derivedClass->classDecl->methods != NULL, PAL_T("Should have methods array")) &&
                NitsCompareString(derivedClass->classDecl->methods[0]->name, PAL_T("Method1"), PAL_T("Method1 should be overridden from parent")) &&
                NitsCompare(derivedClass->classDecl->methods[0]->numQualifiers, 1, PAL_T("Method1 should have 1 qualifier")) &&
                NitsAssert(derivedClass->classDecl->methods[0]->qualifiers != 0, PAL_T("Method1 qualifier list should exist")) &&
                NitsCompareString(derivedClass->classDecl->methods[0]->qualifiers[0]->name, PAL_T("Qual1"), PAL_T("Method1 should have Qual1 qualifier")) &&
                NitsCompare(derivedClass->classDecl->methods[0]->numParameters, 1, PAL_T("Method1 should have 1 parameters")) &&
                NitsAssert(derivedClass->classDecl->methods[0]->parameters != 0, PAL_T("Method1 parameter list should exist")) &&
                NitsCompareString(derivedClass->classDecl->methods[0]->parameters[0]->name, PAL_T("Parameter1"), PAL_T("Method1 should have Parameter1 parameter")) &&
                NitsAssert(derivedClass->classDecl->methods[0]->parameters[0]->className == NULL, PAL_T("Parameter class name should be NULL")) &&
                NitsCompare(derivedClass->classDecl->methods[0]->parameters[0]->numQualifiers, 1, PAL_T("Method1 parameter1 should have 1 qualifier")) &&
                NitsAssert(derivedClass->classDecl->methods[0]->parameters[0]->qualifiers != 0, PAL_T("Method1 parameter1 qualifier list should exist")) &&
                NitsCompareString(derivedClass->classDecl->methods[0]->parameters[0]->qualifiers[0]->name, PAL_T("Qual1"), PAL_T("Method1 parameter1 should have Qual1 qualifier"))
                )
            {
                // Yeah!  Validation complete!
            }

            res = derivedClass->ft->Delete(derivedClass);
            NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Deletion should succeed"));
        }

        res = baseClass->ft->Delete(baseClass);
        NitsCompare(res, MI_RESULT_OK, PAL_T("RC Class Deletion should succeed"));
    }
}
NitsEndTest
