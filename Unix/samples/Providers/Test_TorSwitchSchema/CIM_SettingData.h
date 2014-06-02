/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_SettingData_h
#define _CIM_SettingData_h

#include <MI.h>
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** CIM_SettingData [CIM_SettingData]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_SettingData /* extends CIM_ManagedElement */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_SettingData properties */
}
CIM_SettingData;

typedef struct _CIM_SettingData_Ref
{
    CIM_SettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SettingData_Ref;

typedef struct _CIM_SettingData_ConstRef
{
    MI_CONST CIM_SettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SettingData_ConstRef;

typedef struct _CIM_SettingData_Array
{
    struct _CIM_SettingData** data;
    MI_Uint32 size;
}
CIM_SettingData_Array;

typedef struct _CIM_SettingData_ConstArray
{
    struct _CIM_SettingData MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_SettingData_ConstArray;

typedef struct _CIM_SettingData_ArrayRef
{
    CIM_SettingData_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SettingData_ArrayRef;

typedef struct _CIM_SettingData_ConstArrayRef
{
    CIM_SettingData_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SettingData_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_SettingData_rtti;

MI_INLINE MI_Result MI_CALL CIM_SettingData_Construct(
    _Out_ CIM_SettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_SettingData_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_Clone(
    _In_ const CIM_SettingData* self,
    _Outptr_ CIM_SettingData** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_SettingData_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_SettingData_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_Destruct(_Inout_ CIM_SettingData* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_Delete(_Inout_ CIM_SettingData* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_Post(
    _In_ const CIM_SettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_Set_InstanceID(
    _Inout_ CIM_SettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_SetPtr_InstanceID(
    _Inout_ CIM_SettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_Clear_InstanceID(
    _Inout_ CIM_SettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_Set_Caption(
    _Inout_ CIM_SettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_SetPtr_Caption(
    _Inout_ CIM_SettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_Clear_Caption(
    _Inout_ CIM_SettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_Set_Description(
    _Inout_ CIM_SettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_SetPtr_Description(
    _Inout_ CIM_SettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_Clear_Description(
    _Inout_ CIM_SettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_Set_ElementName(
    _Inout_ CIM_SettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_SetPtr_ElementName(
    _Inout_ CIM_SettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SettingData_Clear_ElementName(
    _Inout_ CIM_SettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}


#endif /* _CIM_SettingData_h */
