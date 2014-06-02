/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_ElementSettingData_h
#define _CIM_ElementSettingData_h

#include <MI.h>
#include "CIM_ManagedElement.h"
#include "CIM_SettingData.h"

/*
**==============================================================================
**
** CIM_ElementSettingData [CIM_ElementSettingData]
**
** Keys:
**    ManagedElement
**    SettingData
**
**==============================================================================
*/

typedef struct _CIM_ElementSettingData
{
    MI_Instance __instance;
    /* CIM_ElementSettingData properties */
    /*KEY*/ CIM_ManagedElement_ConstRef ManagedElement;
    /*KEY*/ CIM_SettingData_ConstRef SettingData;
    MI_ConstUint16Field IsDefault;
    MI_ConstUint16Field IsCurrent;
    MI_ConstUint16Field IsNext;
    MI_ConstUint16Field IsMinimum;
    MI_ConstUint16Field IsMaximum;
    MI_ConstUint16Field IsPending;
}
CIM_ElementSettingData;

typedef struct _CIM_ElementSettingData_Ref
{
    CIM_ElementSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementSettingData_Ref;

typedef struct _CIM_ElementSettingData_ConstRef
{
    MI_CONST CIM_ElementSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementSettingData_ConstRef;

typedef struct _CIM_ElementSettingData_Array
{
    struct _CIM_ElementSettingData** data;
    MI_Uint32 size;
}
CIM_ElementSettingData_Array;

typedef struct _CIM_ElementSettingData_ConstArray
{
    struct _CIM_ElementSettingData MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_ElementSettingData_ConstArray;

typedef struct _CIM_ElementSettingData_ArrayRef
{
    CIM_ElementSettingData_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementSettingData_ArrayRef;

typedef struct _CIM_ElementSettingData_ConstArrayRef
{
    CIM_ElementSettingData_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementSettingData_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_ElementSettingData_rtti;

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Construct(
    _Out_ CIM_ElementSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_ElementSettingData_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Clone(
    _In_ const CIM_ElementSettingData* self,
    _Outptr_ CIM_ElementSettingData** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_ElementSettingData_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_ElementSettingData_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Destruct(_Inout_ CIM_ElementSettingData* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Delete(_Inout_ CIM_ElementSettingData* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Post(
    _In_ const CIM_ElementSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Set_ManagedElement(
    _Inout_ CIM_ElementSettingData* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_SetPtr_ManagedElement(
    _Inout_ CIM_ElementSettingData* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Clear_ManagedElement(
    _Inout_ CIM_ElementSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Set_SettingData(
    _Inout_ CIM_ElementSettingData* self,
    _In_ const CIM_SettingData* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_SetPtr_SettingData(
    _Inout_ CIM_ElementSettingData* self,
    _In_ const CIM_SettingData* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Clear_SettingData(
    _Inout_ CIM_ElementSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Set_IsDefault(
    _Inout_ CIM_ElementSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->IsDefault)->value = x;
    ((MI_Uint16Field*)&self->IsDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Clear_IsDefault(
    _Inout_ CIM_ElementSettingData* self)
{
    memset((void*)&self->IsDefault, 0, sizeof(self->IsDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Set_IsCurrent(
    _Inout_ CIM_ElementSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->IsCurrent)->value = x;
    ((MI_Uint16Field*)&self->IsCurrent)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Clear_IsCurrent(
    _Inout_ CIM_ElementSettingData* self)
{
    memset((void*)&self->IsCurrent, 0, sizeof(self->IsCurrent));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Set_IsNext(
    _Inout_ CIM_ElementSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->IsNext)->value = x;
    ((MI_Uint16Field*)&self->IsNext)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Clear_IsNext(
    _Inout_ CIM_ElementSettingData* self)
{
    memset((void*)&self->IsNext, 0, sizeof(self->IsNext));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Set_IsMinimum(
    _Inout_ CIM_ElementSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->IsMinimum)->value = x;
    ((MI_Uint16Field*)&self->IsMinimum)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Clear_IsMinimum(
    _Inout_ CIM_ElementSettingData* self)
{
    memset((void*)&self->IsMinimum, 0, sizeof(self->IsMinimum));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Set_IsMaximum(
    _Inout_ CIM_ElementSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->IsMaximum)->value = x;
    ((MI_Uint16Field*)&self->IsMaximum)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Clear_IsMaximum(
    _Inout_ CIM_ElementSettingData* self)
{
    memset((void*)&self->IsMaximum, 0, sizeof(self->IsMaximum));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Set_IsPending(
    _Inout_ CIM_ElementSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->IsPending)->value = x;
    ((MI_Uint16Field*)&self->IsPending)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ElementSettingData_Clear_IsPending(
    _Inout_ CIM_ElementSettingData* self)
{
    memset((void*)&self->IsPending, 0, sizeof(self->IsPending));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_ElementSettingData provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_ElementSettingData_Self CIM_ElementSettingData_Self;

MI_EXTERN_C void MI_CALL CIM_ElementSettingData_Load(
    _Outptr_result_maybenull_ CIM_ElementSettingData_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_ElementSettingData_Unload(
    _In_opt_ CIM_ElementSettingData_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_ElementSettingData_EnumerateInstances(
    _In_opt_ CIM_ElementSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ElementSettingData_GetInstance(
    _In_opt_ CIM_ElementSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ElementSettingData* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_ElementSettingData_CreateInstance(
    _In_opt_ CIM_ElementSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ElementSettingData* newInstance);

MI_EXTERN_C void MI_CALL CIM_ElementSettingData_ModifyInstance(
    _In_opt_ CIM_ElementSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ElementSettingData* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_ElementSettingData_DeleteInstance(
    _In_opt_ CIM_ElementSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ElementSettingData* instanceName);

MI_EXTERN_C void MI_CALL CIM_ElementSettingData_AssociatorInstancesManagedElement(
    _In_opt_ CIM_ElementSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ElementSettingData_AssociatorInstancesSettingData(
    _In_opt_ CIM_ElementSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SettingData* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ElementSettingData_ReferenceInstancesManagedElement(
    _In_opt_ CIM_ElementSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ElementSettingData_ReferenceInstancesSettingData(
    _In_opt_ CIM_ElementSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SettingData* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_ElementSettingData_h */
