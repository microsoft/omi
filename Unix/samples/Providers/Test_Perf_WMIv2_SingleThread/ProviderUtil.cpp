/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "ProviderUtil.h"

#ifdef _MSC_VER
#include <strsafe.h>
#endif

#include <pal/format.h>

#define PSS_NONE 0 
#define PSS_VERBOSE  1
#define PSS_DEBUG 2
#define PSS_WARNING 4 
#define PSS_ERROR 8
#define PSS_PROGRESS 16
#define PSS_SHOULDPROCESS 32
#define PSS_SHOULDCONTINUE 64

MI_Result CreateEmbeddedInstance(MI_Context* context, Perf_Embedded* embeddedInstance)
{
    MI_Result result = MI_RESULT_FAILED;
    result = Perf_Embedded_Construct(embeddedInstance, context);
    if(result != MI_RESULT_OK)
    {
        return result;
    }

    result = Perf_Embedded_Set_v_embeddedKey(embeddedInstance, 1);
    if(result != MI_RESULT_OK)
    {
        return result;
    }

    result = Perf_Embedded_Set_v_string(embeddedInstance, MI_T("Embedded String"));

    return result;
}

void SetDateTime(MI_Datetime *date)
{
    MI_Timestamp timeStamp;
    timeStamp.year = 2011;
    timeStamp.month = 3;
    timeStamp.day = 2;
    timeStamp.hour = 14;
    timeStamp.minute = 42;
    timeStamp.second = 47;
    timeStamp.microseconds = 0;
    timeStamp.utc = 830;
    date->isTimestamp = 1;
    date->u.timestamp = timeStamp;
}

