/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_ConnectivityCollection_h
#define _CIM_ConnectivityCollection_h

#include <MI.h>
#include "CIM_SystemSpecificCollection.h"

/*
**==============================================================================
**
** CIM_ConnectivityCollection [CIM_ConnectivityCollection]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_ConnectivityCollection /* extends CIM_SystemSpecificCollection */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Collection properties */
    /* CIM_SystemSpecificCollection properties */
    /* CIM_ConnectivityCollection properties */
    MI_ConstUint16Field ConnectivityStatus;
}
CIM_ConnectivityCollection;

typedef struct _CIM_ConnectivityCollection_Ref
{
    CIM_ConnectivityCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConnectivityCollection_Ref;

typedef struct _CIM_ConnectivityCollection_ConstRef
{
    MI_CONST CIM_ConnectivityCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConnectivityCollection_ConstRef;

typedef struct _CIM_ConnectivityCollection_Array
{
    struct _CIM_ConnectivityCollection** data;
    MI_Uint32 size;
}
CIM_ConnectivityCollection_Array;

typedef struct _CIM_ConnectivityCollection_ConstArray
{
    struct _CIM_ConnectivityCollection MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_ConnectivityCollection_ConstArray;

typedef struct _CIM_ConnectivityCollection_ArrayRef
{
    CIM_ConnectivityCollection_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConnectivityCollection_ArrayRef;

typedef struct _CIM_ConnectivityCollection_ConstArrayRef
{
    CIM_ConnectivityCollection_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConnectivityCollection_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_ConnectivityCollection_rtti;

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_Construct(
    CIM_ConnectivityCollection* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_ConnectivityCollection_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_Clone(
    const CIM_ConnectivityCollection* self,
    CIM_ConnectivityCollection** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_ConnectivityCollection_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_ConnectivityCollection_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_Destruct(CIM_ConnectivityCollection* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_Delete(CIM_ConnectivityCollection* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_Post(
    const CIM_ConnectivityCollection* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_Set_InstanceID(
    CIM_ConnectivityCollection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_SetPtr_InstanceID(
    CIM_ConnectivityCollection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_Clear_InstanceID(
    CIM_ConnectivityCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_Set_Caption(
    CIM_ConnectivityCollection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_SetPtr_Caption(
    CIM_ConnectivityCollection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_Clear_Caption(
    CIM_ConnectivityCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_Set_Description(
    CIM_ConnectivityCollection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_SetPtr_Description(
    CIM_ConnectivityCollection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_Clear_Description(
    CIM_ConnectivityCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_Set_ElementName(
    CIM_ConnectivityCollection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_SetPtr_ElementName(
    CIM_ConnectivityCollection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_Clear_ElementName(
    CIM_ConnectivityCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_Set_ConnectivityStatus(
    CIM_ConnectivityCollection* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ConnectivityStatus)->value = x;
    ((MI_Uint16Field*)&self->ConnectivityStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConnectivityCollection_Clear_ConnectivityStatus(
    CIM_ConnectivityCollection* self)
{
    memset((void*)&self->ConnectivityStatus, 0, sizeof(self->ConnectivityStatus));
    return MI_RESULT_OK;
}


#endif /* _CIM_ConnectivityCollection_h */
