/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#include <ctype.h>
#include <MI.h>
#include "Identifier.h"
#include "Reference.h"
#include "Test.h"
#include "Main.h"
#include "AllTypes.h"
#include "Performance.h"

/*
**==============================================================================
**
** Schema Declaration
**
**==============================================================================
*/

extern MI_SchemaDecl schemaDecl;

/*
**==============================================================================
**
** _Match()
**
**==============================================================================
*/

static int _Match(const MI_Char* p, const MI_Char* q)
{
    if (!p || !q || !p[0] || !q[0])
        return 1;

    while (*p && *q)
        if (toupper((MI_Uint16)*p++) - toupper((MI_Uint16)*q++))
            return 0;

    return *p == '\0' && *q == '\0';
}

/*
**==============================================================================
**
** Qualifier declarations
**
**==============================================================================
*/

/*
**==============================================================================
**
** Identifier
**
**==============================================================================
*/

/* property Identifier.NameSpace */
static MI_CONST MI_PropertyDecl Identifier_NameSpace_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E6509, /* code */
    MI_T("NameSpace"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identifier, NameSpace), /* offset */
    MI_T("Demo_Identifier"), /* origin */
    MI_T("Demo_Identifier"), /* propagator */
    NULL,
};

/* property Identifier.ClassName */
static MI_CONST MI_PropertyDecl Identifier_ClassName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00636509, /* code */
    MI_T("ClassName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identifier, ClassName), /* offset */
    MI_T("Demo_Identifier"), /* origin */
    MI_T("Demo_Identifier"), /* propagator */
    NULL,
};

/* property Identifier.MethodName */
static MI_CONST MI_PropertyDecl Identifier_MethodName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006D650A, /* code */
    MI_T("MethodName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identifier, MethodName), /* offset */
    MI_T("Demo_Identifier"), /* origin */
    MI_T("Demo_Identifier"), /* propagator */
    NULL,
};

/* property Identifier.pid */
static MI_CONST MI_PropertyDecl Identifier_pid_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00706403, /* code */
    MI_T("pid"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identifier, pid), /* offset */
    MI_T("Demo_Identifier"), /* origin */
    MI_T("Demo_Identifier"), /* propagator */
    NULL,
};

/* property Identifier.uid */
static MI_CONST MI_PropertyDecl Identifier_uid_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00756403, /* code */
    MI_T("uid"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identifier, uid), /* offset */
    MI_T("Demo_Identifier"), /* origin */
    MI_T("Demo_Identifier"), /* propagator */
    NULL,
};

/* property Identifier.gid */
static MI_CONST MI_PropertyDecl Identifier_gid_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00676403, /* code */
    MI_T("gid"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identifier, gid), /* offset */
    MI_T("Demo_Identifier"), /* origin */
    MI_T("Demo_Identifier"), /* propagator */
    NULL,
};

/* property Identifier.user */
static MI_CONST MI_PropertyDecl Identifier_user_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00757204, /* code */
    MI_T("user"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identifier, user), /* offset */
    MI_T("Demo_Identifier"), /* origin */
    MI_T("Demo_Identifier"), /* propagator */
    NULL,
};

