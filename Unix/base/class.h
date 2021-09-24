/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _CLASS_h
#define _CLASS_h

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

MI_EXTERN_C MI_Result ClassConstructor_New(
        _In_opt_ MI_Class *parentClass, 
        _In_opt_z_ const MI_Char *namespaceName, /* Not needed if parentClass is passed in */
        _In_opt_z_ const MI_Char *serverName,    /* Not needed if parentClass is passed in */
        _In_z_ const MI_Char *className, 
        MI_Uint32 numberClassQualifiers,         /* number of extra class qualifiers you want to create.  Allows us to pre-create array of correct size */
        MI_Uint32 numberProperties,              /* number of extra properties you want to create.  Allows us to pre-create array of correct size */
        MI_Uint32 numberMethods,                 /* number of extra methods you want to create. Allows us to pre-create array of correct size */
        _Out_ MI_Class **newClass              /* Object that is ready to receive new qualifiers/properties/methods */
        );

    /* Add a qualifier to a ref-counted class.  The qualifier array needs to be pre-created by passing in the number of classQualifiers
       to the Class_New API
    */
MI_EXTERN_C    MI_Result Class_AddClassQualifier(
        _In_ MI_Class *refcountedClass, /* Object created from Class_New only */
        _In_z_ const MI_Char *name,     /* qualifier name */
        MI_Type type,                   /* Type of qualifier */
        MI_Value value,                 /* Value of qualifier */
        MI_Uint32 flavors);             /* Flavor of qualifier */
    
    /* Array verion of Class_AddClassQualifier.  Pass in how many items there are and it returns a qualifier index to be used to add each
     * item in tern.
     */
MI_EXTERN_C    MI_Result Class_AddClassQualifierArray(
        _In_ MI_Class *refcountedClass,/* Object created from Class_New only */
        _In_z_ const MI_Char *name,      /* qualifier name */
        MI_Type type,                    /* Type of qualifier */
        MI_Uint32 flavors,               /* Flavor of qualifier */
        MI_Uint32 numberArrayItems,      /* Number of items in qualifier array */
        _Out_ MI_Uint32 *qualifierIndex);/* this qualifier index */

    /* Add an array item to the array created with call to Class_AddClassQualifierArray
     */
MI_EXTERN_C    MI_Result Class_AddClassQualifierArrayItem(
        _In_ MI_Class *refcountedClass, /* Object created from Class_New only */
        MI_Uint32 qualifierIndex,         /* qualifier index */
        MI_Value value);                  /* value to add to array */

    /* Add a element to a ref-counted class.  The element array needs to be pre-created by passing in the number of classProperties
       to the Class_New API
    */
MI_EXTERN_C    MI_Result Class_AddElement(
        _In_ MI_Class *refcountedClass,  /* Object created from Class_New only */
        _In_z_ const MI_Char *name,      /* element name */
        MI_Type type,                    /* Element type */
        MI_Value value,                  /* element default value */
        MI_Uint32 flags,                 /* element flags */
        _In_opt_z_ const MI_Char *associatedClassName, /* EmbeddedInstance class name or reference class name */
        MI_Boolean propagated,
        _In_opt_z_ const MI_Char *classOrigin,
        MI_Uint32 numberElementQualifiers, /* Number of qualifiers this element is going to get.  Allows us to pre-create array of correct size */
        _Out_ MI_Uint32 *elementId);
    
MI_EXTERN_C    MI_Result Class_AddElementArray(
        _In_ MI_Class *refcountedClass,  /* Object created from Class_New only */
        _In_z_ const MI_Char *name,      /* element name */
        MI_Type type,                    /* Element type */
        MI_Uint32 flags,                 /* element flags */
        _In_opt_z_ const MI_Char *associatedClassName, /* EmbeddedInstance class name or reference class name */
        MI_Boolean propagated,
        _In_opt_z_ const MI_Char *originClass,
        MI_Uint32 maxArrayLength,
        MI_Uint32 numberElementQualifiers, /* Number of qualifiers this element is going to get.  Allows us to pre-create array of correct size */
        MI_Uint32 numberPropertyArrayItems,
        _Out_ MI_Uint32 *elementId);

MI_EXTERN_C    MI_Result Class_AddElementArrayItem(
        _In_ MI_Class *refcountedClass,  /* Object created from Class_New only */
        MI_Uint32 elementId,      
        MI_Value value);                   /* element array item*/

    /* Add a element qualifierto a ref-counted class.  The element property qualifier array needs to be pre-created by passing in the correct numberPropertyQualifiers
       to the Class_AddElement API
    */
