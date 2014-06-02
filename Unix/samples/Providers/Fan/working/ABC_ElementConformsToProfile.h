/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_ElementConformsToProfile_h
#define _ABC_ElementConformsToProfile_h

#include <MI.h>
#include "CIM_ElementConformsToProfile.h"
#include "CIM_RegisteredProfile.h"
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** ABC_ElementConformsToProfile [ABC_ElementConformsToProfile]
**
** Keys:
**    ConformantStandard
**    ManagedElement
**
**==============================================================================
*/

typedef struct _ABC_ElementConformsToProfile /* extends CIM_ElementConformsToProfile */
{
    MI_Instance __instance;
    /* CIM_ElementConformsToProfile properties */
    /*KEY*/ CIM_RegisteredProfile_ConstRef ConformantStandard;
    /*KEY*/ CIM_ManagedElement_ConstRef ManagedElement;
    /* ABC_ElementConformsToProfile properties */
}
ABC_ElementConformsToProfile;

typedef struct _ABC_ElementConformsToProfile_Ref
{
    ABC_ElementConformsToProfile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ElementConformsToProfile_Ref;

typedef struct _ABC_ElementConformsToProfile_ConstRef
{
    MI_CONST ABC_ElementConformsToProfile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ElementConformsToProfile_ConstRef;

typedef struct _ABC_ElementConformsToProfile_Array
{
    struct _ABC_ElementConformsToProfile** data;
    MI_Uint32 size;
}
ABC_ElementConformsToProfile_Array;

typedef struct _ABC_ElementConformsToProfile_ConstArray
{
    struct _ABC_ElementConformsToProfile MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_ElementConformsToProfile_ConstArray;

typedef struct _ABC_ElementConformsToProfile_ArrayRef
{
    ABC_ElementConformsToProfile_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ElementConformsToProfile_ArrayRef;

typedef struct _ABC_ElementConformsToProfile_ConstArrayRef
{
    ABC_ElementConformsToProfile_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ElementConformsToProfile_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_ElementConformsToProfile_rtti;

MI_INLINE MI_Result MI_CALL ABC_ElementConformsToProfile_Construct(
    ABC_ElementConformsToProfile* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_ElementConformsToProfile_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ElementConformsToProfile_Clone(
    const ABC_ElementConformsToProfile* self,
    ABC_ElementConformsToProfile** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_ElementConformsToProfile_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_ElementConformsToProfile_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_ElementConformsToProfile_Destruct(ABC_ElementConformsToProfile* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ElementConformsToProfile_Delete(ABC_ElementConformsToProfile* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ElementConformsToProfile_Post(
    const ABC_ElementConformsToProfile* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ElementConformsToProfile_Set_ConformantStandard(
    ABC_ElementConformsToProfile* self,
    const CIM_RegisteredProfile* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ElementConformsToProfile_SetPtr_ConformantStandard(
    ABC_ElementConformsToProfile* self,
    const CIM_RegisteredProfile* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ElementConformsToProfile_Clear_ConformantStandard(
    ABC_ElementConformsToProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ElementConformsToProfile_Set_ManagedElement(
    ABC_ElementConformsToProfile* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ElementConformsToProfile_SetPtr_ManagedElement(
    ABC_ElementConformsToProfile* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ElementConformsToProfile_Clear_ManagedElement(
    ABC_ElementConformsToProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** ABC_ElementConformsToProfile provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_ElementConformsToProfile_Self ABC_ElementConformsToProfile_Self;

MI_EXTERN_C void MI_CALL ABC_ElementConformsToProfile_Load(
    ABC_ElementConformsToProfile_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_ElementConformsToProfile_Unload(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_ElementConformsToProfile_EnumerateInstances(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_ElementConformsToProfile_GetInstance(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementConformsToProfile* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_ElementConformsToProfile_CreateInstance(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementConformsToProfile* newInstance);

MI_EXTERN_C void MI_CALL ABC_ElementConformsToProfile_ModifyInstance(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementConformsToProfile* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_ElementConformsToProfile_DeleteInstance(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementConformsToProfile* instanceName);

MI_EXTERN_C void MI_CALL ABC_ElementConformsToProfile_AssociatorInstancesConformantStandard(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_RegisteredProfile* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_ElementConformsToProfile_AssociatorInstancesManagedElement(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_ManagedElement* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_ElementConformsToProfile_ReferenceInstancesConformantStandard(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_RegisteredProfile* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_ElementConformsToProfile_ReferenceInstancesManagedElement(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_ManagedElement* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _ABC_ElementConformsToProfile_h */