MI_Result SetPropertyValue(MI_Context* context, MI_Instance* newInstance, MI_Uint32 index, MI_Value val, MI_Type type, MI_Uint32 flags, MI_Uint64 keyValue)
{    
    MI_Uint8 i = 0;
    MI_Result result = MI_RESULT_FAILED;
    MI_Datetime date;
    Perf_Embedded embeddedInstance;
    MI_Boolean aBool[5] = { MI_TRUE, MI_FALSE,MI_TRUE, MI_FALSE, MI_TRUE};
    MI_Uint8 aUint8[5] = {1,2,3,4,5};
    MI_Sint8 aSint8[5] = {-1,-2,-3,-4,-5};
    MI_Uint16 aUint16[5] = {6,7,8,9,10};
    MI_Sint16 aSint16[5] = {-6,-7,-8,-9,-10};
    MI_Uint32 aUint32[5] = {11,12,13,14,15};
    MI_Sint32 aSint32[5] = {-11,-12,-13,-14,-15};
    MI_Uint64 aUint64[5] = {16,17,18,19,20};
    MI_Sint64 aSint64[5] = {-16,-17,-18,-19,-20};
    MI_Real32 aReal32[5] = {1E1,2E2,3E3,4E4,5E5};
    MI_Real64 aReal64[5] = {-6E1,-7E2,-8E3,-9E4,-10E5};
    MI_Char16 aChar16[5] = {33,34,35,36,37};
    MI_Datetime aDatetime[5];
    MI_Char* aString[5];
    //MI_Char* aString[5] = {MI_T("Embedded String1"),MI_T("Embedded String2"),MI_T("Embedded String3"),MI_T("Embedded String4"),MI_T("Embedded String5")};
    Perf_Embedded aInstance[5]; //will be used for ref as well as embedded instance arrays

    MI_Char vStringVal[100];
    memset(vStringVal, 0, sizeof(MI_Char) * 100);

    MI_Char aString0[100];
    MI_Char aString1[100];
    MI_Char aString2[100];
    MI_Char aString3[100];
    MI_Char aString4[100];

    memset(aString0, 0, sizeof(MI_Char) * 100);
    memset(aString1, 0, sizeof(MI_Char) * 100);
    memset(aString2, 0, sizeof(MI_Char) * 100);
    memset(aString3, 0, sizeof(MI_Char) * 100);
    memset(aString4, 0, sizeof(MI_Char) * 100);

    Stprintf(aString0, 100, MI_T("%s"), MI_T("Embedded String1"));
    Stprintf(aString1, 100, MI_T("%s"), MI_T("Embedded String2"));
    Stprintf(aString2, 100, MI_T("%s"), MI_T("Embedded String3"));
    Stprintf(aString3, 100, MI_T("%s"), MI_T("Embedded String4"));
    Stprintf(aString4, 100, MI_T("%s"), MI_T("Embedded String5"));

    aString[0] = aString0;
    aString[1] = aString1;
    aString[2] = aString2;
    aString[3] = aString3;
    aString[4] = aString4;

    MI_Array arr;
    arr.size = 5;

    switch(type)
    {
    case MI_BOOLEAN:
        val.boolean = MI_TRUE;
        break;

    case MI_UINT8:
        val.uint8 = 2;
        break;

    case MI_SINT8:
        val.sint8 = -2;
        break;

    case MI_UINT16:
        val.uint16 = 4;
        break;

    case MI_SINT16:
        val.sint16 = -4;
        break;

    case MI_UINT32:
        val.uint32 = 8;
        break;

    case MI_SINT32:
        val.sint16 = -8;
        break;

    case MI_UINT64:
        val.uint64 = keyValue;
        break;

    case MI_SINT64:
        val.sint64 = -16;
        break;

    case MI_REAL32:
        val.real32 = 8E1;
        break;

    case MI_REAL64:
        val.real32 = -16E1;
        break;

    case MI_CHAR16:
        val.char16 = 33;
        break;

    case MI_DATETIME:        
        SetDateTime(&date);
        val.datetime = date;
        break;

    case MI_STRING:
        Stprintf(vStringVal, 100, MI_T("%s"), MI_T("Sample string"));
        val.string = vStringVal;
        //val.string = MI_T("Sample string");
        break;

    case MI_REFERENCE:        
    case MI_INSTANCE:
        result = CreateEmbeddedInstance(context, &embeddedInstance);
        if(result != MI_RESULT_OK)
            return result;

        if(type == MI_INSTANCE)
            val.instance = &embeddedInstance.__instance;
        else
            val.reference = &embeddedInstance.__instance;

        break;        

    case MI_BOOLEANA:        
        arr.data = (void *) aBool;
        result = MI_Instance_SetElementAt(newInstance, index, (MI_Value*)&arr, type, 0);
        return result;

    case MI_UINT8A:        
        arr.data = (void *) aUint8;
        result = MI_Instance_SetElementAt(newInstance, index, (MI_Value*)&arr, type, 0);
        return result;

    case MI_SINT8A:
        arr.data = (void *) aSint8;
        result = MI_Instance_SetElementAt(newInstance, index, (MI_Value*)&arr, type, 0);
        return result;

    case MI_UINT16A:
        arr.data = (void *) aUint16;
        result = MI_Instance_SetElementAt(newInstance, index, (MI_Value*)&arr, type, 0);
        return result;

    case MI_SINT16A:
        arr.data = (void *) aSint16;
        result = MI_Instance_SetElementAt(newInstance, index, (MI_Value*)&arr, type, 0);
        return result;

    case MI_UINT32A:
        arr.data = (void *) aUint32;
        result = MI_Instance_SetElementAt(newInstance, index, (MI_Value*)&arr, type, 0);
        return result;

    case MI_SINT32A:
        arr.data = (void *) aSint32;
        result = MI_Instance_SetElementAt(newInstance, index, (MI_Value*)&arr, type, 0);
        return result;

    case MI_UINT64A:
        arr.data = (void *) aUint64;
        result = MI_Instance_SetElementAt(newInstance, index, (MI_Value*)&arr, type, 0);
        return result;

    case MI_SINT64A:
        arr.data = (void *) aSint64;
        result = MI_Instance_SetElementAt(newInstance, index, (MI_Value*)&arr, type, 0);
        return result;

    case MI_REAL32A:
        arr.data = (void *) aReal32;
        result = MI_Instance_SetElementAt(newInstance, index, (MI_Value*)&arr, type, 0);
        return result;

    case MI_REAL64A:
        arr.data = (void *) aReal64;
        result = MI_Instance_SetElementAt(newInstance, index, (MI_Value*)&arr, type, 0);
        return result;

    case MI_CHAR16A:
        arr.data = (void *) aChar16;
        result = MI_Instance_SetElementAt(newInstance, index, (MI_Value*)&arr, type, 0);
        return result;

    case MI_DATETIMEA:
        SetDateTime(&aDatetime[0]);
        SetDateTime(&aDatetime[1]);
        SetDateTime(&aDatetime[2]);
        SetDateTime(&aDatetime[3]);
        SetDateTime(&aDatetime[4]);

        arr.data = (void *) aDatetime;
        result = MI_Instance_SetElementAt(newInstance, index, (MI_Value*)&arr, type, 0);
        return result;

    case MI_STRINGA:
        arr.data = (void *) aString;
        result = MI_Instance_SetElementAt(newInstance, index, (MI_Value*)&arr, type, 0);
        return result;


    case MI_REFERENCEA:
    case MI_INSTANCEA:    
        for(i = 0; i < 5; i++)
        {
            CreateEmbeddedInstance(context, &aInstance[i]);
        }

        arr.data = (void *) aInstance;
        result = MI_Instance_SetElementAt(newInstance, index, (MI_Value*)&arr, type, 0);
        break;        
    }

    result = MI_Instance_SetElementAt(newInstance, index, &val, type, 0);
    if(result != MI_RESULT_OK)
        return result;

    if(type == MI_INSTANCE || type == MI_REFERENCE)
    {
        MI_Instance_Destruct(&embeddedInstance.__instance);
    }
    else if(type == MI_INSTANCEA || type == MI_REFERENCEA)
    {
        for(i = 0; i < 5; i++)
        {
            MI_Instance_Destruct(&aInstance[i].__instance);
        }
    }

    return result;
}

