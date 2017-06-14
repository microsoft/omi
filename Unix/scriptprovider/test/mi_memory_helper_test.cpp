// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#include "mi_memory_helper_test.hpp"


#include <cstdlib>
#include <mi_memory_helper.hpp>
#include <sstream>


using test::mi_memory_helper_test;


namespace
{


template<typename T, size_t N>
size_t
card (T const (&)[N])
{
    return N;
}


struct TestItem
{
    static size_t count;
    /*ctor*/ TestItem () { ++count; }
    /*dtor*/ ~TestItem () { --count; }
};

/*static*/ size_t TestItem::count = 0;


template<typename T>
int
BaseType_test ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<T, typename BaseType<T>::type>::value ||
        !util::is_same<T, typename BaseType<T*>::type>::value ||
        !util::is_same<T, typename BaseType<T&>::type>::value ||
        !util::is_same<T, typename BaseType<T const*>::type>::value ||
        !util::is_same<T, typename BaseType<T const&>::type>::value ||
        !util::is_same<T, typename BaseType<T const* const>::type>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


template<typename T>
int
ConstRemover_test ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<T, typename ConstRemover<T>::type>::value ||
        !util::is_same<T, typename ConstRemover<T const>::type>::value ||
        !util::is_same<T*, typename ConstRemover<T const*>::type>::value ||
        !util::is_same<T*, typename ConstRemover<T const* const>::type>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


template<typename T>
int
MI_DeleteArray_test ()
{
    int rval = EXIT_SUCCESS;
    {
        T* pArray = new T[10];
        MI_DeleteArray (pArray);
        if (NULL != pArray)
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


template<typename ARRAY>
int
MI_BuiltInArrayDestroy_test ()
{
    size_t const COUNT = 10;
    int rval = EXIT_SUCCESS;
    {
        ARRAY array;
        array.data = new typename TypeTraits<ARRAY>::aggregate_t[COUNT];
        array.size = COUNT;
        MI_BuiltInArrayDestroy<ARRAY>::destroy (array);
        if (NULL != array.data ||
            0 != array.size)
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


template<typename ARRAY>
int
MI_ArrayDestroy_test ()
{
    size_t const COUNT = 10;
    int rval = EXIT_SUCCESS;
    {
        ARRAY array;
        array.data = new typename TypeTraits<ARRAY>::aggregate_t[COUNT];
        array.size = COUNT;
        MI_ArrayDestroy<ARRAY>::destroy (array);
        if (NULL != array.data ||
            0 != array.size)
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


template<typename ARRAY>
int
MI_DestroyHelper_test ()
{
    size_t const COUNT = 10;
    int rval = EXIT_SUCCESS;
    {
        ARRAY array;
        array.data = new typename TypeTraits<ARRAY>::aggregate_t[COUNT];
        array.size = COUNT;
        MI_DestroyHelper<ARRAY>::destroy (array);
        if (NULL != array.data ||
            0 != array.size)
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


template<typename ARRAY>
int
MI_Destroy_test ()
{
    size_t const COUNT = 10;
    int rval = EXIT_SUCCESS;
    {
        ARRAY array;
        array.data = new typename TypeTraits<ARRAY>::aggregate_t[COUNT];
        array.size = COUNT;
        MI_Destroy (array);
        if (NULL != array.data ||
            0 != array.size)
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


void
init_value_str (
    MI_Char const* const name,
    MI_Value* const pValueOut)
{
    pValueOut->string = strcpy (new MI_Char[strlen (name) + 1], name);
}


void
init_qualifier_decl (
    MI_Char const* const name,
    bool createValue,
    MI_QualifierDecl* const pQualifierOut)
{
    pQualifierOut->name = strcpy (new MI_Char[strlen (name) + 1], name);
    pQualifierOut->type = MI_STRING;
    pQualifierOut->scope = 0;
    pQualifierOut->flavor = 0;
    pQualifierOut->subscript = 0;
    if (createValue)
    {
        MI_Value* pValue = new MI_Value;
        std::ostringstream strm;
        strm << name << "_value";
        init_value_str (strm.str ().c_str (), pValue);
        pQualifierOut->value = pValue;
    }
    else
    {
        pQualifierOut->value = NULL;
    }
}


void
init_qualifier (
    MI_Char const* const name,
    bool createValue,
    MI_Qualifier* const pQualifierOut)
{
    pQualifierOut->name = strcpy (new MI_Char[strlen (name) + 1], name);
    pQualifierOut->type = MI_STRING;
    pQualifierOut->flavor = 0;
    if (createValue)
    {
        MI_Value* pValue = new MI_Value;
        std::ostringstream strm;
        strm << name << "_value";
        init_value_str (strm.str ().c_str (), pValue);
        pQualifierOut->value = pValue;
    }
    else
    {
        pQualifierOut->value = NULL;
    }
}


void
init_parameter_decl (
    MI_Char const* const name,
    size_t nQualifiers,
    bool createClassName,
    MI_ParameterDecl* const pParameterOut)
{
    std::ostringstream strm;
    pParameterOut->name = strcpy (new MI_Char[strlen (name) + 1], name);
    pParameterOut->flags = 0;
    pParameterOut->code = 0;
    pParameterOut->type = MI_STRING;
    pParameterOut->subscript = 0;
    pParameterOut->offset = 0;
    pParameterOut->numQualifiers = nQualifiers;
    if (0 < nQualifiers)
    {
        MI_Qualifier** ppQualifiers = new MI_Qualifier*[nQualifiers];
        for (size_t i = 0; i < nQualifiers; ++i)
        {
            strm << name << "_qualifier_" << i;
            MI_Qualifier* pQualifier = new MI_Qualifier;
            init_qualifier (strm.str ().c_str (), true, pQualifier);
            strm.str ("");
            strm.clear ();
            ppQualifiers[i] = pQualifier;
        }
        pParameterOut->qualifiers = ppQualifiers;
    }
    else
    {
        pParameterOut->qualifiers = NULL;
    }
    if (createClassName)
    {
        strm << name << "_class";
        MI_Char const* className = strm.str ().c_str ();
        pParameterOut->className =
            strcpy (new MI_Char[strlen (className) + 1], className);
    }
    else
    {
        pParameterOut->className = NULL;
    }
}


void
init_property_decl (
    MI_Char const* const name,
    size_t nQualifiers,
    bool createValues,
    MI_PropertyDecl* const pPropertyOut)
{
    std::ostringstream strm;
    pPropertyOut->name = strcpy (new MI_Char[strlen (name) + 1], name);
    pPropertyOut->flags = 0;
    pPropertyOut->code = 0;
    pPropertyOut->type = MI_STRING;
    pPropertyOut->subscript = 0;
    pPropertyOut->offset = 0;
    pPropertyOut->numQualifiers = nQualifiers;
    if (0 < nQualifiers)
    {
        MI_Qualifier** ppQualifiers = new MI_Qualifier*[nQualifiers];
        for (size_t i = 0; i < nQualifiers; ++i)
        {
            strm << name << "_qualifier_" << i;
            MI_Qualifier* pQualifier = new MI_Qualifier;
            init_qualifier (strm.str ().c_str (), true, pQualifier);
            strm.str ("");
            strm.clear ();
            ppQualifiers[i] = pQualifier;
        }
        pPropertyOut->qualifiers = ppQualifiers;
    }
    else
    {
        pPropertyOut->qualifiers = NULL;
    }
    if (createValues)
    {
        strm << name << "_class";
        MI_Char const* className = strm.str ().c_str ();
        pPropertyOut->className =
            strcpy (new MI_Char[strlen (className) + 1], className);
        strm.str ("");
        strm.clear ();
        strm << name << "_origin";
        MI_Char const* originName = strm.str ().c_str ();
        pPropertyOut->origin =
            strcpy (new MI_Char[strlen (originName) + 1], originName);
        strm.str ("");
        strm.clear ();
        strm << name << "propagator";
        MI_Char const* propName = strm.str ().c_str ();
        pPropertyOut->propagator =
            strcpy (new MI_Char[strlen (propName) + 1], propName);
        strm.str ("");
        strm.clear ();
        MI_Value* pValue = new MI_Value;
        strm << name << "_value";
        init_value_str (strm.str ().c_str (), pValue);
        pPropertyOut->value = pValue;
    }
    else
    {
        pPropertyOut->className = NULL;
        pPropertyOut->origin = NULL;
        pPropertyOut->propagator = NULL;
        pPropertyOut->value = NULL;
    }
}


void
init_method_decl (
    MI_Char const* const name,
    size_t nQualifiers,
    size_t nParameters,
    bool createValues,
    MI_MethodDecl* const pMethodOut)
{
    std::ostringstream strm;
    pMethodOut->name = strcpy (new MI_Char[strlen (name) + 1], name);
    pMethodOut->flags = 0;
    pMethodOut->code = 0;
    pMethodOut->size = 0;
    pMethodOut->returnType = MI_UINT32;
    pMethodOut->schema = NULL;
    pMethodOut->function = NULL;
    pMethodOut->numQualifiers = nQualifiers;
    if (0 < nQualifiers)
    {
        MI_Qualifier** ppQualifiers = new MI_Qualifier*[nQualifiers];
        for (size_t i = 0; i < nQualifiers; ++i)
        {
            strm << name << "_qualifier_" << i;
            MI_Qualifier* pQualifier = new MI_Qualifier;
            init_qualifier (strm.str ().c_str (), true, pQualifier);
            strm.str ("");
            strm.clear ();
            ppQualifiers[i] = pQualifier;
        }
        pMethodOut->qualifiers = ppQualifiers;
    }
    else
    {
        pMethodOut->qualifiers = NULL;
    }
    pMethodOut->numParameters = nParameters;
    if (0 < nParameters)
    {
        MI_ParameterDecl** ppParameters = new MI_ParameterDecl*[nParameters];
        for (size_t i = 0; i < nParameters; ++i)
        {
            strm << name << "_parameter_" << i;
            MI_ParameterDecl* pParameter = new MI_ParameterDecl;
            init_parameter_decl (strm.str ().c_str (), 3, true, pParameter);
            strm.str ("");
            strm.clear ();
            ppParameters[i] = pParameter;
        }
        pMethodOut->parameters = ppParameters;
    }
    else
    {
        pMethodOut->parameters = NULL;
    }
    if (createValues)
    {
        strm << name << "_origin";
        MI_Char const* originName = strm.str ().c_str ();
        pMethodOut->origin =
            strcpy (new MI_Char[strlen (originName) + 1], originName);
        strm.str ("");
        strm.clear ();
        strm << name << "propagator";
        MI_Char const* propName = strm.str ().c_str ();
        pMethodOut->propagator =
            strcpy (new MI_Char[strlen (propName) + 1], propName);
    }
    else
    {
        pMethodOut->origin = NULL;
        pMethodOut->propagator = NULL;
    }
}


void
init_class_decl (
    MI_Char const* const name,
    size_t nQualifiers,
    size_t nProperties,
    size_t nMethods,
    bool createValues,
    MI_ClassDeclEx* const pClassOut)
{
    std::ostringstream strm;
    pClassOut->name = strcpy (new MI_Char[strlen (name) + 1], name);
    pClassOut->flags = 0;
    pClassOut->code = 0;
    pClassOut->size = 0;
    pClassOut->superClassDecl = NULL;
    pClassOut->schema = NULL;
    pClassOut->owningClass = NULL;
    pClassOut->functionTableFlags = 0;
    pClassOut->numQualifiers = nQualifiers;
    if (0 < nQualifiers)
    {
        MI_Qualifier** ppQualifiers = new MI_Qualifier*[nQualifiers];
        for (size_t i = 0; i < nQualifiers; ++i)
        {
            strm << name << "_qualifier_" << i;
            MI_Qualifier* pQualifier = new MI_Qualifier;
            init_qualifier (strm.str ().c_str (), true, pQualifier);
            strm.str ("");
            strm.clear ();
            ppQualifiers[i] = pQualifier;
        }
        pClassOut->qualifiers = ppQualifiers;
    }
    else
    {
        pClassOut->qualifiers = NULL;
    }
    pClassOut->numProperties = nProperties;
    if (0 < nProperties)
    {
        MI_PropertyDecl** ppProperties = new MI_PropertyDecl*[nProperties];
        for (size_t i = 0; i < nProperties; ++i)
        {
            strm << name << "_property_" << i;
            MI_PropertyDecl* pProperty = new MI_PropertyDecl;
            init_property_decl (strm.str ().c_str (), 3, true, pProperty);
            strm.str ("");
            strm.clear ();
            ppProperties[i] = pProperty;
        }
        pClassOut->properties = ppProperties;
    }
    else
    {
        pClassOut->properties = NULL;
    }
    pClassOut->numMethods = nMethods;
    if (0 < nMethods)
    {
        MI_MethodDecl** ppMethods = new MI_MethodDecl*[nMethods];
        for (size_t i = 0; i < nMethods; ++i)
        {
            strm << name << "_method_" << i;
            MI_MethodDecl* pMethod = new MI_MethodDecl;
            init_method_decl (strm.str ().c_str (), 3, 3, true, pMethod);
            strm.str ("");
            strm.clear ();
            ppMethods[i] = pMethod;
        }
        pClassOut->methods = ppMethods;
    }
    else
    {
        pClassOut->methods = NULL;
    }
    if (createValues)
    {
        strm << name << "_super_class";
        MI_Char const* superClass = strm.str ().c_str ();
        pClassOut->superClass =
            strcpy (new MI_Char[strlen (superClass) + 1], superClass);
        strm.str ("");
        strm.clear ();
        strm << name << "_owning_class";
        MI_Char const* owningClass = strm.str ().c_str ();
        pClassOut->owningClassName =
            strcpy (new MI_Char[strlen (owningClass) + 1], owningClass);
        pClassOut->providerFT = new MI_ProviderFT;
    }
    else
    {
        pClassOut->superClass = NULL;
        pClassOut->owningClassName = NULL;
        pClassOut->providerFT = NULL;
    }
}


void
init_schema_decl (
    size_t nQualifierDecls,
    size_t nClassDecls,
    MI_SchemaDecl* const pSchemaOut)
{
    std::ostringstream strm;
    pSchemaOut->numQualifierDecls = nQualifierDecls;
    if (0 < nQualifierDecls)
    {
        MI_QualifierDecl** qualifierDecls =
            new MI_QualifierDecl*[nQualifierDecls];
        for (size_t i = 0; i < nQualifierDecls; ++i)
        {
            strm << "qualifier_" << i;
            MI_QualifierDecl* pQualifier = new MI_QualifierDecl;
            init_qualifier_decl (strm.str ().c_str (), true, pQualifier);
            strm.str ("");
            strm.clear ();
            qualifierDecls[i] = pQualifier;
        }
        pSchemaOut->qualifierDecls = qualifierDecls;
    }
    else
    {
        pSchemaOut->qualifierDecls = NULL;
    }
    pSchemaOut->numClassDecls = nClassDecls;
    if (0 < nClassDecls)
    {
        MI_ClassDecl** classDecls = new MI_ClassDecl*[nClassDecls];
        for (size_t i = 0; i < nClassDecls; ++i)
        {
            strm << "class_" << i;
            MI_ClassDeclEx* pClass = new MI_ClassDeclEx;
            init_class_decl (strm.str ().c_str (), 3, 3, 3, true, pClass);
            strm.str ("");
            strm.clear ();
            classDecls[i] = pClass;
        }
        pSchemaOut->classDecls = classDecls;
    }
    else
    {
        pSchemaOut->classDecls = NULL;
    }
}


} // namespace <unnamed>


/*ctor*/
mi_memory_helper_test::mi_memory_helper_test ()
{
    add_test (MAKE_TEST (mi_memory_helper_test::test01));
    add_test (MAKE_TEST (mi_memory_helper_test::test02));
    add_test (MAKE_TEST (mi_memory_helper_test::test03));
    add_test (MAKE_TEST (mi_memory_helper_test::test04));
    add_test (MAKE_TEST (mi_memory_helper_test::test05));
    add_test (MAKE_TEST (mi_memory_helper_test::test06));
    add_test (MAKE_TEST (mi_memory_helper_test::test07));
    add_test (MAKE_TEST (mi_memory_helper_test::test08));
    add_test (MAKE_TEST (mi_memory_helper_test::test09));
    add_test (MAKE_TEST (mi_memory_helper_test::test10));
    add_test (MAKE_TEST (mi_memory_helper_test::test11));
    add_test (MAKE_TEST (mi_memory_helper_test::test12));
    add_test (MAKE_TEST (mi_memory_helper_test::test13));
    add_test (MAKE_TEST (mi_memory_helper_test::test14));
    add_test (MAKE_TEST (mi_memory_helper_test::test15));
    add_test (MAKE_TEST (mi_memory_helper_test::test16));
    add_test (MAKE_TEST (mi_memory_helper_test::test17));
    add_test (MAKE_TEST (mi_memory_helper_test::test18));
    add_test (MAKE_TEST (mi_memory_helper_test::test19));
    add_test (MAKE_TEST (mi_memory_helper_test::test20));
    add_test (MAKE_TEST (mi_memory_helper_test::test21));
    add_test (MAKE_TEST (mi_memory_helper_test::test22));
    add_test (MAKE_TEST (mi_memory_helper_test::test23));
    add_test (MAKE_TEST (mi_memory_helper_test::test24));
    add_test (MAKE_TEST (mi_memory_helper_test::test25));
    add_test (MAKE_TEST (mi_memory_helper_test::test26));
    add_test (MAKE_TEST (mi_memory_helper_test::test27));
    add_test (MAKE_TEST (mi_memory_helper_test::test28));
    add_test (MAKE_TEST (mi_memory_helper_test::test29));
    add_test (MAKE_TEST (mi_memory_helper_test::test30));
    add_test (MAKE_TEST (mi_memory_helper_test::test31));
}


int
mi_memory_helper_test::test01 ()
{
    // test BaseType
    int rval = EXIT_SUCCESS;
    if (EXIT_FAILURE == BaseType_test<MI_Boolean> () ||
        EXIT_FAILURE == BaseType_test<MI_Uint8> () ||
        EXIT_FAILURE == BaseType_test<MI_Sint8> () ||
        EXIT_FAILURE == BaseType_test<MI_Uint16> () ||
        EXIT_FAILURE == BaseType_test<MI_Sint16> () ||
        EXIT_FAILURE == BaseType_test<MI_Uint32> () ||
        EXIT_FAILURE == BaseType_test<MI_Sint32> () ||
        EXIT_FAILURE == BaseType_test<MI_Uint64> () ||
        EXIT_FAILURE == BaseType_test<MI_Sint64> () ||
        EXIT_FAILURE == BaseType_test<MI_Real32> () ||
        EXIT_FAILURE == BaseType_test<MI_Real64> () ||
        EXIT_FAILURE == BaseType_test<MI_Char16> () ||
        EXIT_FAILURE == BaseType_test<MI_Datetime> () ||
        EXIT_FAILURE == BaseType_test<MI_Char> () ||
        EXIT_FAILURE == BaseType_test<MI_Instance> () ||
        EXIT_FAILURE == BaseType_test<MI_BooleanA> () ||
        EXIT_FAILURE == BaseType_test<MI_Uint8A> () ||
        EXIT_FAILURE == BaseType_test<MI_Sint8A> () ||
        EXIT_FAILURE == BaseType_test<MI_Uint16A> () ||
        EXIT_FAILURE == BaseType_test<MI_Sint16A> () ||
        EXIT_FAILURE == BaseType_test<MI_Uint32A> () ||
        EXIT_FAILURE == BaseType_test<MI_Sint32A> () ||
        EXIT_FAILURE == BaseType_test<MI_Uint64A> () ||
        EXIT_FAILURE == BaseType_test<MI_Sint64A> () ||
        EXIT_FAILURE == BaseType_test<MI_Real32A> () ||
        EXIT_FAILURE == BaseType_test<MI_Real64A> () ||
        EXIT_FAILURE == BaseType_test<MI_Char16A> () ||
        EXIT_FAILURE == BaseType_test<MI_DatetimeA> () ||
        EXIT_FAILURE == BaseType_test<MI_StringA> () ||
        EXIT_FAILURE == BaseType_test<MI_InstanceA> ())
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test02 ()
{
    // test TypeTraits::IsArray
    int rval = EXIT_SUCCESS;
    if (TypeTraits<MI_Boolean>::IsArray ||
        TypeTraits<MI_Uint8>::IsArray ||
        TypeTraits<MI_Sint8>::IsArray ||
        TypeTraits<MI_Uint16>::IsArray ||
        TypeTraits<MI_Sint16>::IsArray ||
        TypeTraits<MI_Uint32>::IsArray ||
        TypeTraits<MI_Sint32>::IsArray ||
        TypeTraits<MI_Uint64>::IsArray ||
        TypeTraits<MI_Sint64>::IsArray ||
        TypeTraits<MI_Real32>::IsArray ||
        TypeTraits<MI_Real64>::IsArray ||
        TypeTraits<MI_Char16>::IsArray ||
        TypeTraits<MI_Datetime>::IsArray ||
        TypeTraits<MI_Char*>::IsArray ||
        TypeTraits<MI_Instance*>::IsArray ||
        !TypeTraits<MI_BooleanA>::IsArray ||
        !TypeTraits<MI_Uint8A>::IsArray ||
        !TypeTraits<MI_Sint8A>::IsArray ||
        !TypeTraits<MI_Uint16A>::IsArray ||
        !TypeTraits<MI_Sint16A>::IsArray ||
        !TypeTraits<MI_Uint32A>::IsArray ||
        !TypeTraits<MI_Sint32A>::IsArray ||
        !TypeTraits<MI_Uint64A>::IsArray ||
        !TypeTraits<MI_Sint64A>::IsArray ||
        !TypeTraits<MI_Real32A>::IsArray ||
        !TypeTraits<MI_Real64A>::IsArray ||
        !TypeTraits<MI_Char16A>::IsArray ||
        !TypeTraits<MI_DatetimeA>::IsArray ||
        !TypeTraits<MI_StringA>::IsArray ||
        !TypeTraits<MI_InstanceA>::IsArray)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test03 ()
{
    // test TypeTraits::IsArray
    int rval = EXIT_SUCCESS;
    if (TypeTraits<MI_Boolean>::HasDestruct ||
        TypeTraits<MI_Uint8>::HasDestruct ||
        TypeTraits<MI_Sint8>::HasDestruct ||
        TypeTraits<MI_Uint16>::HasDestruct ||
        TypeTraits<MI_Sint16>::HasDestruct ||
        TypeTraits<MI_Uint32>::HasDestruct ||
        TypeTraits<MI_Sint32>::HasDestruct ||
        TypeTraits<MI_Uint64>::HasDestruct ||
        TypeTraits<MI_Sint64>::HasDestruct ||
        TypeTraits<MI_Real32>::HasDestruct ||
        TypeTraits<MI_Real64>::HasDestruct ||
        TypeTraits<MI_Char16>::HasDestruct ||
        TypeTraits<MI_Datetime>::HasDestruct ||
        !TypeTraits<MI_Char*>::HasDestruct ||
        !TypeTraits<MI_Instance*>::HasDestruct)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test04 ()
{
    // test TypeTraits::aggregate_t
    int rval = EXIT_SUCCESS;
    if (!util::is_same<MI_Boolean,
                       TypeTraits<MI_BooleanA>::aggregate_t>::value ||
        !util::is_same<MI_Uint8, TypeTraits<MI_Uint8A>::aggregate_t>::value ||
        !util::is_same<MI_Sint8, TypeTraits<MI_Sint8A>::aggregate_t>::value ||
        !util::is_same<MI_Uint16, TypeTraits<MI_Uint16A>::aggregate_t>::value ||
        !util::is_same<MI_Sint16, TypeTraits<MI_Sint16A>::aggregate_t>::value ||
        !util::is_same<MI_Uint32, TypeTraits<MI_Uint32A>::aggregate_t>::value ||
        !util::is_same<MI_Sint32, TypeTraits<MI_Sint32A>::aggregate_t>::value ||
        !util::is_same<MI_Uint64, TypeTraits<MI_Uint64A>::aggregate_t>::value ||
        !util::is_same<MI_Sint64, TypeTraits<MI_Sint64A>::aggregate_t>::value ||
        !util::is_same<MI_Real32, TypeTraits<MI_Real32A>::aggregate_t>::value ||
        !util::is_same<MI_Real64, TypeTraits<MI_Real64A>::aggregate_t>::value ||
        !util::is_same<MI_Char16, TypeTraits<MI_Char16A>::aggregate_t>::value ||
        !util::is_same<MI_Datetime,
                       TypeTraits<MI_DatetimeA>::aggregate_t>::value ||
        !util::is_same<MI_Char*, TypeTraits<MI_StringA>::aggregate_t>::value ||
        !util::is_same<MI_Instance*,
                       TypeTraits<MI_InstanceA>::aggregate_t>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test05 ()
{
    // test ConstRemover
    int rval = EXIT_SUCCESS;
    if (EXIT_FAILURE == ConstRemover_test<MI_Boolean> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Uint8> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Sint8> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Uint16> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Sint16> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Uint32> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Sint32> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Uint64> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Sint64> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Real32> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Real64> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Char16> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Datetime> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Char> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Instance> () ||
        EXIT_FAILURE == ConstRemover_test<MI_BooleanA> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Uint8A> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Sint8A> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Uint16A> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Sint16A> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Uint32A> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Sint32A> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Uint64A> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Sint64A> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Real32A> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Real64A> () ||
        EXIT_FAILURE == ConstRemover_test<MI_Char16A> () ||
        EXIT_FAILURE == ConstRemover_test<MI_DatetimeA> () ||
        EXIT_FAILURE == ConstRemover_test<MI_StringA> () ||
        EXIT_FAILURE == ConstRemover_test<MI_InstanceA> ())
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test06 ()
{
    // test MI_DeleteArray
    int rval = EXIT_SUCCESS;
    {
        TestItem* pArray = NULL;
        pArray = new TestItem[10];
        if (10 != TestItem::count)
        {
            rval = EXIT_FAILURE;
        }
        MI_DeleteArray (pArray);
        if (0 != TestItem::count ||
            NULL != pArray)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        TestItem const* pArray = NULL;
        pArray = new TestItem[10];
        if (10 != TestItem::count)
        {
            rval = EXIT_FAILURE;
        }
        MI_DeleteArray (pArray);
        if (0 != TestItem::count ||
            NULL != pArray)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (EXIT_FAILURE == MI_DeleteArray_test<MI_Boolean> () ||
        EXIT_FAILURE == MI_DeleteArray_test<MI_Uint8> () ||
        EXIT_FAILURE == MI_DeleteArray_test<MI_Sint8> () ||
        EXIT_FAILURE == MI_DeleteArray_test<MI_Uint16> () ||
        EXIT_FAILURE == MI_DeleteArray_test<MI_Sint16> () ||
        EXIT_FAILURE == MI_DeleteArray_test<MI_Uint32> () ||
        EXIT_FAILURE == MI_DeleteArray_test<MI_Sint32> () ||
        EXIT_FAILURE == MI_DeleteArray_test<MI_Uint64> () ||
        EXIT_FAILURE == MI_DeleteArray_test<MI_Sint64> () ||
        EXIT_FAILURE == MI_DeleteArray_test<MI_Real32> () ||
        EXIT_FAILURE == MI_DeleteArray_test<MI_Real64> () ||
        EXIT_FAILURE == MI_DeleteArray_test<MI_Char16> () ||
        EXIT_FAILURE == MI_DeleteArray_test<MI_Datetime> () ||
        EXIT_FAILURE == MI_DeleteArray_test<MI_Char> ())
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test07 ()
{
    // test MI_BuiltInArrayDestroy::destroy
    int rval = EXIT_SUCCESS;
    if (EXIT_FAILURE == MI_BuiltInArrayDestroy_test<MI_BooleanA> () ||
        EXIT_FAILURE == MI_BuiltInArrayDestroy_test<MI_Uint8A> () ||
        EXIT_FAILURE == MI_BuiltInArrayDestroy_test<MI_Sint8A> () ||
        EXIT_FAILURE == MI_BuiltInArrayDestroy_test<MI_Uint16A> () ||
        EXIT_FAILURE == MI_BuiltInArrayDestroy_test<MI_Sint16A> () ||
        EXIT_FAILURE == MI_BuiltInArrayDestroy_test<MI_Uint32A> () ||
        EXIT_FAILURE == MI_BuiltInArrayDestroy_test<MI_Sint32A> () ||
        EXIT_FAILURE == MI_BuiltInArrayDestroy_test<MI_Uint64A> () ||
        EXIT_FAILURE == MI_BuiltInArrayDestroy_test<MI_Sint64A> () ||
        EXIT_FAILURE == MI_BuiltInArrayDestroy_test<MI_Real32A> () ||
        EXIT_FAILURE == MI_BuiltInArrayDestroy_test<MI_Real64A> () ||
        EXIT_FAILURE == MI_BuiltInArrayDestroy_test<MI_Char16A> () ||
        EXIT_FAILURE == MI_BuiltInArrayDestroy_test<MI_DatetimeA> ())
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test08 ()
{
    // test MI_DestroyHelper<MI_Char*>
    int rval = EXIT_SUCCESS;
    static MI_Char const* const TEST_STRING = "test08";
    MI_Char* pString =
        strcpy (new MI_Char[strlen (TEST_STRING) + 1], TEST_STRING);
    MI_DestroyHelper<MI_Char*>::destroy (pString);
    if (NULL != pString)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test09 ()
{
    // test MI_Destroy<MI_Char*>
    int rval = EXIT_SUCCESS;
    static MI_Char const* const TEST_STRING = "test09";
    MI_Char* pString =
        strcpy (new MI_Char[strlen (TEST_STRING) + 1], TEST_STRING);
    MI_Destroy (pString);
    if (NULL != pString)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test10 ()
{
    // test MI_DestroyArrayItems<MI_Char*>
    int rval = EXIT_SUCCESS;
    static MI_Char const* const TEST_STRINGS[] = {
        "test10-00",
        "test10-01",
        "test10-02",
        "test10-03",
        "test10-04",
        "test10-05",
        "test10-06",
        "test10-07",
        "test10-08",
        "test10-09",
    };
    MI_Char* strings[card (TEST_STRINGS)];
    for (size_t i = 0; i < card (TEST_STRINGS); ++i)
    {
        strings[i] =
            strcpy (new MI_Char[strlen (TEST_STRINGS[i]) + 1], TEST_STRINGS[i]);
    }
    MI_DestroyArrayItems (strings, card (TEST_STRINGS));
    for (size_t i = 0; i < card (TEST_STRINGS); ++i)
    {
        if (//NULL != stringA.data[i] ||
            NULL != strings[i])
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
mi_memory_helper_test::test11 ()
{
    // test MI_CompoundArrayDestroy<MI_Char*>::destroy
    int rval = EXIT_SUCCESS;
    static MI_Char const* const TEST_STRINGS[] = {
        "test11-00",
        "test11-01",
        "test11-02",
        "test11-03",
        "test11-04",
        "test11-05",
        "test11-06",
        "test11-07",
        "test11-08",
        "test11-09",
    };
    MI_StringA stringA = {
        new MI_Char*[card (TEST_STRINGS)],
        card (TEST_STRINGS)
    };
    for (size_t i = 0; i < card (TEST_STRINGS); ++i)
    {
        stringA.data[i] =
            strcpy (new MI_Char[strlen (TEST_STRINGS[i]) + 1], TEST_STRINGS[i]);
    }
    MI_CompoundArrayDestroy<MI_StringA>::destroy (stringA);
    if (NULL != stringA.data ||
        0 != stringA.size)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test12 ()
{
    // test MI_ArrayDestroy::destroy
    int rval = EXIT_SUCCESS;
    static MI_Char const* const TEST_STRINGS[] = {
        "test12-00",
        "test12-01",
        "test12-02",
        "test12-03",
        "test12-04",
        "test12-05",
        "test12-06",
        "test12-07",
        "test12-08",
        "test12-09",
    };
    if (EXIT_FAILURE == MI_ArrayDestroy_test<MI_BooleanA> () ||
        EXIT_FAILURE == MI_ArrayDestroy_test<MI_Uint8A> () ||
        EXIT_FAILURE == MI_ArrayDestroy_test<MI_Sint8A> () ||
        EXIT_FAILURE == MI_ArrayDestroy_test<MI_Uint16A> () ||
        EXIT_FAILURE == MI_ArrayDestroy_test<MI_Sint16A> () ||
        EXIT_FAILURE == MI_ArrayDestroy_test<MI_Uint32A> () ||
        EXIT_FAILURE == MI_ArrayDestroy_test<MI_Sint32A> () ||
        EXIT_FAILURE == MI_ArrayDestroy_test<MI_Uint64A> () ||
        EXIT_FAILURE == MI_ArrayDestroy_test<MI_Sint64A> () ||
        EXIT_FAILURE == MI_ArrayDestroy_test<MI_Real32A> () ||
        EXIT_FAILURE == MI_ArrayDestroy_test<MI_Real64A> () ||
        EXIT_FAILURE == MI_ArrayDestroy_test<MI_Char16A> () ||
        EXIT_FAILURE == MI_ArrayDestroy_test<MI_DatetimeA> ())
    {
        rval = EXIT_FAILURE;
    }
    MI_StringA stringA = {
        new MI_Char*[card (TEST_STRINGS)],
        card (TEST_STRINGS)
    };
    for (size_t i = 0; i < card (TEST_STRINGS); ++i)
    {
        stringA.data[i] =
            strcpy (new MI_Char[strlen (TEST_STRINGS[i]) + 1], TEST_STRINGS[i]);
    }
    MI_ArrayDestroy<MI_StringA>::destroy (stringA);
    if (NULL != stringA.data ||
        0 != stringA.size)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test13 ()
{
    // test MI_DestroyHelper::destroy (non-specialized types)
    int rval = EXIT_SUCCESS;
    static MI_Char const* const TEST_STRINGS[] = {
        "test13-00",
        "test13-01",
        "test13-02",
        "test13-03",
        "test13-04",
        "test13-05",
        "test13-06",
        "test13-07",
        "test13-08",
        "test13-09",
    };
    if (EXIT_FAILURE == MI_DestroyHelper_test<MI_BooleanA> () ||
        EXIT_FAILURE == MI_DestroyHelper_test<MI_Uint8A> () ||
        EXIT_FAILURE == MI_DestroyHelper_test<MI_Sint8A> () ||
        EXIT_FAILURE == MI_DestroyHelper_test<MI_Uint16A> () ||
        EXIT_FAILURE == MI_DestroyHelper_test<MI_Sint16A> () ||
        EXIT_FAILURE == MI_DestroyHelper_test<MI_Uint32A> () ||
        EXIT_FAILURE == MI_DestroyHelper_test<MI_Sint32A> () ||
        EXIT_FAILURE == MI_DestroyHelper_test<MI_Uint64A> () ||
        EXIT_FAILURE == MI_DestroyHelper_test<MI_Sint64A> () ||
        EXIT_FAILURE == MI_DestroyHelper_test<MI_Real32A> () ||
        EXIT_FAILURE == MI_DestroyHelper_test<MI_Real64A> () ||
        EXIT_FAILURE == MI_DestroyHelper_test<MI_Char16A> () ||
        EXIT_FAILURE == MI_DestroyHelper_test<MI_DatetimeA> ())
    {
        rval = EXIT_FAILURE;
    }
    MI_StringA stringA = {
        new MI_Char*[card (TEST_STRINGS)],
        card (TEST_STRINGS)
    };
    for (size_t i = 0; i < card (TEST_STRINGS); ++i)
    {
        stringA.data[i] =
            strcpy (new MI_Char[strlen (TEST_STRINGS[i]) + 1], TEST_STRINGS[i]);
    }
    MI_DestroyHelper<MI_StringA>::destroy (stringA);
    if (NULL != stringA.data ||
        0 != stringA.size)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test14 ()
{
    // test MI_Destroy (non-specialized types)
    int rval = EXIT_SUCCESS;
    static MI_Char const* const TEST_STRINGS[] = {
        "test14-00",
        "test14-01",
        "test14-02",
        "test14-03",
        "test14-04",
        "test14-05",
        "test14-06",
        "test14-07",
        "test14-08",
        "test14-09",
    };
    if (EXIT_FAILURE == MI_Destroy_test<MI_BooleanA> () ||
        EXIT_FAILURE == MI_Destroy_test<MI_Uint8A> () ||
        EXIT_FAILURE == MI_Destroy_test<MI_Sint8A> () ||
        EXIT_FAILURE == MI_Destroy_test<MI_Uint16A> () ||
        EXIT_FAILURE == MI_Destroy_test<MI_Sint16A> () ||
        EXIT_FAILURE == MI_Destroy_test<MI_Uint32A> () ||
        EXIT_FAILURE == MI_Destroy_test<MI_Sint32A> () ||
        EXIT_FAILURE == MI_Destroy_test<MI_Uint64A> () ||
        EXIT_FAILURE == MI_Destroy_test<MI_Sint64A> () ||
        EXIT_FAILURE == MI_Destroy_test<MI_Real32A> () ||
        EXIT_FAILURE == MI_Destroy_test<MI_Real64A> () ||
        EXIT_FAILURE == MI_Destroy_test<MI_Char16A> () ||
        EXIT_FAILURE == MI_Destroy_test<MI_DatetimeA> ())
    {
        rval = EXIT_FAILURE;
    }
    MI_StringA stringA = {
        new MI_Char*[card (TEST_STRINGS)],
        card (TEST_STRINGS)
    };
    for (size_t i = 0; i < card (TEST_STRINGS); ++i)
    {
        stringA.data[i] =
            strcpy (new MI_Char[strlen (TEST_STRINGS[i]) + 1], TEST_STRINGS[i]);
    }
    MI_Destroy (stringA);
    if (NULL != stringA.data ||
        0 != stringA.size)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test15 ()
{
    // test MI_DestroyHelper<MI_QualifierDecl> && MI_Destroy<MI_QualifierDecl>
    int rval = EXIT_SUCCESS;
    MI_Char const* const NAME = "qualifier_decl_name";
    // test MI_DestroyHelper with NULL value
    MI_QualifierDecl qualifierDecl;
    init_qualifier_decl (NAME, false, &qualifierDecl);
    MI_DestroyHelper<MI_QualifierDecl>::destroy (qualifierDecl);
    if (NULL != qualifierDecl.name ||
        NULL != qualifierDecl.value)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DestroyHelper with non-NULL value
    init_qualifier_decl (NAME, true, &qualifierDecl);
    MI_DestroyHelper<MI_QualifierDecl>::destroy (qualifierDecl);
    if (NULL != qualifierDecl.name ||
        NULL != qualifierDecl.value)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Destroy with NULL value
    init_qualifier_decl (NAME, false, &qualifierDecl);
    MI_Destroy (qualifierDecl);
    if (NULL != qualifierDecl.name ||
        NULL != qualifierDecl.value)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Destroy with non-NULL value
    init_qualifier_decl (NAME, true, &qualifierDecl);
    MI_Destroy (qualifierDecl);
    if (NULL != qualifierDecl.name ||
        NULL != qualifierDecl.value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test16 ()
{
    // test MI_DestroyHelper<MI_Qualifier> & MI_Destroy<MI_Qualifier>
    int rval = EXIT_SUCCESS;
    MI_Char const* const NAME = "qualifier_name";
    // test MI_DestroyHelper with NULL value
    MI_Qualifier qualifier;
    init_qualifier (NAME, false, &qualifier);
    MI_DestroyHelper<MI_Qualifier>::destroy (qualifier);
    if (NULL != qualifier.name ||
        NULL != qualifier.value)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DestroyHelper with non-NULL value
    init_qualifier (NAME, true, &qualifier);
    MI_DestroyHelper<MI_Qualifier>::destroy (qualifier);
    if (NULL != qualifier.name ||
        NULL != qualifier.value)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Destroy with NULL value
    init_qualifier (NAME, false, &qualifier);
    MI_Destroy (qualifier);
    if (NULL != qualifier.name ||
        NULL != qualifier.value)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Destroy with non-NULL value
    init_qualifier (NAME, true, &qualifier);
    MI_Destroy (qualifier);
    if (NULL != qualifier.name ||
        NULL != qualifier.value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test17 ()
{
    // test MI_Delete<MI_QualifierDecl> && MI_DeleteArrayItems<MI_QualifierDecl>
    int rval = EXIT_SUCCESS;
    MI_Char const* const NAME_BASE = "qualifier";
    // test MI_Delete with NULL value
    MI_QualifierDecl* pQualifierDecl = new MI_QualifierDecl;
    init_qualifier_decl (NAME_BASE, false, pQualifierDecl);
    MI_Delete (pQualifierDecl);
    if (NULL != pQualifierDecl)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Delete with non-NULL value
    pQualifierDecl = new MI_QualifierDecl;
    init_qualifier_decl (NAME_BASE, true, pQualifierDecl);
    MI_Delete (pQualifierDecl);
    if (NULL != pQualifierDecl)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DeleteArrayItems with NULL values
    MI_QualifierDecl* pQualifierDecls[3];
    std::ostringstream strm;
    for (int i = 0; i < 3; ++i)
    {
        pQualifierDecls[i] = new MI_QualifierDecl;
        strm << NAME_BASE << '_' << i;
        init_qualifier_decl (strm.str ().c_str (), false, pQualifierDecls[i]);
        strm.str ("");
        strm.clear ();
    }
    MI_DeleteArrayItems (pQualifierDecls, 3);
    if (NULL != pQualifierDecls[0] ||
        NULL != pQualifierDecls[1] ||
        NULL != pQualifierDecls[2])
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DeleteArrayItems with NULL values
    for (int i = 0; i < 3; ++i)
    {
        pQualifierDecls[i] = new MI_QualifierDecl;
        strm << NAME_BASE << '_' << i;
        init_qualifier_decl (strm.str ().c_str (), true, pQualifierDecls[i]);
        strm.str ("");
        strm.clear ();
    }
    MI_DeleteArrayItems (pQualifierDecls, 3);
    if (NULL != pQualifierDecls[0] ||
        NULL != pQualifierDecls[1] ||
        NULL != pQualifierDecls[2])
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test18 ()
{
    // test MI_Delete<MI_Qualifier> && MI_DeleteArrayItems<MI_Qualifier>
    int rval = EXIT_SUCCESS;
    MI_Char const* const NAME_BASE = "qualifier";
    // test MI_Delete with NULL value
    MI_Qualifier* pQualifier = new MI_Qualifier;
    init_qualifier (NAME_BASE, false, pQualifier);
    MI_Delete (pQualifier);
    if (NULL != pQualifier)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Delete with non-NULL value
    pQualifier = new MI_Qualifier;
    init_qualifier (NAME_BASE, true, pQualifier);
    MI_Delete (pQualifier);
    if (NULL != pQualifier)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DeleteArrayItems with NULL values
    MI_Qualifier* pQualifiers[3];
    std::ostringstream strm;
    for (int i = 0; i < 3; ++i)
    {
        pQualifiers[i] = new MI_Qualifier;
        strm << NAME_BASE << '_' << i;
        init_qualifier (strm.str ().c_str (), false, pQualifiers[i]);
        strm.str ("");
        strm.clear ();
    }
    MI_DeleteArrayItems (pQualifiers, 3);
    if (NULL != pQualifiers[0] ||
        NULL != pQualifiers[1] ||
        NULL != pQualifiers[2])
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DeleteArrayItems with non-NULL values
    for (int i = 0; i < 3; ++i)
    {
        pQualifiers[i] = new MI_Qualifier;
        strm << NAME_BASE << '_' << i;
        init_qualifier (strm.str ().c_str (), true, pQualifiers[i]);
        strm.str ("");
        strm.clear ();
    }
    MI_DeleteArrayItems (pQualifiers, 3);
    if (NULL != pQualifiers[0] ||
        NULL != pQualifiers[1] ||
        NULL != pQualifiers[2])
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test19 ()
{
    // test MI_DestroyHelper<MI_ParameterDecl> && MI_Destroy<MI_ParameterDecl>
    int rval = EXIT_SUCCESS;
    MI_Char const* const NAME_BASE = "parameter";
    // test MI_DestroyHelper with NULL values
    MI_ParameterDecl param;
    init_parameter_decl (NAME_BASE, 0, false, &param);
    MI_DestroyHelper<MI_ParameterDecl>::destroy (param);
    if (NULL != param.name ||
        NULL != param.qualifiers ||
        0 != param.numQualifiers ||
        NULL != param.className)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DestroyHelper with non-NULL values
    init_parameter_decl (NAME_BASE, 3, true, &param);
    MI_DestroyHelper<MI_ParameterDecl>::destroy (param);
    if (NULL != param.name ||
        NULL != param.qualifiers ||
        0 != param.numQualifiers ||
        NULL != param.className)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Destroy with NULL values
    init_parameter_decl (NAME_BASE, 0, false, &param);
    MI_Destroy (param);
    if (NULL != param.name ||
        NULL != param.qualifiers ||
        0 != param.numQualifiers ||
        NULL != param.className)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Destroy with non-NULL values
    init_parameter_decl (NAME_BASE, 3, true, &param);
    MI_Destroy (param);
    if (NULL != param.name ||
        NULL != param.qualifiers ||
        0 != param.numQualifiers ||
        NULL != param.className)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test20 ()
{
    // test MI_Delete<MI_ParameterDecl> && MI_DeleteArrayItems<MI_ParameterDecl>
    int rval = EXIT_SUCCESS;
    MI_Char const* const NAME_BASE = "parameter";
    // test MI_Delete with NULL values
    MI_ParameterDecl* pParam = new MI_ParameterDecl;
    init_parameter_decl (NAME_BASE, 0, false, pParam);
    MI_Delete (pParam);
    if (NULL != pParam)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Delete with non-NULL values
    pParam = new MI_ParameterDecl;
    init_parameter_decl (NAME_BASE, 3, true, pParam);
    MI_Delete (pParam);
    if (NULL != pParam)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DeleteArrayItems with NULL values
    MI_ParameterDecl* pParams[3];
    std::ostringstream strm;
    for (size_t i = 0; i < 3; ++i)
    {
        strm << NAME_BASE << "_" << i;
        pParams[i] = new MI_ParameterDecl;
        init_parameter_decl (strm.str ().c_str (), 0, false, pParams[i]);
        strm.str ("");
        strm.clear ();
    }
    MI_DeleteArrayItems (pParams, 3);
    if (NULL != pParams[0] ||
        NULL != pParams[1] ||
        NULL != pParams[2])
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DeleteArrayItems with non-NULL values
    for (size_t i = 0; i < 3; ++i)
    {
        strm << NAME_BASE << "_" << i;
        pParams[i] = new MI_ParameterDecl;
        init_parameter_decl (strm.str ().c_str (), 3, true, pParams[i]);
        strm.str ("");
        strm.clear ();
    }
    MI_DeleteArrayItems (pParams, 3);
    if (NULL != pParams[0] ||
        NULL != pParams[1] ||
        NULL != pParams[2])
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test21 ()
{
    // test MI_DestroyHelper<MI_PropertyDecl> && MI_Destroy<MI_PropertyDecl>
    int rval = EXIT_SUCCESS;
    MI_Char const* const NAME_BASE = "property";
    // test MI_DestroyHelper with NULL values
    MI_PropertyDecl property;
    init_property_decl (NAME_BASE, 0, false, &property);
    MI_DestroyHelper<MI_PropertyDecl>::destroy (property);
    if (NULL != property.name ||
        NULL != property.qualifiers ||
        0 != property.numQualifiers ||
        NULL != property.className ||
        NULL != property.origin ||
        NULL != property.propagator ||
        NULL != property.value)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DestroyHelper with non-NULL values
    init_property_decl (NAME_BASE, 3, true, &property);
    MI_DestroyHelper<MI_PropertyDecl>::destroy (property);
    if (NULL != property.name ||
        NULL != property.qualifiers ||
        0 != property.numQualifiers ||
        NULL != property.className ||
        NULL != property.origin ||
        NULL != property.propagator ||
        NULL != property.value)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Destroy with NULL values
    init_property_decl (NAME_BASE, 0, false, &property);
    MI_Destroy (property);
    if (NULL != property.name ||
        NULL != property.qualifiers ||
        0 != property.numQualifiers ||
        NULL != property.className ||
        NULL != property.origin ||
        NULL != property.propagator ||
        NULL != property.value)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Destroy with non-NULL values
    init_property_decl (NAME_BASE, 3, true, &property);
    MI_Destroy (property);
    if (NULL != property.name ||
        NULL != property.qualifiers ||
        0 != property.numQualifiers ||
        NULL != property.className ||
        NULL != property.origin ||
        NULL != property.propagator ||
        NULL != property.value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test22 ()
{
    // test MI_Delete<MI_PropertyDecl> && MI_DeleteArrayItems<MI_PropertyDecl>
    int rval = EXIT_SUCCESS;
    MI_Char const* const NAME_BASE = "property";
    // test MI_Delete with NULL values
    MI_PropertyDecl* pProperty = new MI_PropertyDecl;
    init_property_decl (NAME_BASE, 0, false, pProperty);
    MI_Delete (pProperty);
    if (NULL != pProperty)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Delete with non-NULL values
    pProperty = new MI_PropertyDecl;
    init_property_decl (NAME_BASE, 3, true, pProperty);
    MI_Delete (pProperty);
    if (NULL != pProperty)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DeleteArrayItems with NULL values
    MI_PropertyDecl* pProps[3];
    std::ostringstream strm;
    for (size_t i = 0; i < 3; ++i)
    {
        strm << NAME_BASE << "_" << i;
        pProps[i] = new MI_PropertyDecl;
        init_property_decl (strm.str ().c_str (), 0, false, pProps[i]);
        strm.str ("");
        strm.clear ();
    }
    MI_DeleteArrayItems (pProps, 3);
    if (NULL != pProps[0] ||
        NULL != pProps[1] ||
        NULL != pProps[2])
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DeleteArrayItems with non-NULL values
    for (size_t i = 0; i < 3; ++i)
    {
        strm << NAME_BASE << "_" << i;
        pProps[i] = new MI_PropertyDecl;
        init_property_decl (strm.str ().c_str (), 3, true, pProps[i]);
        strm.str ("");
        strm.clear ();
    }
    MI_DeleteArrayItems (pProps, 3);
    if (NULL != pProps[0] ||
        NULL != pProps[1] ||
        NULL != pProps[2])
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test23 ()
{
    // test MI_DestroyHelper<MI_MethodDecl> && MI_Destroy<MI_MethodDecl>
    int rval = EXIT_SUCCESS;
    MI_Char const* const NAME_BASE = "method";
    // test MI_DestroyHelper with NULL values
    MI_MethodDecl method;
    init_method_decl (NAME_BASE, 0, 0, false, &method);
    MI_DestroyHelper<MI_MethodDecl>::destroy (method);
    if (NULL != method.name ||
        NULL != method.qualifiers ||
        0 != method.numQualifiers ||
        NULL != method.parameters ||
        0 != method.numParameters ||
        NULL != method.origin ||
        NULL != method.propagator)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DestroyHelper with non-NULL values
    init_method_decl (NAME_BASE, 3, 3, true, &method);
    MI_DestroyHelper<MI_MethodDecl>::destroy (method);
    if (NULL != method.name ||
        NULL != method.qualifiers ||
        0 != method.numQualifiers ||
        NULL != method.parameters ||
        0 != method.numParameters ||
        NULL != method.origin ||
        NULL != method.propagator)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Destroy with NULL values
    init_method_decl (NAME_BASE, 0, 0, false, &method);
    MI_Destroy (method);
    if (NULL != method.name ||
        NULL != method.qualifiers ||
        0 != method.numQualifiers ||
        NULL != method.parameters ||
        0 != method.numParameters ||
        NULL != method.origin ||
        NULL != method.propagator)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Destroy with non-NULL values
    init_method_decl (NAME_BASE, 3, 3, true, &method);
    MI_Destroy (method);
    if (NULL != method.name ||
        NULL != method.qualifiers ||
        0 != method.numQualifiers ||
        NULL != method.parameters ||
        0 != method.numParameters ||
        NULL != method.origin ||
        NULL != method.propagator)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test24 ()
{
    // test MI_Delete<MI_MethodDecl> && MI_DeleteArrayItems<MI_MethodDecl>
    int rval = EXIT_SUCCESS;
    MI_Char const* const NAME_BASE = "method";
    // test MI_Delete with NULL values
    MI_MethodDecl* pMethod = new MI_MethodDecl;
    init_method_decl (NAME_BASE, 0, 0, false, pMethod);
    MI_Delete (pMethod);
    if (NULL != pMethod)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Delete with non-NULL values
    pMethod = new MI_MethodDecl;
    init_method_decl (NAME_BASE, 3, 3, true, pMethod);
    MI_Delete (pMethod);
    if (NULL != pMethod)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DeleteArrayItems with NULL values
    MI_MethodDecl* pMethods[3];
    std::ostringstream strm;
    for (size_t i = 0; i < 3; ++i)
    {
        strm << NAME_BASE << "_" << i;
        pMethods[i] = new MI_MethodDecl;
        init_method_decl (strm.str ().c_str (), 0, 0, false, pMethods[i]);
        strm.str ("");
        strm.clear ();
    }
    MI_DeleteArrayItems (pMethods, 3);
    if (NULL != pMethods[0] ||
        NULL != pMethods[1] ||
        NULL != pMethods[2])
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DeleteArrayItems with non-NULL values
    for (size_t i = 0; i < 3; ++i)
    {
        strm << NAME_BASE << "_" << i;
        pMethods[i] = new MI_MethodDecl;
        init_method_decl (strm.str ().c_str (), 3, 3, true, pMethods[i]);
        strm.str ("");
        strm.clear ();
    }
    MI_DeleteArrayItems (pMethods, 3);
    if (NULL != pMethods[0] ||
        NULL != pMethods[1] ||
        NULL != pMethods[2])
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test25 ()
{
    // test MI_DestroyHelper<MI_ClassDeclEx> && MI_Destroy<MI_ClassDeclEx>
    int rval = EXIT_SUCCESS;
    MI_Char const* const NAME_BASE = "class";
    // test MI_DestroyHelper with NULL values
    MI_ClassDeclEx classDecl;
    init_class_decl (NAME_BASE, 0, 0, 0, false, &classDecl);
    MI_DestroyHelper<MI_ClassDeclEx>::destroy (classDecl);
    if (NULL != classDecl.name ||
        NULL != classDecl.qualifiers ||
        0 != classDecl.numQualifiers ||
        NULL != classDecl.properties ||
        0 != classDecl.numProperties ||
        NULL != classDecl.superClass ||
        NULL != classDecl.methods ||
        0 != classDecl.numMethods ||
        NULL != classDecl.providerFT ||
        NULL != classDecl.owningClassName)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DestroyHelper with non-NULL values
    init_class_decl (NAME_BASE, 3, 3, 3, true, &classDecl);
    MI_DestroyHelper<MI_ClassDeclEx>::destroy (classDecl);
    if (NULL != classDecl.name ||
        NULL != classDecl.qualifiers ||
        0 != classDecl.numQualifiers ||
        NULL != classDecl.properties ||
        0 != classDecl.numProperties ||
        NULL != classDecl.superClass ||
        NULL != classDecl.methods ||
        0 != classDecl.numMethods ||
        NULL != classDecl.providerFT ||
        NULL != classDecl.owningClassName)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Destroy with NULL values
    init_class_decl (NAME_BASE, 0, 0, 0, false, &classDecl);
    MI_Destroy (classDecl);
    if (NULL != classDecl.name ||
        NULL != classDecl.qualifiers ||
        0 != classDecl.numQualifiers ||
        NULL != classDecl.properties ||
        0 != classDecl.numProperties ||
        NULL != classDecl.superClass ||
        NULL != classDecl.methods ||
        0 != classDecl.numMethods ||
        NULL != classDecl.providerFT ||
        NULL != classDecl.owningClassName)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Destroy with non-NULL values
    init_class_decl (NAME_BASE, 3, 3, 3, true, &classDecl);
    MI_Destroy (classDecl);
    if (NULL != classDecl.name ||
        NULL != classDecl.qualifiers ||
        0 != classDecl.numQualifiers ||
        NULL != classDecl.properties ||
        0 != classDecl.numProperties ||
        NULL != classDecl.superClass ||
        NULL != classDecl.methods ||
        0 != classDecl.numMethods ||
        NULL != classDecl.providerFT ||
        NULL != classDecl.owningClassName)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test26 ()
{
    // test MI_Delete<MI_ClassDeclEx> && MI_DeleteArrayItems<MI_ClassDeclEx>
    int rval = EXIT_SUCCESS;
    MI_Char const* const NAME_BASE = "class";
    // test MI_Delete with NULL values
    MI_ClassDeclEx* pClass = new MI_ClassDeclEx;
    init_class_decl (NAME_BASE, 0, 0, 0, false, pClass);
    MI_Delete (pClass);
    if (NULL != pClass)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Delete with non-NULL values
    pClass = new MI_ClassDeclEx;
    init_class_decl (NAME_BASE, 3, 3, 3, true, pClass);
    MI_Delete (pClass);
    if (NULL != pClass)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DeleteArrayItems with NULL values
    MI_ClassDeclEx* pClasses[3];
    std::ostringstream strm;
    for (size_t i = 0; i < 3; ++i)
    {
        strm << NAME_BASE << "_" << i;
        pClasses[i] = new MI_ClassDeclEx;
        init_class_decl (strm.str ().c_str (), 0, 0, 0, false, pClasses[i]);
        strm.str ("");
        strm.clear ();
    }
    MI_DeleteArrayItems (pClasses, 3);
    if (NULL != pClasses[0] ||
        NULL != pClasses[1] ||
        NULL != pClasses[2])
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DeleteArrayItems with non-NULL values
    for (size_t i = 0; i < 3; ++i)
    {
        strm << NAME_BASE << "_" << i;
        pClasses[i] = new MI_ClassDeclEx;
        init_class_decl (strm.str ().c_str (), 3, 3, 3, true, pClasses[i]);
        strm.str ("");
        strm.clear ();
    }
    MI_DeleteArrayItems (pClasses, 3);
    if (NULL != pClasses[0] ||
        NULL != pClasses[1] ||
        NULL != pClasses[2])
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test27 ()
{
    // test MI_DestroyHelper<MI_SchemaDecl> && MI_Destroy<MI_SchemaDecl>
    int rval = EXIT_SUCCESS;
    // test MI_DestroyHelper with NULL values
    MI_SchemaDecl schemaDecl;
    init_schema_decl (0, 0, &schemaDecl);
    MI_DestroyHelper<MI_SchemaDecl>::destroy (schemaDecl);
    if (NULL != schemaDecl.qualifierDecls ||
        0 != schemaDecl.numQualifierDecls ||
        NULL != schemaDecl.classDecls ||
        0 != schemaDecl.numClassDecls)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_DestroyHelper with non-NULL values
    init_schema_decl (3, 3, &schemaDecl);
    MI_DestroyHelper<MI_SchemaDecl>::destroy (schemaDecl);
    if (NULL != schemaDecl.qualifierDecls ||
        0 != schemaDecl.numQualifierDecls ||
        NULL != schemaDecl.classDecls ||
        0 != schemaDecl.numClassDecls)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Destroy with NULL values
    init_schema_decl (0, 0, &schemaDecl);
    MI_Destroy (schemaDecl);
    if (NULL != schemaDecl.qualifierDecls ||
        0 != schemaDecl.numQualifierDecls ||
        NULL != schemaDecl.classDecls ||
        0 != schemaDecl.numClassDecls)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Destroy with non-NULL values
    init_schema_decl (3, 3, &schemaDecl);
    MI_Destroy (schemaDecl);
    if (NULL != schemaDecl.qualifierDecls ||
        0 != schemaDecl.numQualifierDecls ||
        NULL != schemaDecl.classDecls ||
        0 != schemaDecl.numClassDecls)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test28 ()
{
    // test MI_Delete<MI_SchemaDecl>
    int rval = EXIT_SUCCESS;
    // test MI_Delete with NULL values
    MI_SchemaDecl* pSchema = new MI_SchemaDecl;
    init_schema_decl (0, 0, pSchema);
    MI_Delete (pSchema);
    if (NULL != pSchema)
    {
        rval = EXIT_FAILURE;
    }
    // test MI_Delete with non-NULL values
    pSchema = new MI_SchemaDecl;
    init_schema_decl (3, 3, pSchema);
    MI_Delete (pSchema);
    if (NULL != pSchema)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test29 ()
{
    // test MI_Destroy (MI_Value, MI_Type)
    MI_Char const* const TEST_STRING = "test_string";
    int rval = EXIT_SUCCESS;
    MI_Value value;
    // MI_BOOLEAN
    MI_Destroy (value, MI_BOOLEAN);
    // MI_UINT8
    MI_Destroy (value, MI_UINT8);
    // MI_SINT8
    MI_Destroy (value, MI_SINT8);
    // MI_UINT16
    MI_Destroy (value, MI_UINT16);
    // MI_SINT16
    MI_Destroy (value, MI_SINT16);
    // MI_UINT32
    MI_Destroy (value, MI_UINT32);
    // MI_SINT32
    MI_Destroy (value, MI_SINT32);
    // MI_UINT64
    MI_Destroy (value, MI_UINT64);
    // MI_SINT64
    MI_Destroy (value, MI_SINT64);
    // MI_REAL32
    MI_Destroy (value, MI_REAL32);
    // MI_REAL64
    MI_Destroy (value, MI_REAL64);
    // MI_CHAR16
    MI_Destroy (value, MI_CHAR16);
    // MI_DATETIME
    MI_Destroy (value, MI_DATETIME);
    // MI_STRING
    value.string = strcpy (new MI_Char[strlen (TEST_STRING) + 1], TEST_STRING);
    MI_Destroy (value, MI_STRING);
    if (NULL != value.string)
    {
        rval = EXIT_FAILURE;
    }
    // MI_BOOLEANA
    value.booleana.data = new MI_Boolean[3];
    value.booleana.size = 3;
    MI_Destroy (value, MI_BOOLEANA);
    if (NULL != value.booleana.data ||
        0 != value.booleana.size)
    {
        rval = EXIT_FAILURE;
    }
    // MI_UINT8A
    value.uint8a.data = new MI_Uint8[3];
    value.uint8a.size = 3;
    MI_Destroy (value, MI_UINT8A);
    if (NULL != value.uint8a.data ||
        0 != value.uint8a.size)
    {
        rval = EXIT_FAILURE;
    }
    // MI_SINT8A
    value.sint8a.data = new MI_Sint8[3];
    value.sint8a.size = 3;
    MI_Destroy (value, MI_SINT8A);
    if (NULL != value.sint8a.data ||
        0 != value.sint8a.size)
    {
        rval = EXIT_FAILURE;
    }
    // MI_UINT16A
    value.uint16a.data = new MI_Uint16[3];
    value.uint16a.size = 3;
    MI_Destroy (value, MI_UINT16A);
    if (NULL != value.uint16a.data ||
        0 != value.uint16a.size)
    {
        rval = EXIT_FAILURE;
    }
    // MI_SINT16A
    value.sint16a.data = new MI_Sint16[3];
    value.sint16a.size = 3;
    MI_Destroy (value, MI_SINT16A);
    if (NULL != value.sint16a.data ||
        0 != value.sint16a.size)
    {
        rval = EXIT_FAILURE;
    }
    // MI_UINT32A
    value.uint32a.data = new MI_Uint32[3];
    value.uint32a.size = 3;
    MI_Destroy (value, MI_UINT32A);
    if (NULL != value.uint32a.data ||
        0 != value.uint32a.size)
    {
        rval = EXIT_FAILURE;
    }
    // MI_SINT32A
    value.sint32a.data = new MI_Sint32[3];
    value.sint32a.size = 3;
    MI_Destroy (value, MI_SINT32A);
    if (NULL != value.sint32a.data ||
        0 != value.sint32a.size)
    {
        rval = EXIT_FAILURE;
    }
    // MI_UINT64A
    value.uint64a.data = new MI_Uint64[3];
    value.uint64a.size = 3;
    MI_Destroy (value, MI_UINT64A);
    if (NULL != value.uint64a.data ||
        0 != value.uint64a.size)
    {
        rval = EXIT_FAILURE;
    }
    // MI_SINT64A
    value.sint64a.data = new MI_Sint64[3];
    value.sint64a.size = 3;
    MI_Destroy (value, MI_SINT64A);
    if (NULL != value.sint64a.data ||
        0 != value.sint64a.size)
    {
        rval = EXIT_FAILURE;
    }
    // MI_REAL32A
    value.real32a.data = new MI_Real32[3];
    value.real32a.size = 3;
    MI_Destroy (value, MI_REAL32A);
    if (NULL != value.real32a.data ||
        0 != value.real32a.size)
    {
        rval = EXIT_FAILURE;
    }
    // MI_REAL64A
    value.real64a.data = new MI_Real64[3];
    value.real64a.size = 3;
    MI_Destroy (value, MI_REAL64A);
    if (NULL != value.real64a.data ||
        0 != value.real64a.size)
    {
        rval = EXIT_FAILURE;
    }
    // MI_CHAR16A
    value.char16a.data = new MI_Char16[3];
    value.char16a.size = 3;
    MI_Destroy (value, MI_CHAR16A);
    if (NULL != value.char16a.data ||
        0 != value.char16a.size)
    {
        rval = EXIT_FAILURE;
    }
    // MI_DATETIMEA:
    value.datetimea.data = new MI_Datetime[3];
    value.datetimea.size = 3;
    MI_Destroy (value, MI_DATETIMEA);
    if (NULL != value.datetimea.data ||
        0 != value.datetimea.size)
    {
        rval = EXIT_FAILURE;
    }
    // MI_STRINGA:
    value.stringa.data = new MI_Char*[3];
    value.stringa.size = 3;
    for (size_t i = 0; i < 3; ++i)
    {
        value.stringa.data[i] =
            strcpy (new MI_Char[strlen (TEST_STRING) + 1], TEST_STRING);
    }
    MI_Destroy (value, MI_STRINGA);
    if (NULL != value.stringa.data ||
        0 != value.stringa.size)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test30 ()
{
    // test MI_Delete (MI_Value, MI_Type)
    MI_Char const* const TEST_STRING = "test_string";
    int rval = EXIT_SUCCESS;
    MI_Value* pValue = NULL;
    // MI_BOOLEAN
    pValue = new MI_Value;
    MI_Delete (pValue, MI_BOOLEAN);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_UINT8
    pValue = new MI_Value;
    MI_Delete (pValue, MI_UINT8);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_SINT8
    pValue = new MI_Value;
    MI_Delete (pValue, MI_SINT8);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_UINT16
    pValue = new MI_Value;
    MI_Delete (pValue, MI_UINT16);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_SINT16
    pValue = new MI_Value;
    MI_Delete (pValue, MI_SINT16);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_UINT32
    pValue = new MI_Value;
    MI_Delete (pValue, MI_UINT32);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_SINT32
    pValue = new MI_Value;
    MI_Delete (pValue, MI_SINT32);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_UINT64
    pValue = new MI_Value;
    MI_Delete (pValue, MI_UINT64);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_SINT64
    pValue = new MI_Value;
    MI_Delete (pValue, MI_SINT64);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_REAL32
    pValue = new MI_Value;
    MI_Delete (pValue, MI_REAL32);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_REAL64
    pValue = new MI_Value;
    MI_Delete (pValue, MI_REAL64);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_CHAR16
    pValue = new MI_Value;
    MI_Delete (pValue, MI_CHAR16);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_DATETIME
    pValue = new MI_Value;
    MI_Delete (pValue, MI_DATETIME);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_STRING
    pValue = new MI_Value;
    pValue->string =
        strcpy (new MI_Char[strlen (TEST_STRING) + 1], TEST_STRING);
    MI_Delete (pValue, MI_STRING);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_BOOLEANA
    pValue = new MI_Value;
    pValue->booleana.data = new MI_Boolean[3];
    pValue->booleana.size = 3;
    MI_Delete (pValue, MI_BOOLEANA);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_UINT8A
    pValue = new MI_Value;
    pValue->uint8a.data = new MI_Uint8[3];
    pValue->uint8a.size = 3;
    MI_Delete (pValue, MI_UINT8A);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_SINT8A
    pValue = new MI_Value;
    pValue->sint8a.data = new MI_Sint8[3];
    pValue->sint8a.size = 3;
    MI_Delete (pValue, MI_SINT8A);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_UINT16A
    pValue = new MI_Value;
    pValue->uint16a.data = new MI_Uint16[3];
    pValue->uint16a.size = 3;
    MI_Delete (pValue, MI_UINT16A);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_SINT16A
    pValue = new MI_Value;
    pValue->sint16a.data = new MI_Sint16[3];
    pValue->sint16a.size = 3;
    MI_Delete (pValue, MI_SINT16A);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_UINT32A
    pValue = new MI_Value;
    pValue->uint32a.data = new MI_Uint32[3];
    pValue->uint32a.size = 3;
    MI_Delete (pValue, MI_UINT32A);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_SINT32A
    pValue = new MI_Value;
    pValue->sint32a.data = new MI_Sint32[3];
    pValue->sint32a.size = 3;
    MI_Delete (pValue, MI_SINT32A);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_UINT64A
    pValue = new MI_Value;
    pValue->uint64a.data = new MI_Uint64[3];
    pValue->uint64a.size = 3;
    MI_Delete (pValue, MI_UINT64A);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_SINT64A
    pValue = new MI_Value;
    pValue->sint64a.data = new MI_Sint64[3];
    pValue->sint64a.size = 3;
    MI_Delete (pValue, MI_SINT64A);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_REAL32A
    pValue = new MI_Value;
    pValue->real32a.data = new MI_Real32[3];
    pValue->real32a.size = 3;
    MI_Delete (pValue, MI_REAL32A);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_REAL64A
    pValue = new MI_Value;
    pValue->real64a.data = new MI_Real64[3];
    pValue->real64a.size = 3;
    MI_Delete (pValue, MI_REAL64A);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_CHAR16A
    pValue = new MI_Value;
    pValue->char16a.data = new MI_Char16[3];
    pValue->char16a.size = 3;
    MI_Delete (pValue, MI_CHAR16A);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_DATETIMEA:
    pValue = new MI_Value;
    pValue->datetimea.data = new MI_Datetime[3];
    pValue->datetimea.size = 3;
    MI_Delete (pValue, MI_DATETIMEA);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    // MI_STRINGA:
    pValue = new MI_Value;
    pValue->stringa.data = new MI_Char*[3];
    pValue->stringa.size = 3;
    for (size_t i = 0; i < 3; ++i)
    {
        pValue->stringa.data[i] =
            strcpy (new MI_Char[strlen (TEST_STRING) + 1], TEST_STRING);
    }
    MI_Delete (pValue, MI_STRINGA);
    if (NULL != pValue)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_memory_helper_test::test31 ()
{
    // test MI_Deleter
    int rval = EXIT_SUCCESS;
    MI_Deleter<MI_QualifierDecl> qualifierDeclDeleter;
    MI_QualifierDecl* pQualifierDecl = new MI_QualifierDecl;
    init_qualifier_decl ("qualifier_decl", true, pQualifierDecl);
    qualifierDeclDeleter (pQualifierDecl);
    if (NULL != pQualifierDecl)
    {
        rval = EXIT_FAILURE;
    }
    MI_Deleter<MI_Qualifier> qualifierDeleter;
    MI_Qualifier* pQualifier = new MI_Qualifier;
    init_qualifier ("qualifier", true, pQualifier);
    qualifierDeleter (pQualifier);
    if (NULL != pQualifier)
    {
        rval = EXIT_FAILURE;
    }
    MI_Deleter<MI_ParameterDecl> parameterDeclDeleter;
    MI_ParameterDecl* pParameterDecl = new MI_ParameterDecl;
    init_parameter_decl ("parameter_decl", 3, true, pParameterDecl);
    parameterDeclDeleter (pParameterDecl);
    if (NULL != pParameterDecl)
    {
        rval = EXIT_FAILURE;
    }
    MI_Deleter<MI_PropertyDecl> propertyDeclDeleter;
    MI_PropertyDecl* pPropertyDecl = new MI_PropertyDecl;
    init_property_decl ("property_decl", 3, true, pPropertyDecl);
    propertyDeclDeleter (pPropertyDecl);
    if (NULL != pPropertyDecl)
    {
        rval = EXIT_FAILURE;
    }
    MI_Deleter<MI_MethodDecl> methodDeclDeleter;
    MI_MethodDecl* pMethodDecl = new MI_MethodDecl;
    init_method_decl ("method_decl", 3, 3, true, pMethodDecl);
    methodDeclDeleter (pMethodDecl);
    if (NULL != pMethodDecl)
    {
        rval = EXIT_FAILURE;
    }
    MI_Deleter<MI_ClassDeclEx> classDeclDeleter;
    MI_ClassDeclEx* pClassDecl = new MI_ClassDeclEx;
    init_class_decl ("class_decl", 3, 3, 3, true, pClassDecl);
    classDeclDeleter (pClassDecl);
    if (NULL != pClassDecl)
    {
        rval = EXIT_FAILURE;
    }
    MI_Deleter<MI_SchemaDecl> schemaDeclDeleter;
    MI_SchemaDecl* pSchemaDecl = new MI_SchemaDecl;
    init_schema_decl (3, 3, pSchemaDecl);
    schemaDeclDeleter (pSchemaDecl);
    if (NULL != pSchemaDecl)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}
