/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyClassRestrictedQualsOnBaseElements_h
#define _MyClassRestrictedQualsOnBaseElements_h

#include <MI.h>

/*
**==============================================================================
**
** MyClassRestrictedQualsOnBaseElements [MyClassRestrictedQualsOnBaseElements]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyClassRestrictedQualsOnBaseElements
{
    MI_Instance __instance;
    /* MyClassRestrictedQualsOnBaseElements properties */
    MI_ConstUint32Field myProp;
}
MyClassRestrictedQualsOnBaseElements;

typedef struct _MyClassRestrictedQualsOnBaseElements_Ref
{
    MyClassRestrictedQualsOnBaseElements* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyClassRestrictedQualsOnBaseElements_Ref;

typedef struct _MyClassRestrictedQualsOnBaseElements_ConstRef
{
    MI_CONST MyClassRestrictedQualsOnBaseElements* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyClassRestrictedQualsOnBaseElements_ConstRef;

typedef struct _MyClassRestrictedQualsOnBaseElements_Array
{
    struct _MyClassRestrictedQualsOnBaseElements** data;
    MI_Uint32 size;
}
MyClassRestrictedQualsOnBaseElements_Array;

typedef struct _MyClassRestrictedQualsOnBaseElements_ConstArray
{
    struct _MyClassRestrictedQualsOnBaseElements MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyClassRestrictedQualsOnBaseElements_ConstArray;

typedef struct _MyClassRestrictedQualsOnBaseElements_ArrayRef
{
    MyClassRestrictedQualsOnBaseElements_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyClassRestrictedQualsOnBaseElements_ArrayRef;

typedef struct _MyClassRestrictedQualsOnBaseElements_ConstArrayRef
{
    MyClassRestrictedQualsOnBaseElements_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyClassRestrictedQualsOnBaseElements_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyClassRestrictedQualsOnBaseElements_rtti;

MI_INLINE MI_Result MI_CALL MyClassRestrictedQualsOnBaseElements_Construct(
    MyClassRestrictedQualsOnBaseElements* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyClassRestrictedQualsOnBaseElements_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyClassRestrictedQualsOnBaseElements_Clone(
    const MyClassRestrictedQualsOnBaseElements* self,
    MyClassRestrictedQualsOnBaseElements** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyClassRestrictedQualsOnBaseElements_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyClassRestrictedQualsOnBaseElements_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyClassRestrictedQualsOnBaseElements_Destruct(MyClassRestrictedQualsOnBaseElements* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyClassRestrictedQualsOnBaseElements_Delete(MyClassRestrictedQualsOnBaseElements* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyClassRestrictedQualsOnBaseElements_Post(
    const MyClassRestrictedQualsOnBaseElements* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyClassRestrictedQualsOnBaseElements_Set_myProp(
    MyClassRestrictedQualsOnBaseElements* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->myProp)->value = x;
    ((MI_Uint32Field*)&self->myProp)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyClassRestrictedQualsOnBaseElements_Clear_myProp(
    MyClassRestrictedQualsOnBaseElements* self)
{
    memset((void*)&self->myProp, 0, sizeof(self->myProp));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyClassRestrictedQualsOnBaseElements.myMethod()
**
**==============================================================================
*/

typedef struct _MyClassRestrictedQualsOnBaseElements_myMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MyClassRestrictedQualsOnBaseElements_myMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyClassRestrictedQualsOnBaseElements_myMethod_rtti;

MI_INLINE MI_Result MI_CALL MyClassRestrictedQualsOnBaseElements_myMethod_Construct(
    MyClassRestrictedQualsOnBaseElements_myMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyClassRestrictedQualsOnBaseElements_myMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyClassRestrictedQualsOnBaseElements_myMethod_Clone(
    const MyClassRestrictedQualsOnBaseElements_myMethod* self,
    MyClassRestrictedQualsOnBaseElements_myMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyClassRestrictedQualsOnBaseElements_myMethod_Destruct(
    MyClassRestrictedQualsOnBaseElements_myMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyClassRestrictedQualsOnBaseElements_myMethod_Delete(
    MyClassRestrictedQualsOnBaseElements_myMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyClassRestrictedQualsOnBaseElements_myMethod_Post(
    const MyClassRestrictedQualsOnBaseElements_myMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyClassRestrictedQualsOnBaseElements_myMethod_Set_MIReturn(
    MyClassRestrictedQualsOnBaseElements_myMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyClassRestrictedQualsOnBaseElements_myMethod_Clear_MIReturn(
    MyClassRestrictedQualsOnBaseElements_myMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyClassRestrictedQualsOnBaseElements provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyClassRestrictedQualsOnBaseElements_Self MyClassRestrictedQualsOnBaseElements_Self;

MI_EXTERN_C void MI_CALL MyClassRestrictedQualsOnBaseElements_Load(
    MyClassRestrictedQualsOnBaseElements_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyClassRestrictedQualsOnBaseElements_Unload(
    MyClassRestrictedQualsOnBaseElements_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyClassRestrictedQualsOnBaseElements_Invoke_myMethod(
    MyClassRestrictedQualsOnBaseElements_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyClassRestrictedQualsOnBaseElements* instanceName,
    const MyClassRestrictedQualsOnBaseElements_myMethod* in);


#endif /* _MyClassRestrictedQualsOnBaseElements_h */
