/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

#include <vector>
#include <set>
#include <cstdlib>
#include <iostream>
#include <ut/ut.h>
#include <xml/xml.h>
#include <pal/strings.h>
#include <base/helpers.h>
#include <base/class.h>
#include <base/instance.h>
#include <xmlserializer/xmlserializer.h>
#include <xmlserializer/xmldeserializer.h>
#include <pal/dir.h>

using namespace std;

#define FULL_RTTI_SERIALIZATION_FLAGS (MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | \
        MI_SERIALIZER_FLAGS_INCLUDE_INHERITANCE_HIERARCHY | \
        MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS)

#define STANDARD_RTTI_SERIALIZATION_FLAGS (FULL_RTTI_SERIALIZATION_FLAGS | \
                        MI_SERIALIZER_FLAGS_INCLUDE_INHERITED_ELEMENTS)

MI_EXTERN_C MI_SchemaDecl schemaDecl;

MI_Uint8 serializedBuffer[10000] = {0};

typedef struct _ValidationError
{
    const MI_Char *XML;
    MI_Result result;
} ValidationError;

typedef struct _ValidationData
{
    const MI_Char *XML;
    MI_Type type;
    const MI_Char *value;
} ValidationData;

typedef struct _ValidationDataArray
{
    const MI_Char *XML;
    MI_Type type;
    const MI_Char *value[2];
} ValidationDataArray;

_Check_return_ static MI_Result _StringToMiValue(
    _In_z_ const MI_Char *str, 
    MI_Type type, 
    _Out_ MI_Value *value)
{
    MI_Result result = MI_RESULT_OK;

    if (type == MI_CHAR16)
    {
        if (str[0])
        {
            value->char16 = str[0];
        }
        else
            result = MI_RESULT_INVALID_PARAMETER;
    }
    else
    {
        result = StringToMiValue(str, type, value);
    }

    return result;
}

MI_Boolean CompareMiValue(MI_Value *resultValue, MI_Type resultType, const MI_Char *stringValue, NitsCallSite callsite)
{
    MI_Value compareValue = {0};

    if (NitsCompareEx(_StringToMiValue(stringValue, resultType, &compareValue), MI_RESULT_OK, PAL_T("Failed to convert comparison string to MI_Value"), callsite, NitsAutomatic))
    {
        switch(resultType)
        {
        case MI_BOOLEAN:
            return compareValue.boolean == resultValue->boolean;
            break;
        case MI_UINT8:
            return compareValue.uint8 == resultValue->uint8;
            break;
        case MI_SINT8:
            return compareValue.sint8 == resultValue->sint8;
            break;
        case MI_UINT16:
            return compareValue.uint16 == resultValue->uint16;
            break;
        case MI_SINT16:
            return compareValue.sint16 == resultValue->sint16;
            break;
        case MI_UINT32:
            return compareValue.uint32 == resultValue->uint32;
            break;
        case MI_SINT32:
            return compareValue.sint32 == resultValue->sint32;
            break;
        case MI_UINT64:
            return compareValue.uint64 == resultValue->uint64;
            break;
        case MI_SINT64:
            return compareValue.sint64 == resultValue->sint64;
            break;
        case MI_REAL32:
            return compareValue.real32 == resultValue->real32;
            break;
        case MI_REAL64:
            return compareValue.real64 == resultValue->real64;
            break;
        case MI_CHAR16:
            return compareValue.char16 == resultValue->char16;
            break;
        case MI_DATETIME:
            return memcmp(&compareValue.datetime, &resultValue->datetime, sizeof(resultValue->datetime))==0;
            break;
        case MI_STRING:
            return Tcscmp(compareValue.string, resultValue->string)==0;
            break;
        case MI_REFERENCE:
        case MI_INSTANCE:
        case MI_BOOLEANA:
        case MI_UINT8A:
        case MI_SINT8A:
        case MI_UINT16A:
        case MI_SINT16A:
        case MI_UINT32A:
        case MI_SINT32A:
        case MI_UINT64A:
        case MI_SINT64A:
        case MI_REAL32A:
        case MI_REAL64A:
        case MI_CHAR16A:
        case MI_DATETIMEA:
        case MI_STRINGA:
        case MI_REFERENCEA:
        case MI_INSTANCEA:
        default:
            return FALSE;
        }
    }
    return FALSE;
}

MI_Boolean CompareMiValueArray(MI_Value *resultValue, MI_Type resultType, _In_reads_z_(stringValueArrayLength) const MI_Char **stringValueArray, MI_Uint32 stringValueArrayLength, NitsCallSite callsite)
{
    MI_Value compareValue = {0};
    for (MI_Uint32 i = 0; i != stringValueArrayLength; i++)
    {
        if (NitsCompareEx(_StringToMiValue(stringValueArray[i], (MI_Type)(resultType&~MI_ARRAY), &compareValue), MI_RESULT_OK, PAL_T("Failed to convert comparison string to MI_Value"), callsite, NitsAutomatic))
        {
            switch(resultType)
            {
            case MI_BOOLEANA:
                return compareValue.boolean == resultValue->booleana.data[i];
                break;
            case MI_UINT8A:
                return compareValue.uint8 == resultValue->uint8a.data[i];
                break;
            case MI_SINT8A:
                return compareValue.sint8 == resultValue->sint8a.data[i];
                break;
            case MI_UINT16A:
                return compareValue.uint16 == resultValue->uint16a.data[i];
                break;
            case MI_SINT16A:
                return compareValue.sint16 == resultValue->sint16a.data[i];
                break;
            case MI_UINT32A:
                return compareValue.uint32 == resultValue->uint32a.data[i];
                break;
            case MI_SINT32A:
                return compareValue.sint32 == resultValue->sint32a.data[i];
                break;
            case MI_UINT64A:
                return compareValue.uint64 == resultValue->uint64a.data[i];
                break;
            case MI_SINT64A:
                return compareValue.sint64 == resultValue->sint64a.data[i];
                break;
            case MI_REAL32A:
                return compareValue.real32 == resultValue->real32a.data[i];
                break;
            case MI_REAL64A:
                return compareValue.real64 == resultValue->real64a.data[i];
                break;
            case MI_CHAR16A:
                return compareValue.char16 == resultValue->char16a.data[i];
                break;
            case MI_DATETIMEA:
                return memcmp(&compareValue.datetime, &resultValue->datetimea.data[i], sizeof(resultValue->datetimea.data[i]))==0;
                break;
            case MI_STRINGA:
                return Tcscmp(compareValue.string, resultValue->stringa.data[i])==0;
                break;
            case MI_REFERENCEA:
            case MI_INSTANCEA:
            case MI_BOOLEAN:
            case MI_UINT8:
            case MI_SINT8:
            case MI_UINT16:
            case MI_SINT16:
            case MI_UINT32:
            case MI_SINT32:
            case MI_UINT64:
            case MI_SINT64:
            case MI_REAL32:
            case MI_REAL64:
            case MI_CHAR16:
            case MI_DATETIME:
            case MI_STRING:
            case MI_REFERENCE:
            case MI_INSTANCE:
            default:
                return FALSE;
            }
        }
    }
    return FALSE;
}

static const MI_ClassDecl *GetSerializerTestClassDecl(const MI_Char *className)
{
    if(className == NULL)
        return NULL;

    MI_Uint32 count = 0;
    for(count = 0; count < schemaDecl.numClassDecls; count++)
    {
        if(Tcscmp(className, schemaDecl.classDecls[count]->name) == 0)
            return schemaDecl.classDecls[count];
    }

    return NULL;
}

static void SerializerTestCompare(const MI_Uint8 *actual, const MI_Char *expected, NitsCallSite testLine)
{
    size_t lengthOfExpected = Tcslen(expected);

    NitsTraceEx((PAL_T("Comparing between expected and actual serialization strings:-")), testLine, NitsAutomatic);
    NitsTraceEx(expected, testLine, NitsAutomatic);
    NitsTraceEx((MI_Char *)actual, testLine, NitsAutomatic);
    NitsAssertEx(Tcsncmp((MI_Char *)actual, expected, lengthOfExpected) == 0, PAL_T("failed comparison"), testLine, NitsAutomatic);
}

static void TestClassSerialization(const MI_Char *className, const MI_Char *expectedSerialization,
                NitsCallSite testLine, MI_Uint32 flags)
{
    MI_Result result = MI_RESULT_OK;

    MI_Application miApplication = MI_APPLICATION_NULL;
    MI_Serializer miSerializer;
    MI_Uint32 bufferLenForSerialization = 0;
    MI_Class classObject;
    const MI_ClassDecl *testClassDecl;

    result = XmlSerializer_Create(
                &miApplication,
                0, (MI_Char *)(PAL_T("MI_XML")),
                &miSerializer);
    NitsAssertEx(MI_RESULT_OK == result, PAL_T("failed creating serializer"), testLine, NitsAutomatic);

    testClassDecl = GetSerializerTestClassDecl(className);
    if(!NitsAssertEx(testClassDecl != NULL, PAL_T("Class not found"), testLine, NitsAutomatic))
        return;

    Class_Construct(&classObject, testClassDecl);

    XmlSerializer_SerializeClassEx(&miSerializer,
                                    flags,
                                    &classObject,
                                    NULL,
                                    0,
                                    &bufferLenForSerialization);

    MI_Uint8 *neededBuffer = (MI_Uint8 *)malloc((bufferLenForSerialization + sizeof(MI_Char)));
    if(!NitsAssertEx(neededBuffer != NULL, PAL_T("Memory allocation failed"), testLine, NitsAutomatic))
        return;

    result = XmlSerializer_SerializeClassEx(&miSerializer,
                                        flags,
                                        &classObject,
                                        neededBuffer,
                                        bufferLenForSerialization,
                                        &bufferLenForSerialization);

    if(!NitsAssertEx(MI_RESULT_OK == result, PAL_T("failed to serialize class"), testLine, NitsAutomatic))
        return;

    if(neededBuffer)
    {
        ((MI_Char *)(neededBuffer))[(bufferLenForSerialization/sizeof(MI_Char))] = PAL_T('\0');
    }

    SerializerTestCompare(neededBuffer, expectedSerialization, testLine);

    free(neededBuffer);

    result = XmlSerializer_Close(&miSerializer);

    NitsAssertEx(MI_RESULT_OK == result, PAL_T("failed to close serializer"), testLine, NitsAutomatic);
}

static void TestStandardRttiSerialization(const MI_Char *className, const MI_Char *expectedSerialization,
                NitsCallSite testLine)
{
    NitsTraceEx(PAL_T("Doing standard rtti serialization for "), testLine, NitsAutomatic);
    NitsTraceEx(className, testLine, NitsAutomatic);
    TestClassSerialization(className, expectedSerialization, testLine, STANDARD_RTTI_SERIALIZATION_FLAGS);
}

static void TestFullRttiSerialization(const MI_Char *className, const MI_Char *expectedSerialization,
                NitsCallSite testLine)
{
    NitsTraceEx(PAL_T("Doing full rtti serialization for "), testLine, NitsAutomatic);
    NitsTraceEx(className, testLine, NitsAutomatic);
    TestClassSerialization(className, expectedSerialization, testLine, FULL_RTTI_SERIALIZATION_FLAGS);
}

