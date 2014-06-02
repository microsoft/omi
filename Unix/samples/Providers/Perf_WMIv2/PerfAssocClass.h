/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _PerfAssocClass_h
#define _PerfAssocClass_h

#include <MI.h>
#include "Perf_WithPsSemantics.h"
#include "Perf_NoPsSemantics.h"

/*
**==============================================================================
**
** PerfAssocClass [PerfAssocClass]
**
** Keys:
**    antecedent
**    dependent
**
**==============================================================================
*/

typedef struct _PerfAssocClass
{
    MI_Instance __instance;
    /* PerfAssocClass properties */
    /*KEY*/ Perf_WithPsSemantics_ConstRef antecedent;
    /*KEY*/ Perf_NoPsSemantics_ConstRef dependent;
}
PerfAssocClass;

typedef struct _PerfAssocClass_Ref
{
    PerfAssocClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PerfAssocClass_Ref;

typedef struct _PerfAssocClass_ConstRef
{
    MI_CONST PerfAssocClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PerfAssocClass_ConstRef;

typedef struct _PerfAssocClass_Array
{
    struct _PerfAssocClass** data;
    MI_Uint32 size;
}
PerfAssocClass_Array;

typedef struct _PerfAssocClass_ConstArray
{
    struct _PerfAssocClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
PerfAssocClass_ConstArray;

typedef struct _PerfAssocClass_ArrayRef
{
    PerfAssocClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PerfAssocClass_ArrayRef;

typedef struct _PerfAssocClass_ConstArrayRef
{
    PerfAssocClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PerfAssocClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl PerfAssocClass_rtti;

MI_INLINE MI_Result MI_CALL PerfAssocClass_Construct(
    _Inout_ PerfAssocClass* self,
    _In_ MI_Context* context)
{
    return MI_ConstructInstance(context, &PerfAssocClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL PerfAssocClass_Clone(
    _In_ const PerfAssocClass* self,
    _Outptr_ PerfAssocClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL PerfAssocClass_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &PerfAssocClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL PerfAssocClass_Destruct(_Inout_ PerfAssocClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL PerfAssocClass_Delete(_Inout_ PerfAssocClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL PerfAssocClass_Post(
    _In_ const PerfAssocClass* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL PerfAssocClass_Set_antecedent(
    _Inout_ PerfAssocClass* self,
    _In_ const Perf_WithPsSemantics* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL PerfAssocClass_SetPtr_antecedent(
    _Inout_ PerfAssocClass* self,
    _In_ const Perf_WithPsSemantics* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PerfAssocClass_Clear_antecedent(
    _Inout_ PerfAssocClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL PerfAssocClass_Set_dependent(
    _Inout_ PerfAssocClass* self,
    _In_ const Perf_NoPsSemantics* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL PerfAssocClass_SetPtr_dependent(
    _Inout_ PerfAssocClass* self,
    _In_ const Perf_NoPsSemantics* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PerfAssocClass_Clear_dependent(
    _Inout_ PerfAssocClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** PerfAssocClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _PerfAssocClass_Self PerfAssocClass_Self;

MI_EXTERN_C void MI_CALL PerfAssocClass_Load(
    _Outptr_result_maybenull_ PerfAssocClass_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL PerfAssocClass_Unload(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL PerfAssocClass_EnumerateInstances(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL PerfAssocClass_GetInstance(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const PerfAssocClass* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL PerfAssocClass_CreateInstance(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const PerfAssocClass* newInstance);

MI_EXTERN_C void MI_CALL PerfAssocClass_ModifyInstance(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const PerfAssocClass* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL PerfAssocClass_DeleteInstance(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const PerfAssocClass* instanceName);

MI_EXTERN_C void MI_CALL PerfAssocClass_AssociatorInstancesantecedent(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_WithPsSemantics* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL PerfAssocClass_AssociatorInstancesdependent(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_NoPsSemantics* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL PerfAssocClass_ReferenceInstancesantecedent(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_WithPsSemantics* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL PerfAssocClass_ReferenceInstancesdependent(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_NoPsSemantics* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _PerfAssocClass_h */
