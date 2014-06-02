/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Derived_h
#define _Derived_h

#include <MI.h>
#include "Base.h"

/*
**==============================================================================
**
** Derived [XYZ_Derived]
**
** Keys:
**
**==============================================================================
*/

typedef struct _Derived /* extends XYZ_Base */
{
    MI_Instance __instance;
    /* Base properties */
    MI_ConstUint32Field X;
    MI_ConstUint32Field Property;
    /* Derived properties */
}
Derived;

typedef struct _Derived_Ref
{
    Derived* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Derived_Ref;

typedef struct _Derived_ConstRef
{
    MI_CONST Derived* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Derived_ConstRef;

typedef struct _Derived_Array
{
    struct _Derived** data;
    MI_Uint32 size;
}
Derived_Array;

typedef struct _Derived_ConstArray
{
    struct _Derived MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Derived_ConstArray;

typedef struct _Derived_ArrayRef
{
    Derived_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Derived_ArrayRef;

typedef struct _Derived_ConstArrayRef
{
    Derived_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Derived_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Derived_rtti;

MI_INLINE MI_Result MI_CALL Derived_Construct(
    Derived* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Derived_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Derived_Clone(
    const Derived* self,
    Derived** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Derived_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Derived_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Derived_Destruct(Derived* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Derived_Delete(Derived* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Derived_Post(
    const Derived* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Derived_Set_X(
    Derived* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->X)->value = x;
    ((MI_Uint32Field*)&self->X)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Derived_Clear_X(
    Derived* self)
{
    memset((void*)&self->X, 0, sizeof(self->X));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Derived_Set_Property(
    Derived* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Property)->value = x;
    ((MI_Uint32Field*)&self->Property)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Derived_Clear_Property(
    Derived* self)
{
    memset((void*)&self->Property, 0, sizeof(self->Property));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Derived.Foo()
**
**==============================================================================
*/

typedef struct _Derived_Foo
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
Derived_Foo;

MI_EXTERN_C MI_CONST MI_MethodDecl Derived_Foo_rtti;

MI_INLINE MI_Result MI_CALL Derived_Foo_Construct(
    Derived_Foo* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &Derived_Foo_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Derived_Foo_Clone(
    const Derived_Foo* self,
    Derived_Foo** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Derived_Foo_Destruct(
    Derived_Foo* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Derived_Foo_Delete(
    Derived_Foo* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Derived_Foo_Post(
    const Derived_Foo* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Derived_Foo_Set_MIReturn(
    Derived_Foo* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Derived_Foo_Clear_MIReturn(
    Derived_Foo* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Derived provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Derived_Self Derived_Self;

MI_EXTERN_C void MI_CALL Derived_Load(
    Derived_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Derived_Unload(
    Derived_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Derived_Invoke_Foo(
    Derived_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Derived* instanceName,
    const Derived_Foo* in);


#endif /* _Derived_h */
