/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_SystemSpecificCollection_h
#define _CIM_SystemSpecificCollection_h

#include <MI.h>
#include "CIM_Collection.h"

/*
**==============================================================================
**
** CIM_SystemSpecificCollection [CIM_SystemSpecificCollection]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_SystemSpecificCollection /* extends CIM_Collection */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Collection properties */
    /* CIM_SystemSpecificCollection properties */
}
CIM_SystemSpecificCollection;

typedef struct _CIM_SystemSpecificCollection_Ref
{
    CIM_SystemSpecificCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemSpecificCollection_Ref;

typedef struct _CIM_SystemSpecificCollection_ConstRef
{
    MI_CONST CIM_SystemSpecificCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemSpecificCollection_ConstRef;

typedef struct _CIM_SystemSpecificCollection_Array
{
    struct _CIM_SystemSpecificCollection** data;
    MI_Uint32 size;
}
CIM_SystemSpecificCollection_Array;

typedef struct _CIM_SystemSpecificCollection_ConstArray
{
    struct _CIM_SystemSpecificCollection MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_SystemSpecificCollection_ConstArray;

typedef struct _CIM_SystemSpecificCollection_ArrayRef
{
    CIM_SystemSpecificCollection_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemSpecificCollection_ArrayRef;

typedef struct _CIM_SystemSpecificCollection_ConstArrayRef
{
    CIM_SystemSpecificCollection_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemSpecificCollection_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_SystemSpecificCollection_rtti;

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_Construct(
    _Out_ CIM_SystemSpecificCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_SystemSpecificCollection_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_Clone(
    _In_ const CIM_SystemSpecificCollection* self,
    _Outptr_ CIM_SystemSpecificCollection** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_SystemSpecificCollection_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_SystemSpecificCollection_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_Destruct(_Inout_ CIM_SystemSpecificCollection* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_Delete(_Inout_ CIM_SystemSpecificCollection* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_Post(
    _In_ const CIM_SystemSpecificCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_Set_InstanceID(
    _Inout_ CIM_SystemSpecificCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_SetPtr_InstanceID(
    _Inout_ CIM_SystemSpecificCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_Clear_InstanceID(
    _Inout_ CIM_SystemSpecificCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_Set_Caption(
    _Inout_ CIM_SystemSpecificCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_SetPtr_Caption(
    _Inout_ CIM_SystemSpecificCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_Clear_Caption(
    _Inout_ CIM_SystemSpecificCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_Set_Description(
    _Inout_ CIM_SystemSpecificCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_SetPtr_Description(
    _Inout_ CIM_SystemSpecificCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_Clear_Description(
    _Inout_ CIM_SystemSpecificCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_Set_ElementName(
    _Inout_ CIM_SystemSpecificCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_SetPtr_ElementName(
    _Inout_ CIM_SystemSpecificCollection* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SystemSpecificCollection_Clear_ElementName(
    _Inout_ CIM_SystemSpecificCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** CIM_SystemSpecificCollection provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_SystemSpecificCollection_Self CIM_SystemSpecificCollection_Self;

MI_EXTERN_C void MI_CALL CIM_SystemSpecificCollection_Load(
    _Outptr_result_maybenull_ CIM_SystemSpecificCollection_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_SystemSpecificCollection_Unload(
    _In_opt_ CIM_SystemSpecificCollection_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_SystemSpecificCollection_EnumerateInstances(
    _In_opt_ CIM_SystemSpecificCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_SystemSpecificCollection_GetInstance(
    _In_opt_ CIM_SystemSpecificCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SystemSpecificCollection* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_SystemSpecificCollection_CreateInstance(
    _In_opt_ CIM_SystemSpecificCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SystemSpecificCollection* newInstance);

MI_EXTERN_C void MI_CALL CIM_SystemSpecificCollection_ModifyInstance(
    _In_opt_ CIM_SystemSpecificCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SystemSpecificCollection* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_SystemSpecificCollection_DeleteInstance(
    _In_opt_ CIM_SystemSpecificCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SystemSpecificCollection* instanceName);


#endif /* _CIM_SystemSpecificCollection_h */
