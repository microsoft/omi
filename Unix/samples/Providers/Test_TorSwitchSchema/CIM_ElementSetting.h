/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_ElementSetting_h
#define _CIM_ElementSetting_h

#include <MI.h>
#include "CIM_ManagedSystemElement.h"
#include "CIM_Setting.h"

/*
**==============================================================================
**
** CIM_ElementSetting [CIM_ElementSetting]
**
** Keys:
**    Element
**    Setting
**
**==============================================================================
*/

typedef struct _CIM_ElementSetting
{
    MI_Instance __instance;
    /* CIM_ElementSetting properties */
    /*KEY*/ CIM_ManagedSystemElement_ConstRef Element;
    /*KEY*/ CIM_Setting_ConstRef Setting;
}
CIM_ElementSetting;

typedef struct _CIM_ElementSetting_Ref
{
    CIM_ElementSetting* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementSetting_Ref;

typedef struct _CIM_ElementSetting_ConstRef
{
    MI_CONST CIM_ElementSetting* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementSetting_ConstRef;

typedef struct _CIM_ElementSetting_Array
{
    struct _CIM_ElementSetting** data;
    MI_Uint32 size;
}
CIM_ElementSetting_Array;

typedef struct _CIM_ElementSetting_ConstArray
{
    struct _CIM_ElementSetting MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_ElementSetting_ConstArray;

typedef struct _CIM_ElementSetting_ArrayRef
{
    CIM_ElementSetting_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementSetting_ArrayRef;

typedef struct _CIM_ElementSetting_ConstArrayRef
{
    CIM_ElementSetting_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementSetting_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_ElementSetting_rtti;

MI_INLINE MI_Result MI_CALL CIM_ElementSetting_Construct(
    _Out_ CIM_ElementSetting* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_ElementSetting_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSetting_Clone(
    _In_ const CIM_ElementSetting* self,
    _Outptr_ CIM_ElementSetting** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_ElementSetting_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_ElementSetting_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_ElementSetting_Destruct(_Inout_ CIM_ElementSetting* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSetting_Delete(_Inout_ CIM_ElementSetting* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSetting_Post(
    _In_ const CIM_ElementSetting* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSetting_Set_Element(
    _Inout_ CIM_ElementSetting* self,
    _In_ const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSetting_SetPtr_Element(
    _Inout_ CIM_ElementSetting* self,
    _In_ const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSetting_Clear_Element(
    _Inout_ CIM_ElementSetting* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSetting_Set_Setting(
    _Inout_ CIM_ElementSetting* self,
    _In_ const CIM_Setting* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSetting_SetPtr_Setting(
    _Inout_ CIM_ElementSetting* self,
    _In_ const CIM_Setting* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ElementSetting_Clear_Setting(
    _Inout_ CIM_ElementSetting* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_ElementSetting provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_ElementSetting_Self CIM_ElementSetting_Self;

MI_EXTERN_C void MI_CALL CIM_ElementSetting_Load(
    _Outptr_result_maybenull_ CIM_ElementSetting_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_ElementSetting_Unload(
    _In_opt_ CIM_ElementSetting_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_ElementSetting_EnumerateInstances(
    _In_opt_ CIM_ElementSetting_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ElementSetting_GetInstance(
    _In_opt_ CIM_ElementSetting_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ElementSetting* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_ElementSetting_CreateInstance(
    _In_opt_ CIM_ElementSetting_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ElementSetting* newInstance);

MI_EXTERN_C void MI_CALL CIM_ElementSetting_ModifyInstance(
    _In_opt_ CIM_ElementSetting_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ElementSetting* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_ElementSetting_DeleteInstance(
    _In_opt_ CIM_ElementSetting_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ElementSetting* instanceName);

MI_EXTERN_C void MI_CALL CIM_ElementSetting_AssociatorInstancesElement(
    _In_opt_ CIM_ElementSetting_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedSystemElement* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ElementSetting_AssociatorInstancesSetting(
    _In_opt_ CIM_ElementSetting_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Setting* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ElementSetting_ReferenceInstancesElement(
    _In_opt_ CIM_ElementSetting_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedSystemElement* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ElementSetting_ReferenceInstancesSetting(
    _In_opt_ CIM_ElementSetting_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Setting* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_ElementSetting_h */