MI_EXTERN_C    MI_Result Class_AddElementQualifier(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 elementIndex, 
        _In_z_ const MI_Char *name, 
        MI_Type type, 
        MI_Value value,
        MI_Uint32 flavor) ;

MI_EXTERN_C    MI_Result Class_AddElementQualifierArray(
        _In_ MI_Class *refcountedClass,  /* Object created from Class_New only */
        MI_Uint32 elementId,               /* element index returned from Class_AddElement */
        _In_z_ const MI_Char *name, 
        MI_Type type, 
        MI_Uint32 flavor,
        MI_Uint32 numberItemsInQualifierArray,
        _Out_ MI_Uint32 *qualifierIndex) ;

MI_EXTERN_C    MI_Result Class_AddElementQualifierArrayItem(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 elementIndex, 
        MI_Uint32 qualifierIndex,
        MI_Value value) ;

    /* Add a method to a refcounted class.  The class method array was precreated by passing numberMethods to Class_New.
       Add the method in the next slot by querying how many methods are currently there.  Don't add more methods than 
       you said you wanted as the array is fixed.
    */
MI_EXTERN_C    MI_Result Class_AddMethod(
        _In_ MI_Class *refcountedClass, 
        _In_z_ const MI_Char *name, 
        MI_Uint32 flags,    /* Is this needed? */
        MI_Uint32 numberParameters, 
        MI_Uint32 numberQualifiers,
        _Out_ MI_Uint32 *methodID);

    /* Add a method qualifier to a refcounted class.  The method qualifier array was precreated by passing numberQualifiers to Class_AddMethod.
       Add the qualifier in the next slot by querying how many qualifiers are currently there.  Don't add more qualifiers than
       you said you wanted as the array is fixed
    */
MI_EXTERN_C    MI_Result Class_AddMethodQualifier(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 methodIndex, 
        _In_z_ const MI_Char *name, 
        MI_Type type, 
        MI_Value value,
        MI_Uint32 flavor);

MI_EXTERN_C    MI_Result Class_AddMethodQualifierArray(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 methodIndex, 
        _In_z_ const MI_Char *name, 
        MI_Type type, 
        MI_Uint32 flavor,
        MI_Uint32 numberItemsInArray,
        _Out_ MI_Uint32 *qualifierId);
        
MI_EXTERN_C    MI_Result Class_AddMethodQualifierArrayItem(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 methodIndex, 
        MI_Uint32 qualifierId, 
        MI_Value value);

    /* Add a method parameter to a refcounted class.  The method parameter array was precreated by passing numberParameters to Class_AddMethod.
       Add the parameter in the next slot by querying how many qualifiers are currently there.  Don't add more properties than 
       you said you wanted as the array is fixed
    */
MI_EXTERN_C    MI_Result Class_AddMethodParameter(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 methodIndex, 
        _In_z_ const MI_Char *name,
        _In_opt_z_ const MI_Char *refClassname,
        MI_Type type, 
        MI_Uint32 flags,
        MI_Uint32 maxArrayLength,
        MI_Uint32 numberQualifiers,
        _Out_ MI_Uint32 *parameterIndex);

    /* Add a method parameter qualifier to a refcounted class.  The method parameter qualifier array was precreated by passing numberQualifiers to Class_AddMethodProperty.
       Add the qualifier in the next slot by querying how many method property qualifiers are currently there.  Don't add more qualifiers than 
       you said you wanted as the array is fixed
    */
MI_EXTERN_C    MI_Result Class_AddMethodParameterQualifier(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 methodIndex, 
        MI_Uint32 parameterIndex, 
        _In_z_ const MI_Char *name, 
        MI_Type type, 
        MI_Value value,
        MI_Uint32 flavor);

MI_EXTERN_C    MI_Result Class_AddMethodParameterQualifierArray(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 methodIndex, 
        MI_Uint32 parameterIndex, 
        _In_z_ const MI_Char *name, 
        MI_Type type, 
        MI_Uint32 flavor,
        MI_Uint32 numberItemsInArray,
        _Out_ MI_Uint32 *qualifierIndex);

MI_EXTERN_C    MI_Result Class_AddMethodParameterQualifierArrayItem(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 methodIndex, 
        MI_Uint32 parameterIndex, 
        MI_Uint32 qualifierIndex,
        MI_Value value);

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

BEGIN_EXTERNC

extern const MI_ClassExtendedFTInternal g_ClassExtendedFTInternal;
extern const MI_ParameterSetExtendedFTInternal g_parameterExtendedFTInternal;
extern const MI_QualifierSetFT g_qualifierFT;

END_EXTERNC

#endif // End _CLASS_h
