/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _PS_ModuleToModuleFile_h
#define _PS_ModuleToModuleFile_h

#include <MI.h>
#include "CIM_Dependency.h"
#include "PS_Module.h"
#include "PS_ModuleFile.h"

/*
**==============================================================================
**
** PS_ModuleToModuleFile [PS_ModuleToModuleFile]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _PS_ModuleToModuleFile /* extends CIM_Dependency */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ PS_Module_ConstRef Antecedent;
    /*KEY*/ PS_ModuleFile_ConstRef Dependent;
    /* PS_ModuleToModuleFile properties */
}
PS_ModuleToModuleFile;

typedef struct _PS_ModuleToModuleFile_Ref
{
    PS_ModuleToModuleFile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PS_ModuleToModuleFile_Ref;

typedef struct _PS_ModuleToModuleFile_ConstRef
{
    MI_CONST PS_ModuleToModuleFile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PS_ModuleToModuleFile_ConstRef;

typedef struct _PS_ModuleToModuleFile_Array
{
    struct _PS_ModuleToModuleFile** data;
    MI_Uint32 size;
}
PS_ModuleToModuleFile_Array;

typedef struct _PS_ModuleToModuleFile_ConstArray
{
    struct _PS_ModuleToModuleFile MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
PS_ModuleToModuleFile_ConstArray;

typedef struct _PS_ModuleToModuleFile_ArrayRef
{
    PS_ModuleToModuleFile_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PS_ModuleToModuleFile_ArrayRef;

typedef struct _PS_ModuleToModuleFile_ConstArrayRef
{
    PS_ModuleToModuleFile_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PS_ModuleToModuleFile_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl PS_ModuleToModuleFile_rtti;

MI_INLINE MI_Result MI_CALL PS_ModuleToModuleFile_Construct(
    PS_ModuleToModuleFile* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &PS_ModuleToModuleFile_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL PS_ModuleToModuleFile_Clone(
    const PS_ModuleToModuleFile* self,
    PS_ModuleToModuleFile** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL PS_ModuleToModuleFile_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &PS_ModuleToModuleFile_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL PS_ModuleToModuleFile_Destruct(PS_ModuleToModuleFile* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL PS_ModuleToModuleFile_Delete(PS_ModuleToModuleFile* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL PS_ModuleToModuleFile_Post(
    const PS_ModuleToModuleFile* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL PS_ModuleToModuleFile_Set_Antecedent(
    PS_ModuleToModuleFile* self,
    const PS_Module* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL PS_ModuleToModuleFile_SetPtr_Antecedent(
    PS_ModuleToModuleFile* self,
    const PS_Module* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PS_ModuleToModuleFile_Clear_Antecedent(
    PS_ModuleToModuleFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL PS_ModuleToModuleFile_Set_Dependent(
    PS_ModuleToModuleFile* self,
    const PS_ModuleFile* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL PS_ModuleToModuleFile_SetPtr_Dependent(
    PS_ModuleToModuleFile* self,
    const PS_ModuleFile* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PS_ModuleToModuleFile_Clear_Dependent(
    PS_ModuleToModuleFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** PS_ModuleToModuleFile provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _PS_ModuleToModuleFile_Self PS_ModuleToModuleFile_Self;

MI_EXTERN_C void MI_CALL PS_ModuleToModuleFile_Load(
    PS_ModuleToModuleFile_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL PS_ModuleToModuleFile_Unload(
    PS_ModuleToModuleFile_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL PS_ModuleToModuleFile_EnumerateInstances(
    PS_ModuleToModuleFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL PS_ModuleToModuleFile_GetInstance(
    PS_ModuleToModuleFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_ModuleToModuleFile* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL PS_ModuleToModuleFile_CreateInstance(
    PS_ModuleToModuleFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_ModuleToModuleFile* newInstance);

MI_EXTERN_C void MI_CALL PS_ModuleToModuleFile_ModifyInstance(
    PS_ModuleToModuleFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_ModuleToModuleFile* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL PS_ModuleToModuleFile_DeleteInstance(
    PS_ModuleToModuleFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_ModuleToModuleFile* instanceName);

MI_EXTERN_C void MI_CALL PS_ModuleToModuleFile_AssociatorInstancesAntecedent(
    PS_ModuleToModuleFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_Module* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL PS_ModuleToModuleFile_AssociatorInstancesDependent(
    PS_ModuleToModuleFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_ModuleFile* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL PS_ModuleToModuleFile_ReferenceInstancesAntecedent(
    PS_ModuleToModuleFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_Module* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL PS_ModuleToModuleFile_ReferenceInstancesDependent(
    PS_ModuleToModuleFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_ModuleFile* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _PS_ModuleToModuleFile_h */
