/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _TestClass_ForEmbedded_h
#define _TestClass_ForEmbedded_h

#include <MI.h>

/*
**==============================================================================
**
** TestClass_ForEmbedded [TestClass_ForEmbedded]
**
** Keys:
**    embeddedStringValue
**
**==============================================================================
*/

typedef struct _TestClass_ForEmbedded
{
    MI_Instance __instance;
    /* TestClass_ForEmbedded properties */
    /*KEY*/ MI_ConstStringField embeddedStringValue;
}
TestClass_ForEmbedded;

typedef struct _TestClass_ForEmbedded_Ref
{
    TestClass_ForEmbedded* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_ForEmbedded_Ref;

typedef struct _TestClass_ForEmbedded_ConstRef
{
    MI_CONST TestClass_ForEmbedded* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_ForEmbedded_ConstRef;

typedef struct _TestClass_ForEmbedded_Array
{
    struct _TestClass_ForEmbedded** data;
    MI_Uint32 size;
}
TestClass_ForEmbedded_Array;

typedef struct _TestClass_ForEmbedded_ConstArray
{
    struct _TestClass_ForEmbedded MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
TestClass_ForEmbedded_ConstArray;

typedef struct _TestClass_ForEmbedded_ArrayRef
{
    TestClass_ForEmbedded_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_ForEmbedded_ArrayRef;

typedef struct _TestClass_ForEmbedded_ConstArrayRef
{
    TestClass_ForEmbedded_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_ForEmbedded_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl TestClass_ForEmbedded_rtti;

MI_INLINE MI_Result MI_CALL TestClass_ForEmbedded_Construct(
    _Inout_ TestClass_ForEmbedded* self,
    _In_ MI_Context* context)
{
    return MI_ConstructInstance(context, &TestClass_ForEmbedded_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_ForEmbedded_Clone(
    _In_ const TestClass_ForEmbedded* self,
    _Outptr_ TestClass_ForEmbedded** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL TestClass_ForEmbedded_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &TestClass_ForEmbedded_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL TestClass_ForEmbedded_Destruct(_Inout_ TestClass_ForEmbedded* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_ForEmbedded_Delete(_Inout_ TestClass_ForEmbedded* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_ForEmbedded_Post(
    _In_ const TestClass_ForEmbedded* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_ForEmbedded_Set_embeddedStringValue(
    _Inout_ TestClass_ForEmbedded* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_ForEmbedded_SetPtr_embeddedStringValue(
    _Inout_ TestClass_ForEmbedded* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_ForEmbedded_Clear_embeddedStringValue(
    _Inout_ TestClass_ForEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** TestClass_ForEmbedded provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _TestClass_ForEmbedded_Self TestClass_ForEmbedded_Self;

MI_EXTERN_C void MI_CALL TestClass_ForEmbedded_Load(
    _Outptr_result_maybenull_ TestClass_ForEmbedded_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL TestClass_ForEmbedded_Unload(
    _In_opt_ TestClass_ForEmbedded_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL TestClass_ForEmbedded_EnumerateInstances(
    _In_opt_ TestClass_ForEmbedded_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL TestClass_ForEmbedded_GetInstance(
    _In_opt_ TestClass_ForEmbedded_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TestClass_ForEmbedded* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL TestClass_ForEmbedded_CreateInstance(
    _In_opt_ TestClass_ForEmbedded_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TestClass_ForEmbedded* newInstance);

MI_EXTERN_C void MI_CALL TestClass_ForEmbedded_ModifyInstance(
    _In_opt_ TestClass_ForEmbedded_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TestClass_ForEmbedded* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL TestClass_ForEmbedded_DeleteInstance(
    _In_opt_ TestClass_ForEmbedded_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TestClass_ForEmbedded* instanceName);


#endif /* _TestClass_ForEmbedded_h */
