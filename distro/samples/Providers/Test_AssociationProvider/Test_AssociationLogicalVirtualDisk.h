/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Test_AssociationLogicalVirtualDisk_h
#define _Test_AssociationLogicalVirtualDisk_h

#include <MI.h>
#include "Test_LogicalDisk.h"
#include "Test_VirtualDisk.h"

/*
**==============================================================================
**
** Test_AssociationLogicalVirtualDisk [Test_AssociationLogicalVirtualDisk]
**
** Keys:
**    antecedent
**    dependent
**
**==============================================================================
*/

typedef struct _Test_AssociationLogicalVirtualDisk
{
    MI_Instance __instance;
    /* Test_AssociationLogicalVirtualDisk properties */
    /*KEY*/ Test_LogicalDisk_ConstRef antecedent;
    /*KEY*/ Test_VirtualDisk_ConstRef dependent;
}
Test_AssociationLogicalVirtualDisk;

typedef struct _Test_AssociationLogicalVirtualDisk_Ref
{
    Test_AssociationLogicalVirtualDisk* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_AssociationLogicalVirtualDisk_Ref;

typedef struct _Test_AssociationLogicalVirtualDisk_ConstRef
{
    MI_CONST Test_AssociationLogicalVirtualDisk* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_AssociationLogicalVirtualDisk_ConstRef;

typedef struct _Test_AssociationLogicalVirtualDisk_Array
{
    struct _Test_AssociationLogicalVirtualDisk** data;
    MI_Uint32 size;
}
Test_AssociationLogicalVirtualDisk_Array;

typedef struct _Test_AssociationLogicalVirtualDisk_ConstArray
{
    struct _Test_AssociationLogicalVirtualDisk MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Test_AssociationLogicalVirtualDisk_ConstArray;

typedef struct _Test_AssociationLogicalVirtualDisk_ArrayRef
{
    Test_AssociationLogicalVirtualDisk_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_AssociationLogicalVirtualDisk_ArrayRef;

typedef struct _Test_AssociationLogicalVirtualDisk_ConstArrayRef
{
    Test_AssociationLogicalVirtualDisk_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_AssociationLogicalVirtualDisk_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Test_AssociationLogicalVirtualDisk_rtti;

MI_INLINE MI_Result MI_CALL Test_AssociationLogicalVirtualDisk_Construct(
    Test_AssociationLogicalVirtualDisk* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Test_AssociationLogicalVirtualDisk_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_AssociationLogicalVirtualDisk_Clone(
    const Test_AssociationLogicalVirtualDisk* self,
    Test_AssociationLogicalVirtualDisk** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Test_AssociationLogicalVirtualDisk_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Test_AssociationLogicalVirtualDisk_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Test_AssociationLogicalVirtualDisk_Destruct(Test_AssociationLogicalVirtualDisk* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_AssociationLogicalVirtualDisk_Delete(Test_AssociationLogicalVirtualDisk* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_AssociationLogicalVirtualDisk_Post(
    const Test_AssociationLogicalVirtualDisk* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_AssociationLogicalVirtualDisk_Set_antecedent(
    Test_AssociationLogicalVirtualDisk* self,
    const Test_LogicalDisk* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL Test_AssociationLogicalVirtualDisk_SetPtr_antecedent(
    Test_AssociationLogicalVirtualDisk* self,
    const Test_LogicalDisk* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_AssociationLogicalVirtualDisk_Clear_antecedent(
    Test_AssociationLogicalVirtualDisk* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Test_AssociationLogicalVirtualDisk_Set_dependent(
    Test_AssociationLogicalVirtualDisk* self,
    const Test_VirtualDisk* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL Test_AssociationLogicalVirtualDisk_SetPtr_dependent(
    Test_AssociationLogicalVirtualDisk* self,
    const Test_VirtualDisk* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_AssociationLogicalVirtualDisk_Clear_dependent(
    Test_AssociationLogicalVirtualDisk* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** Test_AssociationLogicalVirtualDisk provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Test_AssociationLogicalVirtualDisk_Self Test_AssociationLogicalVirtualDisk_Self;

MI_EXTERN_C void MI_CALL Test_AssociationLogicalVirtualDisk_Load(
    Test_AssociationLogicalVirtualDisk_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_AssociationLogicalVirtualDisk_Unload(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_AssociationLogicalVirtualDisk_EnumerateInstances(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_AssociationLogicalVirtualDisk_GetInstance(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationLogicalVirtualDisk* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_AssociationLogicalVirtualDisk_CreateInstance(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationLogicalVirtualDisk* newInstance);

MI_EXTERN_C void MI_CALL Test_AssociationLogicalVirtualDisk_ModifyInstance(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationLogicalVirtualDisk* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_AssociationLogicalVirtualDisk_DeleteInstance(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationLogicalVirtualDisk* instanceName);

MI_EXTERN_C void MI_CALL Test_AssociationLogicalVirtualDisk_AssociatorInstancesantecedent(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_AssociationLogicalVirtualDisk_AssociatorInstancesdependent(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_VirtualDisk* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_AssociationLogicalVirtualDisk_ReferenceInstancesantecedent(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_AssociationLogicalVirtualDisk_ReferenceInstancesdependent(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_VirtualDisk* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _Test_AssociationLogicalVirtualDisk_h */
