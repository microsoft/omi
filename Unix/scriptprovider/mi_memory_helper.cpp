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
        break;
    case MI_STRING:
        MI_Destroy (val.string);
        break;
    case MI_BOOLEANA:
        MI_Destroy (val.booleana);
        break;
    case MI_UINT8A:
        MI_Destroy (val.uint8a);
        break;
    case MI_SINT8A:
        MI_Destroy (val.sint8a);
        break;
    case MI_UINT16A:
        MI_Destroy (val.uint16a);
        break;
    case MI_SINT16A:
        MI_Destroy (val.sint16a);
        break;
    case MI_UINT32A:
        MI_Destroy (val.uint32a);
        break;
    case MI_SINT32A:
        MI_Destroy (val.sint32a);
        break;
    case MI_UINT64A:
        MI_Destroy (val.uint64a);
        break;
    case MI_SINT64A:
        MI_Destroy (val.sint64a);
        break;
    case MI_REAL32A:
        MI_Destroy (val.real32a);
        break;
    case MI_REAL64A:
        MI_Destroy (val.real64a);
        break;
    case MI_CHAR16A:
        MI_Destroy (val.char16a);
        break;
    case MI_DATETIMEA:
        MI_Destroy (val.datetimea);
        break;
    case MI_STRINGA:
        MI_Destroy (val.stringa);
        break;
    case MI_INSTANCE:
    case MI_INSTANCEA:
    case MI_REFERENCE:
    case MI_REFERENCEA:
        // not necessary
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
