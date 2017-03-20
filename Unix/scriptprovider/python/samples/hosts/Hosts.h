/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Hosts_h
#define _Hosts_h

#include <MI.h>

/*
**==============================================================================
**
** Hosts [Hosts]
**
** Keys:
**    FQDN
**
**==============================================================================
*/

typedef struct _Hosts
{
    MI_Instance __instance;
    /* Hosts properties */
    /*KEY*/ MI_ConstStringField FQDN;
    MI_ConstStringField IPAddress;
}
Hosts;

typedef struct _Hosts_Ref
{
    Hosts* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Hosts_Ref;

typedef struct _Hosts_ConstRef
{
    MI_CONST Hosts* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Hosts_ConstRef;

typedef struct _Hosts_Array
{
    struct _Hosts** data;
    MI_Uint32 size;
}
Hosts_Array;

typedef struct _Hosts_ConstArray
{
    struct _Hosts MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Hosts_ConstArray;

typedef struct _Hosts_ArrayRef
{
    Hosts_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Hosts_ArrayRef;

typedef struct _Hosts_ConstArrayRef
{
    Hosts_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Hosts_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Hosts_rtti;

MI_INLINE MI_Result MI_CALL Hosts_Construct(
    Hosts* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Hosts_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Hosts_Clone(
    const Hosts* self,
    Hosts** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Hosts_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Hosts_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Hosts_Destruct(Hosts* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Hosts_Delete(Hosts* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Hosts_Post(
    const Hosts* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Hosts_Set_FQDN(
    Hosts* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Hosts_SetPtr_FQDN(
    Hosts* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Hosts_Clear_FQDN(
    Hosts* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Hosts_Set_IPAddress(
    Hosts* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Hosts_SetPtr_IPAddress(
    Hosts* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Hosts_Clear_IPAddress(
    Hosts* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** Hosts.Ping()
**
**==============================================================================
*/

typedef struct _Hosts_Ping
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint64Field MIReturn;
}
Hosts_Ping;

MI_EXTERN_C MI_CONST MI_MethodDecl Hosts_Ping_rtti;

MI_INLINE MI_Result MI_CALL Hosts_Ping_Construct(
    Hosts_Ping* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &Hosts_Ping_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Hosts_Ping_Clone(
    const Hosts_Ping* self,
    Hosts_Ping** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Hosts_Ping_Destruct(
    Hosts_Ping* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Hosts_Ping_Delete(
    Hosts_Ping* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Hosts_Ping_Post(
    const Hosts_Ping* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Hosts_Ping_Set_MIReturn(
    Hosts_Ping* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MIReturn)->value = x;
    ((MI_Uint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Hosts_Ping_Clear_MIReturn(
    Hosts_Ping* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Hosts provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Hosts_Self Hosts_Self;

MI_EXTERN_C void MI_CALL Hosts_Load(
    Hosts_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Hosts_Unload(
    Hosts_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Hosts_EnumerateInstances(
    Hosts_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Hosts_GetInstance(
    Hosts_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Hosts* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Hosts_CreateInstance(
    Hosts_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Hosts* newInstance);

MI_EXTERN_C void MI_CALL Hosts_ModifyInstance(
    Hosts_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Hosts* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Hosts_DeleteInstance(
    Hosts_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Hosts* instanceName);

MI_EXTERN_C void MI_CALL Hosts_Invoke_Ping(
    Hosts_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Hosts* instanceName,
    const Hosts_Ping* in);


#endif /* _Hosts_h */
