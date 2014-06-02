#ifndef _omiutils_h
#define _omiutils_h

#include <MI.h>
#ifndef _NO_PAL
#include <pal/palcommon.h>
#include <pal/intlstr.h>
#include <pal/strings.h>

PAL_BEGIN_EXTERNC

PAL_INLINE int Tcscmp_s(
    _In_opt_z_ const TChar* s1, 
    _In_opt_z_ const TChar* s2)
{
    if (!s1)
        return (!s2)? 0:-1;
    else if (!s2)
        return 1;

    return Tcscmp(s1, s2);
}

PAL_INLINE int Tcscasecmp_s(
    _In_opt_z_ const TChar* s1, 
    _In_opt_z_ const TChar* s2)
{
    if (!s1)
        return (!s2)? 0:-1;
    else if (!s2)
        return 1;

    return Tcscasecmp(s1, s2);
}

MI_Result MI_CALL Instance_New(
    _In_ const MI_ClassDecl* classDecl,
    _Out_ MI_Instance **instance);

/* Create ref-counted MI_Class with minimal memory allocations that allows properties/etc to be added efficiently.   
       No reallocations should happen as all arrays like qualifier arrays will be pre-created to the correct size based on client telling us when necessary.
       Note!!! If you say there are 5 items for an array and you add 6 it will corrupt the object as the arrays have a size, but don't have an allocated size.
       MI_Class_Delete will be overloaded for this class such that it will bump down the refcount and if zero will delete it.
       MI_Class_Clone can be overloaded to just bump the refcount (optional perf improvement).
       All other MI_Class_* methods can be a pass-through to the main functions with no change as the rest of the object is the same.
    */
    MI_Result RCClass_New(
        _In_opt_ MI_Class *parentClass, 
        _In_opt_z_ const MI_Char *namespaceName, /* Not needed if parentClass is passed in */
        _In_opt_z_ const MI_Char *serverName,    /* Not needed if parentClass is passed in */
        _In_z_ const MI_Char *className, 
        MI_Uint32 numberClassQualifiers,         /* number of extra class qualifiers you want to create.  Allowes us to pre-create array of correct size */
        MI_Uint32 numberProperties,              /* number of extra properties you want to create.  Allowes us to pre-create array of correct size */
        MI_Uint32 numberMethods,                 /* number of extra methods you want to create. Allowes us to pre-create array of correct size */
        _Out_ MI_Class **newClass              /* Object that is ready to receive new qualifiers/properties/methods */
        );

    /* Add a qualifier to a ref-counted class.  The qualifier array needs to be pre-created by passing in the number of classQualifiers
       to the RCClass_New API
    */
    MI_Result RCClass_AddClassQualifier(
        _In_ MI_Class *refcountedClass, /* Object created from RCClass_New only */
        _In_z_ const MI_Char *name,     /* qualifier name */
        MI_Type type,                   /* Type of qualifier */
        MI_Value value,                 /* Value of qualifier */
        MI_Uint32 flavors);             /* Flavor of qualifier */
    
    /* Array verion of RCClass_AddClassQualifier.  Pass in how many items there are and it returns a qualifier index to be used to add each
     * item in tern.
     */
    MI_Result RCClass_AddClassQualifierArray(
        _In_ MI_Class *refcountedClass,/* Object created from RCClass_New only */
        _In_z_ const MI_Char *name,      /* qualifier name */
        MI_Type type,                    /* Type of qualifier */
        MI_Uint32 flavors,               /* Flavor of qualifier */
        MI_Uint32 numberArrayItems,      /* Number of items in qualifier array */
        _Out_ MI_Uint32 *qualifierIndex);/* this qualifier index */

    /* Add an array item to the array created with call to RCClass_AddClassQualifierArray
     */
    MI_Result RCClass_AddClassQualifierArrayItem(
        _In_ MI_Class *refcountedClass, /* Object created from RCClass_New only */
        MI_Uint32 qualifierIndex,         /* qualifier index */
        MI_Value value);                  /* value to add to array */

    /* Add a element to a ref-counted class.  The element array needs to be pre-created by passing in the number of classProperties
       to the RCClass_New API
    */
    MI_Result RCClass_AddElement(
        _In_ MI_Class *refcountedClass,  /* Object created from RCClass_New only */
        _In_z_ const MI_Char *name,      /* element name */
        MI_Type type,                    /* Element type */
        MI_Value value,                  /* element default value */
        MI_Uint32 flags,                 /* element flags */
        _In_opt_z_ const MI_Char *associatedClassName, /* EmbeddedInstance class name or reference class name */
        MI_Boolean propagated,
        _In_opt_z_ const MI_Char *classOrigin,
        MI_Uint32 numberElementQualifiers, /* Number of qualifiers this element is going to get.  Allows us to pre-create array of correct size */
        _Out_ MI_Uint32 *elementId);
    
    MI_Result RCClass_AddElementArray(
        _In_ MI_Class *refcountedClass,  /* Object created from RCClass_New only */
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

    MI_Result RCClass_AddElementArrayItem(
        _In_ MI_Class *refcountedClass,  /* Object created from RCClass_New only */
        MI_Uint32 elementId,      
        MI_Value value);                   /* element array item*/

    /* Add a element qualifierto a ref-counted class.  The element property qualifier array needs to be pre-created by passing in the correct numberPropertyQualifiers
       to the RCClass_AddElement API
    */
    MI_Result RCClass_AddElementQualifier(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 elementIndex, 
        _In_z_ const MI_Char *name, 
        MI_Type type, 
        MI_Value value,
        MI_Uint32 flavor) ;

    MI_Result RCClass_AddElementQualifierArray(
        _In_ MI_Class *refcountedClass,  /* Object created from RCClass_New only */
        MI_Uint32 elementId,               /* element index returned from RCClass_AddElement */
        _In_z_ const MI_Char *name, 
        MI_Type type, 
        MI_Uint32 flavor,
        MI_Uint32 numberItemsInQualifierArray,
        _Out_ MI_Uint32 *qualifierIndex) ;

    MI_Result RCClass_AddElementQualifierArrayItem(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 elementIndex, 
        MI_Uint32 qualifierIndex,
        MI_Value value) ;

    /* Add a method to a refcounted class.  The class method array was precreated by passing numberMethods to RCClass_New.
       Add the method in the next slot by querying how many methods are currently there.  Don't add more methods than 
       you said you wanted as the array is fixed.
    */
    MI_Result RCClass_AddMethod(
        _In_ MI_Class *refcountedClass, 
        _In_z_ const MI_Char *name, 
        MI_Uint32 flags,    /* Is this needed? */
        MI_Uint32 numberParameters, 
        MI_Uint32 numberQualifiers,
        _Out_ MI_Uint32 *methodID);

    /* Add a method qualifier to a refcounted class.  The method qualifier array was precreated by passing numberQualifiers to RCClass_AddMethod.
       Add the qualifier in the next slot by querying how many qualifiers are currently there.  Don't add more qualifiers than
       you said you wanted as the array is fixed
    */
    MI_Result RCClass_AddMethodQualifier(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 methodIndex, 
        _In_z_ const MI_Char *name, 
        MI_Type type, 
        MI_Value value,
        MI_Uint32 flavor);

    MI_Result RCClass_AddMethodQualifierArray(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 methodIndex, 
        _In_z_ const MI_Char *name, 
        MI_Type type, 
        MI_Uint32 flavor,
        MI_Uint32 numberItemsInArray,
        _Out_ MI_Uint32 *qualifierId);
        
    MI_Result RCClass_AddMethodQualifierArrayItem(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 methodIndex, 
        MI_Uint32 qualifierId, 
        MI_Value value);

    /* Add a method parameter to a refcounted class.  The method parameter array was precreated by passing numberParameters to RCClass_AddMethod.
       Add the parameter in the next slot by querying how many qualifiers are currently there.  Don't add more properties than 
       you said you wanted as the array is fixed
    */
    MI_Result RCClass_AddMethodParameter(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 methodIndex, 
        _In_z_ const MI_Char *name,
        _In_opt_z_ const MI_Char *refClassname,
        MI_Type type, 
        MI_Uint32 flags,
        MI_Uint32 maxArrayLength,
        MI_Uint32 numberQualifiers,
        _Out_ MI_Uint32 *parameterIndex);

    /* Add a method parameter qualifier to a refcounted class.  The method parameter qualifier array was precreated by passing numberQualifiers to RCClass_AddMethodProperty.
       Add the qualifier in the next slot by querying how many method property qualifiers are currently there.  Don't add more qualifiers than 
       you said you wanted as the array is fixed
    */
    MI_Result RCClass_AddMethodParameterQualifier(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 methodIndex, 
        MI_Uint32 parameterIndex, 
        _In_z_ const MI_Char *name, 
        MI_Type type, 
        MI_Value value,
        MI_Uint32 flavor);

    MI_Result RCClass_AddMethodParameterQualifierArray(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 methodIndex, 
        MI_Uint32 parameterIndex, 
        _In_z_ const MI_Char *name, 
        MI_Type type, 
        MI_Uint32 flavor,
        MI_Uint32 numberItemsInArray,
        _Out_ MI_Uint32 *qualifierIndex);

    MI_Result RCClass_AddMethodParameterQualifierArrayItem(
        _In_ MI_Class *refcountedClass, 
        MI_Uint32 methodIndex, 
        MI_Uint32 parameterIndex, 
        MI_Uint32 qualifierIndex,
        MI_Value value);

    MI_Result Class_New(
        _In_ const MI_ClassDecl *classDecl,
        _In_opt_z_ const MI_Char *namespaceName,
        _In_opt_z_ const MI_Char *serverName,
        _In_opt_ void *batch,
        _Out_ MI_Class **newClass);

    MI_Result Instance_InitDynamic(
    MI_Instance** self,
    const MI_Char* className,
    MI_Uint32 metaType);

    MI_Uint64 GetClassDeclId(_In_ const MI_ClassDecl* classDecl);


#endif

/*------------------------------------------------------------------------------
    Creates a new instance of OMI_Error and sets the values of Message, 
    OMI_ErrorCode, OMI_ErrorType and OMI_ErrorCategory properties. 
------------------------------------------------------------------------------*/
MI_Result MI_CALL CreateOMIError(
    _In_opt_z_ const MI_Char* message,
    MI_Uint32 errorCode, 
    _In_z_ const MI_Char* errorType, 
    MI_Uint16 errorCategory, 
    _Outptr_ MI_Instance **omiError);

#ifndef _NO_PAL
PAL_INLINE MI_Result CreateOMIError_IntlstrMessage(
    _In_ _At_(message.str, _Post_invalid_) Intlstr message,
    MI_Uint32 errorCode, 
    _In_z_ const MI_Char* errorType, 
    MI_Uint16 errorCategory, 
    _Outptr_ MI_Instance **omiError)
{
    MI_Result result = CreateOMIError(message.str, errorCode, errorType, errorCategory, omiError);
    Intlstr_Free(message);
    return result;
}
#endif

/*------------------------------------------------------------------------------
    Creates a new instance of OMI_DebugError and sets the values of Message, 
    OMI_ErrorCode, OMI_ErrorType and OMI_ErrorCategory properties. 
------------------------------------------------------------------------------*/
MI_Result MI_CALL CreateOMIDebugError(
    _In_opt_z_ const MI_Char* message,
    MI_Uint32 errorCode, 
    _In_z_ const MI_Char* errorType, 
    MI_Uint16 errorCategory, 
    _Outptr_ MI_Instance **omiError);

#ifndef _NO_PAL
PAL_INLINE MI_Result CreateOMIDebugError_IntlstrMessage(
    _In_ _At_(message.str, _Post_invalid_) Intlstr message,
    MI_Uint32 errorCode, 
    _In_z_ const MI_Char* errorType, 
    MI_Uint16 errorCategory, 
    _Outptr_ MI_Instance **omiError)
{
    MI_Result result = CreateOMIDebugError(message.str, errorCode, errorType, errorCategory, omiError);
    Intlstr_Free(message);
    return result;
}
#endif

MI_Result MI_CALL CreateOMIError_FromMiResult(
    MI_Result miResult,
    _Outptr_ MI_Instance **omiError);

MI_Result MI_CALL CreateOMIDebugError_FromMiResult(
    MI_Result miResult,
    _Outptr_ MI_Instance **omiError);

#ifndef _NO_PAL
PAL_END_EXTERNC
#endif

#endif /* _omiutils_h */
