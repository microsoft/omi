/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_ElementCapabilities_h
#define _CIM_ElementCapabilities_h

#include <MI.h>
#include "CIM_ManagedElement.h"
#include "CIM_Capabilities.h"

/*
**==============================================================================
**
** CIM_ElementCapabilities [CIM_ElementCapabilities]
**
** Keys:
**    ManagedElement
**    Capabilities
**
**==============================================================================
*/

typedef struct _CIM_ElementCapabilities
{
    MI_Instance __instance;
    /* CIM_ElementCapabilities properties */
    /*KEY*/ CIM_ManagedElement_ConstRef ManagedElement;
    /*KEY*/ CIM_Capabilities_ConstRef Capabilities;
    MI_ConstUint16AField Characteristics;
}
CIM_ElementCapabilities;

typedef struct _CIM_ElementCapabilities_Ref
{
    CIM_ElementCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementCapabilities_Ref;

typedef struct _CIM_ElementCapabilities_ConstRef
{
    MI_CONST CIM_ElementCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementCapabilities_ConstRef;

typedef struct _CIM_ElementCapabilities_Array
{
    struct _CIM_ElementCapabilities** data;
    MI_Uint32 size;
}
CIM_ElementCapabilities_Array;

typedef struct _CIM_ElementCapabilities_ConstArray
{
    struct _CIM_ElementCapabilities MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_ElementCapabilities_ConstArray;

typedef struct _CIM_ElementCapabilities_ArrayRef
{
    CIM_ElementCapabilities_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementCapabilities_ArrayRef;

typedef struct _CIM_ElementCapabilities_ConstArrayRef
{
    CIM_ElementCapabilities_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementCapabilities_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_ElementCapabilities_rtti;

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Construct(
    _Out_ CIM_ElementCapabilities* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_ElementCapabilities_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Clone(
    _In_ const CIM_ElementCapabilities* self,
    _Outptr_ CIM_ElementCapabilities** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_ElementCapabilities_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_ElementCapabilities_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Destruct(_Inout_ CIM_ElementCapabilities* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Delete(_Inout_ CIM_ElementCapabilities* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Post(
    _In_ const CIM_ElementCapabilities* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Set_ManagedElement(
    _Inout_ CIM_ElementCapabilities* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_SetPtr_ManagedElement(
    _Inout_ CIM_ElementCapabilities* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Clear_ManagedElement(
    _Inout_ CIM_ElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Set_Capabilities(
    _Inout_ CIM_ElementCapabilities* self,
    _In_ const CIM_Capabilities* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_SetPtr_Capabilities(
    _Inout_ CIM_ElementCapabilities* self,
    _In_ const CIM_Capabilities* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Clear_Capabilities(
    _Inout_ CIM_ElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Set_Characteristics(
    _Inout_ CIM_ElementCapabilities* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_SetPtr_Characteristics(
    _Inout_ CIM_ElementCapabilities* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Clear_Characteristics(
    _Inout_ CIM_ElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** CIM_ElementCapabilities provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_ElementCapabilities_Self CIM_ElementCapabilities_Self;

MI_EXTERN_C void MI_CALL CIM_ElementCapabilities_Load(
    _Outptr_result_maybenull_ CIM_ElementCapabilities_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_ElementCapabilities_Unload(
    _In_opt_ CIM_ElementCapabilities_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_ElementCapabilities_EnumerateInstances(
    _In_opt_ CIM_ElementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ElementCapabilities_GetInstance(
    _In_opt_ CIM_ElementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ElementCapabilities* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_ElementCapabilities_CreateInstance(
    _In_opt_ CIM_ElementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ElementCapabilities* newInstance);

MI_EXTERN_C void MI_CALL CIM_ElementCapabilities_ModifyInstance(
    _In_opt_ CIM_ElementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ElementCapabilities* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_ElementCapabilities_DeleteInstance(
    _In_opt_ CIM_ElementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ElementCapabilities* instanceName);

MI_EXTERN_C void MI_CALL CIM_ElementCapabilities_AssociatorInstancesManagedElement(
    _In_opt_ CIM_ElementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ElementCapabilities_AssociatorInstancesCapabilities(
    _In_opt_ CIM_ElementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Capabilities* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ElementCapabilities_ReferenceInstancesManagedElement(
    _In_opt_ CIM_ElementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ElementCapabilities_ReferenceInstancesCapabilities(
    _In_opt_ CIM_ElementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Capabilities* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_ElementCapabilities_h */
