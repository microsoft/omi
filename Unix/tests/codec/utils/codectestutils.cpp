//#include <windows.h>
#include "codectestutils.h"
#ifdef _PREFAST_
#pragma warning(push)
#pragma warning(disable:28957)
#endif
#include <nits.h>
#ifdef _PREFAST_
#pragma warning(pop)
#endif 
#include <strings.h>

#define CompareScalarArrays(a, b) \
    for (;;) \
    { \
        if (a.size != b.size) \
            return false; \
        for (MI_Uint32 i=0; i<a.size; i++) \
            if (a.data[i] != b.data[i]) \
                return false; \
        return true; \
        break; \
    }

MI_INLINE bool CompareU8A(MI_Uint8A& a, MI_Uint8A& b)
{
    CompareScalarArrays(a,b)
}

MI_INLINE bool CompareU16A(MI_Uint16A& a, MI_Uint16A& b)
{
    CompareScalarArrays(a,b)
}

MI_INLINE bool CompareU32A(MI_Uint32A& a, MI_Uint32A& b)
{
    CompareScalarArrays(a,b)
}

MI_INLINE bool CompareU64A(MI_Uint64A& a, MI_Uint64A& b)
{
    CompareScalarArrays(a,b)
}

MI_INLINE bool CompareDT(MI_Datetime& dtA, MI_Datetime& dtB)
{
    if (dtA.isTimestamp != dtB.isTimestamp)
        return false;

    if (dtA.isTimestamp)
        return ((dtA.u.timestamp.year == dtB.u.timestamp.year) &&
        (dtA.u.timestamp.month == dtB.u.timestamp.month) &&
        (dtA.u.timestamp.day == dtB.u.timestamp.day) &&
        (dtA.u.timestamp.hour == dtB.u.timestamp.hour) &&
        (dtA.u.timestamp.minute == dtB.u.timestamp.minute) &&
        (dtA.u.timestamp.second == dtB.u.timestamp.second) &&
        (dtA.u.timestamp.microseconds == dtB.u.timestamp.microseconds) &&
        (dtA.u.timestamp.utc == dtB.u.timestamp.utc));
    else
        return ((dtA.u.interval.days == dtB.u.interval.days) &&
        (dtA.u.interval.hours == dtB.u.interval.hours) &&
        (dtA.u.interval.minutes == dtB.u.interval.minutes) &&
        (dtA.u.interval.seconds == dtB.u.interval.seconds) &&
        (dtA.u.interval.microseconds == dtB.u.interval.microseconds));
}

MI_INLINE bool CompareDTA(MI_DatetimeA& dtaA, MI_DatetimeA& dtaB)
{
    if (dtaA.size != dtaB.size)
        return false;

    for (MI_Uint32 i=0 ; i < dtaA.size; i++)
        if (!CompareDT(dtaA.data[i], dtaB.data[i]))
            return false;

    return true;
}

MI_INLINE bool CompareStr(_In_opt_z_ const MI_Char* str1, _In_opt_z_ const MI_Char* str2)
{
    if (!str1 || !str2)
        if (str1 || str2)
            return false;
        else
            return true;
    
    size_t len1 = Tcslen(str1);
    size_t len2 = Tcslen(str2);

    if (len1 != len2)
        return false;

    if (Tcsncmp(str1, str2, len1) != 0)
        return false;

    return true;
}

MI_INLINE bool CompareStrA(MI_StringA& straA,MI_StringA& straB)
{
    if (straA.size != straB.size)
        return false;

    for (MI_Uint32 i=0; i < straA.size; i++)
        if (!CompareStr(straA.data[i], straB.data[i]))
            return false;

    return true;
}

MI_INLINE bool CompareInstanceA(MI_InstanceA& iaA, MI_InstanceA& iaB)
{
    if (iaA.size != iaB.size)
        return false;

    for (MI_Uint32 i=0; i < iaA.size; i++)
        if (!CompareInstances(iaA.data[i], iaB.data[i]))
            return false;

    return true;
}

