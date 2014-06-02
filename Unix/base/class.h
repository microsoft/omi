/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */
#ifndef _CLASS_h
#define _CLASS_h

#if defined(_MSC_VER)
#if defined(GetClassName)
# undef GetClassName
#endif
#endif

#include <base/batch.h>
#include "MI.h"

#define MI_CLASS_NULL { NULL, NULL, NULL, NULL, {0, 0, 0, 0} }


/*============================================================================
 * This table should be used only internally; this provides functions which can be used to get more information
 * from schema than the MI_ClassFT functions. 
 *============================================================================
 */
typedef struct _MI_ClassExtendedFTInternal
{
    // existing functions from MI_ClassFT
    MI_Result (MI_CALL *GetClassName)(
        _In_ const MI_Class* self, 
        _Outptr_result_maybenull_z_ const MI_Char** className);

    MI_Result (MI_CALL *GetNameSpace)(
        _In_ const MI_Class* self, 
        _Outptr_result_maybenull_z_ const MI_Char** nameSpace);

    MI_Result (MI_CALL *GetServerName)(
        _In_ const MI_Class* self, 
        _Outptr_result_maybenull_z_ const MI_Char** serverName);

    MI_Result (MI_CALL *GetElementCount)(
        _In_ const MI_Class* self,
        _Out_ MI_Uint32* count);

    MI_Result (MI_CALL *GetElement)(
        _In_      const MI_Class* self, 
        _In_z_    const MI_Char* name,
        _Out_opt_ MI_Value* value,
        _Out_opt_ MI_Boolean* valueExists,
        _Out_opt_ MI_Type* type,
        _Outptr_opt_result_maybenull_z_ MI_Char **referenceClass,
        _Out_opt_ MI_QualifierSet *qualifierSet,
        _Out_opt_ MI_Uint32* flags,
        _Out_opt_ MI_Uint32* index);

    MI_Result (MI_CALL *GetElementAt)(
        _In_ const MI_Class* self, 
        MI_Uint32 index,
        _Outptr_opt_result_maybenull_z_ const MI_Char** name,
        _Out_opt_ MI_Value* value,
        _Out_opt_ MI_Boolean* valueExists,
        _Out_opt_ MI_Type* type,
        _Outptr_opt_result_maybenull_z_ MI_Char **referenceClass,
        _Out_opt_ MI_QualifierSet *qualifierSet,
        _Out_opt_ MI_Uint32* flags);

    MI_Result (MI_CALL *GetClassQualifierSet)(
        _In_ const MI_Class* self, 
        _Out_opt_ MI_QualifierSet *qualifierSet
        );

    MI_Result (MI_CALL *GetMethodCount)(
        _In_ const MI_Class* self,
        _Out_ MI_Uint32* count);

    MI_Result (MI_CALL *GetMethodAt)(
        _In_ const MI_Class *self,
        MI_Uint32 index,
        _Outptr_result_z_ const MI_Char **name,
        _Out_opt_ MI_QualifierSet *qualifierSet,
        _Out_opt_ MI_ParameterSet *parameterSet
        );

    MI_Result (MI_CALL *GetMethod)(
        _In_ const MI_Class *self,
        _In_z_ const MI_Char *name,
        _Out_opt_ MI_QualifierSet *qualifierSet,
        _Out_opt_ MI_ParameterSet *parameterSet,
        _Out_opt_ MI_Uint32 *index
        );

    MI_Result (MI_CALL *GetParentClassName)(
        _In_ const MI_Class *self,
        _Outptr_result_maybenull_z_ const MI_Char **name);

    MI_Result (MI_CALL *GetParentClass)(
        _In_ const MI_Class *self,
        _Outptr_ MI_Class **parentClass);

    MI_Result (MI_CALL *Delete)(
        _Inout_ MI_Class* self);

    MI_Result (MI_CALL *Clone)(
        _In_ const MI_Class* self,
        _Outptr_ MI_Class** newClass);

    // new functions extending the existing functionality
    MI_Result (MI_CALL *GetClassFlagsExt)(
            _In_ const MI_Class* self,
            _Out_ MI_Uint32* flags);

    // here the caller provides a class object and the function just fills in the class decl
    MI_Result (MI_CALL *GetParentClassExt)(
            _In_ const MI_Class* self,
            _Out_ MI_Class *parentClass);

    MI_Result (MI_CALL *GetElementAtExt)(
        _In_ const MI_Class* self,
        MI_Uint32 index,
        _Outptr_opt_result_maybenull_z_ const MI_Char** name,
        _Out_opt_ MI_Value* value,
        _Out_opt_ MI_Boolean* valueExists,
        _Out_opt_ MI_Type* type,
        _Out_opt_ MI_Uint32* subscript,
        _Out_opt_ MI_Uint32* offset,
        _Outptr_opt_result_maybenull_z_ MI_Char **referenceClass,
        _Outptr_opt_result_maybenull_z_ MI_Char **originClass,
        _Outptr_opt_result_maybenull_z_ MI_Char **propagatorClass,        
        _Out_opt_ MI_QualifierSet *qualifierSet,
        _Out_opt_ MI_Uint32* flags);

    MI_Result (MI_CALL *GetMethodAtExt)(
        _In_ const MI_Class *self,
        MI_Uint32 index,
        _Outptr_result_z_ const MI_Char **name,
        _Outptr_opt_result_maybenull_z_ MI_Char **originClass,
        _Outptr_opt_result_maybenull_z_ MI_Char **propagatorClass,
        _Out_opt_ MI_QualifierSet *qualifierSet,
        _Out_opt_ MI_ParameterSet *parameterSet,
        _Out_opt_ MI_Uint32* flags);    
} MI_ClassExtendedFTInternal;

