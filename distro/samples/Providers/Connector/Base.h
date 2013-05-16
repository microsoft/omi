/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Base_h
#define _Base_h

#include <MI.h>

/*
**==============================================================================
**
** Base [XYZ_Base]
**
** Keys:
**
**==============================================================================
*/

typedef struct _Base
{
    MI_Instance __instance;
    /* Base properties */
    MI_ConstUint32Field X;
    MI_ConstUint32Field Property;
}
Base;

typedef struct _Base_Ref
{
    Base* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Base_Ref;

typedef struct _Base_ConstRef
{
    MI_CONST Base* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Base_ConstRef;

typedef struct _Base_Array
{
    struct _Base** data;
    MI_Uint32 size;
}
Base_Array;

typedef struct _Base_ConstArray
{
    struct _Base MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Base_ConstArray;

typedef struct _Base_ArrayRef
{
    Base_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Base_ArrayRef;

typedef struct _Base_ConstArrayRef
{
    Base_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Base_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Base_rtti;

MI_INLINE MI_Result MI_CALL Base_Construct(
    Base* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Base_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Base_Clone(
    const Base* self,
    Base** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Base_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Base_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Base_Destruct(Base* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Base_Delete(Base* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Base_Post(
    const Base* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Base_Set_X(
    Base* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->X)->value = x;
    ((MI_Uint32Field*)&self->X)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Base_Clear_X(
    Base* self)
{
    memset((void*)&self->X, 0, sizeof(self->X));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Base_Set_Property(
    Base* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Property)->value = x;
    ((MI_Uint32Field*)&self->Property)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Base_Clear_Property(
    Base* self)
{
    memset((void*)&self->Property, 0, sizeof(self->Property));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Base.Foo()
**
**==============================================================================
*/

typedef struct _Base_Foo
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
Base_Foo;

MI_EXTERN_C MI_CONST MI_MethodDecl Base_Foo_rtti;

MI_INLINE MI_Result MI_CALL Base_Foo_Construct(
    Base_Foo* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &Base_Foo_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Base_Foo_Clone(
    const Base_Foo* self,
    Base_Foo** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Base_Foo_Destruct(
    Base_Foo* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Base_Foo_Delete(
    Base_Foo* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Base_Foo_Post(
    const Base_Foo* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Base_Foo_Set_MIReturn(
    Base_Foo* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Base_Foo_Clear_MIReturn(
    Base_Foo* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Base provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Base_Self Base_Self;

MI_EXTERN_C void MI_CALL Base_Load(
    Base_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Base_Unload(
    Base_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Base_Invoke_Foo(
    Base_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Base* instanceName,
    const Base_Foo* in);


#endif /* _Base_h */