bool CompareMIValues(MI_Value& valueA, MI_Value& valueB, MI_Type type)
{
    switch (type)
        {
            case MI_BOOLEAN:
            case MI_UINT8:
            case MI_SINT8:
                if (!NitsAssert(valueA.uint8 == valueB.uint8, L"values should be the same"))
                    return false;;
                break;
            case MI_UINT16:
            case MI_SINT16:
            case MI_CHAR16:
                if (!NitsAssert(valueA.uint16 == valueB.uint16, L"values should be the same"))
                    return false;;
                break;
            case MI_UINT32:
            case MI_SINT32:
            case MI_REAL32:
                if (!NitsAssert(valueA.uint32 == valueB.uint32, L"values should be the same"))
                    return false;;
                break;
            case MI_UINT64:
            case MI_SINT64:
            case MI_REAL64:
                if (!NitsAssert(valueA.uint64 == valueB.uint64, L"values should be the same"))
                    return false;;
                break;
            case MI_DATETIME:
                if (!NitsAssert(CompareDT(valueA.datetime,valueB.datetime), L"values should be the same"))
                    return false;;
                break; 
            case MI_BOOLEANA:
            case MI_UINT8A:
            case MI_SINT8A:
                if (!NitsAssert(CompareU8A(valueA.uint8a, valueB.uint8a), L"values should be the same"))
                    return false;;
                break;
            case MI_UINT16A:
            case MI_SINT16A:
            case MI_CHAR16A:
                if (!NitsAssert(CompareU16A(valueA.uint16a, valueB.uint16a), L"values should be the same"))
                    return false;;
                break;
            case MI_UINT32A:
            case MI_SINT32A:
            case MI_REAL32A:
                if (!NitsAssert(CompareU32A(valueA.uint32a, valueB.uint32a), L"values should be the same"))
                    return false;;
                break;
            case MI_UINT64A:
            case MI_SINT64A:
            case MI_REAL64A:
                if (!NitsAssert(CompareU64A(valueA.uint64a, valueB.uint64a), L"values should be the same"))
                    return false;;
                break;
            case MI_REFERENCE:
            case MI_INSTANCE:
                if (!NitsAssert(CompareInstances(valueA.instance, valueB.instance), L"values should be the same"))
                    return false;;
                break;
            case MI_STRING:
                if (!NitsAssert(CompareStr(valueA.string, valueB.string), L"values should be the same"))
                    return false;
                break;
            case MI_DATETIMEA:
                if (!NitsAssert(CompareDTA(valueA.datetimea, valueB.datetimea), L"values should be the same"))
                    return false;
                break;
            case MI_STRINGA:
                if (!NitsAssert(CompareStrA(valueA.stringa, valueB.stringa), L"values should be the same"))
                    return false;
                break;
            case MI_REFERENCEA:
            case MI_INSTANCEA:
                if (!NitsAssert(CompareInstanceA(valueA.instancea, valueB.instancea), L"values should be the same"))
                    return false;
                break;
            default:
                NitsAssert(false, L"should not hit");
                break;
        }
    return true;
}

_Use_decl_annotations_
bool CompareInstances(MI_Instance* instanceA, MI_Instance* instanceB)
{
    const MI_ClassDecl* classDeclA = instanceA->classDecl;
    const MI_ClassDecl* classDeclB = instanceB->classDecl;

    //compare class decls
    if (!NitsAssert(classDeclA->numProperties ==  classDeclB->numProperties, L"instances should be of the same type"))
        return false;;

    //compare namespaces
    if (!NitsAssert(CompareStr(instanceA->nameSpace, instanceB->nameSpace), L"namespaces should be the same"))
        return false;

    //compare servernames
    if (!NitsAssert(CompareStr(instanceA->serverName, instanceB->serverName), L"servernames should be the same"))
        return false;

    for (MI_Uint32 propertyIndex = 0; propertyIndex < classDeclA->numProperties; propertyIndex++)
    {
        if (!NitsAssert(classDeclA->properties[propertyIndex]->type ==  classDeclB->properties[propertyIndex]->type, L"properties should be of the same type"))
            return false;;

        MI_Value valueA, valueB;
        MI_Uint32 propertyValueFlagsA = 0, propertyValueFlagsB = 0;
        if (!NitsAssert(MI_RESULT_OK == MI_Instance_GetElementAt(instanceA, propertyIndex, NULL, &valueA, NULL, &propertyValueFlagsA), L"GetElementAt should succeed"))
            return false;;

        if (!NitsAssert(MI_RESULT_OK == MI_Instance_GetElementAt(instanceB, propertyIndex, NULL, &valueB, NULL, &propertyValueFlagsB), L"GetElementAt should succeed"))
            return false;;

        if (!NitsAssert( (propertyValueFlagsA & MI_FLAG_NULL) == (propertyValueFlagsB & MI_FLAG_NULL), L"properties should either exist or not"))
            return false;;

        if (propertyValueFlagsA & MI_FLAG_NULL)
            continue;

        if (!NitsAssert(CompareMIValues(valueA, valueB, (MI_Type)classDeclA->properties[propertyIndex]->type), L"values should be the same"))
            return false;
    }

    return true;
}