/* property Identifier.group */
static MI_CONST MI_PropertyDecl Identifier_group_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00677005, /* code */
    MI_T("group"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identifier, group), /* offset */
    MI_T("Demo_Identifier"), /* origin */
    MI_T("Demo_Identifier"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Identifier_props[] =
{
    &Identifier_NameSpace_prop,
    &Identifier_ClassName_prop,
    &Identifier_MethodName_prop,
    &Identifier_pid_prop,
    &Identifier_uid_prop,
    &Identifier_gid_prop,
    &Identifier_user_prop,
    &Identifier_group_prop,
};

static MI_CONST MI_ProviderFT Identifier_funcs =
{
  (MI_ProviderFT_Load)Identifier_Load,
  (MI_ProviderFT_Unload)Identifier_Unload,
  (MI_ProviderFT_GetInstance)Identifier_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Identifier_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Identifier_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Identifier_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Identifier_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Identifier */
MI_CONST MI_ClassDecl Identifier_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0064720F, /* code */
    MI_T("Demo_Identifier"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Identifier_props, /* properties */
    MI_COUNT(Identifier_props), /* numProperties */
    sizeof(Identifier), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Identifier_funcs, /* functions */
};

/*
**==============================================================================
**
** Reference
**
**==============================================================================
*/

/* property Reference.Description */
static MI_CONST MI_PropertyDecl Reference_Description_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00646E0B, /* code */
    MI_T("Description"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Reference, Description), /* offset */
    MI_T("Demo_Reference"), /* origin */
    MI_T("Demo_Reference"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Reference_props[] =
{
    &Reference_Description_prop,
};

static MI_CONST MI_ProviderFT Reference_funcs =
{
  (MI_ProviderFT_Load)Reference_Load,
  (MI_ProviderFT_Unload)Reference_Unload,
  (MI_ProviderFT_GetInstance)Reference_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Reference_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Reference_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Reference_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Reference_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Reference */
MI_CONST MI_ClassDecl Reference_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0064650E, /* code */
    MI_T("Demo_Reference"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Reference_props, /* properties */
    MI_COUNT(Reference_props), /* numProperties */
    sizeof(Reference), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Reference_funcs, /* functions */
};

/*
**==============================================================================
**
** Test
**
**==============================================================================
*/

/* property Test.Id */
static MI_CONST MI_PropertyDecl Test_Id_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00696402, /* code */
    MI_T("Id"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Demo_Identifier"), /* className */
    0, /* subscript */
    offsetof(Test, Id), /* offset */
    MI_T("Demo_Test"), /* origin */
    MI_T("Demo_Test"), /* propagator */
    NULL,
};

/* property Test.Rf */
static MI_CONST MI_PropertyDecl Test_Rf_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00726602, /* code */
    MI_T("Rf"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Demo_Reference"), /* className */
    0, /* subscript */
    offsetof(Test, Rf), /* offset */
    MI_T("Demo_Test"), /* origin */
    MI_T("Demo_Test"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Test_props[] =
{
    &Test_Id_prop,
    &Test_Rf_prop,
};

/* parameter Test.StaticFun(): MIReturn */
static MI_CONST MI_ParameterDecl Test_StaticFun_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_StaticFun, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Test_StaticFun_params[] =
{
    &Test_StaticFun_MIReturn_param,
};

/* method Test.StaticFun() */
MI_CONST MI_MethodDecl Test_StaticFun_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00736E09, /* code */
    MI_T("StaticFun"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Test_StaticFun_params, /* parameters */
    MI_COUNT(Test_StaticFun_params), /* numParameters */
    sizeof(Test_StaticFun), /* size */
    MI_UINT32, /* returnType */
    MI_T("Demo_Test"), /* origin */
    MI_T("Demo_Test"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Test_Invoke_StaticFun, /* method */
};

/* parameter Test.InstanceFun(): MIReturn */
static MI_CONST MI_ParameterDecl Test_InstanceFun_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_InstanceFun, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Test_InstanceFun_params[] =
{
    &Test_InstanceFun_MIReturn_param,
};

/* method Test.InstanceFun() */
MI_CONST MI_MethodDecl Test_InstanceFun_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00696E0B, /* code */
    MI_T("InstanceFun"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Test_InstanceFun_params, /* parameters */
    MI_COUNT(Test_InstanceFun_params), /* numParameters */
    sizeof(Test_InstanceFun), /* size */
    MI_UINT32, /* returnType */
    MI_T("Demo_Test"), /* origin */
    MI_T("Demo_Test"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Test_Invoke_InstanceFun, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST Test_meths[] =
{
    &Test_StaticFun_rtti,
    &Test_InstanceFun_rtti,
};

static void MI_CALL Test_AssociatorInstances(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (Identifier_IsA(instanceName))
    {
        if (_Match(role, MI_T("Id")) && 
            _Match(resultRole, MI_T("Rf")))
        {
            Test_AssociatorInstancesId(
                self, 
                context, 
                nameSpace, 
                className, 
                (Identifier*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (Reference_IsA(instanceName))
    {
        if (_Match(role, MI_T("Rf")) && 
            _Match(resultRole, MI_T("Id")))
        {
            Test_AssociatorInstancesRf(
                self, 
                context, 
                nameSpace, 
                className, 
                (Reference*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL Test_ReferenceInstances(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (Identifier_IsA(instanceName))
    {
        if (_Match(role, MI_T("Id")))
        {
            Test_ReferenceInstancesId(
                self, 
                context, 
                nameSpace, 
                className, 
                (Identifier*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (Reference_IsA(instanceName))
    {
        if (_Match(role, MI_T("Rf")))
        {
            Test_ReferenceInstancesRf(
                self, 
                context, 
                nameSpace, 
                className, 
                (Reference*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT Test_funcs =
{
  (MI_ProviderFT_Load)Test_Load,
  (MI_ProviderFT_Unload)Test_Unload,
  (MI_ProviderFT_GetInstance)Test_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Test_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Test_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Test_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Test_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)Test_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)Test_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Test */
MI_CONST MI_ClassDecl Test_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00647409, /* code */
    MI_T("Demo_Test"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Test_props, /* properties */
    MI_COUNT(Test_props), /* numProperties */
    sizeof(Test), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    Test_meths, /* methods */
    MI_COUNT(Test_meths), /* numMethods */
    &schemaDecl, /* schema */
    &Test_funcs, /* functions */
};

/*
**==============================================================================
**
** Main
**
**==============================================================================
*/

/* property Main.SN */
static MI_CONST MI_PropertyDecl Main_SN_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00736E02, /* code */
    MI_T("SN"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Main, SN), /* offset */
    MI_T("Demo_Main"), /* origin */
    MI_T("Demo_Main"), /* propagator */
    NULL,
};

/* property Main.Name */
static MI_CONST MI_PropertyDecl Main_Name_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Main, Name), /* offset */
    MI_T("Demo_Main"), /* origin */
    MI_T("Demo_Main"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Main_props[] =
{
    &Main_SN_prop,
    &Main_Name_prop,
};

/* parameter Main.ChangeState(): NewState */
static MI_CONST MI_ParameterDecl Main_ChangeState_NewState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006E6508, /* code */
    MI_T("NewState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Main_ChangeState, NewState), /* offset */
};

/* parameter Main.ChangeState(): OldState */
static MI_CONST MI_ParameterDecl Main_ChangeState_OldState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F6508, /* code */
    MI_T("OldState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Main_ChangeState, OldState), /* offset */
};

/* parameter Main.ChangeState(): MIReturn */
static MI_CONST MI_ParameterDecl Main_ChangeState_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Main_ChangeState, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Main_ChangeState_params[] =
{
    &Main_ChangeState_MIReturn_param,
    &Main_ChangeState_NewState_param,
    &Main_ChangeState_OldState_param,
};

/* method Main.ChangeState() */
MI_CONST MI_MethodDecl Main_ChangeState_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0063650B, /* code */
    MI_T("ChangeState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Main_ChangeState_params, /* parameters */
    MI_COUNT(Main_ChangeState_params), /* numParameters */
    sizeof(Main_ChangeState), /* size */
    MI_UINT32, /* returnType */
    MI_T("Demo_Main"), /* origin */
    MI_T("Demo_Main"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Main_Invoke_ChangeState, /* method */
};

/* parameter Main.HelloWorld(): NewValue */
static MI_CONST MI_ParameterDecl Main_HelloWorld_NewValue_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006E6508, /* code */
    MI_T("NewValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Main_HelloWorld, NewValue), /* offset */
};

/* parameter Main.HelloWorld(): MIReturn */
static MI_CONST MI_ParameterDecl Main_HelloWorld_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Main_HelloWorld, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Main_HelloWorld_params[] =
{
    &Main_HelloWorld_MIReturn_param,
    &Main_HelloWorld_NewValue_param,
};

/* method Main.HelloWorld() */
MI_CONST MI_MethodDecl Main_HelloWorld_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0068640A, /* code */
    MI_T("HelloWorld"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Main_HelloWorld_params, /* parameters */
    MI_COUNT(Main_HelloWorld_params), /* numParameters */
    sizeof(Main_HelloWorld), /* size */
    MI_UINT32, /* returnType */
    MI_T("Demo_Main"), /* origin */
    MI_T("Demo_Main"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Main_Invoke_HelloWorld, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST Main_meths[] =
{
    &Main_ChangeState_rtti,
    &Main_HelloWorld_rtti,
};

static MI_CONST MI_ProviderFT Main_funcs =
{
  (MI_ProviderFT_Load)Main_Load,
  (MI_ProviderFT_Unload)Main_Unload,
  (MI_ProviderFT_GetInstance)Main_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Main_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Main_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Main_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Main_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Main */
MI_CONST MI_ClassDecl Main_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00646E09, /* code */
    MI_T("Demo_Main"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Main_props, /* properties */
    MI_COUNT(Main_props), /* numProperties */
    sizeof(Main), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    Main_meths, /* methods */
    MI_COUNT(Main_meths), /* numMethods */
    &schemaDecl, /* schema */
    &Main_funcs, /* functions */
};

/*
**==============================================================================
**
** AllTypes
**
**==============================================================================
*/

/* property AllTypes.id */
static MI_CONST MI_PropertyDecl AllTypes_id_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00696402, /* code */
    MI_T("id"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, id), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.refMain */
static MI_CONST MI_PropertyDecl AllTypes_refMain_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726E07, /* code */
    MI_T("refMain"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Demo_Main"), /* className */
    0, /* subscript */
    offsetof(AllTypes, refMain), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.refRef */
static MI_CONST MI_PropertyDecl AllTypes_refRef_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726606, /* code */
    MI_T("refRef"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Demo_Reference"), /* className */
    0, /* subscript */
    offsetof(AllTypes, refRef), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.boolValue */
static MI_CONST MI_PropertyDecl AllTypes_boolValue_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00626509, /* code */
    MI_T("boolValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, boolValue), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.uint8Value */
static MI_CONST MI_PropertyDecl AllTypes_uint8Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075650A, /* code */
    MI_T("uint8Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, uint8Value), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.sint8Value */
static MI_CONST MI_PropertyDecl AllTypes_sint8Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650A, /* code */
    MI_T("sint8Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, sint8Value), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.uint16Value */
static MI_CONST MI_PropertyDecl AllTypes_uint16Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075650B, /* code */
    MI_T("uint16Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, uint16Value), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.sint16Value */
static MI_CONST MI_PropertyDecl AllTypes_sint16Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650B, /* code */
    MI_T("sint16Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, sint16Value), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.uint32Value */
static MI_CONST MI_PropertyDecl AllTypes_uint32Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075650B, /* code */
    MI_T("uint32Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, uint32Value), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.sint32Value */
static MI_CONST MI_PropertyDecl AllTypes_sint32Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650B, /* code */
    MI_T("sint32Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, sint32Value), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.uint64Value */
static MI_CONST MI_PropertyDecl AllTypes_uint64Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075650B, /* code */
    MI_T("uint64Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, uint64Value), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.sint64Value */
static MI_CONST MI_PropertyDecl AllTypes_sint64Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650B, /* code */
    MI_T("sint64Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, sint64Value), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.real32Value */
static MI_CONST MI_PropertyDecl AllTypes_real32Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072650B, /* code */
    MI_T("real32Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, real32Value), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.real64Value */
static MI_CONST MI_PropertyDecl AllTypes_real64Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072650B, /* code */
    MI_T("real64Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, real64Value), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.datetimetValue */
static MI_CONST MI_PropertyDecl AllTypes_datetimetValue_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064650E, /* code */
    MI_T("datetimetValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, datetimetValue), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.stringValue */
static MI_CONST MI_PropertyDecl AllTypes_stringValue_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650B, /* code */
    MI_T("stringValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, stringValue), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.char16Value */
static MI_CONST MI_PropertyDecl AllTypes_char16Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063650B, /* code */
    MI_T("char16Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, char16Value), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* AllTypes_instanceTest_EmbeddedInstance_qual_value = MI_T("Demo_Main");

static MI_CONST MI_Qualifier AllTypes_instanceTest_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &AllTypes_instanceTest_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST AllTypes_instanceTest_quals[] =
{
    &AllTypes_instanceTest_EmbeddedInstance_qual,
};

/* property AllTypes.instanceTest */
static MI_CONST MI_PropertyDecl AllTypes_instanceTest_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069740C, /* code */
    MI_T("instanceTest"), /* name */
    AllTypes_instanceTest_quals, /* qualifiers */
    MI_COUNT(AllTypes_instanceTest_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Demo_Main"), /* className */
    0, /* subscript */
    offsetof(AllTypes, instanceTest), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.boolArray */
static MI_CONST MI_PropertyDecl AllTypes_boolArray_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00627909, /* code */
    MI_T("boolArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, boolArray), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.uint8Array */
static MI_CONST MI_PropertyDecl AllTypes_uint8Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075790A, /* code */
    MI_T("uint8Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, uint8Array), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.sint8Array */
static MI_CONST MI_PropertyDecl AllTypes_sint8Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790A, /* code */
    MI_T("sint8Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, sint8Array), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.uint16Array */
static MI_CONST MI_PropertyDecl AllTypes_uint16Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075790B, /* code */
    MI_T("uint16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, uint16Array), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.sint16Array */
static MI_CONST MI_PropertyDecl AllTypes_sint16Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790B, /* code */
    MI_T("sint16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, sint16Array), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.uint32Array */
static MI_CONST MI_PropertyDecl AllTypes_uint32Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075790B, /* code */
    MI_T("uint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, uint32Array), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.sint32Array */
static MI_CONST MI_PropertyDecl AllTypes_sint32Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790B, /* code */
    MI_T("sint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, sint32Array), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.uint64Array */
static MI_CONST MI_PropertyDecl AllTypes_uint64Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075790B, /* code */
    MI_T("uint64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, uint64Array), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.sint64Array */
static MI_CONST MI_PropertyDecl AllTypes_sint64Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790B, /* code */
    MI_T("sint64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, sint64Array), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.real32Array */
static MI_CONST MI_PropertyDecl AllTypes_real32Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072790B, /* code */
    MI_T("real32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, real32Array), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.real64Array */
static MI_CONST MI_PropertyDecl AllTypes_real64Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072790B, /* code */
    MI_T("real64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, real64Array), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.datetimeArray */
static MI_CONST MI_PropertyDecl AllTypes_datetimeArray_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064790D, /* code */
    MI_T("datetimeArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, datetimeArray), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.stringArray */
static MI_CONST MI_PropertyDecl AllTypes_stringArray_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790B, /* code */
    MI_T("stringArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, stringArray), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

/* property AllTypes.char16Array */
static MI_CONST MI_PropertyDecl AllTypes_char16Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063790B, /* code */
    MI_T("char16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(AllTypes, char16Array), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* AllTypes_instanceArrayTest_EmbeddedInstance_qual_value = MI_T("Demo_Main");

static MI_CONST MI_Qualifier AllTypes_instanceArrayTest_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &AllTypes_instanceArrayTest_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST AllTypes_instanceArrayTest_quals[] =
{
    &AllTypes_instanceArrayTest_EmbeddedInstance_qual,
};

/* property AllTypes.instanceArrayTest */
static MI_CONST MI_PropertyDecl AllTypes_instanceArrayTest_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00697411, /* code */
    MI_T("instanceArrayTest"), /* name */
    AllTypes_instanceArrayTest_quals, /* qualifiers */
    MI_COUNT(AllTypes_instanceArrayTest_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("Demo_Main"), /* className */
    0, /* subscript */
    offsetof(AllTypes, instanceArrayTest), /* offset */
    MI_T("Demo_TestWithAllTypes"), /* origin */
    MI_T("Demo_TestWithAllTypes"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST AllTypes_props[] =
{
    &AllTypes_id_prop,
    &AllTypes_refMain_prop,
    &AllTypes_refRef_prop,
    &AllTypes_boolValue_prop,
    &AllTypes_uint8Value_prop,
    &AllTypes_sint8Value_prop,
    &AllTypes_uint16Value_prop,
    &AllTypes_sint16Value_prop,
    &AllTypes_uint32Value_prop,
    &AllTypes_sint32Value_prop,
    &AllTypes_uint64Value_prop,
    &AllTypes_sint64Value_prop,
    &AllTypes_real32Value_prop,
    &AllTypes_real64Value_prop,
    &AllTypes_datetimetValue_prop,
    &AllTypes_stringValue_prop,
    &AllTypes_char16Value_prop,
    &AllTypes_instanceTest_prop,
    &AllTypes_boolArray_prop,
    &AllTypes_uint8Array_prop,
    &AllTypes_sint8Array_prop,
    &AllTypes_uint16Array_prop,
    &AllTypes_sint16Array_prop,
    &AllTypes_uint32Array_prop,
    &AllTypes_sint32Array_prop,
    &AllTypes_uint64Array_prop,
    &AllTypes_sint64Array_prop,
    &AllTypes_real32Array_prop,
    &AllTypes_real64Array_prop,
    &AllTypes_datetimeArray_prop,
    &AllTypes_stringArray_prop,
    &AllTypes_char16Array_prop,
    &AllTypes_instanceArrayTest_prop,
};

static void MI_CALL AllTypes_AssociatorInstances(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (Main_IsA(instanceName))
    {
        if (_Match(role, MI_T("refMain")) && 
            _Match(resultRole, MI_T("refRef")))
        {
            AllTypes_AssociatorInstancesrefMain(
                self, 
                context, 
                nameSpace, 
                className, 
                (Main*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (Reference_IsA(instanceName))
    {
        if (_Match(role, MI_T("refRef")) && 
            _Match(resultRole, MI_T("refMain")))
        {
            AllTypes_AssociatorInstancesrefRef(
                self, 
                context, 
                nameSpace, 
                className, 
                (Reference*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL AllTypes_ReferenceInstances(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (Main_IsA(instanceName))
    {
        if (_Match(role, MI_T("refMain")))
        {
            AllTypes_ReferenceInstancesrefMain(
                self, 
                context, 
                nameSpace, 
                className, 
                (Main*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (Reference_IsA(instanceName))
    {
        if (_Match(role, MI_T("refRef")))
        {
            AllTypes_ReferenceInstancesrefRef(
                self, 
                context, 
                nameSpace, 
                className, 
                (Reference*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT AllTypes_funcs =
{
  (MI_ProviderFT_Load)AllTypes_Load,
  (MI_ProviderFT_Unload)AllTypes_Unload,
  (MI_ProviderFT_GetInstance)AllTypes_GetInstance,
  (MI_ProviderFT_EnumerateInstances)AllTypes_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)AllTypes_CreateInstance,
  (MI_ProviderFT_ModifyInstance)AllTypes_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)AllTypes_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)AllTypes_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)AllTypes_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class AllTypes */
MI_CONST MI_ClassDecl AllTypes_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00647315, /* code */
    MI_T("Demo_TestWithAllTypes"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    AllTypes_props, /* properties */
    MI_COUNT(AllTypes_props), /* numProperties */
    sizeof(AllTypes), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &AllTypes_funcs, /* functions */
};

/*
**==============================================================================
**
** Performance
**
**==============================================================================
*/

/* property Performance.id */
static MI_CONST MI_PropertyDecl Performance_id_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00696402, /* code */
    MI_T("id"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Performance, id), /* offset */
    MI_T("Demo_Performance"), /* origin */
    MI_T("Demo_Performance"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Performance_props[] =
{
    &Performance_id_prop,
};

static MI_CONST MI_ProviderFT Performance_funcs =
{
  (MI_ProviderFT_Load)Performance_Load,
  (MI_ProviderFT_Unload)Performance_Unload,
  (MI_ProviderFT_GetInstance)Performance_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Performance_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Performance_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Performance_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Performance_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Performance */
MI_CONST MI_ClassDecl Performance_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00646510, /* code */
    MI_T("Demo_Performance"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Performance_props, /* properties */
    MI_COUNT(Performance_props), /* numProperties */
    sizeof(Performance), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Performance_funcs, /* functions */
};

/*
**==============================================================================
**
** __mi_server
**
**==============================================================================
*/

MI_Server* __mi_server;
/*
**==============================================================================
**
** Schema
**
**==============================================================================
*/

static MI_ClassDecl MI_CONST* MI_CONST classes[] =
{
    &Identifier_rtti,
    &Main_rtti,
    &Performance_rtti,
    &Reference_rtti,
    &Test_rtti,
    &AllTypes_rtti,
};

MI_SchemaDecl schemaDecl =
{
    NULL, /* qualifierDecls */
    0, /* numQualifierDecls */
    classes, /* classDecls */
    MI_COUNT(classes), /* classDecls */
};

/*
**==============================================================================
**
** MI_Server Methods
**
**==============================================================================
*/

MI_Result MI_CALL MI_Server_GetVersion(
    MI_Uint32* version){
    return __mi_server->serverFT->GetVersion(version);
}

MI_Result MI_CALL MI_Server_GetSystemName(
    const MI_Char** systemName)
{
    return __mi_server->serverFT->GetSystemName(systemName);
}