MI_Result FillInstance(MI_Context* context, MI_Instance* newInstance, MI_Uint64 keyValue)
{
    MI_Result result = MI_RESULT_FAILED;
    MI_Uint32 i=0;
    MI_Uint32 instanceElementCount = 0;
    MI_Value val;
    MI_Type type;
    MI_Uint32 flags;

    result = MI_Instance_GetElementCount(newInstance, &instanceElementCount);
    if(result != MI_RESULT_OK)
        return result;

    for(i=0; i < instanceElementCount; ++i)
    {
        result = MI_Instance_GetElementAt(newInstance, i, 0, &val, &type, &flags);
        if(result != MI_RESULT_OK)
            return result;

        result = SetPropertyValue(context, newInstance, i, val, type, flags, keyValue);
        if(result != MI_RESULT_OK)
            return result;
    }

    return result;
}

MI_Result PostVerbose(MI_Context* context, const MI_Char* message, MI_Uint32 psSemanticsCount)
{
    MI_Result result = MI_RESULT_FAILED;

    for(MI_Uint16 i = 0; i < psSemanticsCount; i++)
    {
        result = MI_WriteVerbose(context, message);
        if(result != MI_RESULT_OK)
            return result;
    }

    return result;
}

MI_Result PostWarning(MI_Context* context, const MI_Char* message, MI_Uint32 psSemanticsCount)
{
    MI_Result result = MI_RESULT_FAILED;

    for(MI_Uint16 i = 0; i < psSemanticsCount; i++)
    {
        result = MI_WriteWarning(context, message);
        if(result != MI_RESULT_OK)
            return result;
    }

    return result;
}

MI_Result PostDebug(MI_Context* context, const MI_Char* message, MI_Uint32 psSemanticsCount)
{
    MI_Result result = MI_RESULT_FAILED;

    for(MI_Uint16 i = 0; i < psSemanticsCount; i++)
    {
        result = MI_WriteDebug(context, message);
        if(result != MI_RESULT_OK)
            return result;
    }

    return result;
}

//MI_Result PostError(MI_Context* context, MI_Char* errorId, MI_ErrorCategory errorCategory, MI_Char* errorMessage, MI_Char* targetName, MI_Boolean* flag, MI_Uint32 psSemanticsCount)
MI_Result PostError(MI_Context* context, MI_Uint32 resultCode, const MI_Char* resultType, const MI_Char* errorMessage, MI_Boolean* flag, MI_Uint32 psSemanticsCount)
{
    MI_Result result = MI_RESULT_FAILED;

    for(MI_Uint16 i = 0; i < psSemanticsCount; i++)
    {
        //result = MI_WriteError(context, errorId, errorCategory, errorMessage, targetName, flag);
        result = MI_WriteError(context, resultCode, resultType, errorMessage, flag);
        if(result != MI_RESULT_OK)
            return result;
    }

    return result;
}