//=========class comparison utils

bool CompareFlags(MI_Uint32 flagsA, MI_Uint32 flagsB)
{
    NitsAssert((flagsA & MI_FLAG_CLASS)  == (flagsB & MI_FLAG_CLASS), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_METHOD)  == (flagsB & MI_FLAG_METHOD), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_PROPERTY)  == (flagsB & MI_FLAG_PROPERTY), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_PARAMETER)  == (flagsB & MI_FLAG_PARAMETER), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_ASSOCIATION)  == (flagsB & MI_FLAG_ASSOCIATION), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_INDICATION)  == (flagsB & MI_FLAG_INDICATION), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_REFERENCE)  == (flagsB & MI_FLAG_REFERENCE), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_ENABLEOVERRIDE)  == (flagsB & MI_FLAG_ENABLEOVERRIDE), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_DISABLEOVERRIDE)  == (flagsB & MI_FLAG_DISABLEOVERRIDE), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_RESTRICTED)  == (flagsB & MI_FLAG_RESTRICTED), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_TOSUBCLASS)  == (flagsB & MI_FLAG_TOSUBCLASS), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_TRANSLATABLE)  == (flagsB & MI_FLAG_TRANSLATABLE), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_KEY)  == (flagsB & MI_FLAG_KEY), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_IN)  == (flagsB & MI_FLAG_IN), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_OUT)  == (flagsB & MI_FLAG_OUT), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_REQUIRED)  == (flagsB & MI_FLAG_REQUIRED), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_STATIC)  == (flagsB & MI_FLAG_STATIC), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_ABSTRACT)  == (flagsB & MI_FLAG_ABSTRACT), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_TERMINAL)  == (flagsB & MI_FLAG_TERMINAL), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_EXPENSIVE)  == (flagsB & MI_FLAG_EXPENSIVE), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_STREAM)  == (flagsB & MI_FLAG_STREAM), L"flags should be the same");
    NitsAssert((flagsA & MI_FLAG_READONLY)  == (flagsB & MI_FLAG_READONLY), L"flags should be the same");
    return true;
}

bool CompareQualifiers(MI_Qualifier MI_CONST* MI_CONST* qualifiersA, MI_Qualifier MI_CONST* MI_CONST* qualifiersB, MI_Uint32 numQualifiers)
{
    if (!numQualifiers)
        return true;

    for (MI_Uint32 i = 0; i < numQualifiers; i++)
    {
        const MI_Qualifier *qualifierA, *qualifierB;
        qualifierA = *(qualifiersA + i);
        qualifierB = *(qualifiersB + i);

        if (!NitsAssert(qualifierA->type == qualifierB->type, L"types should be the same"))
            return false;

        if (!NitsAssert(qualifierA->flavor == qualifierB->flavor, L"types should be the same"))
            return false;

        if (!NitsAssert(Tcscmp(qualifierA->name,qualifierB->name) == 0, L"types should be the same"))
            return false;

        if (!qualifierA->value || !qualifierB->value)
        {
            //BUG # :This validation should be enabled once this bug is fixed
            /*if (qualifierA->value || qualifierB->value)
            {
                NitsAssert(false, L"values should either exist or not");
                return false;
            }*/
            if (qualifierA->value && !qualifierB->value)
            {
                NitsAssert(false, L"values should either exist or not");
                return false;
            }
        }
        else
            if (!NitsAssert(CompareMIValues(*((MI_Value*)qualifierA->value), *((MI_Value*)qualifierB->value), (MI_Type)qualifierA->type), 
                        L"values should be the same"))
                return false;
    }

    return true;
}

