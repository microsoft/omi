/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_ElementCapabilities_h
#define _ABC_ElementCapabilities_h

#include <MI.h>
#include "CIM_ElementCapabilities.h"
#include "ABC_Fan.h"
#include "ABC_EnabledLogicalElementCapabilities.h"

/*
**==============================================================================
**
** ABC_ElementCapabilities [ABC_ElementCapabilities]
**
** Keys:
**    ManagedElement
**    Capabilities
**
**==============================================================================
*/

typedef struct _ABC_ElementCapabilities /* extends CIM_ElementCapabilities */
{
    MI_Instance __instance;
    /* CIM_ElementCapabilities properties */
    /*KEY*/ ABC_Fan_ConstRef ManagedElement;
    /*KEY*/ ABC_EnabledLogicalElementCapabilities_ConstRef Capabilities;
    MI_ConstUint16AField Characteristics;
    /* ABC_ElementCapabilities properties */
}
ABC_ElementCapabilities;

typedef struct _ABC_ElementCapabilities_Ref
{
    ABC_ElementCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ElementCapabilities_Ref;

typedef struct _ABC_ElementCapabilities_ConstRef
{
    MI_CONST ABC_ElementCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ElementCapabilities_ConstRef;

typedef struct _ABC_ElementCapabilities_Array
{
    struct _ABC_ElementCapabilities** data;
    MI_Uint32 size;
}
ABC_ElementCapabilities_Array;

typedef struct _ABC_ElementCapabilities_ConstArray
{
    struct _ABC_ElementCapabilities MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_ElementCapabilities_ConstArray;

typedef struct _ABC_ElementCapabilities_ArrayRef
{
    ABC_ElementCapabilities_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ElementCapabilities_ArrayRef;

typedef struct _ABC_ElementCapabilities_ConstArrayRef
{
    ABC_ElementCapabilities_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ElementCapabilities_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_ElementCapabilities_rtti;

MI_INLINE MI_Result MI_CALL ABC_ElementCapabilities_Construct(
    ABC_ElementCapabilities* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_ElementCapabilities_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ElementCapabilities_Clone(
    const ABC_ElementCapabilities* self,
    ABC_ElementCapabilities** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_ElementCapabilities_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_ElementCapabilities_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_ElementCapabilities_Destruct(ABC_ElementCapabilities* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ElementCapabilities_Delete(ABC_ElementCapabilities* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ElementCapabilities_Post(
    const ABC_ElementCapabilities* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ElementCapabilities_Set_ManagedElement(
    ABC_ElementCapabilities* self,
    const ABC_Fan* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ElementCapabilities_SetPtr_ManagedElement(
    ABC_ElementCapabilities* self,
    const ABC_Fan* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ElementCapabilities_Clear_ManagedElement(
    ABC_ElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ElementCapabilities_Set_Capabilities(
    ABC_ElementCapabilities* self,
    const ABC_EnabledLogicalElementCapabilities* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ElementCapabilities_SetPtr_Capabilities(
    ABC_ElementCapabilities* self,
    const ABC_EnabledLogicalElementCapabilities* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ElementCapabilities_Clear_Capabilities(
    ABC_ElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_ElementCapabilities_Set_Characteristics(
    ABC_ElementCapabilities* self,
    const MI_Uint16* data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL ABC_ElementCapabilities_SetPtr_Characteristics(
    ABC_ElementCapabilities* self,
    const MI_Uint16* data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL ABC_ElementCapabilities_Clear_Characteristics(
    ABC_ElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** ABC_ElementCapabilities provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_ElementCapabilities_Self ABC_ElementCapabilities_Self;

MI_EXTERN_C void MI_CALL ABC_ElementCapabilities_Load(
    ABC_ElementCapabilities_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_ElementCapabilities_Unload(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_ElementCapabilities_EnumerateInstances(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_ElementCapabilities_GetInstance(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementCapabilities* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_ElementCapabilities_CreateInstance(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementCapabilities* newInstance);

MI_EXTERN_C void MI_CALL ABC_ElementCapabilities_ModifyInstance(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementCapabilities* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_ElementCapabilities_DeleteInstance(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementCapabilities* instanceName);

MI_EXTERN_C void MI_CALL ABC_ElementCapabilities_AssociatorInstancesManagedElement(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Fan* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_ElementCapabilities_AssociatorInstancesCapabilities(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EnabledLogicalElementCapabilities* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_ElementCapabilities_ReferenceInstancesManagedElement(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Fan* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_ElementCapabilities_ReferenceInstancesCapabilities(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EnabledLogicalElementCapabilities* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _ABC_ElementCapabilities_h */
