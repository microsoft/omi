/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyReferenceClass_h
#define _MyReferenceClass_h

#include <MI.h>
#include "MyEmbeddedPropertiesClass.h"

/*
**==============================================================================
**
** MyReferenceClass [MyReferenceClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyReferenceClass
{
    MI_Instance __instance;
    /* MyReferenceClass properties */
    MyEmbeddedPropertiesClass_ConstRef refProp;
}
MyReferenceClass;

typedef struct _MyReferenceClass_Ref
{
    MyReferenceClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyReferenceClass_Ref;

typedef struct _MyReferenceClass_ConstRef
{
    MI_CONST MyReferenceClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyReferenceClass_ConstRef;

typedef struct _MyReferenceClass_Array
{
    struct _MyReferenceClass** data;
    MI_Uint32 size;
}
MyReferenceClass_Array;

typedef struct _MyReferenceClass_ConstArray
{
    struct _MyReferenceClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyReferenceClass_ConstArray;

typedef struct _MyReferenceClass_ArrayRef
{
    MyReferenceClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyReferenceClass_ArrayRef;

typedef struct _MyReferenceClass_ConstArrayRef
{
    MyReferenceClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyReferenceClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyReferenceClass_rtti;

MI_INLINE MI_Result MI_CALL MyReferenceClass_Construct(
    MyReferenceClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyReferenceClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_Clone(
    const MyReferenceClass* self,
    MyReferenceClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyReferenceClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyReferenceClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_Destruct(MyReferenceClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_Delete(MyReferenceClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_Post(
    const MyReferenceClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_Set_refProp(
    MyReferenceClass* self,
    const MyEmbeddedPropertiesClass* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_SetPtr_refProp(
    MyReferenceClass* self,
    const MyEmbeddedPropertiesClass* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_Clear_refProp(
    MyReferenceClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** MyReferenceClass.GetReferenceValue()
**
**==============================================================================
*/

typedef struct _MyReferenceClass_GetReferenceValue
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MyEmbeddedPropertiesClass_ConstRef ReferenceVal;
}
MyReferenceClass_GetReferenceValue;

MI_EXTERN_C MI_CONST MI_MethodDecl MyReferenceClass_GetReferenceValue_rtti;

MI_INLINE MI_Result MI_CALL MyReferenceClass_GetReferenceValue_Construct(
    MyReferenceClass_GetReferenceValue* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyReferenceClass_GetReferenceValue_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_GetReferenceValue_Clone(
    const MyReferenceClass_GetReferenceValue* self,
    MyReferenceClass_GetReferenceValue** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_GetReferenceValue_Destruct(
    MyReferenceClass_GetReferenceValue* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_GetReferenceValue_Delete(
    MyReferenceClass_GetReferenceValue* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_GetReferenceValue_Post(
    const MyReferenceClass_GetReferenceValue* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_GetReferenceValue_Set_MIReturn(
    MyReferenceClass_GetReferenceValue* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_GetReferenceValue_Clear_MIReturn(
    MyReferenceClass_GetReferenceValue* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_GetReferenceValue_Set_ReferenceVal(
    MyReferenceClass_GetReferenceValue* self,
    const MyEmbeddedPropertiesClass* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_GetReferenceValue_SetPtr_ReferenceVal(
    MyReferenceClass_GetReferenceValue* self,
    const MyEmbeddedPropertiesClass* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyReferenceClass_GetReferenceValue_Clear_ReferenceVal(
    MyReferenceClass_GetReferenceValue* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyReferenceClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyReferenceClass_Self MyReferenceClass_Self;

MI_EXTERN_C void MI_CALL MyReferenceClass_Load(
    MyReferenceClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyReferenceClass_Unload(
    MyReferenceClass_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyReferenceClass_Invoke_GetReferenceValue(
    MyReferenceClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyReferenceClass* instanceName,
    const MyReferenceClass_GetReferenceValue* in);


#endif /* _MyReferenceClass_h */
