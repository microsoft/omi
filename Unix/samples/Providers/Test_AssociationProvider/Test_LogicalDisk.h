/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Test_LogicalDisk_h
#define _Test_LogicalDisk_h

#include <MI.h>

/*
**==============================================================================
**
** Test_LogicalDisk [Test_LogicalDisk]
**
** Keys:
**    diskID
**    driveLetter
**
**==============================================================================
*/

typedef struct _Test_LogicalDisk
{
    MI_Instance __instance;
    /* Test_LogicalDisk properties */
    /*KEY*/ MI_ConstUint32Field diskID;
    /*KEY*/ MI_ConstStringField driveLetter;
    MI_ConstUint64Field sizeInGb;
}
Test_LogicalDisk;

typedef struct _Test_LogicalDisk_Ref
{
    Test_LogicalDisk* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_LogicalDisk_Ref;

typedef struct _Test_LogicalDisk_ConstRef
{
    MI_CONST Test_LogicalDisk* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_LogicalDisk_ConstRef;

typedef struct _Test_LogicalDisk_Array
{
    struct _Test_LogicalDisk** data;
    MI_Uint32 size;
}
Test_LogicalDisk_Array;

typedef struct _Test_LogicalDisk_ConstArray
{
    struct _Test_LogicalDisk MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Test_LogicalDisk_ConstArray;

typedef struct _Test_LogicalDisk_ArrayRef
{
    Test_LogicalDisk_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_LogicalDisk_ArrayRef;

typedef struct _Test_LogicalDisk_ConstArrayRef
{
    Test_LogicalDisk_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_LogicalDisk_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Test_LogicalDisk_rtti;

MI_INLINE MI_Result MI_CALL Test_LogicalDisk_Construct(
    Test_LogicalDisk* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Test_LogicalDisk_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_LogicalDisk_Clone(
    const Test_LogicalDisk* self,
    Test_LogicalDisk** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Test_LogicalDisk_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Test_LogicalDisk_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Test_LogicalDisk_Destruct(Test_LogicalDisk* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_LogicalDisk_Delete(Test_LogicalDisk* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_LogicalDisk_Post(
    const Test_LogicalDisk* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_LogicalDisk_Set_diskID(
    Test_LogicalDisk* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->diskID)->value = x;
    ((MI_Uint32Field*)&self->diskID)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_LogicalDisk_Clear_diskID(
    Test_LogicalDisk* self)
{
    memset((void*)&self->diskID, 0, sizeof(self->diskID));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_LogicalDisk_Set_driveLetter(
    Test_LogicalDisk* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Test_LogicalDisk_SetPtr_driveLetter(
    Test_LogicalDisk* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_LogicalDisk_Clear_driveLetter(
    Test_LogicalDisk* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Test_LogicalDisk_Set_sizeInGb(
    Test_LogicalDisk* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->sizeInGb)->value = x;
    ((MI_Uint64Field*)&self->sizeInGb)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_LogicalDisk_Clear_sizeInGb(
    Test_LogicalDisk* self)
{
    memset((void*)&self->sizeInGb, 0, sizeof(self->sizeInGb));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Test_LogicalDisk provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Test_LogicalDisk_Self Test_LogicalDisk_Self;

MI_EXTERN_C void MI_CALL Test_LogicalDisk_Load(
    Test_LogicalDisk_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_LogicalDisk_Unload(
    Test_LogicalDisk_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_LogicalDisk_EnumerateInstances(
    Test_LogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_LogicalDisk_GetInstance(
    Test_LogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_LogicalDisk_CreateInstance(
    Test_LogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* newInstance);

MI_EXTERN_C void MI_CALL Test_LogicalDisk_ModifyInstance(
    Test_LogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_LogicalDisk_DeleteInstance(
    Test_LogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_LogicalDisk* instanceName);


#endif /* _Test_LogicalDisk_h */