typedef struct _MI_ParameterSetExtendedFTInternal
{
    // existing functions from MI_ClassFT

    MI_Result (MI_CALL *GetMethodReturnType)(
        _In_  const MI_ParameterSet *self, 
        _Out_ MI_Type *returnType, 
        _Out_ MI_QualifierSet *qualifierSet);

    MI_Result (MI_CALL *GetParameterCount)(
        _In_ const MI_ParameterSet *self, 
        _Out_ MI_Uint32 *count);

    MI_Result (MI_CALL *GetParameterAt)(
        _In_ const MI_ParameterSet *self,
        MI_Uint32 index,
        _Outptr_result_z_ const MI_Char **name,
        MI_Type *parameterType,
        _Outptr_opt_result_maybenull_z_ MI_Char **referenceClass,
        _Out_ MI_QualifierSet *qualifierSet);

    MI_Result (MI_CALL *GetParameter)(
        _In_ const MI_ParameterSet *self,
        _In_z_ const MI_Char *name,
        _Out_ MI_Type *parameterType,
        _Outptr_opt_result_maybenull_z_ MI_Char **referenceClass,
        _Out_ MI_QualifierSet *qualifierSet,
        _Out_ MI_Uint32 *index);

    // new functions extending the existing functionality

    MI_Result (MI_CALL *GetParameterAtExt)(
        _In_ const MI_ParameterSet *self,
        MI_Uint32 index,
        _Outptr_result_z_ const MI_Char **name,
        MI_Type *parameterType,
        _Out_opt_ MI_Uint32* subscript,
        _Outptr_opt_result_maybenull_z_ MI_Char **referenceClass,
        _Out_ MI_QualifierSet *qualifierSet,
        _Out_opt_ MI_Uint32* flags);

} MI_ParameterSetExtendedFTInternal;


    /* Helper functions */
MI_EXTERN_C    MI_Result Class_Clone_ArrayValue(
        _Inout_ Batch *batch,
        MI_Type type, 
        _In_ void *destinationArrayStart,
        MI_Uint32 arrayLocation,
        _In_ const void *oldValueLocation);

MI_EXTERN_C   MI_ClassDecl* Class_Clone_ClassDecl(
        _Inout_ Batch *batch,
        _In_ const MI_ClassDecl *classDecl);


/*============================================================================
 * Assumes that the Class extended function table is present in ft field of MI_Class pointer being passed in
 *============================================================================
 */

MI_INLINE const MI_ClassExtendedFTInternal * MI_CALL GetClassExtendedFt(const MI_Class *miClass)
{
    return ((const MI_ClassExtendedFTInternal *)(miClass->ft));
}

/*============================================================================
 * Assumes that ParameterSet extended function table is present in ft field of ParameterSetFT pointer being passed in
 *============================================================================
 */

MI_INLINE const MI_ParameterSetExtendedFTInternal * MI_CALL GetParameterSetExtendedFt(const MI_ParameterSet *parameterSet)
{
    return ((const MI_ParameterSetExtendedFTInternal *)(parameterSet->ft));
}

/*============================================================================
 * Get function table from qualifierSet
 *============================================================================
 */
MI_INLINE const MI_QualifierSetFT * MI_CALL GetQualifierSetFt(const MI_QualifierSet *qualifierSet)
{
    return qualifierSet->ft;
}

MI_EXTERN_C MI_Result MI_CALL Class_Construct(MI_Class* self, const MI_ClassDecl* classDecl);

MI_EXTERN_C MI_Result MI_CALL Class_New(
    _In_ const MI_ClassDecl *classDecl,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_z_ const MI_Char *serverName,
    _Out_ MI_Class **newClass);


#endif // End _CLASS_h
