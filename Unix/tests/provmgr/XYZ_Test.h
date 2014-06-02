/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _XYZ_Test_h
#define _XYZ_Test_h

#include <MI.h>

/*
**==============================================================================
**
** XYZ_Test [XYZ_Test]
**
** Keys:
**    detailmessage
**
**==============================================================================
*/

typedef struct _XYZ_Test
{
    MI_Instance __instance;
    /* XYZ_Test properties */
    /*KEY*/ MI_ConstStringField detailmessage;
}
XYZ_Test;

typedef struct _XYZ_Test_Ref
{
    XYZ_Test* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Test_Ref;

typedef struct _XYZ_Test_ConstRef
{
    MI_CONST XYZ_Test* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Test_ConstRef;

typedef struct _XYZ_Test_Array
{
    struct _XYZ_Test** data;
    MI_Uint32 size;
}
XYZ_Test_Array;

typedef struct _XYZ_Test_ConstArray
{
    struct _XYZ_Test MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
XYZ_Test_ConstArray;

typedef struct _XYZ_Test_ArrayRef
{
    XYZ_Test_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Test_ArrayRef;

typedef struct _XYZ_Test_ConstArrayRef
{
    XYZ_Test_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Test_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl XYZ_Test_rtti;

MI_INLINE MI_Result MI_CALL XYZ_Test_Construct(
    XYZ_Test* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &XYZ_Test_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Clone(
    const XYZ_Test* self,
    XYZ_Test** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL XYZ_Test_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &XYZ_Test_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Destruct(XYZ_Test* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Delete(XYZ_Test* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Post(
    const XYZ_Test* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Set_detailmessage(
    XYZ_Test* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Test_SetPtr_detailmessage(
    XYZ_Test* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Clear_detailmessage(
    XYZ_Test* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** XYZ_Test.Create()
**
**==============================================================================
*/

typedef struct _XYZ_Test_Create
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstStringField CommandLine;
    /*OUT*/ MI_ConstUint32Field result;
}
XYZ_Test_Create;

MI_EXTERN_C MI_CONST MI_MethodDecl XYZ_Test_Create_rtti;

MI_INLINE MI_Result MI_CALL XYZ_Test_Create_Construct(
    XYZ_Test_Create* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &XYZ_Test_Create_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Create_Clone(
    const XYZ_Test_Create* self,
    XYZ_Test_Create** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Create_Destruct(
    XYZ_Test_Create* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Create_Delete(
    XYZ_Test_Create* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Create_Post(
    const XYZ_Test_Create* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Create_Set_MIReturn(
    XYZ_Test_Create* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Create_Clear_MIReturn(
    XYZ_Test_Create* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Create_Set_CommandLine(
    XYZ_Test_Create* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Create_SetPtr_CommandLine(
    XYZ_Test_Create* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Create_Clear_CommandLine(
    XYZ_Test_Create* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Create_Set_result(
    XYZ_Test_Create* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->result)->value = x;
    ((MI_Uint32Field*)&self->result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Test_Create_Clear_result(
    XYZ_Test_Create* self)
{
    memset((void*)&self->result, 0, sizeof(self->result));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** XYZ_Test provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _XYZ_Test_Self XYZ_Test_Self;

MI_EXTERN_C void MI_CALL XYZ_Test_Load(
    XYZ_Test_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Test_Unload(
    XYZ_Test_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Test_EnumerateInstances(
    XYZ_Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL XYZ_Test_GetInstance(
    XYZ_Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Test* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL XYZ_Test_CreateInstance(
    XYZ_Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Test* newInstance);

MI_EXTERN_C void MI_CALL XYZ_Test_ModifyInstance(
    XYZ_Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Test* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL XYZ_Test_DeleteInstance(
    XYZ_Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Test* instanceName);

MI_EXTERN_C void MI_CALL XYZ_Test_Invoke_Create(
    XYZ_Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const XYZ_Test* instanceName,
    const XYZ_Test_Create* in);


#endif /* _XYZ_Test_h */
