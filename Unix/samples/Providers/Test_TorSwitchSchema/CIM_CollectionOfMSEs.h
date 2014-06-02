/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_CollectionOfMSEs_h
#define _CIM_CollectionOfMSEs_h

#include <MI.h>
#include "CIM_Collection.h"

/*
**==============================================================================
**
** CIM_CollectionOfMSEs [CIM_CollectionOfMSEs]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_CollectionOfMSEs /* extends CIM_Collection */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Collection properties */
    /* CIM_CollectionOfMSEs properties */
    MI_ConstStringField CollectionID;
}
CIM_CollectionOfMSEs;

typedef struct _CIM_CollectionOfMSEs_Ref
{
    CIM_CollectionOfMSEs* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_CollectionOfMSEs_Ref;

typedef struct _CIM_CollectionOfMSEs_ConstRef
{
    MI_CONST CIM_CollectionOfMSEs* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_CollectionOfMSEs_ConstRef;

typedef struct _CIM_CollectionOfMSEs_Array
{
    struct _CIM_CollectionOfMSEs** data;
    MI_Uint32 size;
}
CIM_CollectionOfMSEs_Array;

typedef struct _CIM_CollectionOfMSEs_ConstArray
{
    struct _CIM_CollectionOfMSEs MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_CollectionOfMSEs_ConstArray;

typedef struct _CIM_CollectionOfMSEs_ArrayRef
{
    CIM_CollectionOfMSEs_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_CollectionOfMSEs_ArrayRef;

typedef struct _CIM_CollectionOfMSEs_ConstArrayRef
{
    CIM_CollectionOfMSEs_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_CollectionOfMSEs_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_CollectionOfMSEs_rtti;

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_Construct(
    _Out_ CIM_CollectionOfMSEs* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_CollectionOfMSEs_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_Clone(
    _In_ const CIM_CollectionOfMSEs* self,
    _Outptr_ CIM_CollectionOfMSEs** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_CollectionOfMSEs_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_CollectionOfMSEs_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_Destruct(_Inout_ CIM_CollectionOfMSEs* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_Delete(_Inout_ CIM_CollectionOfMSEs* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_Post(
    _In_ const CIM_CollectionOfMSEs* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_Set_InstanceID(
    _Inout_ CIM_CollectionOfMSEs* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_SetPtr_InstanceID(
    _Inout_ CIM_CollectionOfMSEs* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_Clear_InstanceID(
    _Inout_ CIM_CollectionOfMSEs* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_Set_Caption(
    _Inout_ CIM_CollectionOfMSEs* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_SetPtr_Caption(
    _Inout_ CIM_CollectionOfMSEs* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_Clear_Caption(
    _Inout_ CIM_CollectionOfMSEs* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_Set_Description(
    _Inout_ CIM_CollectionOfMSEs* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_SetPtr_Description(
    _Inout_ CIM_CollectionOfMSEs* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_Clear_Description(
    _Inout_ CIM_CollectionOfMSEs* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_Set_ElementName(
    _Inout_ CIM_CollectionOfMSEs* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_SetPtr_ElementName(
    _Inout_ CIM_CollectionOfMSEs* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_Clear_ElementName(
    _Inout_ CIM_CollectionOfMSEs* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_Set_CollectionID(
    _Inout_ CIM_CollectionOfMSEs* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_SetPtr_CollectionID(
    _Inout_ CIM_CollectionOfMSEs* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_CollectionOfMSEs_Clear_CollectionID(
    _Inout_ CIM_CollectionOfMSEs* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}


#endif /* _CIM_CollectionOfMSEs_h */