MI_Result PostProgress(MI_Context* context, const MI_Char* activity, const MI_Char* currentOperation, const MI_Char* statusDescription, MI_Uint32 psSemanticsCount)
{
    MI_Result result = MI_RESULT_FAILED;

    for(MI_Uint16 i = 0; i < psSemanticsCount; i++)
    {
        result = MI_WriteProgress(context, activity, currentOperation, statusDescription, i+1*100 / psSemanticsCount, psSemanticsCount - i+1);
        if(result != MI_RESULT_OK)
            return result;
    }

    return result;
}

MI_Result PostShouldContinue(MI_Context* context, const MI_Char* message, MI_Boolean* flag, MI_Uint32 psSemanticsCount)
{
    MI_Result result = MI_RESULT_FAILED;

    for(MI_Uint16 i = 0; i < psSemanticsCount; i++)
    {
        result = MI_ShouldContinue(context, message, flag);
        if(result != MI_RESULT_OK)
            return result;
    }

    return result;
}

MI_Result PostShouldProcess(MI_Context* context, const MI_Char* target, const MI_Char* action, MI_Boolean* flag, MI_Uint32 psSemanticsCount)
{
    MI_Result result = MI_RESULT_FAILED;

    for(MI_Uint16 i = 0; i < psSemanticsCount; i++)
    {
        result = MI_ShouldProcess(context, target, action, flag);
        if(result != MI_RESULT_OK)
            return result;
    }

    return result;
}

//Flags 0 == None
//        1 == Verbose
//        2 == Debug
//        4 == Warning
//        8 == Error
//        16 == Progress
//        32 == ShouldProcess
//        64 == ShouldContinue
MI_Result PostPsSemantics(MI_Context* context, MI_Uint32 psSemanticsFlags, MI_Uint32 psSemanticsCount)
{
    MI_Result result = MI_RESULT_FAILED;

    /*
    MI_Boolean isVerbose, isDebug, isWarning, isError, isProgress, isShouldProcess, isShouldContinue, flag = MI_FALSE;
    MI_Uint32 i = 0;

    if(psSemanticsFlags == 0 || psSemanticsCount == 0)
    {
    return MI_RESULT_OK;
    }

    isVerbose = (MI_Boolean) (psSemanticsFlags >> 0) % 2;
    isDebug = (MI_Boolean) (psSemanticsFlags >> 1) % 2;
    isWarning = (MI_Boolean) (psSemanticsFlags >> 2) % 2;
    isError = (MI_Boolean) (psSemanticsFlags >> 3) % 2;
    isProgress = (MI_Boolean) (psSemanticsFlags >> 4) % 2;
    isShouldProcess = (MI_Boolean) (psSemanticsFlags >> 5) % 2;
    isShouldContinue = (MI_Boolean) (psSemanticsFlags >> 6) % 2;

    if(isVerbose)
    {
    result = PostVerbose(context, MI_T("Verbose Message"), psSemanticsCount);
    }

    if(isWarning)
    {
    result = PostWarning(context, MI_T("Warning Message"), psSemanticsCount);
    }

    if(isDebug)
    {
    result = PostDebug(context, MI_T("Debug Message"), psSemanticsCount);
    }

    if(isError)
    {
    result = PostError(context, MI_T("Error ID string"), MI_ERRORCATEGORY_NOT_SPECIFIED, MI_T("WriteError Message string"), MI_T("WriteError Targetname"), &flag, psSemanticsCount);
    result = PostError(context, MI_RESULT_FAILED, MI_RESULT_TYPE_MI, MI_T("WriteError Message string"), &flag, psSemanticsCount);
    }

    if(isProgress)
    {
    result = PostProgress(context, MI_T("Activity string"), MI_T("Current Operation string"), MI_T("Status Description"), psSemanticsCount);
    }

    if(isShouldContinue)
    {
    result = PostShouldContinue(context, MI_T("ShouldContinue Message"), &flag, psSemanticsCount);
    }

    if(isShouldProcess)
    {
    result = PostShouldProcess(context, MI_T("Target string"), MI_T("Action string"), &flag, psSemanticsCount);
    }
    */

    return result;
}
