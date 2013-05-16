/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _OMI_ACLAppliesToElement_h
#define _OMI_ACLAppliesToElement_h

#include <MI.h>
#include "MSFT_ACLAppliesToElement.h"
#include "OMI_ACL.h"
#include "OMI_EthernetPort.h"

/*
**==============================================================================
**
** OMI_ACLAppliesToElement [OMI_ACLAppliesToElement]
**
** Keys:
**    PolicySet
**    ManagedElement
**
**==============================================================================
*/

typedef struct _OMI_ACLAppliesToElement /* extends MSFT_ACLAppliesToElement */
{
    MI_Instance __instance;
    /* CIM_PolicySetAppliesToElement properties */
    /*KEY*/ OMI_ACL_ConstRef PolicySet;
    /*KEY*/ OMI_EthernetPort_ConstRef ManagedElement;
    /* MSFT_ACLAppliesToElement properties */
    MI_ConstUint16Field Direction;
    /* OMI_ACLAppliesToElement properties */
}
OMI_ACLAppliesToElement;

typedef struct _OMI_ACLAppliesToElement_Ref
{
    OMI_ACLAppliesToElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ACLAppliesToElement_Ref;

typedef struct _OMI_ACLAppliesToElement_ConstRef
{
    MI_CONST OMI_ACLAppliesToElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ACLAppliesToElement_ConstRef;

typedef struct _OMI_ACLAppliesToElement_Array
{
    struct _OMI_ACLAppliesToElement** data;
    MI_Uint32 size;
}
OMI_ACLAppliesToElement_Array;

typedef struct _OMI_ACLAppliesToElement_ConstArray
{
    struct _OMI_ACLAppliesToElement MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
OMI_ACLAppliesToElement_ConstArray;

typedef struct _OMI_ACLAppliesToElement_ArrayRef
{
    OMI_ACLAppliesToElement_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ACLAppliesToElement_ArrayRef;

typedef struct _OMI_ACLAppliesToElement_ConstArrayRef
{
    OMI_ACLAppliesToElement_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ACLAppliesToElement_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl OMI_ACLAppliesToElement_rtti;

MI_INLINE MI_Result MI_CALL OMI_ACLAppliesToElement_Construct(
    OMI_ACLAppliesToElement* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &OMI_ACLAppliesToElement_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ACLAppliesToElement_Clone(
    const OMI_ACLAppliesToElement* self,
    OMI_ACLAppliesToElement** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL OMI_ACLAppliesToElement_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &OMI_ACLAppliesToElement_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL OMI_ACLAppliesToElement_Destruct(OMI_ACLAppliesToElement* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ACLAppliesToElement_Delete(OMI_ACLAppliesToElement* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ACLAppliesToElement_Post(
    const OMI_ACLAppliesToElement* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ACLAppliesToElement_Set_PolicySet(
    OMI_ACLAppliesToElement* self,
    const OMI_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ACLAppliesToElement_SetPtr_PolicySet(
    OMI_ACLAppliesToElement* self,
    const OMI_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ACLAppliesToElement_Clear_PolicySet(
    OMI_ACLAppliesToElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ACLAppliesToElement_Set_ManagedElement(
    OMI_ACLAppliesToElement* self,
    const OMI_EthernetPort* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ACLAppliesToElement_SetPtr_ManagedElement(
    OMI_ACLAppliesToElement* self,
    const OMI_EthernetPort* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ACLAppliesToElement_Clear_ManagedElement(
    OMI_ACLAppliesToElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_ACLAppliesToElement_Set_Direction(
    OMI_ACLAppliesToElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Direction)->value = x;
    ((MI_Uint16Field*)&self->Direction)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACLAppliesToElement_Clear_Direction(
    OMI_ACLAppliesToElement* self)
{
    memset((void*)&self->Direction, 0, sizeof(self->Direction));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_ACLAppliesToElement provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _OMI_ACLAppliesToElement_Self OMI_ACLAppliesToElement_Self;

MI_EXTERN_C void MI_CALL OMI_ACLAppliesToElement_Load(
    OMI_ACLAppliesToElement_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_ACLAppliesToElement_Unload(
    OMI_ACLAppliesToElement_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_ACLAppliesToElement_EnumerateInstances(
    OMI_ACLAppliesToElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL OMI_ACLAppliesToElement_GetInstance(
    OMI_ACLAppliesToElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_ACLAppliesToElement* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_ACLAppliesToElement_CreateInstance(
    OMI_ACLAppliesToElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_ACLAppliesToElement* newInstance);

MI_EXTERN_C void MI_CALL OMI_ACLAppliesToElement_ModifyInstance(
    OMI_ACLAppliesToElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_ACLAppliesToElement* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_ACLAppliesToElement_DeleteInstance(
    OMI_ACLAppliesToElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_ACLAppliesToElement* instanceName);

MI_EXTERN_C void MI_CALL OMI_ACLAppliesToElement_AssociatorInstancesPolicySet(
    OMI_ACLAppliesToElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_ACL* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL OMI_ACLAppliesToElement_AssociatorInstancesManagedElement(
    OMI_ACLAppliesToElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_EthernetPort* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL OMI_ACLAppliesToElement_ReferenceInstancesPolicySet(
    OMI_ACLAppliesToElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_ACL* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL OMI_ACLAppliesToElement_ReferenceInstancesManagedElement(
    OMI_ACLAppliesToElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_EthernetPort* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _OMI_ACLAppliesToElement_h */
