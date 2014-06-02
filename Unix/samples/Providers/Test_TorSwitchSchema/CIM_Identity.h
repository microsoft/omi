/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_Identity_h
#define _CIM_Identity_h

#include <MI.h>
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** CIM_Identity [CIM_Identity]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_Identity /* extends CIM_ManagedElement */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Identity properties */
    MI_ConstBooleanField CurrentlyAuthenticated;
}
CIM_Identity;

typedef struct _CIM_Identity_Ref
{
    CIM_Identity* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Identity_Ref;

typedef struct _CIM_Identity_ConstRef
{
    MI_CONST CIM_Identity* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Identity_ConstRef;

typedef struct _CIM_Identity_Array
{
    struct _CIM_Identity** data;
    MI_Uint32 size;
}
CIM_Identity_Array;

typedef struct _CIM_Identity_ConstArray
{
    struct _CIM_Identity MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_Identity_ConstArray;

typedef struct _CIM_Identity_ArrayRef
{
    CIM_Identity_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Identity_ArrayRef;

typedef struct _CIM_Identity_ConstArrayRef
{
    CIM_Identity_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Identity_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_Identity_rtti;

MI_INLINE MI_Result MI_CALL CIM_Identity_Construct(
    _Out_ CIM_Identity* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_Identity_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_Clone(
    _In_ const CIM_Identity* self,
    _Outptr_ CIM_Identity** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_Identity_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_Identity_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_Identity_Destruct(_Inout_ CIM_Identity* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_Delete(_Inout_ CIM_Identity* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_Post(
    _In_ const CIM_Identity* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_Set_InstanceID(
    _Inout_ CIM_Identity* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_SetPtr_InstanceID(
    _Inout_ CIM_Identity* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_Clear_InstanceID(
    _Inout_ CIM_Identity* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_Set_Caption(
    _Inout_ CIM_Identity* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_SetPtr_Caption(
    _Inout_ CIM_Identity* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_Clear_Caption(
    _Inout_ CIM_Identity* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_Set_Description(
    _Inout_ CIM_Identity* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_SetPtr_Description(
    _Inout_ CIM_Identity* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_Clear_Description(
    _Inout_ CIM_Identity* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_Set_ElementName(
    _Inout_ CIM_Identity* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_SetPtr_ElementName(
    _Inout_ CIM_Identity* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_Clear_ElementName(
    _Inout_ CIM_Identity* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_Identity_Set_CurrentlyAuthenticated(
    _Inout_ CIM_Identity* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->CurrentlyAuthenticated)->value = x;
    ((MI_BooleanField*)&self->CurrentlyAuthenticated)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Identity_Clear_CurrentlyAuthenticated(
    _Inout_ CIM_Identity* self)
{
    memset((void*)&self->CurrentlyAuthenticated, 0, sizeof(self->CurrentlyAuthenticated));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_Identity provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_Identity_Self CIM_Identity_Self;

MI_EXTERN_C void MI_CALL CIM_Identity_Load(
    _Outptr_result_maybenull_ CIM_Identity_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_Identity_Unload(
    _In_opt_ CIM_Identity_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_Identity_EnumerateInstances(
    _In_opt_ CIM_Identity_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_Identity_GetInstance(
    _In_opt_ CIM_Identity_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Identity* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_Identity_CreateInstance(
    _In_opt_ CIM_Identity_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Identity* newInstance);

MI_EXTERN_C void MI_CALL CIM_Identity_ModifyInstance(
    _In_opt_ CIM_Identity_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Identity* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_Identity_DeleteInstance(
    _In_opt_ CIM_Identity_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Identity* instanceName);


#endif /* _CIM_Identity_h */
