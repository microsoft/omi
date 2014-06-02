/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ClassHierarchyTest_h
#define _ClassHierarchyTest_h

#include <MI.h>

/*
**==============================================================================
**
** ClassHierarchyTest [ClassHierarchyTest]
**
** Keys:
**    TestName
**
**==============================================================================
*/

typedef struct _ClassHierarchyTest
{
    MI_Instance __instance;
    /* ClassHierarchyTest properties */
    /*KEY*/ MI_ConstStringField TestName;
    MI_ConstReferenceField TestInstance;
}
ClassHierarchyTest;

typedef struct _ClassHierarchyTest_Ref
{
    ClassHierarchyTest* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ClassHierarchyTest_Ref;

typedef struct _ClassHierarchyTest_ConstRef
{
    MI_CONST ClassHierarchyTest* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ClassHierarchyTest_ConstRef;

typedef struct _ClassHierarchyTest_Array
{
    struct _ClassHierarchyTest** data;
    MI_Uint32 size;
}
ClassHierarchyTest_Array;

typedef struct _ClassHierarchyTest_ConstArray
{
    struct _ClassHierarchyTest MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ClassHierarchyTest_ConstArray;

typedef struct _ClassHierarchyTest_ArrayRef
{
    ClassHierarchyTest_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ClassHierarchyTest_ArrayRef;

typedef struct _ClassHierarchyTest_ConstArrayRef
{
    ClassHierarchyTest_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ClassHierarchyTest_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ClassHierarchyTest_rtti;

MI_INLINE MI_Result MI_CALL ClassHierarchyTest_Construct(
    _Out_ ClassHierarchyTest* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &ClassHierarchyTest_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ClassHierarchyTest_Clone(
    _In_ const ClassHierarchyTest* self,
    _Outptr_ ClassHierarchyTest** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ClassHierarchyTest_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ClassHierarchyTest_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ClassHierarchyTest_Destruct(_Inout_ ClassHierarchyTest* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ClassHierarchyTest_Delete(_Inout_ ClassHierarchyTest* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ClassHierarchyTest_Post(
    _In_ const ClassHierarchyTest* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ClassHierarchyTest_Set_TestName(
    _Inout_ ClassHierarchyTest* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ClassHierarchyTest_SetPtr_TestName(
    _Inout_ ClassHierarchyTest* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ClassHierarchyTest_Clear_TestName(
    _Inout_ ClassHierarchyTest* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ClassHierarchyTest_Set_TestInstance(
    _Inout_ ClassHierarchyTest* self,
    _In_ const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL ClassHierarchyTest_SetPtr_TestInstance(
    _Inout_ ClassHierarchyTest* self,
    _In_ const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ClassHierarchyTest_Clear_TestInstance(
    _Inout_ ClassHierarchyTest* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** ClassHierarchyTest provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ClassHierarchyTest_Self ClassHierarchyTest_Self;

MI_EXTERN_C void MI_CALL ClassHierarchyTest_Load(
    _Outptr_result_maybenull_ ClassHierarchyTest_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL ClassHierarchyTest_Unload(
    _In_opt_ ClassHierarchyTest_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL ClassHierarchyTest_EnumerateInstances(
    _In_opt_ ClassHierarchyTest_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ClassHierarchyTest_GetInstance(
    _In_opt_ ClassHierarchyTest_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ClassHierarchyTest* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ClassHierarchyTest_CreateInstance(
    _In_opt_ ClassHierarchyTest_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ClassHierarchyTest* newInstance);

MI_EXTERN_C void MI_CALL ClassHierarchyTest_ModifyInstance(
    _In_opt_ ClassHierarchyTest_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ClassHierarchyTest* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ClassHierarchyTest_DeleteInstance(
    _In_opt_ ClassHierarchyTest_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ClassHierarchyTest* instanceName);


#endif /* _ClassHierarchyTest_h */
