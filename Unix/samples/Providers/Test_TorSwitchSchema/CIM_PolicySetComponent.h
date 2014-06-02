/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_PolicySetComponent_h
#define _CIM_PolicySetComponent_h

#include <MI.h>
#include "CIM_PolicyComponent.h"
#include "CIM_PolicySet.h"

/*
**==============================================================================
**
** CIM_PolicySetComponent [CIM_PolicySetComponent]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _CIM_PolicySetComponent /* extends CIM_PolicyComponent */
{
    MI_Instance __instance;
    /* CIM_Component properties */
    /*KEY*/ CIM_PolicySet_ConstRef GroupComponent;
    /*KEY*/ CIM_PolicySet_ConstRef PartComponent;
    /* CIM_PolicyComponent properties */
    /* CIM_PolicySetComponent properties */
    MI_ConstUint16Field Priority;
}
CIM_PolicySetComponent;

typedef struct _CIM_PolicySetComponent_Ref
{
    CIM_PolicySetComponent* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicySetComponent_Ref;

typedef struct _CIM_PolicySetComponent_ConstRef
{
    MI_CONST CIM_PolicySetComponent* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicySetComponent_ConstRef;

typedef struct _CIM_PolicySetComponent_Array
{
    struct _CIM_PolicySetComponent** data;
    MI_Uint32 size;
}
CIM_PolicySetComponent_Array;

typedef struct _CIM_PolicySetComponent_ConstArray
{
    struct _CIM_PolicySetComponent MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_PolicySetComponent_ConstArray;

typedef struct _CIM_PolicySetComponent_ArrayRef
{
    CIM_PolicySetComponent_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicySetComponent_ArrayRef;

typedef struct _CIM_PolicySetComponent_ConstArrayRef
{
    CIM_PolicySetComponent_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicySetComponent_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_PolicySetComponent_rtti;

MI_INLINE MI_Result MI_CALL CIM_PolicySetComponent_Construct(
    _Out_ CIM_PolicySetComponent* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_PolicySetComponent_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetComponent_Clone(
    _In_ const CIM_PolicySetComponent* self,
    _Outptr_ CIM_PolicySetComponent** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_PolicySetComponent_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_PolicySetComponent_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetComponent_Destruct(_Inout_ CIM_PolicySetComponent* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetComponent_Delete(_Inout_ CIM_PolicySetComponent* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetComponent_Post(
    _In_ const CIM_PolicySetComponent* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetComponent_Set_GroupComponent(
    _Inout_ CIM_PolicySetComponent* self,
    _In_ const CIM_PolicySet* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetComponent_SetPtr_GroupComponent(
    _Inout_ CIM_PolicySetComponent* self,
    _In_ const CIM_PolicySet* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetComponent_Clear_GroupComponent(
    _Inout_ CIM_PolicySetComponent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetComponent_Set_PartComponent(
    _Inout_ CIM_PolicySetComponent* self,
    _In_ const CIM_PolicySet* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetComponent_SetPtr_PartComponent(
    _Inout_ CIM_PolicySetComponent* self,
    _In_ const CIM_PolicySet* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetComponent_Clear_PartComponent(
    _Inout_ CIM_PolicySetComponent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetComponent_Set_Priority(
    _Inout_ CIM_PolicySetComponent* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Priority)->value = x;
    ((MI_Uint16Field*)&self->Priority)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetComponent_Clear_Priority(
    _Inout_ CIM_PolicySetComponent* self)
{
    memset((void*)&self->Priority, 0, sizeof(self->Priority));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_PolicySetComponent provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_PolicySetComponent_Self CIM_PolicySetComponent_Self;

MI_EXTERN_C void MI_CALL CIM_PolicySetComponent_Load(
    _Outptr_result_maybenull_ CIM_PolicySetComponent_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_PolicySetComponent_Unload(
    _In_opt_ CIM_PolicySetComponent_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_PolicySetComponent_EnumerateInstances(
    _In_opt_ CIM_PolicySetComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicySetComponent_GetInstance(
    _In_opt_ CIM_PolicySetComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySetComponent* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_PolicySetComponent_CreateInstance(
    _In_opt_ CIM_PolicySetComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySetComponent* newInstance);

MI_EXTERN_C void MI_CALL CIM_PolicySetComponent_ModifyInstance(
    _In_opt_ CIM_PolicySetComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySetComponent* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_PolicySetComponent_DeleteInstance(
    _In_opt_ CIM_PolicySetComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySetComponent* instanceName);

MI_EXTERN_C void MI_CALL CIM_PolicySetComponent_AssociatorInstancesGroupComponent(
    _In_opt_ CIM_PolicySetComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySet* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicySetComponent_AssociatorInstancesPartComponent(
    _In_opt_ CIM_PolicySetComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySet* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicySetComponent_ReferenceInstancesGroupComponent(
    _In_opt_ CIM_PolicySetComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySet* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicySetComponent_ReferenceInstancesPartComponent(
    _In_opt_ CIM_PolicySetComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySet* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_PolicySetComponent_h */