bool CompareProperties(MI_PropertyDecl MI_CONST* MI_CONST* propertiesA, MI_PropertyDecl MI_CONST* MI_CONST* propertiesB, MI_Uint32 numProperties)
{
    if (!numProperties)
        return true;

    for (MI_Uint32 i = 0; i < numProperties; i++)
    {
        const MI_PropertyDecl *propertyA, *propertyB;
        propertyA = *(propertiesA + i);
        propertyB = *(propertiesB + i);

        if (!NitsAssert(CompareFlags(propertyA->flags, propertyB->flags), L"flags should be the same"))
            return false;
        if (!NitsAssert(propertyA->code == propertyB->code, L"code should be the same"))
            return false;
        if (!NitsAssert(Tcscmp(propertyA->name, propertyB->name) == 0, L"names should be the same"))
            return false;
        if (!NitsAssert(propertyA->numQualifiers == propertyB->numQualifiers, L"numQualifiers should be the same"))
            return false;
        if (!NitsAssert(CompareQualifiers(propertyA->qualifiers, propertyB->qualifiers, propertyA->numQualifiers), L"qualifiers should be the same"))
            return false;
        if (!NitsAssert(propertyA->type == propertyB->type, L"types should be the same"))
            return false;
        if (!propertyA->className || !propertyB->className)
        {
            if (!NitsAssert(propertyA->className == propertyB->className, L"Both classNames should be NULL"))
                return false;
        }
        else if (!NitsAssert(Tcscmp(propertyA->className, propertyB->className) == 0, L"classNames should be the same"))
            return false;
        if (!propertyA->origin || !propertyB->origin)
        {
            if (!NitsAssert(propertyA->origin == propertyB->origin, L"Both origins should be NULL"))
                return false;
        }
        else if (!NitsAssert(Tcscmp(propertyA->origin, propertyB->origin) == 0, L"origins should be the same"))
            return false;
        if (!propertyA->propagator || !propertyB->propagator)
        {
            if (!NitsAssert(propertyA->propagator == propertyB->propagator, L"Both propagators should be NULL"))
                return false;
        }
        else if (!NitsAssert(Tcscmp(propertyA->propagator, propertyB->propagator) == 0, L"propagators should be the same"))
            return false;

        //Possible bug: Investigate and enable
        if (!propertyA->value || !propertyB->value)
        {
            
            /*if (propertyA->value || propertyB->value)
            {
                NitsAssert(false, L"values should either exist or not");
                return false;
            }  */     
            if (propertyA->value && !propertyB->value)
            {
                NitsAssert(false, L"values should either exist or not");
                return false;
            }

        }
        else
            if (!NitsAssert(CompareMIValues(*((MI_Value*)propertyA->value), *((MI_Value*)propertyB->value), (MI_Type)propertyA->type), 
                        L"values should be the same"))
                return false;
        
    }
    return true;
}


bool CompareParameters(MI_ParameterDecl MI_CONST* MI_CONST* parametersA, MI_ParameterDecl MI_CONST* MI_CONST* parametersB, MI_Uint32 numParameters)
{
    if (!numParameters)
        return true;

    for (MI_Uint32 i = 0; i < numParameters; i++)
    {
        const MI_ParameterDecl *parameterA, *parameterB;
        parameterA = *(parametersA + i);
        parameterB = *(parametersB + i);

        if (!NitsAssert(CompareFlags(parameterA->flags, parameterB->flags), L"flags should be the same"))
            return false;
        if (!NitsAssert(parameterA->code == parameterB->code, L"codes should be the same"))
            return false;
        if (!NitsAssert(Tcscmp(parameterA->name, parameterB->name) == 0, L"names should be the same"))
            return false;
        if (!NitsAssert(parameterA->numQualifiers == parameterB->numQualifiers, L"numQualifiers should be the same"))
            return false;
        if (!NitsAssert(CompareQualifiers(parameterA->qualifiers, parameterB->qualifiers, parameterA->numQualifiers), L"qualifiers should be the same"))
            return false;
        if (!NitsAssert(parameterA->type == parameterB->type, L"types should be the same"))
            return false;
        if (!parameterA->className || !parameterB->className)
        {
            if (!NitsAssert(parameterA->className == parameterB->className, L"Both classNames should be NULL"))
                return false;
        }
        else if (!NitsAssert(Tcscmp(parameterA->className, parameterB->className) == 0, L"classNames should be the same"))
            return false;
    }

    return true;
}

