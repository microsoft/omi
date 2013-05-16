/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Test_AssociationPhysicalLogicalDisk_h
#define _Test_AssociationPhysicalLogicalDisk_h

#include <MI.h>
#include "Test_PhysicalDisk.h"
#include "Test_LogicalDisk.h"

/*
**==============================================================================
**
** Test_AssociationPhysicalLogicalDisk [Test_AssociationPhysicalLogicalDisk]
**
** Keys:
**    antecedent
**    dependent
**
**==============================================================================
*/

typedef struct _Test_AssociationPhysicalLogicalDisk
{
    MI_Instance __instance;
    /* Test_AssociationPhysicalLogicalDisk properties */
    /*KEY*/ Test_PhysicalDisk_ConstRef antecedent;
    /*KEY*/ Test_LogicalDisk_ConstRef dependent;
}
Test_AssociationPhysicalLogicalDisk;

typedef struct _Test_AssociationPhysicalLogicalDisk_Ref
{
    Test_AssociationPhysicalLogicalDisk* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_AssociationPhysicalLogicalDisk_Ref;

typedef struct _Test_AssociationPhysicalLogicalDisk_ConstRef
{
    MI_CONST Test_AssociationPhysicalLogicalDisk* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_AssociationPhysicalLogicalDisk_ConstRef;

typedef struct _Test_AssociationPhysicalLogicalDisk_Array
{
    struct _Test_AssociationPhysicalLogicalDisk** data;
    MI_Uint32 size;
}
Test_AssociationPhysicalLogicalDisk_Array;

typedef struct _Test_AssociationPhysicalLogicalDisk_ConstArray
{
    struct _Test_AssociationPhysicalLogicalDisk MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Test_AssociationPhysicalLogicalDisk_ConstArray;

typedef struct _Test_AssociationPhysicalLogicalDisk_ArrayRef
{
    Test_AssociationPhysicalLogicalDisk_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_AssociationPhysicalLogicalDisk_ArrayRef;

typedef struct _Test_AssociationPhysicalLogicalDisk_ConstArrayRef
{
    Test_AssociationPhysicalLogicalDisk_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_AssociationPhysicalLogicalDisk_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Test_AssociationPhysicalLogicalDisk_rtti;

MI_INLINE MI_Result MI_CALL Test_AssociationPhysicalLogicalDisk_Construct(
    Test_AssociationPhysicalLogicalDisk* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Test_AssociationPhysicalLogicalDisk_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_AssociationPhysicalLogicalDisk_Clone(
    const Test_AssociationPhysicalLogicalDisk* self,
    Test_AssociationPhysicalLogicalDisk** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Test_AssociationPhysicalLogicalDisk_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Test_AssociationPhysicalLogicalDisk_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Test_AssociationPhysicalLogicalDisk_Destruct(Test_AssociationPhysicalLogicalDisk* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_AssociationPhysicalLogicalDisk_Delete(Test_AssociationPhysicalLogicalDisk* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_AssociationPhysicalLogicalDisk_Post(
    const Test_AssociationPhysicalLogicalDisk* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_AssociationPhysicalLogicalDisk_Set_antecedent(
    Test_AssociationPhysicalLogicalDisk* self,
    const Test_PhysicalDisk* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL Test_AssociationPhysicalLogicalDisk_SetPtr_antecedent(
    Test_AssociationPhysicalLogicalDisk* self,
    const Test_PhysicalDisk* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_AssociationPhysicalLogicalDisk_Clear_antecedent(
    Test_AssociationPhysicalLogicalDisk* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Test_AssociationPhysicalLogicalDisk_Set_dependent(
    Test_AssociationPhysicalLogicalDisk* self,
    const Test_LogicalDisk* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL Test_AssociationPhysicalLogicalDisk_SetPtr_dependent(
    Test_AssociationPhysicalLogicalDisk* self,
    const Test_LogicalDisk* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_AssociationPhysicalLogicalDisk_Clear_dependent(
    Test_AssociationPhysicalLogicalDisk* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** Test_AssociationPhysicalLogicalDisk provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Test_AssociationPhysicalLogicalDisk_Self Test_AssociationPhysicalLogicalDisk_Self;

MI_EXTERN_C void MI_CALL Test_AssociationPhysicalLogicalDisk_Load(
    Test_AssociationPhysicalLogicalDisk_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_AssociationPhysicalLogicalDisk_Unload(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_AssociationPhysicalLogicalDisk_EnumerateInstances(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_AssociationPhysicalLogicalDisk_GetInstance(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationPhysicalLogicalDisk* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_AssociationPhysicalLogicalDisk_CreateInstance(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationPhysicalLogicalDisk* newInstance);

MI_EXTERN_C void MI_CALL Test_AssociationPhysicalLogicalDisk_ModifyInstance(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationPhysicalLogicalDisk* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_AssociationPhysicalLogicalDisk_DeleteInstance(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_AssociationPhysicalLogicalDisk* instanceName);

MI_EXTERN_C void MI_CALL Test_AssociationPhysicalLogicalDisk_AssociatorInstancesantecedent(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_PhysicalDisk* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_AssociationPhysicalLogicalDisk_AssociatorInstancesdependent(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_AssociationPhysicalLogicalDisk_ReferenceInstancesantecedent(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_PhysicalDisk* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_AssociationPhysicalLogicalDisk_ReferenceInstancesdependent(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _Test_AssociationPhysicalLogicalDisk_h */
