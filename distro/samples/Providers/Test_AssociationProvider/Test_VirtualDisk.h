/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Test_VirtualDisk_h
#define _Test_VirtualDisk_h

#include <MI.h>
#include "Test_PhysicalDisk.h"

/*
**==============================================================================
**
** Test_VirtualDisk [Test_VirtualDisk]
**
** Keys:
**    serialNumber
**
**==============================================================================
*/

typedef struct _Test_VirtualDisk /* extends Test_PhysicalDisk */
{
    MI_Instance __instance;
    /* Test_PhysicalDisk properties */
    /*KEY*/ MI_ConstStringField serialNumber;
    MI_ConstUint64Field numSectors;
    MI_ConstUint32Field sectorSize;
    /* Test_VirtualDisk properties */
    MI_ConstStringField filePath;
}
Test_VirtualDisk;

typedef struct _Test_VirtualDisk_Ref
{
    Test_VirtualDisk* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_VirtualDisk_Ref;

typedef struct _Test_VirtualDisk_ConstRef
{
    MI_CONST Test_VirtualDisk* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_VirtualDisk_ConstRef;

typedef struct _Test_VirtualDisk_Array
{
    struct _Test_VirtualDisk** data;
    MI_Uint32 size;
}
Test_VirtualDisk_Array;

typedef struct _Test_VirtualDisk_ConstArray
{
    struct _Test_VirtualDisk MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Test_VirtualDisk_ConstArray;

typedef struct _Test_VirtualDisk_ArrayRef
{
    Test_VirtualDisk_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_VirtualDisk_ArrayRef;

typedef struct _Test_VirtualDisk_ConstArrayRef
{
    Test_VirtualDisk_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_VirtualDisk_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Test_VirtualDisk_rtti;

MI_INLINE MI_Result MI_CALL Test_VirtualDisk_Construct(
    Test_VirtualDisk* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Test_VirtualDisk_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_VirtualDisk_Clone(
    const Test_VirtualDisk* self,
    Test_VirtualDisk** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Test_VirtualDisk_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Test_VirtualDisk_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Test_VirtualDisk_Destruct(Test_VirtualDisk* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_VirtualDisk_Delete(Test_VirtualDisk* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_VirtualDisk_Post(
    const Test_VirtualDisk* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_VirtualDisk_Set_serialNumber(
    Test_VirtualDisk* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Test_VirtualDisk_SetPtr_serialNumber(
    Test_VirtualDisk* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_VirtualDisk_Clear_serialNumber(
    Test_VirtualDisk* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Test_VirtualDisk_Set_numSectors(
    Test_VirtualDisk* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->numSectors)->value = x;
    ((MI_Uint64Field*)&self->numSectors)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_VirtualDisk_Clear_numSectors(
    Test_VirtualDisk* self)
{
    memset((void*)&self->numSectors, 0, sizeof(self->numSectors));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_VirtualDisk_Set_sectorSize(
    Test_VirtualDisk* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->sectorSize)->value = x;
    ((MI_Uint32Field*)&self->sectorSize)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_VirtualDisk_Clear_sectorSize(
    Test_VirtualDisk* self)
{
    memset((void*)&self->sectorSize, 0, sizeof(self->sectorSize));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_VirtualDisk_Set_filePath(
    Test_VirtualDisk* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Test_VirtualDisk_SetPtr_filePath(
    Test_VirtualDisk* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_VirtualDisk_Clear_filePath(
    Test_VirtualDisk* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** Test_VirtualDisk provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Test_VirtualDisk_Self Test_VirtualDisk_Self;

MI_EXTERN_C void MI_CALL Test_VirtualDisk_Load(
    Test_VirtualDisk_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_VirtualDisk_Unload(
    Test_VirtualDisk_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_VirtualDisk_EnumerateInstances(
    Test_VirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_VirtualDisk_GetInstance(
    Test_VirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_VirtualDisk* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_VirtualDisk_CreateInstance(
    Test_VirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_VirtualDisk* newInstance);

MI_EXTERN_C void MI_CALL Test_VirtualDisk_ModifyInstance(
    Test_VirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_VirtualDisk* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_VirtualDisk_DeleteInstance(
    Test_VirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_VirtualDisk* instanceName);


#endif /* _Test_VirtualDisk_h */