NitsTest(Xml_CreateDelete)
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if (NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer")))
        {
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        if (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer")))
        {
            NitsCompare(XmlSerializer_Close(&serializer), MI_RESULT_OK, PAL_T("Close serializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_CreateDelete_InvalidParameters)
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        NitsCompare(XmlDeserializer_Create(NULL, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_INVALID_PARAMETER, PAL_T("Invalid parameter test"));
        NitsCompare(XmlDeserializer_Create(&application, 99, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_INVALID_PARAMETER, PAL_T("Invalid parameter test"));
        NitsCompare(XmlDeserializer_Create(&application, 0, NULL, &deserializer), MI_RESULT_INVALID_PARAMETER, PAL_T("Invalid parameter test"));
        NitsCompare(XmlDeserializer_Create(&application, 0,  (MI_Char *)PAL_T("MI_XML"), NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("Invalid parameter test"));
        NitsCompare(XmlDeserializer_Create(&application, 0,  (MI_Char *)PAL_T("jfdkjhafhs"), &deserializer), MI_RESULT_NOT_SUPPORTED, PAL_T("Invalid parameter test"));

        NitsCompare(XmlSerializer_Create(NULL, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_INVALID_PARAMETER, PAL_T("Invalid parameter test"));
        NitsCompare(XmlSerializer_Create(&application, 99, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_INVALID_PARAMETER, PAL_T("Invalid parameter test"));
        NitsCompare(XmlSerializer_Create(&application, 0, NULL, &serializer), MI_RESULT_INVALID_PARAMETER, PAL_T("Invalid parameter test"));
        NitsCompare(XmlSerializer_Create(&application, 0,  (MI_Char *)PAL_T("MI_XML"), NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("Invalid parameter test"));
        NitsCompare(XmlSerializer_Create(&application, 0,  (MI_Char *)PAL_T("jfdkjhafhs"), &serializer), MI_RESULT_NOT_SUPPORTED, PAL_T("Invalid parameter test"));

        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Superclass)
    const MI_Char *baseClass = PAL_T("<CLASS NAME=\"superclass\"></CLASS>");
    const MI_Char *derivedClass = PAL_T("<CLASS NAME=\"myClass\" SUPERCLASS=\"superclass\"></CLASS>");
    MI_Application application = MI_APPLICATION_NULL;

    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            MI_Class *superclass = NULL;
            MI_Uint32 deserializeSize;
            if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)baseClass, Tcslen(baseClass)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &superclass, NULL), MI_RESULT_OK, PAL_T("successfully deserialize")))
            {
                MI_Class *newClass = NULL;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)derivedClass, Tcslen(derivedClass)*(sizeof(MI_Char)), superclass, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, PAL_T("successfully deserialize")))
                {
                    MI_Uint32 bufferUsed = 0;
                    if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                    {
                        SerializerTestCompare(serializedBuffer, derivedClass, NitsHere());
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }

                NitsCompare(MI_Class_Delete(superclass), MI_RESULT_OK, PAL_T("close class"));
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Superclass_Flat)
    //TODO: DERIVATION
    const MI_Char *derivedClass = PAL_T("<CLASS NAME=\"myClass\" SUPERCLASS=\"superclass\"></CLASS>");
    const MI_Char *serializedClass = PAL_T("<CLASS NAME=\"myClass\"></CLASS>");
    MI_Application application = MI_APPLICATION_NULL;

    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            MI_Uint32 deserializeSize;
            MI_Class *newClass = NULL;
            if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)derivedClass, Tcslen(derivedClass)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, PAL_T("successfully deserialize")))
            {
                MI_Uint32 bufferUsed = 0;
                if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                {
                    //Note that resultant class is different from original as we don't have enough information to deserialize the original accurately
                    SerializerTestCompare(serializedBuffer, serializedClass, NitsHere());
                }
                NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Superclass_DERIVATION)
    const MI_Char *derivedClass = PAL_T("<CLASS NAME=\"myClass\" SUPERCLASS=\"superclass\" DERIVATION=\"superclass,parentclass\"></CLASS>");
    const MI_Char *serializedClass = PAL_T("<CLASS NAME=\"myClass\" SUPERCLASS=\"superclass\"></CLASS>");
    MI_Application application = MI_APPLICATION_NULL;

    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            MI_Uint32 deserializeSize;
            MI_Class *newClass = NULL;
            if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)derivedClass, Tcslen(derivedClass)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, PAL_T("successfully deserialize")))
            {
                MI_Uint32 bufferUsed = 0;
                if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                {
                    //Note that resultant class is different from original as we don't have enough information to deserialize the original accurately
                    SerializerTestCompare(serializedBuffer, serializedClass, NitsHere());
                }
                NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Quals_Simple_Validate)
    ValidationData testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\"><VALUE>true</VALUE></QUALIFIER></CLASS>"),MI_BOOLEAN,PAL_T("true")},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"string\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER></CLASS>"),MI_STRING,PAL_T("hello&'><\"")},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"char16\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\"><VALUE>&#16;</VALUE></QUALIFIER></CLASS>"),MI_CHAR16,PAL_T("\x10")},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint8\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\"><VALUE>10</VALUE></QUALIFIER></CLASS>"),MI_UINT8,PAL_T("10")},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint8\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\"><VALUE>1</VALUE></QUALIFIER></CLASS>"),MI_SINT8,PAL_T("1")},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint16\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\"><VALUE>20</VALUE></QUALIFIER></CLASS>"),MI_UINT16,PAL_T("20")},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint16\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\"><VALUE>-2</VALUE></QUALIFIER></CLASS>"),MI_SINT16,PAL_T("-2")},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint32\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\"><VALUE>3</VALUE></QUALIFIER></CLASS>"),MI_UINT32,PAL_T("3")},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint32\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\"><VALUE>-3</VALUE></QUALIFIER></CLASS>"),MI_SINT32,PAL_T("-3")},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint64\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\"><VALUE>4</VALUE></QUALIFIER></CLASS>"),MI_UINT64,PAL_T("4")},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint64\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\"><VALUE>-4</VALUE></QUALIFIER></CLASS>"),MI_SINT64,PAL_T("-4")},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"datetime\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\"><VALUE>20110314222412.000000+008</VALUE></QUALIFIER></CLASS>"),MI_DATETIME,PAL_T("20110314222412.000000+008")},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real32\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\"><VALUE>1.1000000e+00</VALUE></QUALIFIER></CLASS>"),MI_REAL32,PAL_T("1.1")},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real64\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\"><VALUE>2.2000000000000002e+00</VALUE></QUALIFIER></CLASS>"),MI_REAL64,PAL_T("2.2")}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_QualifierSet qs;
                    MI_Uint32 qsCount;

                    if (NitsCompare(MI_Class_GetClassQualifierSet(newClass, &qs), MI_RESULT_OK, PAL_T("Get class qualifier set")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count")) &&
                        NitsCompare(qsCount, 1, PAL_T("qualifier count should be 1")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, &resultName, &resultType, &resultFlags, &resultValue), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("qual1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type, PAL_T("Qualifier type")) &&
                        NitsCompare(resultFlags, MI_FLAG_TRANSLATABLE|MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, PAL_T("QualifierSet flags")) &&
                        NitsCompare(CompareMiValue(&resultValue, resultType, testData[i].value, NitsHere()), MI_TRUE, testData[i].XML))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Quals_Invalid)
    ValidationError testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER TYPE=\"boolean\" TOSUBCLASS=\"true\" TRANSLATABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></CLASS>"),MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TOSUBCLASS=\"true\" TRANSLATABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></CLASS>"),MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"invalid\" TOSUBCLASS=\"true\" TRANSLATABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></CLASS>"),MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\" TOSUBCLASS=\"invalid\" TRANSLATABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></CLASS>"),MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\" TOSUBCLASS=\"true\" TRANSLATABLE=\"invalid\"><VALUE>true</VALUE></QUALIFIER></CLASS>"),MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" NAME=\"qual1\" TYPE=\"boolean\" TOSUBCLASS=\"true\" TRANSLATABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></CLASS>"),MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\" TYPE=\"boolean\" TOSUBCLASS=\"true\" TRANSLATABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></CLASS>"),MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\" TOSUBCLASS=\"true\" TRANSLATABLE=\"false\"><VALUE>invalid</VALUE></QUALIFIER></CLASS>"),MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\" TOSUBCLASS=\"true\" TRANSLATABLE=\"false\"></QUALIFIER></CLASS>"),MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\" TOSUBCLASS=\"true\" TRANSLATABLE=\"false\"><a/></QUALIFIER></CLASS>"),MI_RESULT_INVALID_PARAMETER}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;

        if (NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer")))
        {
            MI_Class *newClass = NULL;
            MI_Uint32 index;
            for (index = 0; index != sizeof(testData)/sizeof(testData[0]);index++)
            {
                MI_Uint32 deserializeSize;
                NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[index].XML, Tcslen(testData[index].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), testData[index].result, PAL_T("invalid class qualifiers"));
            }

            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Quals_Array_Validate)
    ValidationDataArray testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),MI_BOOLEAN,{PAL_T("true"), PAL_T("false")}},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"string\"><VALUE.ARRAY><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE><VALUE>goodbye</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),MI_STRING,{PAL_T("hello&'><\""), PAL_T("goodbye")}},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"char16\"><VALUE.ARRAY><VALUE>&#8;</VALUE><VALUE>&#16;</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),MI_CHAR16,{PAL_T("\x8"), PAL_T("\x10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint8\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>10</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),MI_UINT8,{PAL_T("1"), PAL_T("10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint8\"><VALUE.ARRAY><VALUE>-1</VALUE><VALUE>1</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),MI_SINT8,{PAL_T("-1"), PAL_T("1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint16\"><VALUE.ARRAY><VALUE>2</VALUE><VALUE>20</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),MI_UINT16,{PAL_T("2"), PAL_T("20")}},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint16\"><VALUE.ARRAY><VALUE>-2</VALUE><VALUE>2</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),MI_SINT16,{PAL_T("-2"), PAL_T("2")}},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint32\"><VALUE.ARRAY><VALUE>3</VALUE><VALUE>30</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),MI_UINT32,{PAL_T("3"), PAL_T("30")}},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint32\"><VALUE.ARRAY><VALUE>-3</VALUE><VALUE>3</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),MI_SINT32,{PAL_T("-3"), PAL_T("3")}},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint64\"><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),MI_UINT64,{PAL_T("4"), PAL_T("40")}},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint64\"><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),MI_SINT64,{PAL_T("-4"), PAL_T("4")}},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"datetime\"><VALUE.ARRAY><VALUE>20110314222412.000000+008</VALUE><VALUE>20110314222412.000000+008</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),MI_DATETIME,{PAL_T("20110314222412.000000+008"), PAL_T("20110314222412.000000+008")}},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real32\"><VALUE.ARRAY><VALUE>1.1000000e+00</VALUE><VALUE>-1.1000000e+00</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),MI_REAL32,{PAL_T("1.1"), PAL_T("-1.1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real64\"><VALUE.ARRAY><VALUE>2.2000000000000002e+00</VALUE><VALUE>-2.2000000000000002e+00</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),MI_REAL64,{PAL_T("2.2"), PAL_T("-2.2")}}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_QualifierSet qs;
                    MI_Uint32 qsCount;

                    if (NitsCompare(MI_Class_GetClassQualifierSet(newClass, &qs), MI_RESULT_OK, PAL_T("Get class qualifier set")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count")) &&
                        NitsCompare(qsCount, 1, PAL_T("qualifier count should be 1")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, &resultName, &resultType, &resultFlags, &resultValue), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("qual1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type|MI_ARRAY, PAL_T("Qualifier type")) &&
                        NitsCompare(resultFlags, MI_FLAG_TOSUBCLASS|MI_FLAG_ENABLEOVERRIDE, PAL_T("QualifierSet flags")) &&
                        CompareMiValueArray(&resultValue, resultType, testData[i].value, 2, NitsHere()))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Prop_None)
    const MI_Char *emptyClass = PAL_T("<CLASS NAME=\"myClass\"></CLASS>");
    MI_Application application = MI_APPLICATION_NULL;

    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            MI_Class *newClass = NULL;
            const MI_Char *className = NULL;
            MI_Uint32 deserializeSize;

            if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)emptyClass, Tcslen(emptyClass)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, PAL_T("successfully deserialize")) &&
                NitsCompare(MI_Class_GetClassName(newClass, &className), MI_RESULT_OK, PAL_T("Get class")) &&
                NitsCompareString(className, PAL_T("myClass"), PAL_T("classname should match")) &&
                NitsCompare(MI_Class_GetParentClassName(newClass, &className), MI_RESULT_INVALID_SUPERCLASS, PAL_T("no superclass")))
            {
                MI_Uint32 bufferUsed = 0;
                if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                {
                    SerializerTestCompare(serializedBuffer, emptyClass, NitsHere());
                }
                NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest


NitsTest(Xml_Class_Prop_None_InvalidParameters)
    const MI_Char *emptyClass = PAL_T("<CLASS NAME=\"myClass\"></CLASS>");
    ValidationError testData[] =
    {
        {PAL_T("<Instance NAME=\"myClass\"></Instance>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("invalid XML"), MI_RESULT_FAILED},
        {PAL_T("<CLASS></CLASS>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\" wrong=\"wrong\"></CLASS>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\" NAME=\"myClass\"></CLASS>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\" SUPERCLASS=\"myClass\" SUPERCLASS=\"myClass\"></CLASS>"), MI_RESULT_INVALID_PARAMETER}
    };
    MI_Uint32 index;
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;

        if (NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer")))
        {
            MI_Class *newClass = NULL;
            MI_Uint32 deserializeSize;

            NitsCompare(XmlDeserializer_DeserializeClass(NULL, 0, (MI_Uint8*)emptyClass, Tcslen(emptyClass)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("Invalid parameter test"));
            NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 999, (MI_Uint8*)emptyClass, Tcslen(emptyClass)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("Invalid parameter test"));
            NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, NULL, Tcslen(emptyClass)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("Invalid parameter test"));
            NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)emptyClass, Tcslen(emptyClass)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, NULL, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("Invalid parameter test"));

            for (index = 0; index != sizeof(testData)/sizeof(testData[0]); index++)
            {
                NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[index].XML, Tcslen(testData[index].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), testData[index].result, PAL_T("invalid XML tests"));
            }

            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Prop_Simple_Validate)
    const ValidationData testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><VALUE>true</VALUE></PROPERTY></CLASS>"), MI_BOOLEAN, PAL_T("true")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></PROPERTY></CLASS>"), MI_STRING, PAL_T("hello&'><\"")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"><VALUE>&#8;</VALUE></PROPERTY></CLASS>"), MI_CHAR16, PAL_T("\x8")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"><VALUE>1</VALUE></PROPERTY></CLASS>"), MI_UINT8, PAL_T("1")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"><VALUE>-1</VALUE></PROPERTY></CLASS>"), MI_SINT8, PAL_T("-1")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"><VALUE>2</VALUE></PROPERTY></CLASS>"), MI_UINT16, PAL_T("2")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"><VALUE>-2</VALUE></PROPERTY></CLASS>"), MI_SINT16, PAL_T("-2")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"><VALUE>3</VALUE></PROPERTY></CLASS>"), MI_UINT32, PAL_T("3")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"><VALUE>-3</VALUE></PROPERTY></CLASS>"), MI_SINT32, PAL_T("-3")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"><VALUE>4</VALUE></PROPERTY></CLASS>"),  MI_UINT64, PAL_T("4")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"><VALUE>-4</VALUE></PROPERTY></CLASS>"), MI_SINT64, PAL_T("-4")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"><VALUE>20110314222412.000000+008</VALUE></PROPERTY></CLASS>"), MI_DATETIME, PAL_T("20110314222412.000000+008")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"><VALUE>1.1000000e+00</VALUE></PROPERTY></CLASS>"), MI_REAL32, PAL_T("1.1")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"><VALUE>2.2000000000000002e+00</VALUE></PROPERTY></CLASS>"), MI_REAL64, PAL_T("2.2")}
    };

    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;

                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_Boolean resultExists;
                    MI_QualifierSet qs;

                    if (NitsCompare(MI_Class_GetElementAt(newClass, 0, &resultName, &resultValue, &resultExists, &resultType, NULL, &qs, &resultFlags), MI_RESULT_OK, PAL_T("Get property value should work")) &&
                        NitsCompare(Tcscmp(resultName, PAL_T("prop1")), 0, PAL_T("propertyName should be prop1")) &&
                        NitsCompare(resultType, testData[i].type, PAL_T("Types should match")) &&
                        NitsCompare(resultFlags, MI_FLAG_PROPERTY, PAL_T("Flags should be MI_FLAG_PROPERTY")))
                    {
                        if (NitsCompare(CompareMiValue(&resultValue, resultType, testData[i].value, NitsHere()), MI_TRUE, testData[i].XML))
                        {
                            MI_Uint32 bufferUsed = 0;
                            if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                            {
                                SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                            }
                        }
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Prop_Simple_Validate_DERIVATION)
    const ValidationData testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"baseClass\"><VALUE>true</VALUE></PROPERTY></CLASS>"), MI_BOOLEAN, PAL_T("true")},
        {PAL_T("<CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><VALUE>true</VALUE></PROPERTY></CLASS>"), MI_BOOLEAN, PAL_T("true")},
        {PAL_T("<CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></CLASS>"), MI_BOOLEAN, PAL_T("true")},
        {PAL_T("<CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\" DERIVATION=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"baseClass\"><VALUE>true</VALUE></PROPERTY></CLASS>"), MI_BOOLEAN, PAL_T("true")},
        {PAL_T("<CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\" DERIVATION=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><VALUE>true</VALUE></PROPERTY></CLASS>"), MI_BOOLEAN, PAL_T("true")},
        {PAL_T("<CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\" DERIVATION=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></CLASS>"), MI_BOOLEAN, PAL_T("true")},
    };

    const MI_Char *propertyClass[] = 
    {
        PAL_T("baseClass"),
        PAL_T("myClass"),
        PAL_T("myClass"),
        PAL_T("baseClass"),
        PAL_T("myClass"),
        PAL_T("myClass")
    };

    const MI_Char *expectedSerializedString[] =
    {
        PAL_T("<CLASS NAME=\"myClass\"></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><VALUE>true</VALUE></PROPERTY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><VALUE>true</VALUE></PROPERTY></CLASS>"), 
        PAL_T("<CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><VALUE>true</VALUE></PROPERTY></CLASS>"), 
        PAL_T("<CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><VALUE>true</VALUE></PROPERTY></CLASS>")
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;

                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_Boolean resultExists;
                    MI_QualifierSet qs;

                    if (NitsCompare(MI_Class_GetElementAt(newClass, 0, &resultName, &resultValue, &resultExists, &resultType, NULL, &qs, &resultFlags), MI_RESULT_OK, PAL_T("Get property value should work")) &&
                        NitsCompare(Tcscmp(resultName, PAL_T("prop1")), 0, PAL_T("propertyName should be prop1")) &&
                        NitsCompare(resultType, testData[i].type, PAL_T("Types should match")) &&
                        NitsCompare(resultFlags, MI_FLAG_PROPERTY, PAL_T("Flags should be MI_FLAG_PROPERTY")),
                        NitsCompareString(propertyClass[i], newClass->classDecl->properties[0]->origin, PAL_T("property origin")))
                    {
                        if (NitsCompare(CompareMiValue(&resultValue, resultType, testData[i].value, NitsHere()), MI_TRUE, testData[i].XML))
                        {
                            MI_Uint32 bufferUsed = 0;
                            if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                            {
                                SerializerTestCompare(serializedBuffer, expectedSerializedString[i], NitsHere());
                            }
                        }
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest


NitsTest(Xml_Class_Prop_Simple_Invalid)
    ValidationError testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY TYPE=\"boolean\" PROPAGATED=\"boo\" CLASSORIGIN=\"goo\"><VALUE>true</VALUE></PROPERTY></CLASS>"), MI_RESULT_INVALID_PARAMETER},
        { PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" PROPAGATED=\"boo\" CLASSORIGIN=\"goo\"><VALUE>true</VALUE></PROPERTY></CLASS>"), MI_RESULT_INVALID_PARAMETER},
        { PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"goo\" PROPAGATED=\"boo\" CLASSORIGIN=\"goo\"><VALUE>true</VALUE></PROPERTY></CLASS>"), MI_RESULT_INVALID_PARAMETER},
        { PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" NAME=\"prop1\" TYPE=\"boolean\" PROPAGATED=\"boo\" CLASSORIGIN=\"goo\"><VALUE>true</VALUE></PROPERTY></CLASS>"), MI_RESULT_INVALID_PARAMETER},
        { PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" TYPE=\"boolean\"  PROPAGATED=\"boo\" CLASSORIGIN=\"goo\"><VALUE>true</VALUE></PROPERTY></CLASS>"), MI_RESULT_INVALID_PARAMETER},
        { PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" PROPAGATED=\"boo\" CLASSORIGIN=\"goo\"><VALUE>goo</VALUE></PROPERTY></CLASS>"), MI_RESULT_INVALID_PARAMETER},
        { PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" PROPAGATED=\"boo\" CLASSORIGIN=\"goo\"><goo>true</goo></PROPERTY></CLASS>"), MI_RESULT_INVALID_PARAMETER}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;

        if (NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer")))
        {
            MI_Class *newClass = NULL;
            MI_Uint32 index;
            for (index = 0; index != sizeof(testData)/sizeof(testData[0]);index++)
            {
                MI_Uint32 deserializeSize;
                NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[index].XML, Tcslen(testData[index].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), testData[index].result, PAL_T("invalid parameters"));
            }

            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Prop_Simple_Quals_Simple_Validate)
    ValidationData testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><VALUE>true</VALUE></PROPERTY></CLASS>"),MI_BOOLEAN,PAL_T("true")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"string\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></PROPERTY></CLASS>"),MI_STRING,PAL_T("hello&'><\"")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"char16\"><VALUE>&#8;</VALUE></QUALIFIER><VALUE>&#8;</VALUE></PROPERTY></CLASS>"),MI_CHAR16, PAL_T("\x8")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint8\"><VALUE>1</VALUE></QUALIFIER><VALUE>1</VALUE></PROPERTY></CLASS>"),MI_UINT8,PAL_T("1")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint8\"><VALUE>-1</VALUE></QUALIFIER><VALUE>-1</VALUE></PROPERTY></CLASS>"),MI_SINT8,PAL_T("-1")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint16\"><VALUE>2</VALUE></QUALIFIER><VALUE>2</VALUE></PROPERTY></CLASS>"),MI_UINT16,PAL_T("2")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint16\"><VALUE>-2</VALUE></QUALIFIER><VALUE>-2</VALUE></PROPERTY></CLASS>"),MI_SINT16,PAL_T("-2")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint32\"><VALUE>3</VALUE></QUALIFIER><VALUE>3</VALUE></PROPERTY></CLASS>"),MI_UINT32,PAL_T("3")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint32\"><VALUE>-3</VALUE></QUALIFIER><VALUE>-3</VALUE></PROPERTY></CLASS>"),MI_SINT32,PAL_T("-3"),},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint64\"><VALUE>4</VALUE></QUALIFIER><VALUE>4</VALUE></PROPERTY></CLASS>"),MI_UINT64,PAL_T("4")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint64\"><VALUE>-4</VALUE></QUALIFIER><VALUE>-4</VALUE></PROPERTY></CLASS>"),MI_SINT64,PAL_T("-4")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"datetime\"><VALUE>20110314222412.000000+008</VALUE></QUALIFIER><VALUE>20110314222412.000000+008</VALUE></PROPERTY></CLASS>"),MI_DATETIME,PAL_T("20110314222412.000000+008")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real32\"><VALUE>1.1000000e+00</VALUE></QUALIFIER><VALUE>1.1000000e+00</VALUE></PROPERTY></CLASS>"),MI_REAL32,PAL_T("1.1")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real64\"><VALUE>2.2000000000000002e+00</VALUE></QUALIFIER><VALUE>2.2000000000000002e+00</VALUE></PROPERTY></CLASS>"),MI_REAL64,PAL_T("2.2")}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;

                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_Boolean valueExists;
                    MI_QualifierSet qs;
                    MI_Uint32 qsCount;

                    if (NitsCompare(MI_Class_GetElementAt(newClass, 0, &resultName, &resultValue, &valueExists, &resultType, NULL, &qs, &resultFlags), MI_RESULT_OK, PAL_T("Get class qualifier set")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count")) &&
                        NitsCompare(qsCount, 1, PAL_T("qualifier count should be 1")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, &resultName, &resultType, &resultFlags, &resultValue), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("qual1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type, PAL_T("Qualifier type")) &&
                        NitsCompare(resultFlags, MI_FLAG_TOSUBCLASS|MI_FLAG_ENABLEOVERRIDE, PAL_T("QualifierSet flags")) &&
                        NitsCompare(CompareMiValue(&resultValue, resultType, testData[i].value, NitsHere()), MI_TRUE, testData[i].XML))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

   
NitsTest(Xml_Class_Prop_Simple_Quals_Array_Validate)
    ValidationDataArray testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>true</VALUE></PROPERTY></CLASS>"),MI_BOOLEAN,{PAL_T("true"), PAL_T("false")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"string\"><VALUE.ARRAY><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE><VALUE>goodbye</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></PROPERTY></CLASS>"),MI_STRING,{PAL_T("hello&'><\""), PAL_T("goodbye")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"char16\"><VALUE.ARRAY><VALUE>&#8;</VALUE><VALUE>&#16;</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>&#8;</VALUE></PROPERTY></CLASS>"),MI_CHAR16,{PAL_T("\x8"), PAL_T("\x10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint8\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>10</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>1</VALUE></PROPERTY></CLASS>"),MI_UINT8,{PAL_T("1"), PAL_T("10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint8\"><VALUE.ARRAY><VALUE>-1</VALUE><VALUE>1</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>-1</VALUE></PROPERTY></CLASS>"),MI_SINT8,{PAL_T("-1"), PAL_T("1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint16\"><VALUE.ARRAY><VALUE>2</VALUE><VALUE>20</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>2</VALUE></PROPERTY></CLASS>"),MI_UINT16,{PAL_T("2"), PAL_T("20")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint16\"><VALUE.ARRAY><VALUE>-2</VALUE><VALUE>2</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>-2</VALUE></PROPERTY></CLASS>"),MI_SINT16,{PAL_T("-2"), PAL_T("2")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint32\"><VALUE.ARRAY><VALUE>3</VALUE><VALUE>30</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>3</VALUE></PROPERTY></CLASS>"),MI_UINT32,{PAL_T("3"), PAL_T("30")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint32\"><VALUE.ARRAY><VALUE>-3</VALUE><VALUE>3</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>-3</VALUE></PROPERTY></CLASS>"),MI_SINT32,{PAL_T("-3"), PAL_T("3")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint64\"><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>4</VALUE></PROPERTY></CLASS>"),MI_UINT64,{PAL_T("4"), PAL_T("40")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint64\"><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>-4</VALUE></PROPERTY></CLASS>"),MI_SINT64,{PAL_T("-4"), PAL_T("4")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"datetime\"><VALUE.ARRAY><VALUE>20110314222412.000000+008</VALUE><VALUE>20110314222412.000000+008</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>20110314222412.000000+008</VALUE></PROPERTY></CLASS>"),MI_DATETIME,{PAL_T("20110314222412.000000+008"), PAL_T("20110314222412.000000+008")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real32\"><VALUE.ARRAY><VALUE>1.1000000e+00</VALUE><VALUE>-1.1000000e+00</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>1.1000000e+00</VALUE></PROPERTY></CLASS>"),MI_REAL32,{PAL_T("1.1"), PAL_T("-1.1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real64\"><VALUE.ARRAY><VALUE>2.2000000000000002e+00</VALUE><VALUE>-2.2000000000000002e+00</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>2.2000000000000002e+00</VALUE></PROPERTY></CLASS>"),MI_REAL64,{PAL_T("2.2"), PAL_T("-2.2")}}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;

                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_Boolean valueExists;
                    MI_QualifierSet qs;
                    MI_Uint32 qsCount;

                    if (NitsCompare(MI_Class_GetElementAt(newClass, 0, &resultName, &resultValue, &valueExists, &resultType, NULL, &qs, &resultFlags), MI_RESULT_OK, PAL_T("Get class qualifier set")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count")) &&
                        NitsCompare(qsCount, 1, PAL_T("qualifier count should be 1")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, &resultName, &resultType, &resultFlags, &resultValue), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("qual1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type|MI_ARRAY, PAL_T("Qualifier type")) &&
                        NitsCompare(resultFlags, MI_FLAG_TOSUBCLASS|MI_FLAG_ENABLEOVERRIDE, PAL_T("QualifierSet flags")) &&
                        CompareMiValueArray(&resultValue, resultType, testData[i].value, 2, NitsHere()))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest
    
NitsTest(Xml_Class_Prop_Array_Validate)
    ValidationDataArray testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_BOOLEAN,{PAL_T("true"), PAL_T("false")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE><VALUE>goodbye</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_STRING,{PAL_T("hello&'><\""), PAL_T("goodbye")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY><VALUE>&#8;</VALUE><VALUE>&#16;</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_CHAR16,{PAL_T("\x8"), PAL_T("\x10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>10</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT8,{PAL_T("1"), PAL_T("10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY><VALUE>-1</VALUE><VALUE>1</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT8,{PAL_T("-1"), PAL_T("1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY><VALUE>2</VALUE><VALUE>20</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT16,{PAL_T("2"), PAL_T("20")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY><VALUE>-2</VALUE><VALUE>2</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT16,{PAL_T("-2"), PAL_T("2")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY><VALUE>3</VALUE><VALUE>30</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT32,{PAL_T("3"), PAL_T("30")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY><VALUE>-3</VALUE><VALUE>3</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT32,{PAL_T("-3"), PAL_T("3")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT64,{PAL_T("4"), PAL_T("40")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT64,{PAL_T("-4"), PAL_T("4")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY><VALUE>20110314222412.000000+008</VALUE><VALUE>20110314222412.000000+008</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_DATETIME,{PAL_T("20110314222412.000000+008"), PAL_T("20110314222412.000000+008")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY><VALUE>1.1000000e+00</VALUE><VALUE>-1.1000000e+00</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_REAL32,{PAL_T("1.1"), PAL_T("-1.1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY><VALUE>2.2000000000000002e+00</VALUE><VALUE>-2.2000000000000002e+00</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_REAL64,{PAL_T("2.2"), PAL_T("-2.2")}}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_Boolean valueExists;
                    MI_QualifierSet qs;

                    if (NitsCompare(MI_Class_GetElementAt(newClass, 0, &resultName, &resultValue, &valueExists, &resultType, NULL, &qs, &resultFlags), MI_RESULT_OK, PAL_T("Get property value should work")) &&
                        resultName &&
                        NitsCompare(Tcscmp(resultName, PAL_T("prop1")), 0, PAL_T("propertyName should be prop1")) &&
                        NitsCompare(resultType, testData[i].type|MI_ARRAY, PAL_T("Types should match")) &&
                        NitsAssert(resultFlags & MI_FLAG_PROPERTY, PAL_T("Flags should be MI_FLAG_PROPERTY")) &&
                        NitsCompare(resultValue.booleana.size, 2, PAL_T("array size should be 2")))
                    {
                        if (CompareMiValueArray(&resultValue, resultType, testData[i].value, 2, NitsHere()))
                        {
                            MI_Uint32 bufferUsed = 0;
                            if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                            {
                                SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                            }
                        }
                    }


                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest
    
NitsTest(Xml_Class_Prop_Array_Invalid)
    const MI_Char *testData[] =
    {
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY TYPE=\"boolean\" ARRAYSIZE=\"2\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" NAME=\"prop1\" TYPE=\"boolean\" ARRAYSIZE=\"2\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" ARRAYSIZE=\"2\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\" TYPE=\"boolean\" ARRAYSIZE=\"2\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\" ARRAYSIZE=\"cc\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\" ARRAYSIZE=\"2\"><goo/></PROPERTY.ARRAY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\" TYPE=\"boolean\" ARRAYSIZE=\"2\" goo=\"goo\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>")
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;

        if (NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer")))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;

                NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i], Tcslen(testData[i])*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_INVALID_PARAMETER, testData[i]);
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest
    
NitsTest(Xml_Class_Prop_Array_Quals_Simple_Validate)
    ValidationData testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_BOOLEAN,PAL_T("true")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"string\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"string\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER><VALUE.ARRAY><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE><VALUE>goodbye</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_STRING,PAL_T("hello&'><\"")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"char16\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"char16\"><VALUE>&#8;</VALUE></QUALIFIER><VALUE.ARRAY><VALUE>&#8;</VALUE><VALUE>&#16;</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_CHAR16, PAL_T("\x8")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint8\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint8\"><VALUE>10</VALUE></QUALIFIER><VALUE.ARRAY><VALUE>1</VALUE><VALUE>10</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT8,PAL_T("10")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint8\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint8\"><VALUE>1</VALUE></QUALIFIER><VALUE.ARRAY><VALUE>-1</VALUE><VALUE>1</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT8,PAL_T("1")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint16\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint16\"><VALUE>2</VALUE></QUALIFIER><VALUE.ARRAY><VALUE>2</VALUE><VALUE>20</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT16,PAL_T("2")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint16\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint16\"><VALUE>-2</VALUE></QUALIFIER><VALUE.ARRAY><VALUE>-2</VALUE><VALUE>2</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT16,PAL_T("-2")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint32\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint32\"><VALUE>3</VALUE></QUALIFIER><VALUE.ARRAY><VALUE>3</VALUE><VALUE>30</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT32,PAL_T("3")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint32\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint32\"><VALUE>-3</VALUE></QUALIFIER><VALUE.ARRAY><VALUE>-3</VALUE><VALUE>3</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT32,PAL_T("-3")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint64\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint64\"><VALUE>4</VALUE></QUALIFIER><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT64,PAL_T("4")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint64\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint64\"><VALUE>-4</VALUE></QUALIFIER><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT64,PAL_T("-4")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"datetime\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"datetime\"><VALUE>20110314222412.000000+008</VALUE></QUALIFIER><VALUE.ARRAY><VALUE>20110314222412.000000+008</VALUE><VALUE>20110314222412.000000+008</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_DATETIME,PAL_T("20110314222412.000000+008")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"real32\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real32\"><VALUE>1.1000000e+00</VALUE></QUALIFIER><VALUE.ARRAY><VALUE>1.1000000e+00</VALUE><VALUE>-1.1000000e+00</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_REAL32,PAL_T("1.1")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"real64\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real64\"><VALUE>2.2000000000000002e+00</VALUE></QUALIFIER><VALUE.ARRAY><VALUE>2.2000000000000002e+00</VALUE><VALUE>-2.2000000000000002e+00</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_REAL64,PAL_T("2.2")}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_Boolean valueExists;
                    MI_QualifierSet qs;
                    MI_Uint32 qsCount;

                    if (NitsCompare(MI_Class_GetElementAt(newClass, 0, &resultName, &resultValue, &valueExists, &resultType, NULL, &qs, &resultFlags), MI_RESULT_OK, PAL_T("Get property value should work")) &&
                        resultName &&
                        NitsCompare(Tcscmp(resultName, PAL_T("prop1")), 0, PAL_T("propertyName should be prop1")) &&
                        NitsCompare(resultType, testData[i].type|MI_ARRAY, PAL_T("Types should match")) &&
                        NitsAssert(resultFlags & MI_FLAG_PROPERTY, PAL_T("Flags should be MI_FLAG_PROPERTY")) &&
                        NitsCompare(resultValue.booleana.size, 2, PAL_T("array size should be 2")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count")) &&
                        NitsCompare(qsCount, 1, PAL_T("qualifier count should be 1")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, &resultName, &resultType, &resultFlags, &resultValue), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("qual1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type, PAL_T("Qualifier type")) &&
                        NitsCompare(resultFlags, MI_FLAG_TOSUBCLASS|MI_FLAG_ENABLEOVERRIDE, PAL_T("QualifierSet flags")) &&
                        NitsCompare(CompareMiValue(&resultValue, resultType, testData[i].value, NitsHere()), MI_TRUE, testData[i].XML))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }

                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Prop_Array_Quals_Array_Validate)
    ValidationDataArray testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_BOOLEAN,{PAL_T("true"), PAL_T("false")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"string\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"string\"><VALUE.ARRAY><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE><VALUE>goodbye</VALUE></VALUE.ARRAY></QUALIFIER><VALUE.ARRAY><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE><VALUE>goodbye</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_STRING,{PAL_T("hello&'><\""), PAL_T("goodbye")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"char16\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"char16\"><VALUE.ARRAY><VALUE>&#8;</VALUE><VALUE>&#16;</VALUE></VALUE.ARRAY></QUALIFIER><VALUE.ARRAY><VALUE>&#8;</VALUE><VALUE>&#16;</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_CHAR16,{PAL_T("\x8"), PAL_T("\x10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint8\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint8\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>10</VALUE></VALUE.ARRAY></QUALIFIER><VALUE.ARRAY><VALUE>1</VALUE><VALUE>10</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT8,{PAL_T("1"), PAL_T("10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint8\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint8\"><VALUE.ARRAY><VALUE>-1</VALUE><VALUE>1</VALUE></VALUE.ARRAY></QUALIFIER><VALUE.ARRAY><VALUE>-1</VALUE><VALUE>1</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT8,{PAL_T("-1"), PAL_T("1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint16\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint16\"><VALUE.ARRAY><VALUE>2</VALUE><VALUE>20</VALUE></VALUE.ARRAY></QUALIFIER><VALUE.ARRAY><VALUE>2</VALUE><VALUE>20</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT16,{PAL_T("2"), PAL_T("20")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint16\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint16\"><VALUE.ARRAY><VALUE>-2</VALUE><VALUE>2</VALUE></VALUE.ARRAY></QUALIFIER><VALUE.ARRAY><VALUE>-2</VALUE><VALUE>2</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT16,{PAL_T("-2"), PAL_T("2")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint32\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint32\"><VALUE.ARRAY><VALUE>3</VALUE><VALUE>30</VALUE></VALUE.ARRAY></QUALIFIER><VALUE.ARRAY><VALUE>3</VALUE><VALUE>30</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT32,{PAL_T("3"), PAL_T("30")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint32\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint32\"><VALUE.ARRAY><VALUE>-3</VALUE><VALUE>3</VALUE></VALUE.ARRAY></QUALIFIER><VALUE.ARRAY><VALUE>-3</VALUE><VALUE>3</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT32,{PAL_T("-3"), PAL_T("3")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint64\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint64\"><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></QUALIFIER><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT64,{PAL_T("4"), PAL_T("40")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint64\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint64\"><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></QUALIFIER><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT64,{PAL_T("-4"), PAL_T("4")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"datetime\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"datetime\"><VALUE.ARRAY><VALUE>20110314222412.000000+008</VALUE><VALUE>20110314222412.000000+008</VALUE></VALUE.ARRAY></QUALIFIER><VALUE.ARRAY><VALUE>20110314222412.000000+008</VALUE><VALUE>20110314222412.000000+008</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_DATETIME,{PAL_T("20110314222412.000000+008"), PAL_T("20110314222412.000000+008")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"real32\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real32\"><VALUE.ARRAY><VALUE>1.1000000e+00</VALUE><VALUE>-1.1000000e+00</VALUE></VALUE.ARRAY></QUALIFIER><VALUE.ARRAY><VALUE>1.1000000e+00</VALUE><VALUE>-1.1000000e+00</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_REAL32,{PAL_T("1.1"), PAL_T("-1.1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"real64\" ARRAYSIZE=\"2\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real64\"><VALUE.ARRAY><VALUE>2.2000000000000002e+00</VALUE><VALUE>-2.2000000000000002e+00</VALUE></VALUE.ARRAY></QUALIFIER><VALUE.ARRAY><VALUE>2.2000000000000002e+00</VALUE><VALUE>-2.2000000000000002e+00</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_REAL64,{PAL_T("2.2"), PAL_T("-2.2")}}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_Boolean valueExists;
                    MI_QualifierSet qs;
                    MI_Uint32 qsCount;

                    if (NitsCompare(MI_Class_GetElementAt(newClass, 0, &resultName, &resultValue, &valueExists, &resultType, NULL, &qs, &resultFlags), MI_RESULT_OK, PAL_T("Get property value should work")) &&
                        resultName &&
                        NitsCompare(Tcscmp(resultName, PAL_T("prop1")), 0, PAL_T("propertyName should be prop1")) &&
                        NitsCompare(resultType, testData[i].type|MI_ARRAY, PAL_T("Types should match")) &&
                        NitsAssert(resultFlags & MI_FLAG_PROPERTY, PAL_T("Flags should be MI_FLAG_PROPERTY")) &&
                        NitsCompare(resultValue.booleana.size, 2, PAL_T("array size should be 2")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count")) &&
                        NitsCompare(qsCount, 1, PAL_T("qualifier count should be 1")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, &resultName, &resultType, &resultFlags, &resultValue), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("qual1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type|MI_ARRAY, PAL_T("Qualifier type")) &&
                        NitsCompare(resultFlags, MI_FLAG_TOSUBCLASS|MI_FLAG_ENABLEOVERRIDE, PAL_T("QualifierSet flags")) &&
                        CompareMiValueArray(&resultValue, resultType, testData[i].value, 2, NitsHere()))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }

                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Method_Params_None_Validate)
    ValidationData testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"></METHOD></CLASS>"), MI_BOOLEAN, NULL},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"></METHOD></CLASS>"), MI_STRING, NULL},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"></METHOD></CLASS>"), MI_CHAR16, NULL},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"></METHOD></CLASS>"), MI_UINT8, NULL},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"></METHOD></CLASS>"), MI_SINT8, NULL},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"></METHOD></CLASS>"), MI_UINT16, NULL},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"></METHOD></CLASS>"), MI_SINT16, NULL},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"></METHOD></CLASS>"), MI_UINT32, NULL},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"></METHOD></CLASS>"), MI_SINT32, NULL},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"></METHOD></CLASS>"), MI_UINT64, NULL},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"></METHOD></CLASS>"), MI_SINT64, NULL},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"></METHOD></CLASS>"), MI_DATETIME, NULL},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"></METHOD></CLASS>"), MI_REAL32, NULL},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"></METHOD></CLASS>"), MI_REAL64, NULL}
    };

    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Type resultType;
                    MI_QualifierSet qs;
                    MI_ParameterSet ps;
                    MI_Uint32 qsCount;
                    MI_Uint32 psCount;
                    MI_Uint32 methodCount;

                    if (NitsCompare(MI_Class_GetMethodCount(newClass, &methodCount), MI_RESULT_OK, PAL_T("method count")) &&
                        NitsCompare(methodCount, 1, PAL_T("method count=1")) &&
                        NitsCompare(MI_Class_GetMethodAt(newClass, 0, &resultName, &qs, &ps), MI_RESULT_OK, PAL_T("Get class qualifier set")) &&
                        NitsAssert(resultName!=NULL, PAL_T("name should exist")) &&
                        NitsCompareString(resultName, PAL_T("Method1"), PAL_T("method name")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")) &&
                        NitsCompare(MI_ParameterSet_GetParameterCount(&ps, &psCount), MI_RESULT_OK, PAL_T("parameterSetCount")) &&
                        NitsCompare(psCount, 0, PAL_T("no parameter")) &&
                        NitsCompare(MI_ParameterSet_GetMethodReturnType(&ps, &resultType, &qs), MI_RESULT_OK, PAL_T("Return type"))&&
                        NitsCompare(resultType, testData[i].type, PAL_T("return type")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count for parameter")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest
    
NitsTest(Xml_Class_Method_Params_None_Invalid)
    ValidationError testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD TYPE=\"boolean\" CLASSORIGIN=\"myClass\" PROPAGATED=\"goo\"></METHOD></CLASS>"),MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" NAME=\"Method1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\" PROPAGATED=\"goo\"></METHOD></CLASS>"),MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" CLASSORIGIN=\"myClass\" PROPAGATED=\"goo\"></METHOD></CLASS>"),MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"boolean\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\" PROPAGATED=\"goo\"></METHOD></CLASS>"),MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\" PROPAGATED=\"goo\" goo=\"goo\"></METHOD></CLASS>"),MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"Method1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\" PROPAGATED=\"goo\"><goo/></METHOD></CLASS>"),MI_RESULT_INVALID_PARAMETER}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;

        if (NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer")))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), testData[i].result, testData[i].XML);
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest
    
NitsTest(Xml_Class_Method_Quals_Simple_Param_None)
    ValidationData testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></METHOD></CLASS>"),MI_BOOLEAN,PAL_T("true")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"string\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER></METHOD></CLASS>"),MI_STRING,PAL_T("hello&'><\"")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"char16\"><VALUE>&#8;</VALUE></QUALIFIER></METHOD></CLASS>"),MI_CHAR16, PAL_T("\x8")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint8\"><VALUE>1</VALUE></QUALIFIER></METHOD></CLASS>"),MI_UINT8,PAL_T("1")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint8\"><VALUE>-1</VALUE></QUALIFIER></METHOD></CLASS>"),MI_SINT8,PAL_T("-1")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint16\"><VALUE>2</VALUE></QUALIFIER></METHOD></CLASS>"),MI_UINT16,PAL_T("2")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint16\"><VALUE>-2</VALUE></QUALIFIER></METHOD></CLASS>"),MI_SINT16,PAL_T("-2")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint32\"><VALUE>3</VALUE></QUALIFIER></METHOD></CLASS>"),MI_UINT32,PAL_T("3")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint32\"><VALUE>-3</VALUE></QUALIFIER></METHOD></CLASS>"),MI_SINT32,PAL_T("-3"),},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint64\"><VALUE>4</VALUE></QUALIFIER></METHOD></CLASS>"),MI_UINT64,PAL_T("4")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint64\"><VALUE>-4</VALUE></QUALIFIER></METHOD></CLASS>"),MI_SINT64,PAL_T("-4")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"datetime\"><VALUE>20110314222412.000000+008</VALUE></QUALIFIER></METHOD></CLASS>"),MI_DATETIME,PAL_T("20110314222412.000000+008")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real32\"><VALUE>1.1000000e+00</VALUE></QUALIFIER></METHOD></CLASS>"),MI_REAL32,PAL_T("1.1")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real64\"><VALUE>2.2000000000000002e+00</VALUE></QUALIFIER></METHOD></CLASS>"),MI_REAL64,PAL_T("2.2")}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_QualifierSet qs;
                    MI_ParameterSet ps;
                    MI_Uint32 qsCount;
                    MI_Uint32 psCount;
                    MI_Uint32 methodCount;

                    if (NitsCompare(MI_Class_GetMethodCount(newClass, &methodCount), MI_RESULT_OK, PAL_T("method count")) &&
                        NitsCompare(methodCount, 1, PAL_T("method count=1")) &&
                        NitsCompare(MI_Class_GetMethodAt(newClass, 0, &resultName, &qs, &ps), MI_RESULT_OK, PAL_T("Get class qualifier set")) &&
                        NitsAssert(resultName!=NULL, PAL_T("name should exist")) &&
                        NitsCompareString(resultName, PAL_T("Method1"), PAL_T("method name")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count")) &&
                        NitsCompare(qsCount, 1, PAL_T("qualifier count ")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, &resultName, &resultType, &resultFlags, &resultValue), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("qual1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type, PAL_T("Qualifier type")) &&
                        NitsCompare(resultFlags, MI_FLAG_TOSUBCLASS|MI_FLAG_ENABLEOVERRIDE, PAL_T("QualifierSet flags")) &&
                        NitsCompare(CompareMiValue(&resultValue, resultType, testData[i].value, NitsHere()), MI_TRUE, testData[i].XML) &&
                        NitsCompare(MI_ParameterSet_GetParameterCount(&ps, &psCount), MI_RESULT_OK, PAL_T("parameterSetCount")) &&
                        NitsCompare(psCount, 0, PAL_T("no parameter")) &&
                        NitsCompare(MI_ParameterSet_GetMethodReturnType(&ps, &resultType, &qs), MI_RESULT_OK, PAL_T("Return type"))&&
                        NitsCompare(resultType, testData[i].type, PAL_T("return type")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count for parameter")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

    
NitsTest(Xml_Class_Method_Quals_Array_Params_None)
    ValidationDataArray testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),MI_BOOLEAN,{PAL_T("true"), PAL_T("false")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"string\"><VALUE.ARRAY><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE><VALUE>goodbye</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),MI_STRING,{PAL_T("hello&'><\""), PAL_T("goodbye")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"char16\"><VALUE.ARRAY><VALUE>&#8;</VALUE><VALUE>&#16;</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),MI_CHAR16,{PAL_T("\x8"), PAL_T("\x10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint8\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>10</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),MI_UINT8,{PAL_T("1"), PAL_T("10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint8\"><VALUE.ARRAY><VALUE>-1</VALUE><VALUE>1</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),MI_SINT8,{PAL_T("-1"), PAL_T("1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint16\"><VALUE.ARRAY><VALUE>2</VALUE><VALUE>20</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),MI_UINT16,{PAL_T("2"), PAL_T("20")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint16\"><VALUE.ARRAY><VALUE>-2</VALUE><VALUE>2</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),MI_SINT16,{PAL_T("-2"), PAL_T("2")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint32\"><VALUE.ARRAY><VALUE>3</VALUE><VALUE>30</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),MI_UINT32,{PAL_T("3"), PAL_T("30")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint32\"><VALUE.ARRAY><VALUE>-3</VALUE><VALUE>3</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),MI_SINT32,{PAL_T("-3"), PAL_T("3")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint64\"><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),MI_UINT64,{PAL_T("4"), PAL_T("40")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint64\"><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),MI_SINT64,{PAL_T("-4"), PAL_T("4")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"datetime\"><VALUE.ARRAY><VALUE>20110314222412.000000+008</VALUE><VALUE>20110314222412.000000+008</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),MI_DATETIME,{PAL_T("20110314222412.000000+008"), PAL_T("20110314222412.000000+008")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real32\"><VALUE.ARRAY><VALUE>1.1000000e+00</VALUE><VALUE>-1.1000000e+00</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),MI_REAL32,{PAL_T("1.1"), PAL_T("-1.1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"real64\"><VALUE.ARRAY><VALUE>2.2000000000000002e+00</VALUE><VALUE>-2.2000000000000002e+00</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),MI_REAL64,{PAL_T("2.2"), PAL_T("-2.2")}}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_QualifierSet qs;
                    MI_ParameterSet ps;
                    MI_Uint32 qsCount;
                    MI_Uint32 psCount;
                    MI_Uint32 methodCount;

                    if (NitsCompare(MI_Class_GetMethodCount(newClass, &methodCount), MI_RESULT_OK, PAL_T("method count")) &&
                        NitsCompare(methodCount, 1, PAL_T("method count=1")) &&
                        NitsCompare(MI_Class_GetMethodAt(newClass, 0, &resultName, &qs, &ps), MI_RESULT_OK, PAL_T("Get class qualifier set")) &&
                        NitsAssert(resultName!=NULL, PAL_T("name should exist")) &&
                        NitsCompareString(resultName, PAL_T("Method1"), PAL_T("method name")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count")) &&
                        NitsCompare(qsCount, 1, PAL_T("qualifier count ")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, &resultName, &resultType, &resultFlags, &resultValue), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("qual1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type|MI_ARRAY, PAL_T("Qualifier type")) &&
                        NitsCompare(resultFlags, MI_FLAG_TOSUBCLASS|MI_FLAG_ENABLEOVERRIDE, PAL_T("QualifierSet flags")) &&
                        CompareMiValueArray(&resultValue, resultType, testData[i].value, 2, NitsHere()) &&
                        NitsCompare(MI_ParameterSet_GetParameterCount(&ps, &psCount), MI_RESULT_OK, PAL_T("parameterSetCount")) &&
                        NitsCompare(psCount, 0, PAL_T("no parameter")) &&
                        NitsCompare(MI_ParameterSet_GetMethodReturnType(&ps, &resultType, &qs), MI_RESULT_OK, PAL_T("Return type"))&&
                        NitsCompare(resultType, testData[i].type, PAL_T("return type")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count for parameter")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest
    
NitsTest(Xml_Class_Method_Params_Simple)
    ValidationData testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"boolean\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_BOOLEAN,PAL_T("true")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"string\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_STRING,PAL_T("hello&'><\"")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"char16\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_CHAR16, PAL_T("\x8")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint8\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_UINT8,PAL_T("1")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"sint8\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_SINT8,PAL_T("-1")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint16\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_UINT16,PAL_T("2")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"sint16\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_SINT16,PAL_T("-2")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint32\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_UINT32,PAL_T("3")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"sint32\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_SINT32,PAL_T("-3"),},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint64\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_UINT64,PAL_T("4")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"sint64\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_SINT64,PAL_T("-4")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"datetime\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_DATETIME,PAL_T("20110314222412.000000+008")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"real32\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_REAL32,PAL_T("1.1")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"real64\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_REAL64,PAL_T("2.2")}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Type resultType;
                    MI_QualifierSet qs;
                    MI_ParameterSet ps;
                    MI_Uint32 qsCount;
                    MI_Uint32 psCount;
                    MI_Uint32 methodCount;

                    if (NitsCompare(MI_Class_GetMethodCount(newClass, &methodCount), MI_RESULT_OK, PAL_T("method count")) &&
                        NitsCompare(methodCount, 1, PAL_T("method count=1")) &&
                        NitsCompare(MI_Class_GetMethodAt(newClass, 0, &resultName, &qs, &ps), MI_RESULT_OK, PAL_T("Get class qualifier set")) &&
                        NitsAssert(resultName!=NULL, PAL_T("name should exist")) &&
                        NitsCompareString(resultName, PAL_T("Method1"), PAL_T("method name")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")) &&
                        NitsCompare(MI_ParameterSet_GetParameterCount(&ps, &psCount), MI_RESULT_OK, PAL_T("parameterSetCount")) &&
                        NitsCompare(psCount, 1, PAL_T("no parameter")) &&
                        NitsCompare(MI_ParameterSet_GetParameterAt(&ps, 0, &resultName, &resultType, NULL, &qs), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("param1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type, PAL_T("Qualifier type")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("parameter qs")) &&
                        NitsCompare(qsCount, 1, PAL_T("qualifier count ")) &&
                        NitsCompare(MI_ParameterSet_GetMethodReturnType(&ps, &resultType, &qs), MI_RESULT_OK, PAL_T("Return type"))&&
                        NitsCompare(resultType, testData[i].type, PAL_T("return type")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count for parameter")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

    
NitsTest(Xml_Class_Method_Params_Simple_Invalid)
    const MI_Char *testData[] =
    {
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER TYPE=\"boolean\"></PARAMETER></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER NAME=\"qual1\" NAME=\"qual1\" TYPE=\"boolean\"></PARAMETER></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER NAME=\"qual1\" ></PARAMETER></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER NAME=\"qual1\" TYPE=\"boolean\" TYPE=\"boolean\"></PARAMETER></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER NAME=\"qual1\" TYPE=\"blah\"></PARAMETER></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER NAME=\"qual1\" TYPE=\"boolean\" blah=\"goo\"></PARAMETER></METHOD></CLASS>")
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;

        if (NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer")))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i], Tcslen(testData[i])*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_INVALID_PARAMETER, testData[i]);
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

    
NitsTest(Xml_Class_Method_Params_Array)
    ValidationData testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"boolean\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_BOOLEAN,PAL_T("true")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"string\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_STRING,PAL_T("hello&'><\"")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"char16\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_CHAR16, PAL_T("\x8")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"uint8\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_UINT8,PAL_T("1")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"sint8\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_SINT8,PAL_T("-1")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"uint16\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_UINT16,PAL_T("2")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"sint16\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_SINT16,PAL_T("-2")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"uint32\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_UINT32,PAL_T("3")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"sint32\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_SINT32,PAL_T("-3"),},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"uint64\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_UINT64,PAL_T("4")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"sint64\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_SINT64,PAL_T("-4")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"datetime\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_DATETIME,PAL_T("20110314222412.000000+008")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"real32\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_REAL32,PAL_T("1.1")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"real64\"><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_REAL64,PAL_T("2.2")}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Type resultType;
                    MI_QualifierSet qs;
                    MI_ParameterSet ps;
                    MI_Uint32 qsCount;
                    MI_Uint32 psCount;
                    MI_Uint32 methodCount;

                    if (NitsCompare(MI_Class_GetMethodCount(newClass, &methodCount), MI_RESULT_OK, PAL_T("method count")) &&
                        NitsCompare(methodCount, 1, PAL_T("method count=1")) &&
                        NitsCompare(MI_Class_GetMethodAt(newClass, 0, &resultName, &qs, &ps), MI_RESULT_OK, PAL_T("Get class qualifier set")) &&
                        NitsAssert(resultName!=NULL, PAL_T("name should exist")) &&
                        NitsCompareString(resultName, PAL_T("Method1"), PAL_T("method name")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")) &&
                        NitsCompare(MI_ParameterSet_GetParameterCount(&ps, &psCount), MI_RESULT_OK, PAL_T("parameterSetCount")) &&
                        NitsCompare(psCount, 1, PAL_T("no parameter")) &&
                        NitsCompare(MI_ParameterSet_GetParameterAt(&ps, 0, &resultName, &resultType, NULL, &qs), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("param1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type|MI_ARRAY, PAL_T("Qualifier type")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("parameter qs")) &&
                        NitsCompare(qsCount, 1, PAL_T("qualifier count ")) &&
                        NitsCompare(MI_ParameterSet_GetMethodReturnType(&ps, &resultType, &qs), MI_RESULT_OK, PAL_T("Return type"))&&
                        NitsCompare(resultType, testData[i].type, PAL_T("return type")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count for parameter")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Method_Params_Array_Invalid)
    ValidationError testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real64\"><PARAMETER.ARRAY TYPE=\"boolean\"></PARAMETER.ARRAY></METHOD></CLASS>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real64\"><PARAMETER.ARRAY NAME=\"prop1\" ></PARAMETER.ARRAY></METHOD></CLASS>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real64\"><PARAMETER.ARRAY NAME=\"prop1\" NAME=\"prop1\" TYPE=\"boolean\"></PARAMETER.ARRAY></METHOD></CLASS>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real64\"><PARAMETER.ARRAY NAME=\"prop1\" TYPE=\"boolean\" TYPE=\"boolean\"></PARAMETER.ARRAY></METHOD></CLASS>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real64\"><PARAMETER.ARRAY NAME=\"prop1\" TYPE=\"boolean\"><x/></PARAMETER.ARRAY></METHOD></CLASS>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real64\"><PARAMETER.ARRAY NAME=\"prop1\" TYPE=\"foo\"></PARAMETER.ARRAY></METHOD></CLASS>"), MI_RESULT_INVALID_PARAMETER}
    };   
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;

        if (NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer")))
        {
            MI_Class *newClass = NULL;
            MI_Uint32 i;
            for (i = 0; i != sizeof(testData)/sizeof(testData[0]);i++)
            {
                MI_Uint32 deserializeSize;
                NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), testData[i].result, PAL_T("invalid method params"));
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Method_Params_Array_Quals_Simple_Validate)
    ValidationData testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"boolean\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_BOOLEAN,PAL_T("true")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"string\"><QUALIFIER NAME=\"qual1\" TYPE=\"string\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_STRING,PAL_T("hello&'><\"")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"char16\"><QUALIFIER NAME=\"qual1\" TYPE=\"char16\"><VALUE>&#8;</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_CHAR16, PAL_T("\x8")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"uint8\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint8\"><VALUE>1</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_UINT8,PAL_T("1")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"sint8\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint8\"><VALUE>-1</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_SINT8,PAL_T("-1")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"uint16\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint16\"><VALUE>2</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_UINT16,PAL_T("2")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"sint16\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint16\"><VALUE>-2</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_SINT16,PAL_T("-2")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"uint32\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint32\"><VALUE>3</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_UINT32,PAL_T("3")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"sint32\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint32\"><VALUE>-3</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_SINT32,PAL_T("-3")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"uint64\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint64\"><VALUE>4</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_UINT64,PAL_T("4")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"sint64\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint64\"><VALUE>-4</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_SINT64,PAL_T("-4")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"datetime\"><QUALIFIER NAME=\"qual1\" TYPE=\"datetime\"><VALUE>20110314222412.000000+008</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_DATETIME,PAL_T("20110314222412.000000+008")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"real32\"><QUALIFIER NAME=\"qual1\" TYPE=\"real32\"><VALUE>1.1000000e+00</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_REAL32,PAL_T("1.1")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"real64\"><QUALIFIER NAME=\"qual1\" TYPE=\"real64\"><VALUE>2.2000000000000002e+00</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_REAL64,PAL_T("2.2")}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_QualifierSet qs;
                    MI_ParameterSet ps;
                    MI_Uint32 qsCount;
                    MI_Uint32 psCount;
                    MI_Uint32 methodCount;

                    if (NitsCompare(MI_Class_GetMethodCount(newClass, &methodCount), MI_RESULT_OK, PAL_T("method count")) &&
                        NitsCompare(methodCount, 1, PAL_T("method count=1")) &&
                        NitsCompare(MI_Class_GetMethodAt(newClass, 0, &resultName, &qs, &ps), MI_RESULT_OK, PAL_T("Get class qualifier set")) &&
                        NitsAssert(resultName!=NULL, PAL_T("name should exist")) &&
                        NitsCompareString(resultName, PAL_T("Method1"), PAL_T("method name")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")) &&
                        NitsCompare(MI_ParameterSet_GetParameterCount(&ps, &psCount), MI_RESULT_OK, PAL_T("parameterSetCount")) &&
                        NitsCompare(psCount, 1, PAL_T("no parameter")) &&
                        NitsCompare(MI_ParameterSet_GetParameterAt(&ps, 0, &resultName, &resultType, NULL, &qs), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("param1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type|MI_ARRAY, PAL_T("Qualifier type")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("parameter qs")) &&
                        NitsCompare(qsCount, 2, PAL_T("qualifier count ")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, &resultName, &resultType, &resultFlags, &resultValue), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("qual1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type, PAL_T("Qualifier type")) &&
                        NitsCompare(resultFlags, MI_FLAG_TOSUBCLASS|MI_FLAG_ENABLEOVERRIDE, PAL_T("QualifierSet flags")) &&
                        NitsCompare(CompareMiValue(&resultValue, resultType, testData[i].value, NitsHere()), MI_TRUE, testData[i].XML) &&
                        NitsCompare(MI_ParameterSet_GetMethodReturnType(&ps, &resultType, &qs), MI_RESULT_OK, PAL_T("Return type"))&&
                        NitsCompare(resultType, testData[i].type, PAL_T("return type")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count for parameter")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Method_Params_Array_Quals_Array_Validate)
    ValidationDataArray testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"boolean\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_BOOLEAN,{PAL_T("true"), PAL_T("false")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"string\"><QUALIFIER NAME=\"qual1\" TYPE=\"string\"><VALUE.ARRAY><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE><VALUE>goodbye</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_STRING,{PAL_T("hello&'><\""), PAL_T("goodbye")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"char16\"><QUALIFIER NAME=\"qual1\" TYPE=\"char16\"><VALUE.ARRAY><VALUE>&#8;</VALUE><VALUE>&#16;</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_CHAR16,{PAL_T("\x8"), PAL_T("\x10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"uint8\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint8\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>10</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_UINT8,{PAL_T("1"), PAL_T("10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"sint8\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint8\"><VALUE.ARRAY><VALUE>-1</VALUE><VALUE>1</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_SINT8,{PAL_T("-1"), PAL_T("1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"uint16\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint16\"><VALUE.ARRAY><VALUE>2</VALUE><VALUE>20</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_UINT16,{PAL_T("2"), PAL_T("20")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"sint16\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint16\"><VALUE.ARRAY><VALUE>-2</VALUE><VALUE>2</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_SINT16,{PAL_T("-2"), PAL_T("2")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"uint32\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint32\"><VALUE.ARRAY><VALUE>3</VALUE><VALUE>30</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_UINT32,{PAL_T("3"), PAL_T("30")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"sint32\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint32\"><VALUE.ARRAY><VALUE>-3</VALUE><VALUE>3</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_SINT32,{PAL_T("-3"), PAL_T("3")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"uint64\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint64\"><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_UINT64,{PAL_T("4"), PAL_T("40")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"sint64\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint64\"><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_SINT64,{PAL_T("-4"), PAL_T("4")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"datetime\"><QUALIFIER NAME=\"qual1\" TYPE=\"datetime\"><VALUE.ARRAY><VALUE>20110314222412.000000+008</VALUE><VALUE>20110314222412.000000+008</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_DATETIME,{PAL_T("20110314222412.000000+008"), PAL_T("20110314222412.000000+008")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"real32\"><QUALIFIER NAME=\"qual1\" TYPE=\"real32\"><VALUE.ARRAY><VALUE>1.1000000e+00</VALUE><VALUE>-1.1000000e+00</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_REAL32,{PAL_T("1.1"), PAL_T("-1.1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"real64\"><QUALIFIER NAME=\"qual1\" TYPE=\"real64\"><VALUE.ARRAY><VALUE>2.2000000000000002e+00</VALUE><VALUE>-2.2000000000000002e+00</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"),MI_REAL64,{PAL_T("2.2"), PAL_T("-2.2")}}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_QualifierSet qs;
                    MI_ParameterSet ps;
                    MI_Uint32 qsCount;
                    MI_Uint32 psCount;
                    MI_Uint32 methodCount;

                    if (NitsCompare(MI_Class_GetMethodCount(newClass, &methodCount), MI_RESULT_OK, PAL_T("method count")) &&
                        NitsCompare(methodCount, 1, PAL_T("method count=1")) &&
                        NitsCompare(MI_Class_GetMethodAt(newClass, 0, &resultName, &qs, &ps), MI_RESULT_OK, PAL_T("Get class qualifier set")) &&
                        NitsAssert(resultName!=NULL, PAL_T("name should exist")) &&
                        NitsCompareString(resultName, PAL_T("Method1"), PAL_T("method name")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")) &&
                        NitsCompare(MI_ParameterSet_GetParameterCount(&ps, &psCount), MI_RESULT_OK, PAL_T("parameterSetCount")) &&
                        NitsCompare(psCount, 1, PAL_T("no parameter")) &&
                        NitsCompare(MI_ParameterSet_GetParameterAt(&ps, 0, &resultName, &resultType, NULL, &qs), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("param1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type|MI_ARRAY, PAL_T("Qualifier type")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("parameter qs")) &&
                        NitsCompare(qsCount, 2, PAL_T("qualifier count ")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, &resultName, &resultType, &resultFlags, &resultValue), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("qual1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type|MI_ARRAY, PAL_T("Qualifier type")) &&
                        NitsCompare(resultFlags, MI_FLAG_TOSUBCLASS|MI_FLAG_ENABLEOVERRIDE, PAL_T("QualifierSet flags")) &&
                        CompareMiValueArray(&resultValue, resultType, testData[i].value, 2, NitsHere()) &&
                        NitsCompare(MI_ParameterSet_GetMethodReturnType(&ps, &resultType, &qs), MI_RESULT_OK, PAL_T("Return type"))&&
                        NitsCompare(resultType, testData[i].type, PAL_T("return type")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count for parameter")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_Method_Params_Array_Quals_Simple_InvalidParams)
    ValidationError testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.ARRAY NAME=\"qual1\" TYPE=\"boolean\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><hello/></PARAMETER.ARRAY></METHOD></CLASS>"),MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.ARRAY  TYPE=\"boolean\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY></METHOD></CLASS>"), MI_RESULT_INVALID_PARAMETER}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;

        if (NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer")))
        {
            MI_Class *newClass = NULL;
            MI_Uint32 i;
            for (i = 0; i != sizeof(testData)/sizeof(testData[0]);i++)
            {
                MI_Uint32 deserializeSize;
                NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), testData[i].result, testData[i].XML);
            }

            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest
    
NitsTest(Xml_Class_Method_Params_Simple_Quals_Simple)
    ValidationData testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"boolean\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_BOOLEAN,PAL_T("true")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"string\"><QUALIFIER NAME=\"qual1\" TYPE=\"string\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_STRING,PAL_T("hello&'><\"")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"char16\"><QUALIFIER NAME=\"qual1\" TYPE=\"char16\"><VALUE>&#8;</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_CHAR16, PAL_T("\x8")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint8\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint8\"><VALUE>1</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_UINT8,PAL_T("1")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"sint8\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint8\"><VALUE>-1</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_SINT8,PAL_T("-1")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint16\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint16\"><VALUE>2</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_UINT16,PAL_T("2")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"sint16\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint16\"><VALUE>-2</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_SINT16,PAL_T("-2")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint32\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint32\"><VALUE>3</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_UINT32,PAL_T("3")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"sint32\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint32\"><VALUE>-3</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_SINT32,PAL_T("-3")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint64\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint64\"><VALUE>4</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_UINT64,PAL_T("4")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"sint64\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint64\"><VALUE>-4</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_SINT64,PAL_T("-4")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"datetime\"><QUALIFIER NAME=\"qual1\" TYPE=\"datetime\"><VALUE>20110314222412.000000+008</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_DATETIME,PAL_T("20110314222412.000000+008")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"real32\"><QUALIFIER NAME=\"qual1\" TYPE=\"real32\"><VALUE>1.1000000e+00</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_REAL32,PAL_T("1.1")},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"real64\"><QUALIFIER NAME=\"qual1\" TYPE=\"real64\"><VALUE>2.2000000000000002e+00</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_REAL64,PAL_T("2.2")}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_QualifierSet qs;
                    MI_ParameterSet ps;
                    MI_Uint32 qsCount;
                    MI_Uint32 psCount;
                    MI_Uint32 methodCount;

                    if (NitsCompare(MI_Class_GetMethodCount(newClass, &methodCount), MI_RESULT_OK, PAL_T("method count")) &&
                        NitsCompare(methodCount, 1, PAL_T("method count=1")) &&
                        NitsCompare(MI_Class_GetMethodAt(newClass, 0, &resultName, &qs, &ps), MI_RESULT_OK, PAL_T("Get class qualifier set")) &&
                        NitsAssert(resultName!=NULL, PAL_T("name should exist")) &&
                        NitsCompareString(resultName, PAL_T("Method1"), PAL_T("method name")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")) &&
                        NitsCompare(MI_ParameterSet_GetParameterCount(&ps, &psCount), MI_RESULT_OK, PAL_T("parameterSetCount")) &&
                        NitsCompare(psCount, 1, PAL_T("no parameter")) &&
                        NitsCompare(MI_ParameterSet_GetParameterAt(&ps, 0, &resultName, &resultType, NULL, &qs), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("param1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type, PAL_T("Qualifier type")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("parameter qs")) &&
                        NitsCompare(qsCount, 2, PAL_T("qualifier count ")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, &resultName, &resultType, &resultFlags, &resultValue), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("qual1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type, PAL_T("Qualifier type")) &&
                        NitsCompare(resultFlags, MI_FLAG_TOSUBCLASS|MI_FLAG_ENABLEOVERRIDE, PAL_T("QualifierSet flags")) &&
                        NitsCompare(CompareMiValue(&resultValue, resultType, testData[i].value, NitsHere()), MI_TRUE, testData[i].XML) &&
                        NitsCompare(MI_ParameterSet_GetMethodReturnType(&ps, &resultType, &qs), MI_RESULT_OK, PAL_T("Return type"))&&
                        NitsCompare(resultType, testData[i].type, PAL_T("return type")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count for parameter")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest
    
NitsTest(Xml_Class_Method_Params_Simple_Quals_Array)
    ValidationDataArray testData[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"boolean\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_BOOLEAN,{PAL_T("true"), PAL_T("false")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"string\"><QUALIFIER NAME=\"qual1\" TYPE=\"string\"><VALUE.ARRAY><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE><VALUE>goodbye</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_STRING,{PAL_T("hello&'><\""), PAL_T("goodbye")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"char16\"><QUALIFIER NAME=\"qual1\" TYPE=\"char16\"><VALUE.ARRAY><VALUE>&#8;</VALUE><VALUE>&#16;</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_CHAR16,{PAL_T("\x8"), PAL_T("\x10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint8\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint8\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>10</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_UINT8,{PAL_T("1"), PAL_T("10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"sint8\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint8\"><VALUE.ARRAY><VALUE>-1</VALUE><VALUE>1</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_SINT8,{PAL_T("-1"), PAL_T("1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint16\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint16\"><VALUE.ARRAY><VALUE>2</VALUE><VALUE>20</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_UINT16,{PAL_T("2"), PAL_T("20")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"sint16\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint16\"><VALUE.ARRAY><VALUE>-2</VALUE><VALUE>2</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_SINT16,{PAL_T("-2"), PAL_T("2")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint32\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint32\"><VALUE.ARRAY><VALUE>3</VALUE><VALUE>30</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_UINT32,{PAL_T("3"), PAL_T("30")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"sint32\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint32\"><VALUE.ARRAY><VALUE>-3</VALUE><VALUE>3</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_SINT32,{PAL_T("-3"), PAL_T("3")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint64\"><QUALIFIER NAME=\"qual1\" TYPE=\"uint64\"><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_UINT64,{PAL_T("4"), PAL_T("40")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"sint64\"><QUALIFIER NAME=\"qual1\" TYPE=\"sint64\"><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_SINT64,{PAL_T("-4"), PAL_T("4")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"datetime\"><QUALIFIER NAME=\"qual1\" TYPE=\"datetime\"><VALUE.ARRAY><VALUE>20110314222412.000000+008</VALUE><VALUE>20110314222412.000000+008</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_DATETIME,{PAL_T("20110314222412.000000+008"), PAL_T("20110314222412.000000+008")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"real32\"><QUALIFIER NAME=\"qual1\" TYPE=\"real32\"><VALUE.ARRAY><VALUE>1.1000000e+00</VALUE><VALUE>-1.1000000e+00</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_REAL32,{PAL_T("1.1"), PAL_T("-1.1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"><PARAMETER NAME=\"param1\" TYPE=\"real64\"><QUALIFIER NAME=\"qual1\" TYPE=\"real64\"><VALUE.ARRAY><VALUE>2.2000000000000002e+00</VALUE><VALUE>-2.2000000000000002e+00</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>"),MI_REAL64,{PAL_T("2.2"), PAL_T("-2.2")}}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_QualifierSet qs;
                    MI_ParameterSet ps;
                    MI_Uint32 qsCount;
                    MI_Uint32 psCount;
                    MI_Uint32 methodCount;

                    if (NitsCompare(MI_Class_GetMethodCount(newClass, &methodCount), MI_RESULT_OK, PAL_T("method count")) &&
                        NitsCompare(methodCount, 1, PAL_T("method count=1")) &&
                        NitsCompare(MI_Class_GetMethodAt(newClass, 0, &resultName, &qs, &ps), MI_RESULT_OK, PAL_T("Get class qualifier set")) &&
                        NitsAssert(resultName!=NULL, PAL_T("name should exist")) &&
                        NitsCompareString(resultName, PAL_T("Method1"), PAL_T("method name")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")) &&
                        NitsCompare(MI_ParameterSet_GetParameterCount(&ps, &psCount), MI_RESULT_OK, PAL_T("parameterSetCount")) &&
                        NitsCompare(psCount, 1, PAL_T("no parameter")) &&
                        NitsCompare(MI_ParameterSet_GetParameterAt(&ps, 0, &resultName, &resultType, NULL, &qs), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("param1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type, PAL_T("Qualifier type")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("parameter qs")) &&
                        NitsCompare(qsCount, 2, PAL_T("qualifier count ")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierAt(&qs, 0, &resultName, &resultType, &resultFlags, &resultValue), MI_RESULT_OK, PAL_T("QualifierSet details")) &&
                        resultName &&
                        NitsCompareString(resultName, PAL_T("qual1"), PAL_T("qualifierset name")) &&
                        NitsCompare(resultType, testData[i].type|MI_ARRAY, PAL_T("Qualifier type")) &&
                        NitsCompare(resultFlags, MI_FLAG_TOSUBCLASS|MI_FLAG_ENABLEOVERRIDE, PAL_T("QualifierSet flags")) &&
                        CompareMiValueArray(&resultValue, resultType, testData[i].value, 2, NitsHere()) &&
                        NitsCompare(MI_ParameterSet_GetMethodReturnType(&ps, &resultType, &qs), MI_RESULT_OK, PAL_T("Return type"))&&
                        NitsCompare(resultType, testData[i].type, PAL_T("return type")) &&
                        NitsCompare(MI_QualifierSet_GetQualifierCount(&qs, &qsCount), MI_RESULT_OK, PAL_T("Get qualifierset count for parameter")) &&
                        NitsCompare(qsCount, 0, PAL_T("qualifier count ")))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Instance_Prop_None)
    const MI_Char *emptyClass = PAL_T("<CLASS NAME=\"myClass\"></CLASS>");
    const MI_Char *emptyClassInstance = PAL_T("<INSTANCE CLASSNAME=\"myClass\"></INSTANCE>");
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;

        if (NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer")))
        {
            MI_Class *newClass = NULL;
            MI_Uint32 deserializeSize;
            if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)emptyClass, Tcslen(emptyClass)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, PAL_T("successfully deserialize")))
            {
                MI_Instance *newInstance = NULL;
                if (NitsCompare(XmlDeserializer_DeserializeInstance(&deserializer, 0, (MI_Uint8*)emptyClassInstance, Tcslen(emptyClassInstance)*(sizeof(MI_Char)), &newClass, 1, NULL, NULL, &deserializeSize, &newInstance, NULL), MI_RESULT_OK, PAL_T("Deserialize class")))
                {
                    NitsCompare(MI_Instance_Delete(newInstance), MI_RESULT_OK, PAL_T("Deleting instance"));
                }
                NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Instance_Prop_None_InvalidParameters)
    const MI_Char *emptyClass = PAL_T("<CLASS NAME=\"myClass\"></CLASS>");
    ValidationError testData[] =
    {
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"></INSTANCE>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<hello CLASSNAME=\"myClass\"></hello>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<INSTANCE hello=\"myClass\"></INSTANCE>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<INSTANCE CLASSNAME=\"hello\"></INSTANCE>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<INSTANCE ></INSTANCE>"), MI_RESULT_INVALID_PARAMETER}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;

        if (NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer")))
        {
            MI_Class *newClass = NULL;
            MI_Uint32 deserializeSize;
            if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)emptyClass, Tcslen(emptyClass)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, PAL_T("successfully deserialize")))
            {
                MI_Instance *newInstance = NULL;
                MI_Uint32 i;

                NitsCompare(XmlDeserializer_DeserializeInstance(NULL, 0, (MI_Uint8*)testData[0].XML, Tcslen(testData[0].XML)*(sizeof(MI_Char)), &newClass, 1, NULL, NULL, &deserializeSize, &newInstance, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("invalid parameters"));
                NitsCompare(XmlDeserializer_DeserializeInstance(&deserializer, 99, (MI_Uint8*)testData[0].XML, Tcslen(testData[0].XML)*(sizeof(MI_Char)), &newClass, 1, NULL, NULL, &deserializeSize, &newInstance, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("invalid parameters"));
                NitsCompare(XmlDeserializer_DeserializeInstance(&deserializer, 0, NULL, Tcslen(testData[0].XML)*(sizeof(MI_Char)), &newClass, 1, NULL, NULL, &deserializeSize, &newInstance, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("invalid parameters"));
                NitsCompare(XmlDeserializer_DeserializeInstance(&deserializer, 0, (MI_Uint8*)testData[0].XML, Tcslen(testData[0].XML)*(sizeof(MI_Char)), NULL, 0, NULL, NULL, &deserializeSize, &newInstance, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("invalid parameters"));
                NitsCompare(XmlDeserializer_DeserializeInstance(&deserializer, 0, (MI_Uint8*)testData[0].XML, Tcslen(testData[0].XML)*(sizeof(MI_Char)), &newClass, 1, NULL, NULL, &deserializeSize, NULL, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("invalid parameters"));

                for (i = 1; i < sizeof(testData)/sizeof(testData[0]); i++)
                {
                    NitsCompare(XmlDeserializer_DeserializeInstance(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), &newClass, 1, NULL, NULL, &deserializeSize, &newInstance, NULL), testData[i].result, PAL_T("invalid parameters"));
                }

                NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Instance_Prop_Simple_Validate)
    const ValidationData testDataClasses[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></CLASS>"), MI_BOOLEAN, PAL_T("true")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"string\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></PROPERTY></CLASS>"), MI_STRING, PAL_T("hello&'><\"")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"char16\"><VALUE>&#8;</VALUE></PROPERTY></CLASS>"), MI_CHAR16, PAL_T("\x8")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint8\"><VALUE>1</VALUE></PROPERTY></CLASS>"), MI_UINT8, PAL_T("1")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint8\"><VALUE>-1</VALUE></PROPERTY></CLASS>"), MI_SINT8, PAL_T("-1")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint16\"><VALUE>2</VALUE></PROPERTY></CLASS>"), MI_UINT16, PAL_T("2")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint16\"><VALUE>-2</VALUE></PROPERTY></CLASS>"), MI_SINT16, PAL_T("-2")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint32\"><VALUE>3</VALUE></PROPERTY></CLASS>"), MI_UINT32, PAL_T("3")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint32\"><VALUE>-3</VALUE></PROPERTY></CLASS>"), MI_SINT32, PAL_T("-3")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint64\"><VALUE>4</VALUE></PROPERTY></CLASS>"),  MI_UINT64, PAL_T("4")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint64\"><VALUE>-4</VALUE></PROPERTY></CLASS>"), MI_SINT64, PAL_T("-4")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"datetime\"><VALUE>20110314222412.000000+008</VALUE></PROPERTY></CLASS>"), MI_DATETIME, PAL_T("20110314222412.000000+008")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real32\"><VALUE>1.1000000e+00</VALUE></PROPERTY></CLASS>"), MI_REAL32, PAL_T("1.1")},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real64\"><VALUE>2.2000000000000002e+00</VALUE></PROPERTY></CLASS>"), MI_REAL64, PAL_T("2.2")}
    };
    const ValidationData testDataInstances[] =
    {
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></INSTANCE>"), MI_BOOLEAN, PAL_T("true")},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"string\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></PROPERTY></INSTANCE>"), MI_STRING, PAL_T("hello&'><\"")},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"char16\"><VALUE>&#8;</VALUE></PROPERTY></INSTANCE>"), MI_CHAR16, PAL_T("\x8")},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint8\"><VALUE>1</VALUE></PROPERTY></INSTANCE>"), MI_UINT8, PAL_T("1")},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint8\"><VALUE>-1</VALUE></PROPERTY></INSTANCE>"), MI_SINT8, PAL_T("-1")},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint16\"><VALUE>2</VALUE></PROPERTY></INSTANCE>"), MI_UINT16, PAL_T("2")},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint16\"><VALUE>-2</VALUE></PROPERTY></INSTANCE>"), MI_SINT16, PAL_T("-2")},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint32\"><VALUE>3</VALUE></PROPERTY></INSTANCE>"), MI_UINT32, PAL_T("3")},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint32\"><VALUE>-3</VALUE></PROPERTY></INSTANCE>"), MI_SINT32, PAL_T("-3")},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint64\"><VALUE>4</VALUE></PROPERTY></INSTANCE>"),  MI_UINT64, PAL_T("4")},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint64\"><VALUE>-4</VALUE></PROPERTY></INSTANCE>"), MI_SINT64, PAL_T("-4")},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"datetime\"><VALUE>20110314222412.000000+008</VALUE></PROPERTY></INSTANCE>"), MI_DATETIME, PAL_T("20110314222412.000000+008")},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real32\"><VALUE>1.1000000e+00</VALUE></PROPERTY></INSTANCE>"), MI_REAL32, PAL_T("1.1")},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real64\"><VALUE>2.2000000000000002e+00</VALUE></PROPERTY></INSTANCE>"), MI_REAL64, PAL_T("2.2")}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testDataClasses)/sizeof(testDataClasses[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testDataClasses[i].XML, Tcslen(testDataClasses[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testDataClasses[i].XML))
                {
                    MI_Instance *newInstance = NULL;
                    if (NitsCompare(XmlDeserializer_DeserializeInstance(&deserializer, 0, (MI_Uint8*)testDataInstances[i].XML, Tcslen(testDataInstances[i].XML)*(sizeof(MI_Char)), &newClass, 1, NULL, NULL, &deserializeSize, &newInstance, NULL), MI_RESULT_OK, PAL_T("Deserialize class")))
                    {
                        const MI_Char* resultName = NULL;
                        MI_Value resultValue;
                        MI_Type resultType;
                        MI_Uint32 resultFlags;

                        if (NitsCompare(MI_Instance_GetElementAt(newInstance, 0, &resultName, &resultValue, &resultType, &resultFlags), MI_RESULT_OK, PAL_T("Get property value should work")) &&
                            NitsCompare(Tcscmp(resultName, PAL_T("prop1")), 0, PAL_T("propertyName should be prop1")) &&
                            NitsCompare(resultType, testDataInstances[i].type, PAL_T("Types should match")) &&
                            NitsCompare(resultFlags, MI_FLAG_PROPERTY | MI_FLAG_NOT_MODIFIED, PAL_T("Flags should be MI_FLAG_PROPERTY")) &&
                            NitsCompare(CompareMiValue(&resultValue, resultType, testDataInstances[i].value, NitsHere()), MI_TRUE, PAL_T("compare value")))
                        {
                            MI_Uint32 bufferUsed = 0;
                            if (NitsCompare(XmlSerializer_SerializeInstance(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newInstance, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                            {
                                SerializerTestCompare(serializedBuffer, testDataInstances[i].XML, NitsHere());
                            }
                        }
                        NitsCompare(MI_Instance_Delete(newInstance), MI_RESULT_OK, PAL_T("Deleting instance"));
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Instance_Prop_Array_Validate)
    ValidationDataArray testDataClasses[] =
    {
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_BOOLEAN,{PAL_T("true"), PAL_T("false")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"string\"><VALUE.ARRAY><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE><VALUE>goodbye</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_STRING,{PAL_T("hello&'><\""), PAL_T("goodbye")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"char16\"><VALUE.ARRAY><VALUE>&#8;</VALUE><VALUE>&#16;</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_CHAR16,{PAL_T("\x8"), PAL_T("\x10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint8\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>10</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT8,{PAL_T("1"), PAL_T("10")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint8\"><VALUE.ARRAY><VALUE>-1</VALUE><VALUE>1</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT8,{PAL_T("-1"), PAL_T("1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint16\"><VALUE.ARRAY><VALUE>2</VALUE><VALUE>20</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT16,{PAL_T("2"), PAL_T("20")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint16\"><VALUE.ARRAY><VALUE>-2</VALUE><VALUE>2</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT16,{PAL_T("-2"), PAL_T("2")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint32\"><VALUE.ARRAY><VALUE>3</VALUE><VALUE>30</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT32,{PAL_T("3"), PAL_T("30")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint32\"><VALUE.ARRAY><VALUE>-3</VALUE><VALUE>3</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT32,{PAL_T("-3"), PAL_T("3")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint64\"><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_UINT64,{PAL_T("4"), PAL_T("40")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint64\"><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_SINT64,{PAL_T("-4"), PAL_T("4")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"datetime\"><VALUE.ARRAY><VALUE>20110314222412.000000+008</VALUE><VALUE>20110314222412.000000+008</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_DATETIME,{PAL_T("20110314222412.000000+008"), PAL_T("20110314222412.000000+008")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"real32\"><VALUE.ARRAY><VALUE>1.1000000e+00</VALUE><VALUE>-1.1000000e+00</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_REAL32,{PAL_T("1.1"), PAL_T("-1.1")}},
        {PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"real64\"><VALUE.ARRAY><VALUE>2.2000000000000002e+00</VALUE><VALUE>-2.2000000000000002e+00</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),MI_REAL64,{PAL_T("2.2"), PAL_T("-2.2")}}
    };
    ValidationDataArray testDataInstances[] =
    {
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"),MI_BOOLEAN,{PAL_T("true"), PAL_T("false")}},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"string\"><VALUE.ARRAY><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE><VALUE>goodbye</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"),MI_STRING,{PAL_T("hello&'><\""), PAL_T("goodbye")}},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"char16\"><VALUE.ARRAY><VALUE>&#8;</VALUE><VALUE>&#16;</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"),MI_CHAR16,{PAL_T("\x8"), PAL_T("\x10")}},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint8\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>10</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"),MI_UINT8,{PAL_T("1"), PAL_T("10")}},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint8\"><VALUE.ARRAY><VALUE>-1</VALUE><VALUE>1</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"),MI_SINT8,{PAL_T("-1"), PAL_T("1")}},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint16\"><VALUE.ARRAY><VALUE>2</VALUE><VALUE>20</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"),MI_UINT16,{PAL_T("2"), PAL_T("20")}},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint16\"><VALUE.ARRAY><VALUE>-2</VALUE><VALUE>2</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"),MI_SINT16,{PAL_T("-2"), PAL_T("2")}},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint32\"><VALUE.ARRAY><VALUE>3</VALUE><VALUE>30</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"),MI_UINT32,{PAL_T("3"), PAL_T("30")}},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint32\"><VALUE.ARRAY><VALUE>-3</VALUE><VALUE>3</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"),MI_SINT32,{PAL_T("-3"), PAL_T("3")}},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint64\"><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"),MI_UINT64,{PAL_T("4"), PAL_T("40")}},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint64\"><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"),MI_SINT64,{PAL_T("-4"), PAL_T("4")}},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"datetime\"><VALUE.ARRAY><VALUE>20110314222412.000000+008</VALUE><VALUE>20110314222412.000000+008</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"),MI_DATETIME,{PAL_T("20110314222412.000000+008"), PAL_T("20110314222412.000000+008")}},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"real32\"><VALUE.ARRAY><VALUE>1.1000000e+00</VALUE><VALUE>-1.1000000e+00</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"),MI_REAL32,{PAL_T("1.1"), PAL_T("-1.1")}},
        {PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"real64\"><VALUE.ARRAY><VALUE>2.2000000000000002e+00</VALUE><VALUE>-2.2000000000000002e+00</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>"),MI_REAL64,{PAL_T("2.2"), PAL_T("-2.2")}}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testDataClasses)/sizeof(testDataClasses[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Uint32 deserializeSize;
                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testDataClasses[i].XML, Tcslen(testDataClasses[i].XML)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL), MI_RESULT_OK, testDataClasses[i].XML))
                {
                    MI_Instance *newInstance = NULL;
                    if (NitsCompare(XmlDeserializer_DeserializeInstance(&deserializer, 0, (MI_Uint8*)testDataInstances[i].XML, Tcslen(testDataInstances[i].XML)*(sizeof(MI_Char)), &newClass, 1, NULL, NULL, &deserializeSize, &newInstance, NULL), MI_RESULT_OK, PAL_T("Deserialize instance")))
                    {
                        const MI_Char* resultName = NULL;
                        MI_Value resultValue;
                        MI_Type resultType;
                        MI_Uint32 resultFlags;

                        if (NitsCompare(MI_Instance_GetElementAt(newInstance, 0, &resultName, &resultValue, &resultType, &resultFlags), MI_RESULT_OK, PAL_T("Get property value should work")) &&
                            resultName &&
                            NitsCompare(Tcscmp(resultName, PAL_T("prop1")), 0, PAL_T("propertyName should be prop1")) &&
                            NitsCompare(resultType, testDataInstances[i].type|MI_ARRAY, PAL_T("Types should match")) &&
                            NitsAssert(resultFlags & MI_FLAG_PROPERTY, PAL_T("Flags should be MI_FLAG_PROPERTY")) &&
                            NitsCompare(resultValue.booleana.size, 2, PAL_T("array size should be 2")) &&
                            CompareMiValueArray(&resultValue, resultType, testDataInstances[i].value, 2, NitsHere()))
                        {
                            MI_Uint32 bufferUsed = 0;
                            if (NitsCompare(XmlSerializer_SerializeInstance(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newInstance, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                            {
                                SerializerTestCompare(serializedBuffer, testDataInstances[i].XML, NitsHere());
                            }
                        }
                        NitsCompare(MI_Instance_Delete(newInstance), MI_RESULT_OK, PAL_T("Deleting instance"));
                    }
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("close class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_ClassAndInstance_Prop_Simple_Validate)
    const ValidationData testData[] =
    {
        //Properties in derived class
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_BOOLEAN, PAL_T("true")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"string\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_STRING, PAL_T("hello&'><\"")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"char16\"><VALUE>&#8;</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_CHAR16, PAL_T("\x8")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint8\"><VALUE>1</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_UINT8, PAL_T("1")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint8\"><VALUE>-1</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT8, PAL_T("-1")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint16\"><VALUE>2</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_UINT16, PAL_T("2")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint16\"><VALUE>-2</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT16, PAL_T("-2")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint32\"><VALUE>3</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_UINT32, PAL_T("3")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint32\"><VALUE>-3</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT32, PAL_T("-3")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint64\"><VALUE>4</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"),  MI_UINT64, PAL_T("4")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint64\"><VALUE>-4</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT64, PAL_T("-4")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"datetime\"><VALUE>20110314222412.000000+008</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_DATETIME, PAL_T("20110314222412.000000+008")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real32\"><VALUE>1.1000000e+00</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_REAL32, PAL_T("1.1")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real64\"><VALUE>2.2000000000000002e+00</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_REAL64, PAL_T("2.2")},

        //Properties in base class
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"baseClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_BOOLEAN, PAL_T("true")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"string\" CLASSORIGIN=\"baseClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"string\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_STRING, PAL_T("hello&'><\"")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"char16\" CLASSORIGIN=\"baseClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"char16\"><VALUE>&#8;</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_CHAR16, PAL_T("\x8")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint8\" CLASSORIGIN=\"baseClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint8\"><VALUE>1</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_UINT8, PAL_T("1")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint8\" CLASSORIGIN=\"baseClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint8\"><VALUE>-1</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT8, PAL_T("-1")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint16\" CLASSORIGIN=\"baseClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint16\"><VALUE>2</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_UINT16, PAL_T("2")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint16\" CLASSORIGIN=\"baseClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint16\"><VALUE>-2</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT16, PAL_T("-2")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint32\" CLASSORIGIN=\"baseClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint32\"><VALUE>3</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_UINT32, PAL_T("3")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint32\" CLASSORIGIN=\"baseClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint32\"><VALUE>-3</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT32, PAL_T("-3")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint64\" CLASSORIGIN=\"baseClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint64\"><VALUE>4</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"),  MI_UINT64, PAL_T("4")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint64\" CLASSORIGIN=\"baseClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint64\"><VALUE>-4</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT64, PAL_T("-4")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"datetime\" CLASSORIGIN=\"baseClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"datetime\"><VALUE>20110314222412.000000+008</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_DATETIME, PAL_T("20110314222412.000000+008")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real32\" CLASSORIGIN=\"baseClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real32\"><VALUE>1.1000000e+00</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_REAL32, PAL_T("1.1")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real64\" CLASSORIGIN=\"baseClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real64\"><VALUE>2.2000000000000002e+00</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_REAL64, PAL_T("2.2")},

        //No derived class
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_BOOLEAN, PAL_T("true")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"string\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_STRING, PAL_T("hello&'><\"")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"char16\"><VALUE>&#8;</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_CHAR16, PAL_T("\x8")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint8\"><VALUE>1</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_UINT8, PAL_T("1")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint8\"><VALUE>-1</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT8, PAL_T("-1")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint16\"><VALUE>2</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_UINT16, PAL_T("2")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint16\"><VALUE>-2</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT16, PAL_T("-2")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint32\"><VALUE>3</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_UINT32, PAL_T("3")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint32\"><VALUE>-3</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT32, PAL_T("-3")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"uint64\"><VALUE>4</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"),  MI_UINT64, PAL_T("4")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"sint64\"><VALUE>-4</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT64, PAL_T("-4")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"datetime\"><VALUE>20110314222412.000000+008</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_DATETIME, PAL_T("20110314222412.000000+008")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real32\"><VALUE>1.1000000e+00</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_REAL32, PAL_T("1.1")},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"real64\"><VALUE>2.2000000000000002e+00</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_REAL64, PAL_T("2.2")}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Instance *newInstance = NULL;
                MI_Instance *clonedInstance = NULL;
                MI_Uint32 deserializeSize;

                if (NitsCompare(XmlDeserializer_DeserializeInstance(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, 0, NULL, NULL, &deserializeSize, &newInstance, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;

                    if (NitsCompare(MI_Instance_GetElementAt(newInstance, 0, &resultName, &resultValue, &resultType, &resultFlags), MI_RESULT_OK, PAL_T("Get property value should work")) &&
                        resultName &&
                        NitsCompare(Tcscmp(resultName, PAL_T("prop1")), 0, PAL_T("propertyName should be prop1")) &&
                        NitsCompare(resultType, testData[i].type, PAL_T("Types should match")) &&
                        NitsCompare(resultFlags, MI_FLAG_PROPERTY | MI_FLAG_NOT_MODIFIED, PAL_T("Flags should be MI_FLAG_PROPERTY")) &&
                        NitsCompare(CompareMiValue(&resultValue, resultType, testData[i].value, NitsHere()), MI_TRUE, testData[i].XML))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeInstance(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS |MI_SERIALIZER_FLAGS_INSTANCE_WITH_CLASS, newInstance, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    if (NitsCompare(MI_Instance_Clone(newInstance, &clonedInstance), MI_RESULT_OK, PAL_T("Clone should succeed")))
                    {
                        NitsCompare(MI_Instance_Delete(clonedInstance), MI_RESULT_OK, PAL_T("Deleting instance"));
                    }
                    NitsCompare(MI_Instance_Delete(newInstance), MI_RESULT_OK, PAL_T("Deleting instance"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_ClassAndInstance_Prop_Simple_InvalidXML)
    ValidationError testData[] =
    {
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"></CIM>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION></DECLARATION></CIM>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP></DECLGROUP></DECLARATION></CIM>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY></CLASS></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"hello\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS ><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"hello\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_RESULT_INVALID_PARAMETER},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"base\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_RESULT_INVALID_PARAMETER}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;

        if (NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer")))
        {
            MI_Instance *newInstance = NULL;
            MI_Uint32 i;
            for (i = 0; i != sizeof(testData)/sizeof(testData[0]);i++)
            {
                MI_Uint32 deserializeSize;
                NitsCompare(XmlDeserializer_DeserializeInstance(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, 0, NULL, NULL, &deserializeSize, &newInstance, NULL), testData[i].result, PAL_T("invalid XML"));
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_ClassAndInstance_Prop_Array_Validate)
    const ValidationData testData[] =
    {
        //Properties in derived class, null values
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY></VALUE.ARRAY></PROPERTY.ARRAY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY.ARRAY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_BOOLEAN, NULL},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY></VALUE.ARRAY></PROPERTY.ARRAY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"string\"></PROPERTY.ARRAY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_STRING, NULL},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"char16\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY></VALUE.ARRAY></PROPERTY.ARRAY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"char16\"></PROPERTY.ARRAY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_CHAR16, NULL},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint8\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY></VALUE.ARRAY></PROPERTY.ARRAY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint8\"></PROPERTY.ARRAY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_UINT8, NULL},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint8\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY></VALUE.ARRAY></PROPERTY.ARRAY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint8\"></PROPERTY.ARRAY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT8, NULL},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint16\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY></VALUE.ARRAY></PROPERTY.ARRAY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint16\"></PROPERTY.ARRAY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_UINT16, NULL},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint16\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY></VALUE.ARRAY></PROPERTY.ARRAY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint16\"></PROPERTY.ARRAY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT16, NULL},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint32\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY></VALUE.ARRAY></PROPERTY.ARRAY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint32\"></PROPERTY.ARRAY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_UINT32, NULL},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint32\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY></VALUE.ARRAY></PROPERTY.ARRAY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint32\"></PROPERTY.ARRAY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT32, NULL},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint64\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY></VALUE.ARRAY></PROPERTY.ARRAY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"uint64\"></PROPERTY.ARRAY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"),  MI_UINT64, NULL},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint64\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY></VALUE.ARRAY></PROPERTY.ARRAY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"sint64\"></PROPERTY.ARRAY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_SINT64, NULL},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"datetime\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY></VALUE.ARRAY></PROPERTY.ARRAY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"datetime\"></PROPERTY.ARRAY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_DATETIME, NULL},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"real32\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY></VALUE.ARRAY></PROPERTY.ARRAY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"real32\"></PROPERTY.ARRAY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_REAL32, NULL},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"real64\" CLASSORIGIN=\"myClass\"><VALUE.ARRAY></VALUE.ARRAY></PROPERTY.ARRAY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"real64\"></PROPERTY.ARRAY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_REAL64, NULL},
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Instance *newInstance = NULL;
                MI_Instance *cloneInstance = NULL;
                MI_Uint32 deserializeSize;

                if (NitsCompare(XmlDeserializer_DeserializeInstance(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, 0, NULL, NULL, &deserializeSize, &newInstance, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;

                    if (NitsCompare(MI_Instance_GetElementAt(newInstance, 0, &resultName, &resultValue, &resultType, &resultFlags), MI_RESULT_OK, PAL_T("Get property value should work")) &&
                        resultName &&
                        NitsCompare(Tcscmp(resultName, PAL_T("prop1")), 0, PAL_T("propertyName should be prop1")) &&
                        NitsCompare(resultType, testData[i].type|MI_ARRAY, PAL_T("Types should match")) &&
                        NitsCompare(resultFlags, MI_FLAG_PROPERTY|MI_FLAG_NULL|MI_FLAG_NOT_MODIFIED, PAL_T("Flags should be MI_FLAG_PROPERTY")) &&
                        ((testData[i].value == NULL) ||
                         NitsCompare(CompareMiValue(&resultValue, resultType, testData[i].value, NitsHere()), MI_TRUE, testData[i].XML)))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeInstance(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS | MI_SERIALIZER_FLAGS_INSTANCE_WITH_CLASS, newInstance, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    if (NitsCompare(MI_Instance_Clone(newInstance, &cloneInstance), MI_RESULT_OK, PAL_T("Clone should succeed")))
                    {
                        NitsCompare(MI_Instance_Delete(cloneInstance), MI_RESULT_OK, PAL_T("Deleting instance"));
                    }
                    NitsCompare(MI_Instance_Delete(newInstance), MI_RESULT_OK, PAL_T("Deleting instance"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_ClassAndInstance_EmbeddedObjects)
    const ValidationData testData[] =
    {
        //No derived class
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP>")
        PAL_T("<VALUE.OBJECT><CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"string\" CLASSORIGIN=\"myClass\"><QUALIFIER NAME=\"EMBEDDEDINSTANCE\" TYPE=\"string\"><VALUE>embeddedClass</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT>")
        PAL_T("<VALUE.OBJECT><CLASS NAME=\"embeddedClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" CLASSORIGIN=\"embeddedClass\"></PROPERTY></CLASS></VALUE.OBJECT>")
        PAL_T("<VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"string\" EmbeddedObject=\"instance\" EmbeddedClassName=\"embeddedClass\"><VALUE>")
        PAL_T("&lt;INSTANCE CLASSNAME=&quot;embeddedClass&quot;&gt;&lt;PROPERTY NAME=&quot;prop1&quot; TYPE=&quot;boolean&quot;&gt;&lt;VALUE&gt;true&lt;/VALUE&gt;&lt;/PROPERTY&gt;&lt;/INSTANCE&gt;") 
        PAL_T("</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_BOOLEAN, PAL_T("true")}
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Instance *newInstance = NULL;
                MI_Uint32 deserializeSize;

                if (NitsCompare(XmlDeserializer_DeserializeInstance(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, 0, NULL, NULL, &deserializeSize, &newInstance, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    const MI_Char *className = NULL;

                    if (NitsCompare(MI_Instance_GetElementAt(newInstance, 0, &resultName, &resultValue, &resultType, &resultFlags), MI_RESULT_OK, PAL_T("Get property value should work")) &&
                        resultName &&
                        NitsCompare(Tcscmp(resultName, PAL_T("prop1")), 0, PAL_T("propertyName should be prop1")) &&
                        NitsCompare(resultType, MI_INSTANCE, PAL_T("Types should be instance")) &&
                        NitsCompare(resultFlags, MI_FLAG_PROPERTY | MI_FLAG_NOT_MODIFIED, PAL_T("Flags should be MI_FLAG_PROPERTY")) &&
                        NitsAssert(resultValue.instance != NULL, PAL_T("Should have an instance")) &&
                        NitsCompare(MI_Instance_GetClassName(resultValue.instance, &className), MI_RESULT_OK, PAL_T("Get embedded instances class name")) &&
                        NitsCompareString(className, PAL_T("embeddedClass"), PAL_T("embedded instance class name should match")) &&
                        NitsCompare(MI_Instance_GetElementAt(resultValue.instance, 0, &resultName, &resultValue, &resultType, &resultFlags), MI_RESULT_OK, PAL_T("Get property value on embedded object should work")) &&
                        resultName &&
                        NitsCompare(Tcscmp(resultName, PAL_T("prop1")), 0, PAL_T("propertyName should be prop1")) &&
                        NitsCompare(resultType, testData[i].type, PAL_T("Types should in embedded instance should match")) &&
                        NitsCompare(resultFlags, MI_FLAG_PROPERTY | MI_FLAG_NOT_MODIFIED, PAL_T("Flags should be MI_FLAG_PROPERTY")) &&
                        NitsCompare(CompareMiValue(&resultValue, resultType, testData[i].value, NitsHere()), MI_TRUE, testData[i].XML))
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeInstance(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS | MI_SERIALIZER_FLAGS_INSTANCE_WITH_CLASS, newInstance, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    NitsCompare(MI_Instance_Delete(newInstance), MI_RESULT_OK, PAL_T("Deleting instance"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Class_References)
    const MI_Char *XYZ_Link = PAL_T("<CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\" CLASSORIGIN=\"XYZ_Link\"></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\" CLASSORIGIN=\"XYZ_Link\"></PROPERTY.REFERENCE></CLASS>");
    MI_Application application = MI_APPLICATION_NULL;
    
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            {
                MI_Class *assocClass= NULL;
                MI_Uint32 deserializeSize;

                if (NitsCompare(XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)XYZ_Link, Tcslen(XYZ_Link)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &assocClass, NULL), MI_RESULT_OK, XYZ_Link))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;
                    MI_Boolean resultExists;
                    MI_QualifierSet qs;

                    if (NitsCompare(MI_Class_GetElementAt(assocClass, 0, &resultName, &resultValue, &resultExists, &resultType, NULL, &qs, &resultFlags), MI_RESULT_OK, PAL_T("Get property value should work")) &&
                        NitsCompare(resultType, MI_REFERENCE, PAL_T("property should be reference")) &&
                        NitsCompare(MI_Class_GetElementAt(assocClass, 1, &resultName, &resultValue, &resultExists, &resultType, NULL, &qs, &resultFlags), MI_RESULT_OK, PAL_T("Get property value should work")) &&
                        NitsCompare(resultType, MI_REFERENCE, PAL_T("property should be reference")) &&
                        NitsAssert(Tcscmp(assocClass->classDecl->properties[0]->className, PAL_T("XYZ_Widget")) == 0, PAL_T("Prop 0 assoc class not correct")) &&
                        NitsAssert(Tcscmp(assocClass->classDecl->properties[1]->className, PAL_T("XYZ_Gadget")) == 0, PAL_T("Prop 1 assoc class not correct")))

                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeClass(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, assocClass, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, XYZ_Link, NitsHere());
                        }
                    }
                    NitsCompare(MI_Class_Delete(assocClass), MI_RESULT_OK, PAL_T("Deleting instance"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_ClassAndInstance_References)
    const ValidationData testData[] =
    {
        //Strongly typed
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\" CLASSORIGIN=\"XYZ_Link\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\" CLASSORIGIN=\"XYZ_Link\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\" CLASSORIGIN=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\" CLASSORIGIN=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_REFERENCE, NULL},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\" CLASSORIGIN=\"XYZ_Link\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\" CLASSORIGIN=\"XYZ_Link\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\" CLASSORIGIN=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Id2\" TYPE=\"string\" CLASSORIGIN=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\" CLASSORIGIN=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYBINDING NAME=\"Id\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING><KEYBINDING NAME=\"Id2\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_REFERENCE, NULL},
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\" CLASSORIGIN=\"XYZ_Link\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\" CLASSORIGIN=\"XYZ_Link\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\" CLASSORIGIN=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Id2\" TYPE=\"string\" CLASSORIGIN=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\" CLASSORIGIN=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCEPATH><NAMESPACEPATH><HOST>localhost2</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv1\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYBINDING NAME=\"Id\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING><KEYBINDING NAME=\"Id2\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING></INSTANCENAME></INSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><LOCALINSTANCEPATH><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv3\"/></LOCALNAMESPACEPATH><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></LOCALINSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_REFERENCE, NULL},
//TODO: This one causes extra namespace information to get serialized, but other than that it seems to work... disabling until can work out what is causing the namespaces to get serialized.
//        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_LinkLink\"><PROPERTY.REFERENCE NAME=\"Link1\" REFERENCECLASS=\"XYZ_Link\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Link2\" REFERENCECLASS=\"XYZ_Link\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Id2\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_LinkLink\"><PROPERTY.REFERENCE NAME=\"Link1\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Link\"><KEYBINDING NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYBINDING NAME=\"Id\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING><KEYBINDING NAME=\"Id2\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING></INSTANCENAME></VALUE.REFERENCE></KEYBINDING><KEYBINDING NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></KEYBINDING></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Link2\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Link\"><KEYBINDING NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYBINDING NAME=\"Id\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING><KEYBINDING NAME=\"Id2\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING></INSTANCENAME></VALUE.REFERENCE></KEYBINDING><KEYBINDING NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></KEYBINDING></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_REFERENCE, NULL},

        //Weakly typed
        {PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" CLASSORIGIN=\"XYZ_Link\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" CLASSORIGIN=\"XYZ_Link\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\" CLASSORIGIN=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\" CLASSORIGIN=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), MI_REFERENCE, NULL},
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Instance *newInstance = NULL;
                MI_Instance *cloneInstance = NULL;
                MI_Uint32 deserializeSize;

                if (NitsCompare(XmlDeserializer_DeserializeInstance(&deserializer, 0, (MI_Uint8*)testData[i].XML, Tcslen(testData[i].XML)*(sizeof(MI_Char)), NULL, 0, NULL, NULL, &deserializeSize, &newInstance, NULL), MI_RESULT_OK, testData[i].XML))
                {
                    const MI_Char* resultName = NULL;
                    MI_Value resultValue;
                    MI_Type resultType;
                    MI_Uint32 resultFlags;

                    if (NitsCompare(MI_Instance_GetElementAt(newInstance, 0, &resultName, &resultValue, &resultType, &resultFlags), MI_RESULT_OK, PAL_T("Get property value should work")) &&
                        resultName &&
//                        NitsCompare(resultName, PAL_T("Left"), PAL_T("propertyName should be Left")) &&
                        NitsCompare(resultType, MI_REFERENCE, PAL_T("Types should match")) &&
                        NitsCompare(resultFlags, MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_NOT_MODIFIED, PAL_T("Flags should be MI_FLAG_PROPERTY")) &&
                        NitsAssert(resultValue.reference != NULL, PAL_T("Should have reference property")) &&
//                        NitsCompare(resultValue.reference->classDecl->name, PAL_T("XYZ_Widget"), PAL_T("Left instance class should be XYZ_Widget")) &&
                        
                        NitsCompare(MI_Instance_GetElementAt(newInstance, 1, &resultName, &resultValue, &resultType, &resultFlags), MI_RESULT_OK, PAL_T("Get property value should work")) &&
                        resultName &&
//                        NitsCompare(resultName, PAL_T("Right"), PAL_T("propertyName should be Right")) &&
                        NitsCompare(resultType, MI_REFERENCE, PAL_T("Types should match")) &&
                        NitsCompare(resultFlags, MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_NOT_MODIFIED, PAL_T("Flags should be MI_FLAG_PROPERTY")) &&
                        NitsAssert(resultValue.reference != NULL, PAL_T("Should have reference property")) //&&
//                        NitsCompare(resultValue.reference->classDecl->name, PAL_T("XYZ_Gadget"), PAL_T("Left instance class should be XYZ_Gadget"))
                         )
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeInstance(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS | MI_SERIALIZER_FLAGS_INSTANCE_WITH_CLASS, newInstance, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, testData[i].XML))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i].XML, NitsHere());
                        }
                    }
                    if (NitsCompare(MI_Instance_Clone(newInstance, &cloneInstance), MI_RESULT_OK, PAL_T("Clone should succeed")))
                    {
                        NitsCompare(MI_Instance_Delete(cloneInstance), MI_RESULT_OK, PAL_T("Deleting instance"));
                    }
                    NitsCompare(MI_Instance_Delete(newInstance), MI_RESULT_OK, PAL_T("Deleting instance"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_MiscTests)
    const MI_Char *testData[] =
    {
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>PS3323320760</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"CIMOMTests\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"MT_Alltypes_KeyINT\"><PROPERTY NAME=\"kv\" TYPE=\"uint32\" CLASSORIGIN=\"MT_Alltypes_KeyINT\"></PROPERTY><PROPERTY NAME=\"p_char16\" TYPE=\"char16\" CLASSORIGIN=\"MT_Alltypes_KeyINT\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"MT_Alltypes_KeyINT\"><PROPERTY NAME=\"kv\" TYPE=\"uint32\"><VALUE>29</VALUE></PROPERTY><PROPERTY NAME=\"p_char16\" TYPE=\"char16\"><VALUE>&#0;</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>")
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer;
        MI_Serializer serializer;

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Instance *newInstance = NULL;
                MI_Instance *cloneInstance = NULL;
                MI_Uint32 deserializeSize;

                if (NitsCompare(XmlDeserializer_DeserializeInstance(&deserializer, 0, (MI_Uint8*)testData[i], Tcslen(testData[i])*(sizeof(MI_Char)), NULL, 0, NULL, NULL, &deserializeSize, &newInstance, NULL), MI_RESULT_OK, testData[i]))
                {
                    {
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeInstance(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS | MI_SERIALIZER_FLAGS_INSTANCE_WITH_CLASS, newInstance, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i], NitsHere());
                        }
                    }
                    if (NitsCompare(MI_Instance_Clone(newInstance, &cloneInstance), MI_RESULT_OK, PAL_T("Clone should succeed")))
                    {
                        NitsCompare(MI_Instance_Delete(cloneInstance), MI_RESULT_OK, PAL_T("Deleting instance"));
                    }
                    NitsCompare(MI_Instance_Delete(newInstance), MI_RESULT_OK, PAL_T("Deleting instance"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Deserialization_INSTANCE_SchemaErrors)
//        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"),

    const MI_Char* testData[] =
    {
        PAL_T("<INSTANCE CLASSNAME=\"myClass\" foo=\"myClass\"></INSTANCE>"),
        PAL_T("<INSTANCE foo=\"myClass\"></INSTANCE>"),
        PAL_T("<INSTANCE></INSTANCE>"),
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"notFoundClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><FOO NAME=\"a\"></FOO><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><FOO NAME=\"a\"></FOO><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE></VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE></VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"),
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><BOO>localhost</BOO><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><BOO NAME=\"root\\cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"),
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Id2\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCEPATH><BOO><HOST>localhost2</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv1\"/></LOCALNAMESPACEPATH></BOO><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYBINDING NAME=\"Id\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING><KEYBINDING NAME=\"Id2\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING></INSTANCENAME></INSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><LOCALINSTANCEPATH><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv3\"/></LOCALNAMESPACEPATH><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></LOCALINSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"),

        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Id2\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCEPATH><NAMESPACEPATH><HOST>localhost2</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv1\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYBINDING NAME=\"Id\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING><KEYBINDING NAME=\"Id2\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING></INSTANCENAME></INSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><LOCALINSTANCEPATH><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv3\"/></LOCALNAMESPACEPATH><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></LOCALINSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Id2\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCEPATH><NAMESPACEPATH><HOST>localhost2</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv1\"/></LOCALNAMESPACEPATH></NAMESPACEPATH></INSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><LOCALINSTANCEPATH><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv3\"/></LOCALNAMESPACEPATH><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></LOCALINSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Id2\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCEPATH><NAMESPACEPATH><HOST>localhost2</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv1\"/></LOCALNAMESPACEPATH></NAMESPACEPATH></INSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><LOCALINSTANCEPATH><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv3\"/></LOCALNAMESPACEPATH><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></LOCALINSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Id2\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCEPATH><NAMESPACEPATH><HOST>localhost2</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv1\"/></LOCALNAMESPACEPATH></NAMESPACEPATH></INSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><LOCALINSTANCEPATH><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv3\"/></LOCALNAMESPACEPATH><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></LOCALINSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Id2\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCEPATH><NAMESPACEPATH><HOST>localhost2</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv1\"/></LOCALNAMESPACEPATH></NAMESPACEPATH></INSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><LOCALINSTANCEPATH><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv3\"/></LOCALNAMESPACEPATH><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></LOCALINSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><FOO NAME=\"root\\cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"baseClass\"></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"myClass\" SUPERCLASS=\"baseClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>true</VALUE></PROPERTY></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"),

        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Id2\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCEPATH><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYBINDING NAME=\"Id\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING><KEYBINDING NAME=\"Id2\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING></INSTANCENAME></INSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><LOCALINSTANCEPATH><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv3\"/></LOCALNAMESPACEPATH><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></LOCALINSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 

        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Id2\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCEPATH><NAMESPACEPATH><HOST>localhost2</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv1\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYBINDING NAME=\"Id\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING><KEYBINDING NAME=\"Id2\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING></INSTANCENAME></INSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><LOCALINSTANCEPATH></LOCALINSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"),
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Id2\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCEPATH><NAMESPACEPATH><HOST>localhost2</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv1\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYBINDING NAME=\"Id\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING><KEYBINDING NAME=\"Id2\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING></INSTANCENAME></INSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><LOCALINSTANCEPATH><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv3\"/></LOCALNAMESPACEPATH></LOCALINSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"),
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Id2\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCEPATH><NAMESPACEPATH><HOST>localhost2</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv1\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYBINDING NAME=\"Id\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING><KEYBINDING NAME=\"Id2\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></KEYBINDING></INSTANCENAME></INSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><LOCALINSTANCEPATH><FOO/><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv3\"/></LOCALNAMESPACEPATH><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></LOCALINSTANCEPATH></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"),

        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"),
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><CLASSPATH/></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"),
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><BOO/></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"),

//        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\"></KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\" BOO=\"goo\">1001</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYVALUE TYPE=\"string\">1001</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYVALUE VALUETYPE=\"goo\" TYPE=\"string\">1001</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYVALUE VALUETYPE=\"boolean\" TYPE=\"string\">1001</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"boolean\">1001</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYVALUE VALUETYPE=\"numeric\" TYPE=\"string\">1001</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYVALUE VALUETYPE=\"boolean\" TYPE=\"boolean\">boo</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"goo\">1001</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
        PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"real64\">1001</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 

//PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
    PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><BOO VALUETYPE=\"string\" TYPE=\"string\">1001</BOO></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 
    PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP><NAMESPACEPATH><HOST>localhost</HOST><LOCALNAMESPACEPATH><NAMESPACE NAME=\"root\"/><NAMESPACE NAME=\"cimv2\"/></LOCALNAMESPACEPATH></NAMESPACEPATH><VALUE.OBJECT><CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.REFERENCE></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Widget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><CLASS NAME=\"XYZ_Gadget\"><PROPERTY NAME=\"Id\" TYPE=\"string\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY></CLASS></VALUE.OBJECT><VALUE.OBJECT><INSTANCE CLASSNAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"><VALUE.REFERENCE><INSTANCENAME boo=\"XYZ_Widget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\"><VALUE.REFERENCE><INSTANCENAME CLASSNAME=\"XYZ_Gadget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1002</KEYVALUE></INSTANCENAME></VALUE.REFERENCE></PROPERTY.REFERENCE></INSTANCE></VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), 

    };

    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer = {0};

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Instance *newInstance = NULL;
                MI_Instance *extendedError = NULL;
                MI_Uint32 deserializeSize;
                MI_Result result;

                result = XmlDeserializer_DeserializeInstance(&deserializer, 0, (MI_Uint8*)testData[i], Tcslen(testData[i])*(sizeof(MI_Char)), NULL, 0, NULL, NULL, &deserializeSize, &newInstance, &extendedError);
                if (NitsCompare(result, MI_RESULT_INVALID_PARAMETER, testData[i]))
                {
                    if (NitsAssert(extendedError!=NULL, PAL_T("Should have extendedError")))
                    {
                        NitsCompare(MI_Instance_Delete(extendedError), MI_RESULT_OK, PAL_T("Deleting error instance"));
                    }
                }
                else if (result == MI_RESULT_OK)
                {
                    NitsCompare(MI_Instance_Delete(newInstance), MI_RESULT_OK, PAL_T("Deleting instance"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Deserialization_CLASS_SchemaErrors)
    const MI_Char* testData[] =
    {
        PAL_T("<CLASS NAME=\"myClass\" SUPERCLASS=\"superclass\" DERIVATION=\"wrong1,parentclass\"></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><foo/></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY/></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\" PROPAGATED=\"false\" TOINSTANCE=\"false\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\" OVERRIDABLE=\"false\"><VALUE></VALUE></QUALIFIER></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\" PROPAGATED=\"false\" TOINSTANCE=\"false\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\" OVERRIDABLE=\"false\"><VALUE>boo</VALUE></QUALIFIER></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\" PROPAGATED=\"false\" TOINSTANCE=\"false\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\" OVERRIDABLE=\"TRUE\"><VALUE></VALUE></QUALIFIER></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\" OVERRIDABLE=\"false\" TOINSTANCE=\"boo\"><VALUE>TRUE</VALUE></QUALIFIER></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\" OVERRIDABLE=\"false\" TOINSTANCE=\"true\" PROPAGATED=\"foo\"><VALUE>TRUE</VALUE></QUALIFIER></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\" TOINSTANCE=\"true\" TOSUBCLASS=\"false\" TRANSLATABLE=\"foo\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\" TOSUBCLASS=\"foo\" TRANSLATABLE=\"true\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"foo\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\" OVERRIDABLE=\"boo\"><VALUE>true</VALUE></QUALIFIER></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE></VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>TRUE</VALUE><VALUE>boo</VALUE></VALUE.ARRAY></QUALIFIER></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"foo\"><VALUE>true</VALUE></PROPERTY></CLASS>"), 
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><VALUE>foo</VALUE></PROPERTY></CLASS>"), 
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY PROPAGATED=\"TRUE\" NAME=\"prop1\" TYPE=\"boolean\"><VALUE></VALUE></PROPERTY></CLASS>"), 
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"string\" EmbeddedObject=\"foo\"><VALUE></VALUE></PROPERTY></CLASS>"), 
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" MODIFIED=\"foo\"><VALUE>true</VALUE></PROPERTY></CLASS>"), 
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\" MODIFIED=\"TRUE\" EmbeddedClassName=\"foo\"><VALUE>true</VALUE></PROPERTY></CLASS>"), 
        PAL_T("<CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE CLASSORIGIN=\"hello\" PROPAGATED=\"TRUE\" MODIFIED=\"TRUE\" NAME=\"Left\" NAME=\"boo\"  REFERENCECLASS=\"XYZ_Widget\"></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"></PROPERTY.REFERENCE></CLASS>"),
        PAL_T("<CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"  REFERENCECLASS=\"XYZ_Widget\" REFERENCECLASS=\"boo\"></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"></PROPERTY.REFERENCE></CLASS>"),
        PAL_T("<CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"  PROPAGATED=\"boo\" REFERENCECLASS=\"XYZ_Widget\"></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"></PROPERTY.REFERENCE></CLASS>"),
        PAL_T("<CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\"  MODIFIED=\"boo\" REFERENCECLASS=\"XYZ_Widget\"></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"></PROPERTY.REFERENCE></CLASS>"),
        PAL_T("<CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE  REFERENCECLASS=\"XYZ_Widget\"></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"></PROPERTY.REFERENCE></CLASS>"),
        PAL_T("<CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" BOO=\"FOO\" REFERENCECLASS=\"XYZ_Widget\"></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"></PROPERTY.REFERENCE></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><QUALIFIER TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><VALUE>true</VALUE></PROPERTY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><QUALIFIER NAME=\"hello\" TYPE=\"boolean\"><VALUE>boo</VALUE></QUALIFIER><VALUE>true</VALUE></PROPERTY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><QUALIFIER NAME=\"hello\" TYPE=\"boolean\"><VALUE></VALUE></QUALIFIER><VALUE>true</VALUE></PROPERTY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>boo</VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>true</VALUE></PROPERTY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE></VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>true</VALUE></PROPERTY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><QUALIFIER NAME=\"Overridden\" TYPE=\"boolean\"><VALUE>boo</VALUE></QUALIFIER><VALUE>true</VALUE></PROPERTY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><QUALIFIER NAME=\"Overridden\" TYPE=\"boolean\"><VALUE></VALUE></QUALIFIER><VALUE>true</VALUE></PROPERTY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><QUALIFIER NAME=\"Overridden\" TYPE=\"boolean\"></QUALIFIER><VALUE>true</VALUE></PROPERTY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><QUALIFIER NAME=\"EMBEDDEDINSTANCE\" TYPE=\"boolean\"><VALUE>boo</VALUE></QUALIFIER><VALUE>true</VALUE></PROPERTY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><QUALIFIER NAME=\"EMBEDDEDINSTANCE\" TYPE=\"string\"><VALUE></VALUE></QUALIFIER><VALUE>true</VALUE></PROPERTY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><QUALIFIER NAME=\"EMBEDDEDINSTANCE\" TYPE=\"string\"></QUALIFIER><VALUE>true</VALUE></PROPERTY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY NAME=\"prop1\" TYPE=\"boolean\"><BOO>true</BOO></PROPERTY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE></VALUE><VALUE>false</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>boo</VALUE><VALUE>false</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\"><VALUE.ARRAY><BOO>true</BOO><VALUE>false</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE.NULL></VALUE.NULL><VALUE>false</VALUE></VALUE.ARRAY></PROPERTY.ARRAY></CLASS>"),
        PAL_T("<CLASS NAME=\"XYZ_Link\"><PROPERTY.REFERENCE NAME=\"Left\" REFERENCECLASS=\"XYZ_Widget\"><goo><INSTANCENAME CLASSNAME=\"XYZ_Widget\"><KEYVALUE VALUETYPE=\"string\" TYPE=\"string\">1001</KEYVALUE></INSTANCENAME></goo></PROPERTY.REFERENCE><PROPERTY.REFERENCE NAME=\"Right\" REFERENCECLASS=\"XYZ_Gadget\"></PROPERTY.REFERENCE></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE>foo</VALUE></QUALIFIER></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE></VALUE></QUALIFIER></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"></QUALIFIER></METHOD></CLASS>"),
        
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>boo</VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE></VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><foo>true</foo><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE.NULL></VALUE.NULL><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER></METHOD></CLASS>"),

        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boo\"></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\" BOO=\"GOO\"></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\"></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD TYPE=\"boolean\"></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><FOO></FOO></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.ARRAY NAME=\"param1\" TYPE=\"boolean\" ARRAYSIZE=\"abc\"></PARAMETER.ARRAY></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFARRAY NAME=\"param1\" ARRAYSIZE=\"abc\"></PARAMETER.REFARRAY></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFARRAY NAME=\"param1\" NAME=\"goo\"></PARAMETER.REFARRAY></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFARRAY REFERENCECLASS=\"boo\"></PARAMETER.REFARRAY></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFARRAY NAME=\"param1\" REFERENCECLASS=\"boo\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE.NULL></VALUE.NULL><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER></PARAMETER.REFARRAY></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFARRAY NAME=\"param1\" REFERENCECLASS=\"boo\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>boo</VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER></PARAMETER.REFARRAY></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFARRAY NAME=\"param1\" REFERENCECLASS=\"boo\"><GOO NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>boo</VALUE><VALUE>false</VALUE></VALUE.ARRAY></GOO></PARAMETER.REFARRAY></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFARRAY NAME=\"param1\" REFERENCECLASS=\"boo\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE></VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER></PARAMETER.REFARRAY></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFARRAY NAME=\"param1\" REFERENCECLASS=\"boo\"><QUALIFIER TYPE=\"boolean\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER></PARAMETER.REFARRAY></METHOD></CLASS>"),

        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFERENCE NAME=\"param1\" ARRAYSIZE=\"abc\"></PARAMETER.REFERENCE></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFERENCE NAME=\"param1\" NAME=\"goo\"></PARAMETER.REFERENCE></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFERENCE REFERENCECLASS=\"boo\"></PARAMETER.REFERENCE></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFERENCE NAME=\"param1\" REFERENCECLASS=\"boo\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE.NULL></VALUE.NULL><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER></PARAMETER.REFERENCE></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFERENCE NAME=\"param1\" REFERENCECLASS=\"boo\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>boo</VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER></PARAMETER.REFERENCE></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFERENCE NAME=\"param1\" REFERENCECLASS=\"boo\"><GOO NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE>boo</VALUE><VALUE>false</VALUE></VALUE.ARRAY></GOO></PARAMETER.REFERENCE></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFERENCE NAME=\"param1\" REFERENCECLASS=\"boo\"><QUALIFIER NAME=\"qual1\" TYPE=\"boolean\"><VALUE.ARRAY><VALUE></VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER></PARAMETER.REFERENCE></METHOD></CLASS>"),
        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER.REFERENCE NAME=\"param1\" REFERENCECLASS=\"boo\"><QUALIFIER TYPE=\"boolean\"><VALUE.ARRAY><VALUE>true</VALUE><VALUE>false</VALUE></VALUE.ARRAY></QUALIFIER></PARAMETER.REFERENCE></METHOD></CLASS>"),

        PAL_T("<CLASS NAME=\"myClass\"><METHOD NAME=\"method1\" TYPE=\"boolean\"><PARAMETER NAME=\"param1\" TYPE=\"boolean\"><GOO></GOO></PARAMETER></METHOD></CLASS>"),
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer = {0};

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))))
        {
            for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
            {
                MI_Class *newClass = NULL;
                MI_Instance *extendedError = NULL;
                MI_Uint32 deserializeSize;
                MI_Result result;

                result = XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)testData[i], Tcslen(testData[i])*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, &extendedError);

                if (NitsCompare(result, MI_RESULT_INVALID_PARAMETER, testData[i]))
                {
                    if (NitsAssert(extendedError!=NULL, PAL_T("Should have extendedError")))
                    {
                        NitsCompare(MI_Instance_Delete(extendedError), MI_RESULT_OK, PAL_T("Deleting error instance"));
                    }
                }
                else if (result == MI_RESULT_OK)
                {
                    NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("Deleting class"));
                }
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest

NitsTest(Xml_Deserialization_CLASS_Null_Arrays)
    const MI_Char *classString = PAL_T("<CLASS NAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY.ARRAY></CLASS>";
    
    const MI_Char* testData[] =
    {
        PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\"><VALUE.ARRAY></VALUE.ARRAY></PROPERTY.ARRAY></INSTANCE>")),
        PAL_T("<INSTANCE CLASSNAME=\"myClass\"><PROPERTY.ARRAY NAME=\"prop1\" TYPE=\"boolean\"></PROPERTY.ARRAY></INSTANCE>")
    };
    MI_Application application = MI_APPLICATION_NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("Get application should succeed")))
    {
        MI_Deserializer deserializer = {0};
        MI_Serializer serializer = {0};

        if ((NitsCompare(XmlDeserializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &deserializer), MI_RESULT_OK, PAL_T("Get deserializer"))) &&
            (NitsCompare(XmlSerializer_Create(&application, 0, (MI_Char *)PAL_T("MI_XML"), &serializer), MI_RESULT_OK, PAL_T("Get serializer"))))
        {
            MI_Class *newClass = NULL;
            MI_Uint32 deserializeSize;
            MI_Result result;
            result = XmlDeserializer_DeserializeClass(&deserializer, 0, (MI_Uint8*)classString, Tcslen(classString)*(sizeof(MI_Char)), NULL, NULL, NULL, NULL, NULL, &deserializeSize, &newClass, NULL);
            if (NitsCompare(result, MI_RESULT_OK, PAL_T("Deserialization of class failed")))
            {
                for (int i = 0; i != sizeof(testData)/sizeof(testData[0]); i++)
                {
                    MI_Instance *newInstance = NULL;
                    result = XmlDeserializer_DeserializeInstance(&deserializer, 0, (MI_Uint8*)testData[i], Tcslen(testData[i])*(sizeof(MI_Char)), &newClass, 1, NULL, NULL, NULL, &newInstance, NULL);
                    if (NitsCompare(result, MI_RESULT_OK, testData[i]))
                    {
                        const MI_Char *propName = NULL;
                        MI_Value propValue;
                        MI_Uint32 propFlags;
                        MI_Type propType;

                        if (NitsCompare(MI_Instance_GetElementAt(newInstance, 0, &propName, &propValue, &propType, &propFlags), MI_RESULT_OK, PAL_T("should find the property")))
                        {
                            if (i==0)
                            {
                                NitsCompare(propFlags, MI_FLAG_NOT_MODIFIED|MI_FLAG_PROPERTY, PAL_T("property should exist"));
                                NitsCompare(propValue.array.size, 0, PAL_T("should have 0 element in the array"));
                            }
                            else if (i==1)
                            {
                                NitsCompare(propFlags, MI_FLAG_NOT_MODIFIED|MI_FLAG_PROPERTY|MI_FLAG_NULL, PAL_T("property should not exist"));
                                NitsAssert(propValue.array.data == NULL, PAL_T("array should be null"));
                            }
                        }
                        MI_Uint32 bufferUsed = 0;
                        if (NitsCompare(XmlSerializer_SerializeInstance(&serializer, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS, newInstance, serializedBuffer, sizeof(serializedBuffer), &bufferUsed), MI_RESULT_OK, PAL_T("Serialize should work")))
                        {
                            SerializerTestCompare(serializedBuffer, testData[i], NitsHere());
                        }
                        NitsCompare(MI_Instance_Delete(newInstance), MI_RESULT_OK, PAL_T("failed to delete instance"));

                    }
                }
                NitsCompare(MI_Class_Delete(newClass), MI_RESULT_OK, PAL_T("Deleting class"));
            }
            NitsCompare(XmlDeserializer_Close(&deserializer), MI_RESULT_OK, PAL_T("Close deserializer"));
        }
        MI_Application_Close(&application);
    }
NitsEndTest
/* End of original WMI UT */

/* Start of new OMI UT: Derivation, Option flags */
NitsTest(Class_SuperClass_Derivation)
    TestStandardRttiSerialization(PAL_T("MyEmptyClass"), PAL_T("<CLASS NAME=\"MyEmptyClass\" DERIVATION=\"\"></CLASS>"), NitsHere());
    TestStandardRttiSerialization(PAL_T("MyEmptyDerivedClass"), PAL_T("<CLASS NAME=\"MyEmptyDerivedClass\" SUPERCLASS=\"MyEmptyClass\" DERIVATION=\"MyEmptyClass\"></CLASS>"), NitsHere());
    TestStandardRttiSerialization(PAL_T("MyEmptySecondDerivedClass"), PAL_T("<CLASS NAME=\"MyEmptySecondDerivedClass\" SUPERCLASS=\"MyEmptyDerivedClass\" DERIVATION=\"MyEmptyDerivedClass,MyEmptyClass\"></CLASS>"), NitsHere());
NitsEndTest

NitsTest(Class_Various_Array_Lengths)
    const MI_Char *expectedSerialization =
        PAL_T("<CLASS NAME=\"MyVariousArrayLengthClass\" DERIVATION=\"\">")
        PAL_T("<PROPERTY NAME=\"uninitializedValue\" TYPE=\"real32\" CLASSORIGIN=\"MyVariousArrayLengthClass\"></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"booleanUninitializedArray\" TYPE=\"boolean\" CLASSORIGIN=\"MyVariousArrayLengthClass\"></PROPERTY.ARRAY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"nullArray\" TYPE=\"uint16\" CLASSORIGIN=\"MyVariousArrayLengthClass\"></PROPERTY.ARRAY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"uint32Array\" TYPE=\"uint32\" CLASSORIGIN=\"MyVariousArrayLengthClass\"><VALUE.ARRAY><VALUE>10</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"sint32Array\" TYPE=\"sint32\" ARRAYSIZE=\"2\" CLASSORIGIN=\"MyVariousArrayLengthClass\"><VALUE.ARRAY><VALUE>9999</VALUE><VALUE>-9999</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<METHOD NAME=\"MethodWithArrayParam\" TYPE=\"uint32\" CLASSORIGIN=\"MyVariousArrayLengthClass\"><PARAMETER.ARRAY NAME=\"sint64ArrayParam\" TYPE=\"sint64\"></PARAMETER.ARRAY></METHOD>")
        PAL_T("<METHOD NAME=\"MethodWithFixedSizeArrayParam\" TYPE=\"uint32\" CLASSORIGIN=\"MyVariousArrayLengthClass\"><PARAMETER.ARRAY NAME=\"sint64ArrayParam\" TYPE=\"sint64\" ARRAYSIZE=\"5\"></PARAMETER.ARRAY></METHOD></CLASS>");
	TestStandardRttiSerialization(PAL_T("MyVariousArrayLengthClass"), expectedSerialization, NitsHere());
NitsEndTest

/*
#define FULL_RTTI_SERIALIZATION_FLAGS (MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN | \
		MI_SERIALIZER_FLAGS_INCLUDE_INHERITANCE_HIERARCHY | \
		MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS)

#define STANDARD_RTTI_SERIALIZATION_FLAGS (FULL_RTTI_SERIALIZATION_FLAGS | \
						MI_SERIALIZER_FLAGS_INCLUDE_INHERITED_ELEMENTS)
*/

NitsTest(Class_IncludeInheritedElements_Option)
    const MI_Char *expectedOptionSerialization =
        PAL_T("<CLASS NAME=\"MyOptionTestClass\" DERIVATION=\"\">")
        PAL_T("<QUALIFIER NAME=\"BooleanQual\" TYPE=\"boolean\" TRANSLATABLE=\"true\"><VALUE>true</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint64ArrayQual\" TYPE=\"uint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Sint64ArrayQual\" TYPE=\"sint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<PROPERTY NAME=\"uint8Prop\" TYPE=\"uint8\" CLASSORIGIN=\"MyOptionTestClass\"><VALUE>5</VALUE></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"uint64ArrayProp\" TYPE=\"uint64\" ARRAYSIZE=\"3\" CLASSORIGIN=\"MyOptionTestClass\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<PROPERTY NAME=\"sint8PropWithSimpleQual\" TYPE=\"sint8\" CLASSORIGIN=\"MyOptionTestClass\"><QUALIFIER NAME=\"Uint8Qual\" TYPE=\"uint8\" TRANSLATABLE=\"true\"><VALUE>9</VALUE></QUALIFIER></PROPERTY>")
        PAL_T("<PROPERTY NAME=\"uint32PropWithArrayQual\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\"><QUALIFIER NAME=\"Sint64ArrayQual\" TYPE=\"sint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>-999</VALUE><VALUE>-45</VALUE><VALUE>0</VALUE><VALUE>6</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>")
        PAL_T("<METHOD NAME=\"Uint32EmptyParamMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\"></METHOD>")
        PAL_T("<METHOD NAME=\"Sint64SimpleParamsMethod\" TYPE=\"sint64\" CLASSORIGIN=\"MyOptionTestClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint16\">")
        PAL_T("<QUALIFIER NAME=\"In\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"BooleanQual\" TYPE=\"boolean\" TRANSLATABLE=\"true\"><VALUE>true</VALUE></QUALIFIER></PARAMETER>")
        PAL_T("<PARAMETER NAME=\"param2\" TYPE=\"sint16\">")
        PAL_T("<QUALIFIER NAME=\"Out\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE></VALUE></QUALIFIER></PARAMETER></METHOD>")
        PAL_T("<METHOD NAME=\"MultiQualMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\"><QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE>~!@#$%^&amp;*()-_=+&apos;&quot;;:.&gt;,&lt;/?welcome\\&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER><QUALIFIER NAME=\"Uint64ArrayQual\" TYPE=\"uint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<PARAMETER NAME=\"inputParam\" TYPE=\"uint64\"><QUALIFIER NAME=\"In\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></PARAMETER><PARAMETER NAME=\"outputParam\" TYPE=\"uint64\"><QUALIFIER NAME=\"Out\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>");
	TestStandardRttiSerialization(PAL_T("MyOptionTestClass"), expectedOptionSerialization, NitsHere());
    const MI_Char *expectedDerivedStandardSerialization =
        PAL_T("<CLASS NAME=\"MyOptionTestDerivedClass\" SUPERCLASS=\"MyOptionTestClass\" DERIVATION=\"MyOptionTestClass\">")
        PAL_T("<QUALIFIER NAME=\"BooleanQual\" TYPE=\"boolean\" TRANSLATABLE=\"true\"><VALUE>true</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint64ArrayQual\" TYPE=\"uint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Sint64ArrayQual\" TYPE=\"sint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint32Qual\" TYPE=\"uint32\" TRANSLATABLE=\"true\"><VALUE>9</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint32ArrayQual\" TYPE=\"uint32\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>9</VALUE><VALUE>10</VALUE><VALUE>11</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<PROPERTY NAME=\"uint8Prop\" TYPE=\"uint8\" CLASSORIGIN=\"MyOptionTestClass\"><VALUE>10</VALUE></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"uint64ArrayProp\" TYPE=\"uint64\" ARRAYSIZE=\"3\" CLASSORIGIN=\"MyOptionTestClass\" PROPAGATED=\"true\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<PROPERTY NAME=\"sint8PropWithSimpleQual\" TYPE=\"sint8\" CLASSORIGIN=\"MyOptionTestClass\" PROPAGATED=\"true\"><QUALIFIER NAME=\"Uint8Qual\" TYPE=\"uint8\" TRANSLATABLE=\"true\"><VALUE>9</VALUE></QUALIFIER></PROPERTY>")
        PAL_T("<PROPERTY NAME=\"uint32PropWithArrayQual\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\"><QUALIFIER NAME=\"Sint64ArrayQual\" TYPE=\"sint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>-111</VALUE><VALUE>-45</VALUE><VALUE>0</VALUE><VALUE>5</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>")
        PAL_T("<PROPERTY NAME=\"uint8Property\" TYPE=\"uint8\" CLASSORIGIN=\"MyOptionTestDerivedClass\"><VALUE>7</VALUE></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"uint64ArrayProperty\" TYPE=\"uint64\" ARRAYSIZE=\"5\" CLASSORIGIN=\"MyOptionTestDerivedClass\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE><VALUE>4</VALUE><VALUE>5</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<METHOD NAME=\"Uint32EmptyParamMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\" PROPAGATED=\"true\"></METHOD>")
        PAL_T("<METHOD NAME=\"Sint64SimpleParamsMethod\" TYPE=\"sint64\" CLASSORIGIN=\"MyOptionTestClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint16\"><QUALIFIER NAME=\"In\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"BooleanQual\" TYPE=\"boolean\" TRANSLATABLE=\"true\"><VALUE>true</VALUE></QUALIFIER></PARAMETER>")
        PAL_T("<PARAMETER NAME=\"param2\" TYPE=\"sint16\"><QUALIFIER NAME=\"Out\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE></VALUE></QUALIFIER></PARAMETER><PARAMETER NAME=\"param3\" TYPE=\"string\"></PARAMETER></METHOD>")
        PAL_T("<METHOD NAME=\"MultiQualMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\" PROPAGATED=\"true\"><QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE>~!@#$%^&amp;*()-_=+&apos;&quot;;:.&gt;,&lt;/?welcome\\&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint64ArrayQual\" TYPE=\"uint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE></VALUE.ARRAY></QUALIFIER><PARAMETER NAME=\"inputParam\" TYPE=\"uint64\"><QUALIFIER NAME=\"In\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></PARAMETER>")
        PAL_T("<PARAMETER NAME=\"outputParam\" TYPE=\"uint64\"><QUALIFIER NAME=\"Out\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD>")
        PAL_T("<METHOD NAME=\"MyMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestDerivedClass\"><PARAMETER NAME=\"input\" TYPE=\"uint32\"></PARAMETER></METHOD></CLASS>");
	TestStandardRttiSerialization(PAL_T("MyOptionTestDerivedClass"), expectedDerivedStandardSerialization, NitsHere());
    const MI_Char *expectedDerivedFullSerialization =
        PAL_T("<CLASS NAME=\"MyOptionTestDerivedClass\" SUPERCLASS=\"MyOptionTestClass\" DERIVATION=\"MyOptionTestClass\">")
        PAL_T("<QUALIFIER NAME=\"BooleanQual\" TYPE=\"boolean\" TRANSLATABLE=\"true\"><VALUE>true</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint64ArrayQual\" TYPE=\"uint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Sint64ArrayQual\" TYPE=\"sint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint32Qual\" TYPE=\"uint32\" TRANSLATABLE=\"true\"><VALUE>9</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint32ArrayQual\" TYPE=\"uint32\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>9</VALUE><VALUE>10</VALUE><VALUE>11</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<PROPERTY NAME=\"uint8Prop\" TYPE=\"uint8\" CLASSORIGIN=\"MyOptionTestClass\"><VALUE>10</VALUE></PROPERTY>")
        PAL_T("<PROPERTY NAME=\"uint32PropWithArrayQual\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\"><QUALIFIER NAME=\"Sint64ArrayQual\" TYPE=\"sint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>-111</VALUE><VALUE>-45</VALUE><VALUE>0</VALUE><VALUE>5</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>")
        PAL_T("<PROPERTY NAME=\"uint8Property\" TYPE=\"uint8\" CLASSORIGIN=\"MyOptionTestDerivedClass\"><VALUE>7</VALUE></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"uint64ArrayProperty\" TYPE=\"uint64\" ARRAYSIZE=\"5\" CLASSORIGIN=\"MyOptionTestDerivedClass\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE><VALUE>4</VALUE><VALUE>5</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<METHOD NAME=\"Sint64SimpleParamsMethod\" TYPE=\"sint64\" CLASSORIGIN=\"MyOptionTestClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint16\">")
        PAL_T("<QUALIFIER NAME=\"In\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"BooleanQual\" TYPE=\"boolean\" TRANSLATABLE=\"true\"><VALUE>true</VALUE></QUALIFIER></PARAMETER>")
        PAL_T("<PARAMETER NAME=\"param2\" TYPE=\"sint16\"><QUALIFIER NAME=\"Out\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE></VALUE></QUALIFIER></PARAMETER>")
        PAL_T("<PARAMETER NAME=\"param3\" TYPE=\"string\"></PARAMETER></METHOD><METHOD NAME=\"MyMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestDerivedClass\"><PARAMETER NAME=\"input\" TYPE=\"uint32\"></PARAMETER></METHOD></CLASS>");
	TestFullRttiSerialization(PAL_T("MyOptionTestDerivedClass"), expectedDerivedFullSerialization, NitsHere());
NitsEndTest

NitsTest(Class_Skip_IncludeQualifiers_Option)
    const MI_Char *expectedOptionSerialization =
        PAL_T("<CLASS NAME=\"MyOptionTestClass\" DERIVATION=\"\">")
        PAL_T("<PROPERTY NAME=\"uint8Prop\" TYPE=\"uint8\" CLASSORIGIN=\"MyOptionTestClass\"><VALUE>5</VALUE></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"uint64ArrayProp\" TYPE=\"uint64\" ARRAYSIZE=\"3\" CLASSORIGIN=\"MyOptionTestClass\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<PROPERTY NAME=\"sint8PropWithSimpleQual\" TYPE=\"sint8\" CLASSORIGIN=\"MyOptionTestClass\"></PROPERTY>")
        PAL_T("<PROPERTY NAME=\"uint32PropWithArrayQual\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\"></PROPERTY>")
        PAL_T("<METHOD NAME=\"Uint32EmptyParamMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\"></METHOD>")
        PAL_T("<METHOD NAME=\"Sint64SimpleParamsMethod\" TYPE=\"sint64\" CLASSORIGIN=\"MyOptionTestClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint16\"></PARAMETER><PARAMETER NAME=\"param2\" TYPE=\"sint16\"></PARAMETER></METHOD>")
        PAL_T("<METHOD NAME=\"MultiQualMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\"><PARAMETER NAME=\"inputParam\" TYPE=\"uint64\"></PARAMETER><PARAMETER NAME=\"outputParam\" TYPE=\"uint64\"></PARAMETER></METHOD></CLASS>");
	TestClassSerialization(PAL_T("MyOptionTestClass"), expectedOptionSerialization, NitsHere(),
			MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN |
			MI_SERIALIZER_FLAGS_INCLUDE_INHERITANCE_HIERARCHY |
			MI_SERIALIZER_FLAGS_INCLUDE_INHERITED_ELEMENTS);
    const MI_Char *expectedDerivedSerialization =
        PAL_T("<CLASS NAME=\"MyOptionTestDerivedClass\" SUPERCLASS=\"MyOptionTestClass\" DERIVATION=\"MyOptionTestClass\">")
        PAL_T("<PROPERTY NAME=\"uint8Prop\" TYPE=\"uint8\" CLASSORIGIN=\"MyOptionTestClass\"><VALUE>10</VALUE></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"uint64ArrayProp\" TYPE=\"uint64\" ARRAYSIZE=\"3\" CLASSORIGIN=\"MyOptionTestClass\" PROPAGATED=\"true\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<PROPERTY NAME=\"sint8PropWithSimpleQual\" TYPE=\"sint8\" CLASSORIGIN=\"MyOptionTestClass\" PROPAGATED=\"true\"></PROPERTY>")
        PAL_T("<PROPERTY NAME=\"uint32PropWithArrayQual\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\"></PROPERTY>")
        PAL_T("<PROPERTY NAME=\"uint8Property\" TYPE=\"uint8\" CLASSORIGIN=\"MyOptionTestDerivedClass\"><VALUE>7</VALUE></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"uint64ArrayProperty\" TYPE=\"uint64\" ARRAYSIZE=\"5\" CLASSORIGIN=\"MyOptionTestDerivedClass\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE><VALUE>4</VALUE><VALUE>5</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<METHOD NAME=\"Uint32EmptyParamMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\" PROPAGATED=\"true\"></METHOD>")
        PAL_T("<METHOD NAME=\"Sint64SimpleParamsMethod\" TYPE=\"sint64\" CLASSORIGIN=\"MyOptionTestClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint16\"></PARAMETER>")
        PAL_T("<PARAMETER NAME=\"param2\" TYPE=\"sint16\"></PARAMETER><PARAMETER NAME=\"param3\" TYPE=\"string\"></PARAMETER></METHOD>")
        PAL_T("<METHOD NAME=\"MultiQualMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\" PROPAGATED=\"true\"><PARAMETER NAME=\"inputParam\" TYPE=\"uint64\"></PARAMETER><PARAMETER NAME=\"outputParam\" TYPE=\"uint64\"></PARAMETER></METHOD>")
        PAL_T("<METHOD NAME=\"MyMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestDerivedClass\"><PARAMETER NAME=\"input\" TYPE=\"uint32\"></PARAMETER></METHOD></CLASS>");
	TestClassSerialization(PAL_T("MyOptionTestDerivedClass"), expectedDerivedSerialization, NitsHere(),
			MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN |
			MI_SERIALIZER_FLAGS_INCLUDE_INHERITANCE_HIERARCHY |
			MI_SERIALIZER_FLAGS_INCLUDE_INHERITED_ELEMENTS);
NitsEndTest

NitsTest(Class_Skip_IncludeClassOrigin_Option)
    const MI_Char *expectedOptionSerialization =
        PAL_T("<CLASS NAME=\"MyOptionTestClass\" DERIVATION=\"\">")
        PAL_T("<QUALIFIER NAME=\"BooleanQual\" TYPE=\"boolean\" TRANSLATABLE=\"true\"><VALUE>true</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint64ArrayQual\" TYPE=\"uint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Sint64ArrayQual\" TYPE=\"sint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<PROPERTY NAME=\"uint8Prop\" TYPE=\"uint8\"><VALUE>5</VALUE></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"uint64ArrayProp\" TYPE=\"uint64\" ARRAYSIZE=\"3\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<PROPERTY NAME=\"sint8PropWithSimpleQual\" TYPE=\"sint8\"><QUALIFIER NAME=\"Uint8Qual\" TYPE=\"uint8\" TRANSLATABLE=\"true\"><VALUE>9</VALUE></QUALIFIER></PROPERTY>")
        PAL_T("<PROPERTY NAME=\"uint32PropWithArrayQual\" TYPE=\"uint32\"><QUALIFIER NAME=\"Sint64ArrayQual\" TYPE=\"sint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>-999</VALUE><VALUE>-45</VALUE><VALUE>0</VALUE><VALUE>6</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>")
        PAL_T("<METHOD NAME=\"Uint32EmptyParamMethod\" TYPE=\"uint32\"></METHOD>")
        PAL_T("<METHOD NAME=\"Sint64SimpleParamsMethod\" TYPE=\"sint64\"><PARAMETER NAME=\"param1\" TYPE=\"uint16\">")
        PAL_T("<QUALIFIER NAME=\"In\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"BooleanQual\" TYPE=\"boolean\" TRANSLATABLE=\"true\"><VALUE>true</VALUE></QUALIFIER></PARAMETER>")
        PAL_T("<PARAMETER NAME=\"param2\" TYPE=\"sint16\"><QUALIFIER NAME=\"Out\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE></VALUE></QUALIFIER></PARAMETER></METHOD>")
        PAL_T("<METHOD NAME=\"MultiQualMethod\" TYPE=\"uint32\"><QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE>~!@#$%^&amp;*()-_=+&apos;&quot;;:.&gt;,&lt;/?welcome\\&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint64ArrayQual\" TYPE=\"uint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<PARAMETER NAME=\"inputParam\" TYPE=\"uint64\"><QUALIFIER NAME=\"In\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></PARAMETER>")
        PAL_T("<PARAMETER NAME=\"outputParam\" TYPE=\"uint64\"><QUALIFIER NAME=\"Out\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>");
	TestClassSerialization(PAL_T("MyOptionTestClass"), expectedOptionSerialization, NitsHere(),
			MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS |
			MI_SERIALIZER_FLAGS_INCLUDE_INHERITANCE_HIERARCHY |
			MI_SERIALIZER_FLAGS_INCLUDE_INHERITED_ELEMENTS);

    const MI_Char *expectedDerivedSerialization =
        PAL_T("<CLASS NAME=\"MyOptionTestDerivedClass\" SUPERCLASS=\"MyOptionTestClass\" DERIVATION=\"MyOptionTestClass\">")
        PAL_T("<QUALIFIER NAME=\"BooleanQual\" TYPE=\"boolean\" TRANSLATABLE=\"true\"><VALUE>true</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint64ArrayQual\" TYPE=\"uint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Sint64ArrayQual\" TYPE=\"sint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint32Qual\" TYPE=\"uint32\" TRANSLATABLE=\"true\"><VALUE>9</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint32ArrayQual\" TYPE=\"uint32\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>9</VALUE><VALUE>10</VALUE><VALUE>11</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<PROPERTY NAME=\"uint8Prop\" TYPE=\"uint8\"><VALUE>10</VALUE></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"uint64ArrayProp\" TYPE=\"uint64\" ARRAYSIZE=\"3\" PROPAGATED=\"true\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<PROPERTY NAME=\"sint8PropWithSimpleQual\" TYPE=\"sint8\" PROPAGATED=\"true\"><QUALIFIER NAME=\"Uint8Qual\" TYPE=\"uint8\" TRANSLATABLE=\"true\"><VALUE>9</VALUE></QUALIFIER></PROPERTY>")
        PAL_T("<PROPERTY NAME=\"uint32PropWithArrayQual\" TYPE=\"uint32\"><QUALIFIER NAME=\"Sint64ArrayQual\" TYPE=\"sint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>-111</VALUE><VALUE>-45</VALUE><VALUE>0</VALUE><VALUE>5</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>")
        PAL_T("<PROPERTY NAME=\"uint8Property\" TYPE=\"uint8\"><VALUE>7</VALUE></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"uint64ArrayProperty\" TYPE=\"uint64\" ARRAYSIZE=\"5\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE><VALUE>4</VALUE><VALUE>5</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<METHOD NAME=\"Uint32EmptyParamMethod\" TYPE=\"uint32\" PROPAGATED=\"true\"></METHOD>")
        PAL_T("<METHOD NAME=\"Sint64SimpleParamsMethod\" TYPE=\"sint64\"><PARAMETER NAME=\"param1\" TYPE=\"uint16\"><QUALIFIER NAME=\"In\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"BooleanQual\" TYPE=\"boolean\" TRANSLATABLE=\"true\"><VALUE>true</VALUE></QUALIFIER></PARAMETER>")
        PAL_T("<PARAMETER NAME=\"param2\" TYPE=\"sint16\"><QUALIFIER NAME=\"Out\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE></VALUE></QUALIFIER></PARAMETER>")
        PAL_T("<PARAMETER NAME=\"param3\" TYPE=\"string\"></PARAMETER></METHOD>")
        PAL_T("<METHOD NAME=\"MultiQualMethod\" TYPE=\"uint32\" PROPAGATED=\"true\"><QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE>~!@#$%^&amp;*()-_=+&apos;&quot;;:.&gt;,&lt;/?welcome\\&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint64ArrayQual\" TYPE=\"uint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<PARAMETER NAME=\"inputParam\" TYPE=\"uint64\"><QUALIFIER NAME=\"In\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></PARAMETER>")
        PAL_T("<PARAMETER NAME=\"outputParam\" TYPE=\"uint64\"><QUALIFIER NAME=\"Out\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD>")
        PAL_T("<METHOD NAME=\"MyMethod\" TYPE=\"uint32\"><PARAMETER NAME=\"input\" TYPE=\"uint32\"></PARAMETER></METHOD></CLASS>");
	TestClassSerialization(PAL_T("MyOptionTestDerivedClass"), expectedDerivedSerialization, NitsHere(),
			MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS |
			MI_SERIALIZER_FLAGS_INCLUDE_INHERITANCE_HIERARCHY |
			MI_SERIALIZER_FLAGS_INCLUDE_INHERITED_ELEMENTS);
NitsEndTest

NitsTest(Class_Skip_IncludeInheritanceHierarchy_Option)    
    const MI_Char *expectedFirstSerialization =
        PAL_T("<CLASS NAME=\"MyOptionTestDerivedClass\" SUPERCLASS=\"MyOptionTestClass\">")
        PAL_T("<QUALIFIER NAME=\"BooleanQual\" TYPE=\"boolean\" TRANSLATABLE=\"true\"><VALUE>true</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE>hello&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint64ArrayQual\" TYPE=\"uint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>4</VALUE><VALUE>40</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Sint64ArrayQual\" TYPE=\"sint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>-4</VALUE><VALUE>4</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint32Qual\" TYPE=\"uint32\" TRANSLATABLE=\"true\"><VALUE>9</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint32ArrayQual\" TYPE=\"uint32\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>9</VALUE><VALUE>10</VALUE><VALUE>11</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<PROPERTY NAME=\"uint8Prop\" TYPE=\"uint8\" CLASSORIGIN=\"MyOptionTestClass\"><VALUE>10</VALUE></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"uint64ArrayProp\" TYPE=\"uint64\" ARRAYSIZE=\"3\" CLASSORIGIN=\"MyOptionTestClass\" PROPAGATED=\"true\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<PROPERTY NAME=\"sint8PropWithSimpleQual\" TYPE=\"sint8\" CLASSORIGIN=\"MyOptionTestClass\" PROPAGATED=\"true\"><QUALIFIER NAME=\"Uint8Qual\" TYPE=\"uint8\" TRANSLATABLE=\"true\"><VALUE>9</VALUE></QUALIFIER></PROPERTY>")
        PAL_T("<PROPERTY NAME=\"uint32PropWithArrayQual\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\"><QUALIFIER NAME=\"Sint64ArrayQual\" TYPE=\"sint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>-111</VALUE><VALUE>-45</VALUE><VALUE>0</VALUE><VALUE>5</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>")
        PAL_T("<PROPERTY NAME=\"uint8Property\" TYPE=\"uint8\" CLASSORIGIN=\"MyOptionTestDerivedClass\"><VALUE>7</VALUE></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"uint64ArrayProperty\" TYPE=\"uint64\" ARRAYSIZE=\"5\" CLASSORIGIN=\"MyOptionTestDerivedClass\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE><VALUE>4</VALUE><VALUE>5</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<METHOD NAME=\"Uint32EmptyParamMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\" PROPAGATED=\"true\"></METHOD>")
        PAL_T("<METHOD NAME=\"Sint64SimpleParamsMethod\" TYPE=\"sint64\" CLASSORIGIN=\"MyOptionTestClass\"><PARAMETER NAME=\"param1\" TYPE=\"uint16\"><QUALIFIER NAME=\"In\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"BooleanQual\" TYPE=\"boolean\" TRANSLATABLE=\"true\"><VALUE>true</VALUE></QUALIFIER></PARAMETER>")
        PAL_T("<PARAMETER NAME=\"param2\" TYPE=\"sint16\"><QUALIFIER NAME=\"Out\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE></VALUE></QUALIFIER></PARAMETER>")
        PAL_T("<PARAMETER NAME=\"param3\" TYPE=\"string\"></PARAMETER></METHOD>")
        PAL_T("<METHOD NAME=\"MultiQualMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestClass\" PROPAGATED=\"true\"><QUALIFIER NAME=\"StringQual\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE>~!@#$%^&amp;*()-_=+&apos;&quot;;:.&gt;,&lt;/?welcome\\&amp;&apos;&gt;&lt;&quot;</VALUE></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint64ArrayQual\" TYPE=\"uint64\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<PARAMETER NAME=\"inputParam\" TYPE=\"uint64\"><QUALIFIER NAME=\"In\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></PARAMETER>")
        PAL_T("<PARAMETER NAME=\"outputParam\" TYPE=\"uint64\"><QUALIFIER NAME=\"Out\" TYPE=\"boolean\" OVERRIDABLE=\"false\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD>")
        PAL_T("<METHOD NAME=\"MyMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyOptionTestDerivedClass\"><PARAMETER NAME=\"input\" TYPE=\"uint32\"></PARAMETER></METHOD></CLASS>");
	TestClassSerialization(PAL_T("MyOptionTestDerivedClass"), expectedFirstSerialization, NitsHere(),
			MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS |
			MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN |
			MI_SERIALIZER_FLAGS_INCLUDE_INHERITED_ELEMENTS);
	TestClassSerialization(PAL_T("MyEmptySecondDerivedClass"), PAL_T("<CLASS NAME=\"MyEmptySecondDerivedClass\" SUPERCLASS=\"MyEmptyDerivedClass\"></CLASS>"),
						NitsHere(),
						MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS |
						MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN |
						MI_SERIALIZER_FLAGS_INCLUDE_INHERITED_ELEMENTS);
NitsEndTest

NitsTest(Class_Skip_All_GetClassOptions)
    const MI_Char *expectedSerialization =
        PAL_T("<CLASS NAME=\"MyOptionTestClass\">")
        PAL_T("<PROPERTY NAME=\"uint8Prop\" TYPE=\"uint8\"><VALUE>5</VALUE></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"uint64ArrayProp\" TYPE=\"uint64\" ARRAYSIZE=\"3\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<PROPERTY NAME=\"sint8PropWithSimpleQual\" TYPE=\"sint8\"></PROPERTY><PROPERTY NAME=\"uint32PropWithArrayQual\" TYPE=\"uint32\"></PROPERTY>")
        PAL_T("<METHOD NAME=\"Uint32EmptyParamMethod\" TYPE=\"uint32\"></METHOD>")
        PAL_T("<METHOD NAME=\"Sint64SimpleParamsMethod\" TYPE=\"sint64\"><PARAMETER NAME=\"param1\" TYPE=\"uint16\"></PARAMETER><PARAMETER NAME=\"param2\" TYPE=\"sint16\"></PARAMETER></METHOD>")
        PAL_T("<METHOD NAME=\"MultiQualMethod\" TYPE=\"uint32\"><PARAMETER NAME=\"inputParam\" TYPE=\"uint64\"></PARAMETER><PARAMETER NAME=\"outputParam\" TYPE=\"uint64\"></PARAMETER></METHOD></CLASS>");
	TestClassSerialization(PAL_T("MyOptionTestClass"), expectedSerialization, NitsHere(), 0);
    const MI_Char *expectedDerivedSerialization =
        PAL_T("<CLASS NAME=\"MyOptionTestDerivedClass\" SUPERCLASS=\"MyOptionTestClass\">")
        PAL_T("<PROPERTY NAME=\"uint8Prop\" TYPE=\"uint8\"><VALUE>10</VALUE></PROPERTY>")
        PAL_T("<PROPERTY NAME=\"uint32PropWithArrayQual\" TYPE=\"uint32\"></PROPERTY><PROPERTY NAME=\"uint8Property\" TYPE=\"uint8\"><VALUE>7</VALUE></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"uint64ArrayProperty\" TYPE=\"uint64\" ARRAYSIZE=\"5\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE><VALUE>4</VALUE><VALUE>5</VALUE></VALUE.ARRAY></PROPERTY.ARRAY>")
        PAL_T("<METHOD NAME=\"Sint64SimpleParamsMethod\" TYPE=\"sint64\"><PARAMETER NAME=\"param1\" TYPE=\"uint16\"></PARAMETER><PARAMETER NAME=\"param2\" TYPE=\"sint16\"></PARAMETER><PARAMETER NAME=\"param3\" TYPE=\"string\"></PARAMETER></METHOD>")
        PAL_T("<METHOD NAME=\"MyMethod\" TYPE=\"uint32\"><PARAMETER NAME=\"input\" TYPE=\"uint32\"></PARAMETER></METHOD></CLASS>");
	TestClassSerialization(PAL_T("MyOptionTestDerivedClass"), expectedDerivedSerialization, NitsHere(), 0);
NitsEndTest

// Note: Every time you add a new class in schema.mof and regenerate the provider
// please update the schema.c for this class MyClassForTestingAddedEmbeddedQualifier
// to remove all qualifiers from the propertyDecls; this test is specifically testing
// fabrication of qualifiers by wsman serializer.
NitsTest(Class_Embedded_Qualifiers_Not_Explicitly_Specified_In_Schema)
    const MI_Char *expectedSerialization =
        PAL_T("<CLASS NAME=\"MyClassForTestingAddedEmbeddedQualifier\" DERIVATION=\"\">")
        PAL_T("<PROPERTY NAME=\"v_embeddedObject\" TYPE=\"string\" CLASSORIGIN=\"MyClassForTestingAddedEmbeddedQualifier\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY>")
        PAL_T("<PROPERTY NAME=\"v_embeddedInstance\" TYPE=\"string\" CLASSORIGIN=\"MyClassForTestingAddedEmbeddedQualifier\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>MySimplePropertiesClass</VALUE></QUALIFIER></PROPERTY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"a_embeddedObject\" TYPE=\"string\" CLASSORIGIN=\"MyClassForTestingAddedEmbeddedQualifier\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.ARRAY>")
        PAL_T("<PROPERTY.ARRAY NAME=\"a_embeddedInstance\" TYPE=\"string\" CLASSORIGIN=\"MyClassForTestingAddedEmbeddedQualifier\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>MySimplePropertiesClass</VALUE></QUALIFIER></PROPERTY.ARRAY></CLASS>");
    TestStandardRttiSerialization(PAL_T("MyClassForTestingAddedEmbeddedQualifier"), expectedSerialization, NitsHere());
NitsEndTest

NitsTest(Class_RestrictedQuals_OnBaseElements)
    const MI_Char *expectedSerialization =
        PAL_T("<CLASS NAME=\"MyClassRestrictedQualsOnBaseElements\" DERIVATION=\"\">")
        PAL_T("<QUALIFIER NAME=\"Deprecated\" TYPE=\"string\" TOSUBCLASS=\"false\"><VALUE.ARRAY><VALUE>No Value</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<PROPERTY NAME=\"myProp\" TYPE=\"uint32\" CLASSORIGIN=\"MyClassRestrictedQualsOnBaseElements\"><QUALIFIER NAME=\"Deprecated\" TYPE=\"string\" TOSUBCLASS=\"false\"><VALUE.ARRAY><VALUE>No Value</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint8Qual\" TYPE=\"uint8\" TRANSLATABLE=\"true\"><VALUE>10</VALUE></QUALIFIER></PROPERTY>")
        PAL_T("<METHOD NAME=\"myMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyClassRestrictedQualsOnBaseElements\"><QUALIFIER NAME=\"Deprecated\" TYPE=\"string\" TOSUBCLASS=\"false\"><VALUE.ARRAY><VALUE>My value</VALUE></VALUE.ARRAY></QUALIFIER>")
        PAL_T("<QUALIFIER NAME=\"Uint32Qual\" TYPE=\"uint32\" TRANSLATABLE=\"true\"><VALUE>11</VALUE></QUALIFIER></METHOD></CLASS>");
	TestStandardRttiSerialization(PAL_T("MyClassRestrictedQualsOnBaseElements"), expectedSerialization, NitsHere());
NitsEndTest

NitsTest(Class_Derived_From_RestrictedQuals_OnBaseElements)
    const MI_Char *expectedSerialization =
        PAL_T("<CLASS NAME=\"MyDerivedClassOfRestrictedQualsOnBaseElements\" SUPERCLASS=\"MyClassRestrictedQualsOnBaseElements\" DERIVATION=\"MyClassRestrictedQualsOnBaseElements\">")
        PAL_T("<PROPERTY NAME=\"myProp\" TYPE=\"uint32\" CLASSORIGIN=\"MyClassRestrictedQualsOnBaseElements\" PROPAGATED=\"true\"><QUALIFIER NAME=\"Uint8Qual\" TYPE=\"uint8\" TRANSLATABLE=\"true\"><VALUE>10</VALUE></QUALIFIER></PROPERTY>")
        PAL_T("<METHOD NAME=\"myMethod\" TYPE=\"uint32\" CLASSORIGIN=\"MyClassRestrictedQualsOnBaseElements\" PROPAGATED=\"true\"><QUALIFIER NAME=\"Uint32Qual\" TYPE=\"uint32\" TRANSLATABLE=\"true\"><VALUE>11</VALUE></QUALIFIER></METHOD></CLASS>");
    TestStandardRttiSerialization(PAL_T("MyDerivedClassOfRestrictedQualsOnBaseElements"), expectedSerialization, NitsHere());
NitsEndTest
//NitsTest()
	//TestStandardRttiSerialization(PAL_T(""), PAL_T(""), NitsHere());
//NitsEndTest
