/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyDerivedClassOfRestrictedQualsOnBaseElements_h
#define _MyDerivedClassOfRestrictedQualsOnBaseElements_h

#include <MI.h>
#include "MyClassRestrictedQualsOnBaseElements.h"

/*
**==============================================================================
**
** MyDerivedClassOfRestrictedQualsOnBaseElements [MyDerivedClassOfRestrictedQualsOnBaseElements]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyDerivedClassOfRestrictedQualsOnBaseElements /* extends MyClassRestrictedQualsOnBaseElements */
{
    MI_Instance __instance;
    /* MyClassRestrictedQualsOnBaseElements properties */
    MI_ConstUint32Field myProp;
    /* MyDerivedClassOfRestrictedQualsOnBaseElements properties */
}
MyDerivedClassOfRestrictedQualsOnBaseElements;

typedef struct _MyDerivedClassOfRestrictedQualsOnBaseElements_Ref
{
    MyDerivedClassOfRestrictedQualsOnBaseElements* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyDerivedClassOfRestrictedQualsOnBaseElements_Ref;

typedef struct _MyDerivedClassOfRestrictedQualsOnBaseElements_ConstRef
{
    MI_CONST MyDerivedClassOfRestrictedQualsOnBaseElements* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyDerivedClassOfRestrictedQualsOnBaseElements_ConstRef;

typedef struct _MyDerivedClassOfRestrictedQualsOnBaseElements_Array
{
    struct _MyDerivedClassOfRestrictedQualsOnBaseElements** data;
    MI_Uint32 size;
}
MyDerivedClassOfRestrictedQualsOnBaseElements_Array;

typedef struct _MyDerivedClassOfRestrictedQualsOnBaseElements_ConstArray
{
    struct _MyDerivedClassOfRestrictedQualsOnBaseElements MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyDerivedClassOfRestrictedQualsOnBaseElements_ConstArray;

typedef struct _MyDerivedClassOfRestrictedQualsOnBaseElements_ArrayRef
{
    MyDerivedClassOfRestrictedQualsOnBaseElements_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyDerivedClassOfRestrictedQualsOnBaseElements_ArrayRef;

typedef struct _MyDerivedClassOfRestrictedQualsOnBaseElements_ConstArrayRef
{
    MyDerivedClassOfRestrictedQualsOnBaseElements_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyDerivedClassOfRestrictedQualsOnBaseElements_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyDerivedClassOfRestrictedQualsOnBaseElements_rtti;

MI_INLINE MI_Result MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_Construct(
    MyDerivedClassOfRestrictedQualsOnBaseElements* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyDerivedClassOfRestrictedQualsOnBaseElements_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_Clone(
    const MyDerivedClassOfRestrictedQualsOnBaseElements* self,
    MyDerivedClassOfRestrictedQualsOnBaseElements** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyDerivedClassOfRestrictedQualsOnBaseElements_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_Destruct(MyDerivedClassOfRestrictedQualsOnBaseElements* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_Delete(MyDerivedClassOfRestrictedQualsOnBaseElements* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_Post(
    const MyDerivedClassOfRestrictedQualsOnBaseElements* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_Set_myProp(
    MyDerivedClassOfRestrictedQualsOnBaseElements* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->myProp)->value = x;
    ((MI_Uint32Field*)&self->myProp)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_Clear_myProp(
    MyDerivedClassOfRestrictedQualsOnBaseElements* self)
{
    memset((void*)&self->myProp, 0, sizeof(self->myProp));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyDerivedClassOfRestrictedQualsOnBaseElements.myMethod()
**
**==============================================================================
*/

typedef struct _MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_rtti;

MI_INLINE MI_Result MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Construct(
    MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Clone(
    const MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod* self,
    MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Destruct(
    MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Delete(
    MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Post(
    const MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Set_MIReturn(
    MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Clear_MIReturn(
    MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyDerivedClassOfRestrictedQualsOnBaseElements provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyDerivedClassOfRestrictedQualsOnBaseElements_Self MyDerivedClassOfRestrictedQualsOnBaseElements_Self;

MI_EXTERN_C void MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_Load(
    MyDerivedClassOfRestrictedQualsOnBaseElements_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_Unload(
    MyDerivedClassOfRestrictedQualsOnBaseElements_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_Invoke_myMethod(
    MyDerivedClassOfRestrictedQualsOnBaseElements_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyDerivedClassOfRestrictedQualsOnBaseElements* instanceName,
    const MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod* in);


#endif /* _MyDerivedClassOfRestrictedQualsOnBaseElements_h */
