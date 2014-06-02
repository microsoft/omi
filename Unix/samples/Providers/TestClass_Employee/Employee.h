/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Employee_h
#define _Employee_h

#include <MI.h>

/*
**==============================================================================
**
** Employee [Employee]
**
** Keys:
**    SSN
**
**==============================================================================
*/

typedef struct _Employee
{
    MI_Instance __instance;
    /* Employee properties */
    /*KEY*/ MI_ConstStringField SSN;
    MI_ConstStringField firstName;
    MI_ConstStringField lastName;
    MI_ConstDatetimeField dateOfBirth;
}
Employee;

typedef struct _Employee_Ref
{
    Employee* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Employee_Ref;

typedef struct _Employee_ConstRef
{
    MI_CONST Employee* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Employee_ConstRef;

typedef struct _Employee_Array
{
    struct _Employee** data;
    MI_Uint32 size;
}
Employee_Array;

typedef struct _Employee_ConstArray
{
    struct _Employee MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Employee_ConstArray;

typedef struct _Employee_ArrayRef
{
    Employee_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Employee_ArrayRef;

typedef struct _Employee_ConstArrayRef
{
    Employee_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Employee_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Employee_rtti;

MI_INLINE MI_Result MI_CALL Employee_Construct(
    Employee* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Employee_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Employee_Clone(
    const Employee* self,
    Employee** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Employee_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Employee_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Employee_Destruct(Employee* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Employee_Delete(Employee* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Employee_Post(
    const Employee* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Employee_Set_SSN(
    Employee* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Employee_SetPtr_SSN(
    Employee* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Employee_Clear_SSN(
    Employee* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Employee_Set_firstName(
    Employee* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Employee_SetPtr_firstName(
    Employee* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Employee_Clear_firstName(
    Employee* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Employee_Set_lastName(
    Employee* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Employee_SetPtr_lastName(
    Employee* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Employee_Clear_lastName(
    Employee* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL Employee_Set_dateOfBirth(
    Employee* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->dateOfBirth)->value = x;
    ((MI_DatetimeField*)&self->dateOfBirth)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Employee_Clear_dateOfBirth(
    Employee* self)
{
    memset((void*)&self->dateOfBirth, 0, sizeof(self->dateOfBirth));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Employee provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Employee_Self Employee_Self;

MI_EXTERN_C void MI_CALL Employee_Load(
    Employee_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Employee_Unload(
    Employee_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Employee_EnumerateInstances(
    Employee_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Employee_GetInstance(
    Employee_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Employee* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Employee_CreateInstance(
    Employee_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Employee* newInstance);

MI_EXTERN_C void MI_CALL Employee_ModifyInstance(
    Employee_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Employee* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Employee_DeleteInstance(
    Employee_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Employee* instanceName);


#endif /* _Employee_h */
