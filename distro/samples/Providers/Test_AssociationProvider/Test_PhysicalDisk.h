/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Test_PhysicalDisk_h
#define _Test_PhysicalDisk_h

#include <MI.h>

/*
**==============================================================================
**
** Test_PhysicalDisk [Test_PhysicalDisk]
**
** Keys:
**    serialNumber
**
**==============================================================================
*/

typedef struct _Test_PhysicalDisk
{
    MI_Instance __instance;
    /* Test_PhysicalDisk properties */
    /*KEY*/ MI_ConstStringField serialNumber;
    MI_ConstUint64Field numSectors;
    MI_ConstUint32Field sectorSize;
}
Test_PhysicalDisk;

typedef struct _Test_PhysicalDisk_Ref
{
    Test_PhysicalDisk* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_PhysicalDisk_Ref;

typedef struct _Test_PhysicalDisk_ConstRef
{
    MI_CONST Test_PhysicalDisk* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_PhysicalDisk_ConstRef;

typedef struct _Test_PhysicalDisk_Array
{
    struct _Test_PhysicalDisk** data;
    MI_Uint32 size;
}
Test_PhysicalDisk_Array;

typedef struct _Test_PhysicalDisk_ConstArray
{
    struct _Test_PhysicalDisk MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Test_PhysicalDisk_ConstArray;

typedef struct _Test_PhysicalDisk_ArrayRef
{
    Test_PhysicalDisk_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_PhysicalDisk_ArrayRef;

typedef struct _Test_PhysicalDisk_ConstArrayRef
{
    Test_PhysicalDisk_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_PhysicalDisk_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Test_PhysicalDisk_rtti;

MI_INLINE MI_Result MI_CALL Test_PhysicalDisk_Construct(
    Test_PhysicalDisk* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Test_PhysicalDisk_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_PhysicalDisk_Clone(
    const Test_PhysicalDisk* self,
    Test_PhysicalDisk** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Test_PhysicalDisk_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Test_PhysicalDisk_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Test_PhysicalDisk_Destruct(Test_PhysicalDisk* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_PhysicalDisk_Delete(Test_PhysicalDisk* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_PhysicalDisk_Post(
    const Test_PhysicalDisk* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_PhysicalDisk_Set_serialNumber(
    Test_PhysicalDisk* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Test_PhysicalDisk_SetPtr_serialNumber(
    Test_PhysicalDisk* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_PhysicalDisk_Clear_serialNumber(
    Test_PhysicalDisk* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Test_PhysicalDisk_Set_numSectors(
    Test_PhysicalDisk* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->numSectors)->value = x;
    ((MI_Uint64Field*)&self->numSectors)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_PhysicalDisk_Clear_numSectors(
    Test_PhysicalDisk* self)
{
    memset((void*)&self->numSectors, 0, sizeof(self->numSectors));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_PhysicalDisk_Set_sectorSize(
    Test_PhysicalDisk* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->sectorSize)->value = x;
    ((MI_Uint32Field*)&self->sectorSize)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_PhysicalDisk_Clear_sectorSize(
    Test_PhysicalDisk* self)
{
    memset((void*)&self->sectorSize, 0, sizeof(self->sectorSize));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Test_PhysicalDisk provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Test_PhysicalDisk_Self Test_PhysicalDisk_Self;

MI_EXTERN_C void MI_CALL Test_PhysicalDisk_Load(
    Test_PhysicalDisk_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_PhysicalDisk_Unload(
    Test_PhysicalDisk_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_PhysicalDisk_EnumerateInstances(
    Test_PhysicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_PhysicalDisk_GetInstance(
    Test_PhysicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_PhysicalDisk* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_PhysicalDisk_CreateInstance(
    Test_PhysicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_PhysicalDisk* newInstance);

MI_EXTERN_C void MI_CALL Test_PhysicalDisk_ModifyInstance(
    Test_PhysicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_PhysicalDisk* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_PhysicalDisk_DeleteInstance(
    Test_PhysicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_PhysicalDisk* instanceName);

#endif /* _Test_PhysicalDisk_h */
