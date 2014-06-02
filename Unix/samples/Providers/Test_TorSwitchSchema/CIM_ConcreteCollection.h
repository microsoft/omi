/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_ConcreteCollection_h
#define _CIM_ConcreteCollection_h

#include <MI.h>
#include "CIM_Collection.h"

/*
**==============================================================================
**
** CIM_ConcreteCollection [CIM_ConcreteCollection]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_ConcreteCollection /* extends CIM_Collection */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Collection properties */
    /* CIM_ConcreteCollection properties */
}
CIM_ConcreteCollection;

typedef struct _CIM_ConcreteCollection_Ref
{
    CIM_ConcreteCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConcreteCollection_Ref;

typedef struct _CIM_ConcreteCollection_ConstRef
{
    MI_CONST CIM_ConcreteCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConcreteCollection_ConstRef;

typedef struct _CIM_ConcreteCollection_Array
{
    struct _CIM_ConcreteCollection** data;
    MI_Uint32 size;
}
CIM_ConcreteCollection_Array;

typedef struct _CIM_ConcreteCollection_ConstArray
{
    struct _CIM_ConcreteCollection MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_ConcreteCollection_ConstArray;

typedef struct _CIM_ConcreteCollection_ArrayRef
{
    CIM_ConcreteCollection_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConcreteCollection_ArrayRef;

typedef struct _CIM_ConcreteCollection_ConstArrayRef
{
    CIM_ConcreteCollection_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConcreteCollection_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_ConcreteCollection_rtti;

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_Construct(
    _Out_ CIM_ConcreteCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_ConcreteCollection_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_Clone(
    _In_ const CIM_ConcreteCollection* self,
    _Outptr_ CIM_ConcreteCollection** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_ConcreteCollection_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_ConcreteCollection_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_Destruct(_Inout_ CIM_ConcreteCollection* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_Delete(_Inout_ CIM_ConcreteCollection* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_Post(
    _In_ const CIM_ConcreteCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_Set_InstanceID(
    _Inout_ CIM_ConcreteCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_SetPtr_InstanceID(
    _Inout_ CIM_ConcreteCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_Clear_InstanceID(
    _Inout_ CIM_ConcreteCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_Set_Caption(
    _Inout_ CIM_ConcreteCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_SetPtr_Caption(
    _Inout_ CIM_ConcreteCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_Clear_Caption(
    _Inout_ CIM_ConcreteCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_Set_Description(
    _Inout_ CIM_ConcreteCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_SetPtr_Description(
    _Inout_ CIM_ConcreteCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_Clear_Description(
    _Inout_ CIM_ConcreteCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_Set_ElementName(
    _Inout_ CIM_ConcreteCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_SetPtr_ElementName(
    _Inout_ CIM_ConcreteCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteCollection_Clear_ElementName(
    _Inout_ CIM_ConcreteCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** CIM_ConcreteCollection provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_ConcreteCollection_Self CIM_ConcreteCollection_Self;

MI_EXTERN_C void MI_CALL CIM_ConcreteCollection_Load(
    _Outptr_result_maybenull_ CIM_ConcreteCollection_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_ConcreteCollection_Unload(
    _In_opt_ CIM_ConcreteCollection_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_ConcreteCollection_EnumerateInstances(
    _In_opt_ CIM_ConcreteCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ConcreteCollection_GetInstance(
    _In_opt_ CIM_ConcreteCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ConcreteCollection* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_ConcreteCollection_CreateInstance(
    _In_opt_ CIM_ConcreteCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ConcreteCollection* newInstance);

MI_EXTERN_C void MI_CALL CIM_ConcreteCollection_ModifyInstance(
    _In_opt_ CIM_ConcreteCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ConcreteCollection* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_ConcreteCollection_DeleteInstance(
    _In_opt_ CIM_ConcreteCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ConcreteCollection* instanceName);


#endif /* _CIM_ConcreteCollection_h */
