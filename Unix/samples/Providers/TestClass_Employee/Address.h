/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Address_h
#define _Address_h

#include <MI.h>

/*
**==============================================================================
**
** Address [Address]
**
** Keys:
**    addressId
**
**==============================================================================
*/

typedef struct _Address
{
    MI_Instance __instance;
    /* Address properties */
    /*KEY*/ MI_ConstUint32Field addressId;
    MI_ConstStringField City;
    MI_ConstUint16Field zipCode;
}
Address;

typedef struct _Address_Ref
{
    Address* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Address_Ref;

typedef struct _Address_ConstRef
{
    MI_CONST Address* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Address_ConstRef;

typedef struct _Address_Array
{
    struct _Address** data;
    MI_Uint32 size;
}
Address_Array;

typedef struct _Address_ConstArray
{
    struct _Address MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Address_ConstArray;

typedef struct _Address_ArrayRef
{
    Address_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Address_ArrayRef;

typedef struct _Address_ConstArrayRef
{
    Address_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Address_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Address_rtti;

MI_INLINE MI_Result MI_CALL Address_Construct(
    _Inout_ Address* self,
    _In_ MI_Context* context)
{
    return MI_ConstructInstance(context, &Address_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Address_Clone(
    _In_ const Address* self,
    _Outptr_ Address** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Address_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Address_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Address_Destruct(_Inout_ Address* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Address_Delete(_Inout_ Address* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Address_Post(
    _In_ const Address* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Address_Set_addressId(
    _Inout_ Address* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->addressId)->value = x;
    ((MI_Uint32Field*)&self->addressId)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Address_Clear_addressId(
    _Inout_ Address* self)
{
    memset((void*)&self->addressId, 0, sizeof(self->addressId));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Address_Set_City(
    _Inout_ Address* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Address_SetPtr_City(
    _Inout_ Address* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Address_Clear_City(
    _Inout_ Address* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Address_Set_zipCode(
    _Inout_ Address* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->zipCode)->value = x;
    ((MI_Uint16Field*)&self->zipCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Address_Clear_zipCode(
    _Inout_ Address* self)
{
    memset((void*)&self->zipCode, 0, sizeof(self->zipCode));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Address.OperationOptionsStatic()
**
**==============================================================================
*/

typedef struct _Address_OperationOptionsStatic
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
Address_OperationOptionsStatic;

MI_EXTERN_C MI_CONST MI_MethodDecl Address_OperationOptionsStatic_rtti;

MI_INLINE MI_Result MI_CALL Address_OperationOptionsStatic_Construct(
    _Inout_ Address_OperationOptionsStatic* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &Address_OperationOptionsStatic_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Address_OperationOptionsStatic_Clone(
    _In_ const Address_OperationOptionsStatic* self,
    _Outptr_ Address_OperationOptionsStatic** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Address_OperationOptionsStatic_Destruct(
    _Inout_ Address_OperationOptionsStatic* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Address_OperationOptionsStatic_Delete(
    _Inout_ Address_OperationOptionsStatic* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Address_OperationOptionsStatic_Post(
    _In_ const Address_OperationOptionsStatic* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Address_OperationOptionsStatic_Set_MIReturn(
    _Inout_ Address_OperationOptionsStatic* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Address_OperationOptionsStatic_Clear_MIReturn(
    _Inout_ Address_OperationOptionsStatic* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Address.OperationOptionsInstance()
**
**==============================================================================
*/

typedef struct _Address_OperationOptionsInstance
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
Address_OperationOptionsInstance;

MI_EXTERN_C MI_CONST MI_MethodDecl Address_OperationOptionsInstance_rtti;

MI_INLINE MI_Result MI_CALL Address_OperationOptionsInstance_Construct(
    _Inout_ Address_OperationOptionsInstance* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &Address_OperationOptionsInstance_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Address_OperationOptionsInstance_Clone(
    _In_ const Address_OperationOptionsInstance* self,
    _Outptr_ Address_OperationOptionsInstance** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Address_OperationOptionsInstance_Destruct(
    _Inout_ Address_OperationOptionsInstance* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Address_OperationOptionsInstance_Delete(
    _Inout_ Address_OperationOptionsInstance* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Address_OperationOptionsInstance_Post(
    _In_ const Address_OperationOptionsInstance* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Address_OperationOptionsInstance_Set_MIReturn(
    _Inout_ Address_OperationOptionsInstance* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Address_OperationOptionsInstance_Clear_MIReturn(
    _Inout_ Address_OperationOptionsInstance* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Address provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Address_Self Address_Self;

MI_EXTERN_C void MI_CALL Address_Load(
    _Outptr_result_maybenull_ Address_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL Address_Unload(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL Address_EnumerateInstances(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Address_GetInstance(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Address* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Address_CreateInstance(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Address* newInstance);

MI_EXTERN_C void MI_CALL Address_ModifyInstance(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Address* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Address_DeleteInstance(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Address* instanceName);

MI_EXTERN_C void MI_CALL Address_Invoke_OperationOptionsStatic(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Address* instanceName,
    _In_opt_ const Address_OperationOptionsStatic* in);

MI_EXTERN_C void MI_CALL Address_Invoke_OperationOptionsInstance(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Address* instanceName,
    _In_opt_ const Address_OperationOptionsInstance* in);


#endif /* _Address_h */
