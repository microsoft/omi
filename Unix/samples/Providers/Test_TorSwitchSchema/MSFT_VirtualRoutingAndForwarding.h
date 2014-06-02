/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_VirtualRoutingAndForwarding_h
#define _MSFT_VirtualRoutingAndForwarding_h

#include <MI.h>
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** MSFT_VirtualRoutingAndForwarding [MSFT_VirtualRoutingAndForwarding]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _MSFT_VirtualRoutingAndForwarding /* extends CIM_ManagedElement */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* MSFT_VirtualRoutingAndForwarding properties */
    MI_ConstStringField Context;
    MI_ConstBooleanField IsEnabled;
    MI_ConstStringAField Routes;
}
MSFT_VirtualRoutingAndForwarding;

typedef struct _MSFT_VirtualRoutingAndForwarding_Ref
{
    MSFT_VirtualRoutingAndForwarding* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_VirtualRoutingAndForwarding_Ref;

typedef struct _MSFT_VirtualRoutingAndForwarding_ConstRef
{
    MI_CONST MSFT_VirtualRoutingAndForwarding* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_VirtualRoutingAndForwarding_ConstRef;

typedef struct _MSFT_VirtualRoutingAndForwarding_Array
{
    struct _MSFT_VirtualRoutingAndForwarding** data;
    MI_Uint32 size;
}
MSFT_VirtualRoutingAndForwarding_Array;

typedef struct _MSFT_VirtualRoutingAndForwarding_ConstArray
{
    struct _MSFT_VirtualRoutingAndForwarding MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_VirtualRoutingAndForwarding_ConstArray;

typedef struct _MSFT_VirtualRoutingAndForwarding_ArrayRef
{
    MSFT_VirtualRoutingAndForwarding_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_VirtualRoutingAndForwarding_ArrayRef;

typedef struct _MSFT_VirtualRoutingAndForwarding_ConstArrayRef
{
    MSFT_VirtualRoutingAndForwarding_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_VirtualRoutingAndForwarding_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_VirtualRoutingAndForwarding_rtti;

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Construct(
    _Out_ MSFT_VirtualRoutingAndForwarding* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_VirtualRoutingAndForwarding_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Clone(
    _In_ const MSFT_VirtualRoutingAndForwarding* self,
    _Outptr_ MSFT_VirtualRoutingAndForwarding** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_VirtualRoutingAndForwarding_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_VirtualRoutingAndForwarding_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Destruct(_Inout_ MSFT_VirtualRoutingAndForwarding* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Delete(_Inout_ MSFT_VirtualRoutingAndForwarding* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Post(
    _In_ const MSFT_VirtualRoutingAndForwarding* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Set_InstanceID(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_SetPtr_InstanceID(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Clear_InstanceID(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Set_Caption(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_SetPtr_Caption(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Clear_Caption(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Set_Description(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_SetPtr_Description(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Clear_Description(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Set_ElementName(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_SetPtr_ElementName(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Clear_ElementName(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Set_Context(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_SetPtr_Context(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Clear_Context(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Set_IsEnabled(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsEnabled)->value = x;
    ((MI_BooleanField*)&self->IsEnabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Clear_IsEnabled(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self)
{
    memset((void*)&self->IsEnabled, 0, sizeof(self->IsEnabled));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Set_Routes(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_SetPtr_Routes(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualRoutingAndForwarding_Clear_Routes(
    _Inout_ MSFT_VirtualRoutingAndForwarding* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

/*
**==============================================================================
**
** MSFT_VirtualRoutingAndForwarding provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_VirtualRoutingAndForwarding_Self MSFT_VirtualRoutingAndForwarding_Self;

MI_EXTERN_C void MI_CALL MSFT_VirtualRoutingAndForwarding_Load(
    _Outptr_result_maybenull_ MSFT_VirtualRoutingAndForwarding_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_VirtualRoutingAndForwarding_Unload(
    _In_opt_ MSFT_VirtualRoutingAndForwarding_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_VirtualRoutingAndForwarding_EnumerateInstances(
    _In_opt_ MSFT_VirtualRoutingAndForwarding_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_VirtualRoutingAndForwarding_GetInstance(
    _In_opt_ MSFT_VirtualRoutingAndForwarding_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_VirtualRoutingAndForwarding* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_VirtualRoutingAndForwarding_CreateInstance(
    _In_opt_ MSFT_VirtualRoutingAndForwarding_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_VirtualRoutingAndForwarding* newInstance);

MI_EXTERN_C void MI_CALL MSFT_VirtualRoutingAndForwarding_ModifyInstance(
    _In_opt_ MSFT_VirtualRoutingAndForwarding_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_VirtualRoutingAndForwarding* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_VirtualRoutingAndForwarding_DeleteInstance(
    _In_opt_ MSFT_VirtualRoutingAndForwarding_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_VirtualRoutingAndForwarding* instanceName);


#endif /* _MSFT_VirtualRoutingAndForwarding_h */
