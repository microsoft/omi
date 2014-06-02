/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ContactInfo_h
#define _ContactInfo_h

#include <MI.h>
#include "Address.h"

/*
**==============================================================================
**
** ContactInfo [ContactInfo]
**
** Keys:
**    addressId
**
**==============================================================================
*/

typedef struct _ContactInfo /* extends Address */
{
    MI_Instance __instance;
    /* Address properties */
    /*KEY*/ MI_ConstUint32Field addressId;
    MI_ConstStringField City;
    MI_ConstUint16Field zipCode;
    /* ContactInfo properties */
    MI_ConstStringAField phoneNumber;
}
ContactInfo;

typedef struct _ContactInfo_Ref
{
    ContactInfo* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ContactInfo_Ref;

typedef struct _ContactInfo_ConstRef
{
    MI_CONST ContactInfo* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ContactInfo_ConstRef;

typedef struct _ContactInfo_Array
{
    struct _ContactInfo** data;
    MI_Uint32 size;
}
ContactInfo_Array;

typedef struct _ContactInfo_ConstArray
{
    struct _ContactInfo MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ContactInfo_ConstArray;

typedef struct _ContactInfo_ArrayRef
{
    ContactInfo_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ContactInfo_ArrayRef;

typedef struct _ContactInfo_ConstArrayRef
{
    ContactInfo_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ContactInfo_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ContactInfo_rtti;

MI_INLINE MI_Result MI_CALL ContactInfo_Construct(
    _Inout_ ContactInfo* self,
    _In_ MI_Context* context)
{
    return MI_ConstructInstance(context, &ContactInfo_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_Clone(
    _In_ const ContactInfo* self,
    _Outptr_ ContactInfo** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ContactInfo_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ContactInfo_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ContactInfo_Destruct(_Inout_ ContactInfo* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_Delete(_Inout_ ContactInfo* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_Post(
    _In_ const ContactInfo* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_Set_addressId(
    _Inout_ ContactInfo* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->addressId)->value = x;
    ((MI_Uint32Field*)&self->addressId)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ContactInfo_Clear_addressId(
    _Inout_ ContactInfo* self)
{
    memset((void*)&self->addressId, 0, sizeof(self->addressId));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ContactInfo_Set_City(
    _Inout_ ContactInfo* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ContactInfo_SetPtr_City(
    _Inout_ ContactInfo* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ContactInfo_Clear_City(
    _Inout_ ContactInfo* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ContactInfo_Set_zipCode(
    _Inout_ ContactInfo* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->zipCode)->value = x;
    ((MI_Uint16Field*)&self->zipCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ContactInfo_Clear_zipCode(
    _Inout_ ContactInfo* self)
{
    memset((void*)&self->zipCode, 0, sizeof(self->zipCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ContactInfo_Set_phoneNumber(
    _Inout_ ContactInfo* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL ContactInfo_SetPtr_phoneNumber(
    _Inout_ ContactInfo* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ContactInfo_Clear_phoneNumber(
    _Inout_ ContactInfo* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** ContactInfo.OperationOptionsStatic()
**
**==============================================================================
*/

typedef struct _ContactInfo_OperationOptionsStatic
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ContactInfo_OperationOptionsStatic;

MI_EXTERN_C MI_CONST MI_MethodDecl ContactInfo_OperationOptionsStatic_rtti;

MI_INLINE MI_Result MI_CALL ContactInfo_OperationOptionsStatic_Construct(
    _Inout_ ContactInfo_OperationOptionsStatic* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &ContactInfo_OperationOptionsStatic_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_OperationOptionsStatic_Clone(
    _In_ const ContactInfo_OperationOptionsStatic* self,
    _Outptr_ ContactInfo_OperationOptionsStatic** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_OperationOptionsStatic_Destruct(
    _Inout_ ContactInfo_OperationOptionsStatic* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_OperationOptionsStatic_Delete(
    _Inout_ ContactInfo_OperationOptionsStatic* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_OperationOptionsStatic_Post(
    _In_ const ContactInfo_OperationOptionsStatic* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_OperationOptionsStatic_Set_MIReturn(
    _Inout_ ContactInfo_OperationOptionsStatic* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ContactInfo_OperationOptionsStatic_Clear_MIReturn(
    _Inout_ ContactInfo_OperationOptionsStatic* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ContactInfo.OperationOptionsInstance()
**
**==============================================================================
*/

typedef struct _ContactInfo_OperationOptionsInstance
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ContactInfo_OperationOptionsInstance;

MI_EXTERN_C MI_CONST MI_MethodDecl ContactInfo_OperationOptionsInstance_rtti;

MI_INLINE MI_Result MI_CALL ContactInfo_OperationOptionsInstance_Construct(
    _Inout_ ContactInfo_OperationOptionsInstance* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &ContactInfo_OperationOptionsInstance_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_OperationOptionsInstance_Clone(
    _In_ const ContactInfo_OperationOptionsInstance* self,
    _Outptr_ ContactInfo_OperationOptionsInstance** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_OperationOptionsInstance_Destruct(
    _Inout_ ContactInfo_OperationOptionsInstance* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_OperationOptionsInstance_Delete(
    _Inout_ ContactInfo_OperationOptionsInstance* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_OperationOptionsInstance_Post(
    _In_ const ContactInfo_OperationOptionsInstance* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_OperationOptionsInstance_Set_MIReturn(
    _Inout_ ContactInfo_OperationOptionsInstance* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ContactInfo_OperationOptionsInstance_Clear_MIReturn(
    _Inout_ ContactInfo_OperationOptionsInstance* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ContactInfo.GetPhoneNumbers()
**
**==============================================================================
*/

typedef struct _ContactInfo_GetPhoneNumbers
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ContactInfo_GetPhoneNumbers;

MI_EXTERN_C MI_CONST MI_MethodDecl ContactInfo_GetPhoneNumbers_rtti;

MI_INLINE MI_Result MI_CALL ContactInfo_GetPhoneNumbers_Construct(
    _Inout_ ContactInfo_GetPhoneNumbers* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &ContactInfo_GetPhoneNumbers_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_GetPhoneNumbers_Clone(
    _In_ const ContactInfo_GetPhoneNumbers* self,
    _Outptr_ ContactInfo_GetPhoneNumbers** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_GetPhoneNumbers_Destruct(
    _Inout_ ContactInfo_GetPhoneNumbers* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_GetPhoneNumbers_Delete(
    _Inout_ ContactInfo_GetPhoneNumbers* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_GetPhoneNumbers_Post(
    _In_ const ContactInfo_GetPhoneNumbers* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ContactInfo_GetPhoneNumbers_Set_MIReturn(
    _Inout_ ContactInfo_GetPhoneNumbers* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ContactInfo_GetPhoneNumbers_Clear_MIReturn(
    _Inout_ ContactInfo_GetPhoneNumbers* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ContactInfo provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ContactInfo_Self ContactInfo_Self;

MI_EXTERN_C void MI_CALL ContactInfo_Load(
    _Outptr_result_maybenull_ ContactInfo_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL ContactInfo_Unload(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL ContactInfo_EnumerateInstances(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ContactInfo_GetInstance(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ContactInfo* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ContactInfo_CreateInstance(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ContactInfo* newInstance);

MI_EXTERN_C void MI_CALL ContactInfo_ModifyInstance(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ContactInfo* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ContactInfo_DeleteInstance(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ContactInfo* instanceName);

MI_EXTERN_C void MI_CALL ContactInfo_Invoke_OperationOptionsStatic(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const ContactInfo* instanceName,
    _In_opt_ const ContactInfo_OperationOptionsStatic* in);

MI_EXTERN_C void MI_CALL ContactInfo_Invoke_OperationOptionsInstance(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const ContactInfo* instanceName,
    _In_opt_ const ContactInfo_OperationOptionsInstance* in);

MI_EXTERN_C void MI_CALL ContactInfo_Invoke_GetPhoneNumbers(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const ContactInfo* instanceName,
    _In_opt_ const ContactInfo_GetPhoneNumbers* in);


#endif /* _ContactInfo_h */
