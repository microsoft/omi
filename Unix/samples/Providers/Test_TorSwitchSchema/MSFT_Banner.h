/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_Banner_h
#define _MSFT_Banner_h

#include <MI.h>
#include "CIM_SettingData.h"

/*
**==============================================================================
**
** MSFT_Banner [MSFT_Banner]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _MSFT_Banner /* extends CIM_SettingData */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_SettingData properties */
    /* MSFT_Banner properties */
    MI_ConstStringField Banner;
    MI_ConstBooleanField IsEnabled;
}
MSFT_Banner;

typedef struct _MSFT_Banner_Ref
{
    MSFT_Banner* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Banner_Ref;

typedef struct _MSFT_Banner_ConstRef
{
    MI_CONST MSFT_Banner* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Banner_ConstRef;

typedef struct _MSFT_Banner_Array
{
    struct _MSFT_Banner** data;
    MI_Uint32 size;
}
MSFT_Banner_Array;

typedef struct _MSFT_Banner_ConstArray
{
    struct _MSFT_Banner MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_Banner_ConstArray;

typedef struct _MSFT_Banner_ArrayRef
{
    MSFT_Banner_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Banner_ArrayRef;

typedef struct _MSFT_Banner_ConstArrayRef
{
    MSFT_Banner_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Banner_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_Banner_rtti;

MI_INLINE MI_Result MI_CALL MSFT_Banner_Construct(
    _Out_ MSFT_Banner* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_Banner_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Clone(
    _In_ const MSFT_Banner* self,
    _Outptr_ MSFT_Banner** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_Banner_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_Banner_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Destruct(_Inout_ MSFT_Banner* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Delete(_Inout_ MSFT_Banner* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Post(
    _In_ const MSFT_Banner* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Set_InstanceID(
    _Inout_ MSFT_Banner* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_SetPtr_InstanceID(
    _Inout_ MSFT_Banner* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Clear_InstanceID(
    _Inout_ MSFT_Banner* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Set_Caption(
    _Inout_ MSFT_Banner* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_SetPtr_Caption(
    _Inout_ MSFT_Banner* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Clear_Caption(
    _Inout_ MSFT_Banner* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Set_Description(
    _Inout_ MSFT_Banner* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_SetPtr_Description(
    _Inout_ MSFT_Banner* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Clear_Description(
    _Inout_ MSFT_Banner* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Set_ElementName(
    _Inout_ MSFT_Banner* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_SetPtr_ElementName(
    _Inout_ MSFT_Banner* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Clear_ElementName(
    _Inout_ MSFT_Banner* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Set_Banner(
    _Inout_ MSFT_Banner* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_SetPtr_Banner(
    _Inout_ MSFT_Banner* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Clear_Banner(
    _Inout_ MSFT_Banner* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Set_IsEnabled(
    _Inout_ MSFT_Banner* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsEnabled)->value = x;
    ((MI_BooleanField*)&self->IsEnabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Banner_Clear_IsEnabled(
    _Inout_ MSFT_Banner* self)
{
    memset((void*)&self->IsEnabled, 0, sizeof(self->IsEnabled));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_Banner provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_Banner_Self MSFT_Banner_Self;

MI_EXTERN_C void MI_CALL MSFT_Banner_Load(
    _Outptr_result_maybenull_ MSFT_Banner_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_Banner_Unload(
    _In_opt_ MSFT_Banner_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_Banner_EnumerateInstances(
    _In_opt_ MSFT_Banner_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_Banner_GetInstance(
    _In_opt_ MSFT_Banner_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_Banner* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_Banner_CreateInstance(
    _In_opt_ MSFT_Banner_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_Banner* newInstance);

MI_EXTERN_C void MI_CALL MSFT_Banner_ModifyInstance(
    _In_opt_ MSFT_Banner_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_Banner* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_Banner_DeleteInstance(
    _In_opt_ MSFT_Banner_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_Banner* instanceName);


#endif /* _MSFT_Banner_h */
