#include "mi_memory_helper.hpp"


void
MI_Destroy (
    MI_Value& val,
    MI_Type const& type)
{
    _DESTROY_BOOKEND ("MI_Destroy");
    switch (type)
    {
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
        // no additional work to do for the above built-in types
        _DESTROY_PRINT ("built-in type");
        break;
    case MI_STRING:
        _DESTROY_PRINT ("MI_String");
        MI_Destroy (val.string);
        break;
    case MI_INSTANCE:
        // todo
        //MI_Destroy (val.instance);
        break;
    case MI_BOOLEANA:
        _DESTROY_PRINT ("MI_BooleanA");
        MI_Destroy (val.booleana);
        break;
    case MI_UINT8A:
        _DESTROY_PRINT ("MI_Uint8A");
        MI_Destroy (val.uint8a);
        break;
    case MI_SINT8A:
        _DESTROY_PRINT ("MI_Sint8A");
        MI_Destroy (val.sint8a);
        break;
    case MI_UINT16A:
        _DESTROY_PRINT ("MI_Uint16A");
        MI_Destroy (val.uint16a);
        break;
    case MI_SINT16A:
        _DESTROY_PRINT ("MI_Sint16A");
        MI_Destroy (val.sint16a);
        break;
    case MI_UINT32A:
        _DESTROY_PRINT ("MI_Uint32A");
        MI_Destroy (val.uint32a);
        break;
    case MI_SINT32A:
        _DESTROY_PRINT ("MI_Sint32A");
        MI_Destroy (val.sint32a);
        break;
    case MI_UINT64A:
        _DESTROY_PRINT ("MI_Uint64A");
        MI_Destroy (val.uint64a);
        break;
    case MI_SINT64A:
        _DESTROY_PRINT ("MI_Sint64A");
        MI_Destroy (val.sint64a);
        break;
    case MI_REAL32A:
        _DESTROY_PRINT ("MI_Real32A");
        MI_Destroy (val.real32a);
        break;
    case MI_REAL64A:
        _DESTROY_PRINT ("MI_Real64A");
        MI_Destroy (val.real64a);
        break;
    case MI_CHAR16A:
        _DESTROY_PRINT ("MI_Char16A");
        MI_Destroy (val.char16a);
        break;
    case MI_DATETIMEA:
        _DESTROY_PRINT ("MI_DatetimeA");
        MI_Destroy (val.datetimea);
        break;
    case MI_STRINGA:
        _DESTROY_PRINT ("MI_StringA");
        MI_Destroy (val.stringa);
        break;
    case MI_INSTANCEA:
        // todo
        //MI_Destroy (val.instancea);
        break;
    case MI_REFERENCE:
    case MI_REFERENCEA:
        // reference types are not handled
        break;
    }
}


void
MI_Delete (
    MI_Value*& pVal,
    MI_Type const& type)
{
    _DESTROY_BOOKEND ("MI_Delete");
    if (NULL != pVal)
    {
        _DESTROY_PRINT ("pVal is not NULL");
        MI_Destroy (*pVal, type);
        delete pVal;
        pVal = NULL;
    }
}