bool CompareMethods(MI_MethodDecl MI_CONST* MI_CONST* methodsA, MI_MethodDecl MI_CONST* MI_CONST* methodsB, MI_Uint32 numMethods)
{
    if (!numMethods)
        return true;

    for (MI_Uint32 i=0; i < numMethods; i++)
    {
        const MI_MethodDecl *methodA, *methodB;
        methodA = *(methodsA + i);
        methodB = *(methodsB + i);

        if (!NitsAssert(CompareFlags(methodA->flags, methodB->flags), L"flags should be the same"))
            return false;
        if (!NitsAssert(methodA->code == methodB->code, L"codes should be the same"))
            return false;
        if (!NitsAssert(Tcscmp(methodA->name, methodB->name) == 0, L"names should be the same"))
            return false;
        if (!NitsAssert(methodA->numQualifiers == methodB->numQualifiers, L"numQualifiers should be the same"))
            return false;
        if (!NitsAssert(CompareQualifiers(methodA->qualifiers, methodB->qualifiers, methodA->numQualifiers), L"qualifiers should be the same"))
            return false;
        if (!NitsAssert(methodA->numParameters == methodB->numParameters, L"numParameters should be the same"))
            return false;
        if (!NitsAssert(CompareParameters(methodA->parameters, methodB->parameters, methodA->numParameters), L"parameters should be the same"))
            return false;
        if (!NitsAssert(methodA->returnType == methodB->returnType, L"returnType should be the same"))
            return false;
        if (!methodA->origin || !methodB->origin)
        {
            if (!NitsAssert(methodA->origin == methodB->origin, L"Both origins should be NULL"))
                return false;
        }
        else if (!NitsAssert(Tcscmp(methodA->origin, methodB->origin) == 0, L"origins should be the same"))
            return false;
        if (!methodA->propagator || !methodB->propagator)
        {
            if (!NitsAssert(methodA->propagator == methodB->propagator, L"Both propagators should be NULL"))
                return false;
        }
        else if (!NitsAssert(Tcscmp(methodA->propagator, methodB->propagator) == 0, L"propagators should be the same"))
            return false;
    }



    return true;
}

_Use_decl_annotations_
bool CompareClasses(MI_Class* classA, MI_Class* classB)
{
    if (!classA->namespaceName || !classB->namespaceName)
    {
        if (!NitsAssert(classA->namespaceName == classB->namespaceName, L"Both namespaces should be NULL"))
            return false;
    }
    else if (!NitsAssert(Tcscmp(classA->namespaceName, classB->namespaceName) == 0, L"namespaces should be the same"))
        return false;

    if (!classA->serverName || !classB->serverName)
    {
        if (!NitsAssert(classA->serverName == classB->serverName, L"Both servernames should be NULL"))
            return false;
    }
    else if (!NitsAssert(Tcscmp(classA->serverName, classB->serverName) == 0, L"servernames should be the same"))
        return false;

    const MI_ClassDecl *classDeclA, *classDeclB;
    classDeclA = classA->classDecl;
    classDeclB = classB->classDecl;

    if (!NitsAssert(CompareFlags(classDeclA->flags, classDeclB->flags), L"flags should be the same"))
        return false;
    if (!NitsAssert(classDeclA->code == classDeclB->code, L"codes should be the same"))
        return false;
    if (!NitsAssert(Tcscmp(classDeclA->name, classDeclB->name) == 0, L"names should be the same"))
        return false;
    if (!NitsAssert(classDeclA->numQualifiers == classDeclB->numQualifiers, L"numQualifiers should be the same"))
        return false;
    if (!NitsAssert(CompareQualifiers(classDeclA->qualifiers, classDeclB->qualifiers, classDeclA->numQualifiers), L"qualifiers should be the same"))
        return false;
    if (!NitsAssert(classDeclA->numProperties == classDeclB->numProperties, L"numProperties should be the same"))
        return false;
    if (!NitsAssert(CompareProperties(classDeclA->properties, classDeclB->properties, classDeclA->numProperties), L"properties should be the same"))
        return false;
    if (!NitsAssert(classDeclA->numMethods == classDeclB->numMethods, L"numMethods should be the same"))
        return false;
    if (!NitsAssert(CompareMethods(classDeclA->methods, classDeclB->methods, classDeclA->numMethods), L"methods should be the same"))
        return false;    

    return true;
}