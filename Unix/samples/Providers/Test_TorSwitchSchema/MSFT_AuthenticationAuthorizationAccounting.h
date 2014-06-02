/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_AuthenticationAuthorizationAccounting_h
#define _MSFT_AuthenticationAuthorizationAccounting_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_AuthenticationAuthorizationAccounting [MSFT_AuthenticationAuthorizationAccounting]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_AuthenticationAuthorizationAccounting
{
    MI_Instance __instance;
    /* MSFT_AuthenticationAuthorizationAccounting properties */
    MI_ConstStringField Server;
    MI_ConstUint16Field LoginDefaultGroup;
    MI_ConstStringField OtherLoginDefaultGroup;
    MI_ConstUint16Field AccountingDefaultGroup;
    MI_ConstStringField OtherAccountingDefaultGroup;
    MI_ConstBooleanField Is_LoginErrorEnabled;
    MI_ConstBooleanField IsAsciiAuthentication;
}
MSFT_AuthenticationAuthorizationAccounting;

typedef struct _MSFT_AuthenticationAuthorizationAccounting_Ref
{
    MSFT_AuthenticationAuthorizationAccounting* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AuthenticationAuthorizationAccounting_Ref;

typedef struct _MSFT_AuthenticationAuthorizationAccounting_ConstRef
{
    MI_CONST MSFT_AuthenticationAuthorizationAccounting* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AuthenticationAuthorizationAccounting_ConstRef;

typedef struct _MSFT_AuthenticationAuthorizationAccounting_Array
{
    struct _MSFT_AuthenticationAuthorizationAccounting** data;
    MI_Uint32 size;
}
MSFT_AuthenticationAuthorizationAccounting_Array;

typedef struct _MSFT_AuthenticationAuthorizationAccounting_ConstArray
{
    struct _MSFT_AuthenticationAuthorizationAccounting MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_AuthenticationAuthorizationAccounting_ConstArray;

typedef struct _MSFT_AuthenticationAuthorizationAccounting_ArrayRef
{
    MSFT_AuthenticationAuthorizationAccounting_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AuthenticationAuthorizationAccounting_ArrayRef;

typedef struct _MSFT_AuthenticationAuthorizationAccounting_ConstArrayRef
{
    MSFT_AuthenticationAuthorizationAccounting_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AuthenticationAuthorizationAccounting_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_AuthenticationAuthorizationAccounting_rtti;

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Construct(
    _Out_ MSFT_AuthenticationAuthorizationAccounting* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_AuthenticationAuthorizationAccounting_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Clone(
    _In_ const MSFT_AuthenticationAuthorizationAccounting* self,
    _Outptr_ MSFT_AuthenticationAuthorizationAccounting** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_AuthenticationAuthorizationAccounting_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_AuthenticationAuthorizationAccounting_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Destruct(_Inout_ MSFT_AuthenticationAuthorizationAccounting* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Delete(_Inout_ MSFT_AuthenticationAuthorizationAccounting* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Post(
    _In_ const MSFT_AuthenticationAuthorizationAccounting* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Set_Server(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_SetPtr_Server(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Clear_Server(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Set_LoginDefaultGroup(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->LoginDefaultGroup)->value = x;
    ((MI_Uint16Field*)&self->LoginDefaultGroup)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Clear_LoginDefaultGroup(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self)
{
    memset((void*)&self->LoginDefaultGroup, 0, sizeof(self->LoginDefaultGroup));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Set_OtherLoginDefaultGroup(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_SetPtr_OtherLoginDefaultGroup(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Clear_OtherLoginDefaultGroup(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Set_AccountingDefaultGroup(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->AccountingDefaultGroup)->value = x;
    ((MI_Uint16Field*)&self->AccountingDefaultGroup)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Clear_AccountingDefaultGroup(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self)
{
    memset((void*)&self->AccountingDefaultGroup, 0, sizeof(self->AccountingDefaultGroup));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Set_OtherAccountingDefaultGroup(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_SetPtr_OtherAccountingDefaultGroup(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Clear_OtherAccountingDefaultGroup(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Set_Is_LoginErrorEnabled(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Is_LoginErrorEnabled)->value = x;
    ((MI_BooleanField*)&self->Is_LoginErrorEnabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Clear_Is_LoginErrorEnabled(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self)
{
    memset((void*)&self->Is_LoginErrorEnabled, 0, sizeof(self->Is_LoginErrorEnabled));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Set_IsAsciiAuthentication(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsAsciiAuthentication)->value = x;
    ((MI_BooleanField*)&self->IsAsciiAuthentication)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_AuthenticationAuthorizationAccounting_Clear_IsAsciiAuthentication(
    _Inout_ MSFT_AuthenticationAuthorizationAccounting* self)
{
    memset((void*)&self->IsAsciiAuthentication, 0, sizeof(self->IsAsciiAuthentication));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_AuthenticationAuthorizationAccounting provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_AuthenticationAuthorizationAccounting_Self MSFT_AuthenticationAuthorizationAccounting_Self;

MI_EXTERN_C void MI_CALL MSFT_AuthenticationAuthorizationAccounting_Load(
    _Outptr_result_maybenull_ MSFT_AuthenticationAuthorizationAccounting_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_AuthenticationAuthorizationAccounting_Unload(
    _In_opt_ MSFT_AuthenticationAuthorizationAccounting_Self* self,
    _In_ MI_Context* context);


#endif /* _MSFT_AuthenticationAuthorizationAccounting_h */
