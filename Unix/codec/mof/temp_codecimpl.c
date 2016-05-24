/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */

#ifdef _PREFAST_
# pragma prefast (push)
# pragma prefast (disable: 28252)
# pragma prefast (disable: 28253)
#endif

#include <state.h>
#include <base/batch.h>
#include <nits/base/nits.h>
#define _NO_PAL
#include <omiutils/omiutils.h>
#include "codecimpl.h"
#include "instanceutil.h"
#include "ptrarray.h"

#ifdef _PREFAST_
# pragma prefast (pop)
#endif

#define MAX_RESULT_PAGE_SIZE 1024*1000

/*
**==============================================================================
**
** Class_New function
**      Create a class based on a classDecl.  If the classDecl has an
**      owningClass then this method will bump the refcount on the the owning class
**
** TODO: To link to base.lib directly upon the duplicate code get resolved
**       between wmiv2\common and winomi\base
**==============================================================================
*/
typedef MI_Result (MI_CALL *Class_NewFunc)(
        _In_ const MI_ClassDecl *classDecl,
        _In_opt_z_ const MI_Char *namespaceName,
        _In_opt_z_ const MI_Char *serverName,
        _In_opt_  void *batch,
        _Out_ MI_Class **newClass);

extern _Post_z_ MI_Char* mof_LookupString(
    MI_Uint32 id,
    _Out_writes_z_(len) MI_Char *buffer,
    size_t len);

#if defined(_MSC_VER)
#include <class.h>
#else
#include "base/instance.h"
#include "base/class.h"
MI_Result MI_CALL Instance_InternalNew(  const MI_ClassDecl *classDecl, MI_Instance **selfOut)
{
	return Instance_New(selfOut, classDecl, NULL);
}
MI_Result MI_CALL Class_InternalNew ( const MI_ClassDecl *classDecl, const MI_Char *namespaceName, const MI_Char *serverName, void *batch, MI_Class **newClass)
{
	 return Class_New(classDecl, namespaceName, serverName,  newClass);
}
#endif


Instance_NewFunc _GetInstanceNewFunc()
{
#if defined(_MSC_VER)
    Instance_NewFunc f = (Instance_NewFunc)GetProcAddress(
        GetModuleHandle(L"miutils.dll"), 
        "Instance_New");
    if(NULL == f)
        f = Mof_Instance_New;
    return f;
#else
	return Instance_InternalNew;
#endif
}

Class_NewFunc _GetClassNewFunc()
{
#if defined(_MSC_VER)
    Class_NewFunc f = (Class_NewFunc)GetProcAddress(
        GetModuleHandle(L"miutils.dll"), 
        "Class_New");
    return f;
#else
	return Class_InternalNew;
#endif
}
Class_NewFunc g_ClassNewFunc = NULL;

/* Release deserialized class array */
MI_INLINE void MI_CALL MI_Deserializer_ReleaseClassArray_MOF(
    _Inout_ MI_ExtendedArray* self)
{
    if (MI_Array_IsInternal((MI_Array*)self))
    {
        {
            MI_ClassA* classObjects = (MI_ClassA*)self;
            MI_Uint32 i;
            for (i = 0; i < classObjects->size; i++)
            {
                if (classObjects->data[i]) MI_Class_Delete(classObjects->data[i]);
            }
        }
        {
            Batch * batch = (Batch *)self->reserved3;
            if (batch)
            {
                Batch_Delete(batch);
            }
        }
    }
}

/* Release deserialized instance array */
MI_INLINE void MI_CALL MI_Deserializer_ReleaseInstanceArray_MOF(
    _Inout_ MI_ExtendedArray* self)
{
    if (MI_Array_IsInternal((MI_Array*)self))
    {
        {
            MI_InstanceA* instanceObjects = (MI_InstanceA*)self;
            MI_Uint32 i;
            for (i = 0; i < instanceObjects->size; i++)
            {
                if (instanceObjects->data[i]) MI_Instance_Delete(instanceObjects->data[i]);
            }
        }
        {
            Batch * batch = (Batch *)self->reserved3;
            if (batch)
            {
                Batch_Delete(batch);
            }
        }
    }
}

MI_ExtendedArrayFT _releaseClassArrayFT =
{
    MI_Deserializer_ReleaseClassArray_MOF,
};

MI_ExtendedArrayFT _releaseInstanceArrayFT =
{
    MI_Deserializer_ReleaseInstanceArray_MOF,
};


MI_INLINE MI_Result MI_MofCodec_InitOutputObject(
    _Inout_ MI_MofCodec *self)
{
    MI_ExtendedArray *arr = (MI_ExtendedArray *)Batch_GetClear(self->resultbatch, sizeof(MI_ExtendedArray));
    if (arr == NULL)
    {
        mof_report_error(&self->errhandler, ID_OUT_OF_MEMORY, "");
        return MI_RESULT_FAILED;
    }
    arr->reserved1 = cCodecMagic;
    arr->reserved3 = (ptrdiff_t)self->resultbatch;
    switch(self->type)
    {
        case DeserializeClassArray:
            self->classObjects = (MI_ClassA *)(&arr->arr);
            arr->reserved2 = (ptrdiff_t)(&_releaseClassArrayFT);
            break;
        case DeserializeInstanceArray:
            self->instanceObjects = (MI_InstanceA *)(&arr->arr);
            arr->reserved2 = (ptrdiff_t)(&_releaseInstanceArrayFT);
            break;
    }
    return MI_RESULT_OK;
}

/* Read and set operation options */
MI_Result _SetOperationOptions(
    _In_opt_ MI_OperationOptions *options,
    _Inout_ MI_MofCodec *self)
{
    MI_Value ignoreListValue;
    MI_Uint32 flags;
    MI_Type type;
    self->parser->param.schemacheck = SCHEMA_CHECK_DEFAULT;
    if (options)
    {
        const MI_Char * value;
        MI_Result r = MI_OperationOptions_GetString(options, MOFCODEC_SCHEMA_VALIDATION_OPTION_NAME, &value, NULL, NULL);
        if (r == MI_RESULT_OK)
        {
            if (Tcscasecmp(value, MOFCODEC_SCHEMA_VALIDATION_DEFAULT) == 0)
            {
            }
            else if (Tcscasecmp(value, MOFCODEC_SCHEMA_VALIDATION_STRICT) == 0)
            {
                self->parser->param.schemacheck = SCHEMA_CHECK_STRICT;
            }
            else if (Tcscasecmp(value, MOFCODEC_SCHEMA_VALIDATION_LOOSE) == 0)
            {
                self->parser->param.schemacheck = SCHEMA_CHECK_LOOSE;
            }
            else if (Tcscasecmp(value, MOFCODEC_SCHEMA_VALIDATION_IGNORE_PROPERTYTYPE) == 0)
            {
                self->parser->param.schemacheck = SCHEMA_CHECK_IGNORE_PROPERTYTYPE;
            }
            else if (Tcscasecmp(value, MOFCODEC_SCHEMA_VALIDATION_IGNORE) == 0)
            {
                self->parser->param.schemacheck = SCHEMA_CHECK_IGNORE;
            }
            else if (Tcscasecmp(value, MOFCODEC_SCHEMA_VALIDATION_DEFAULT_IGNORE_PROPERTIES) == 0 )
            {
                self->parser->param.schemacheck = SCHEMA_CHECK_DEFAULT_IGNORE_PROPERTIES;
            }
            else if (Tcscasecmp(value, MOFCODEC_SCHEMA_VALIDATION_STRICT_IGNORE_PROPERTIES) == 0 )
            {
                self->parser->param.schemacheck = SCHEMA_CHECK_STRICT_IGNORE_PROPERTIES;
            }
            else
            {
                mof_report_error(&self->errhandler, ID_PARAMETER_INVALID_OPTIONS_VALUE,
                    "", value, MOFCODEC_SCHEMA_VALIDATION_OPTION_NAME);
                return MI_RESULT_NOT_SUPPORTED;                    
            }
            
        }
        r = MI_OperationOptions_GetOption(options, MOFCODEC_SCHEMA_VALIDATION_OPTION_IGNOREPROPERTYLIST, &ignoreListValue, &type, NULL, &flags);
        if (r == MI_RESULT_OK && !(flags & MI_FLAG_NULL) && ignoreListValue.array.size > 0 && type == MI_STRINGA)
        {
            self->parser->param.ignorePropertyList.data = ignoreListValue.stringa.data;
            self->parser->param.ignorePropertyList.size = ignoreListValue.stringa.size;
        }
        

    }
    return MI_RESULT_OK;
}

void MI_CALL Mof_OnAliasDeclared(_In_ void *stateobj)
{
    MOF_State *state = (MOF_State *)stateobj;
    state->lastAliasDeclLineNo = state->buf.lineNo;
}


/* Helper function creates MI_Class object on MI_ClassDecl */
MI_Result _NewClassOnClassDecl(
    _In_ MI_MofCodec * self,
    _In_ const MI_ClassDecl* classDecl,
    _Outptr_result_maybenull_ MI_Class** newClass)
{
    MI_ClassDecl* decl = (MI_ClassDecl*)classDecl;
    MI_Result r;

    /* Set owningClass to -1 so that Class_New clones classdecl deeply */
    decl->owningClass = (MI_Class*)-1;

    if (!g_ClassNewFunc)
    {
        g_ClassNewFunc = _GetClassNewFunc();
    }
    if (g_ClassNewFunc)
    {
        r = g_ClassNewFunc(
            decl,
            self->parser->param.namespaceName,
            self->parser->param.serverName,
            NULL,
            newClass);
    }
    else
    {
        r = MI_RESULT_FAILED;
    }
#ifdef TEST_BUILD
    TASSERT(r == MI_RESULT_OK, L"Ignore out of memory error in unit test fault injection.");
#endif
    if (r != MI_RESULT_OK)
    {
        mof_report_error(&self->errhandler,
            ID_MI_CREATECLASS_FAILED,
            "",
            decl->name,
            r);
    }
    return r;
}

/* Parser need a clone copy of the given classdecl */
/* Return the classdecl if already cloned otherwise clone it */
MI_Result MI_CALL Mof_OnNewClassDecl(
    _In_ void * data,
    _In_ const MI_ClassDecl* classDecl,
    _Outptr_result_maybenull_ MI_ClassDecl** newClassDecl)
{
    MI_MofCodec * self = (MI_MofCodec*)data;
    MI_Uint32 i;
    ClassesOfInstance* coi = self->coi;
    *newClassDecl = NULL;

    /* Initialize if needed */
    if (coi == NULL)
    {
        coi = (ClassesOfInstance*)Batch_GetClear(self->resultbatch, sizeof(ClassesOfInstance));
        if (!coi)
        {
            mof_report_error(&self->errhandler, ID_OUT_OF_MEMORY, "");
            return MI_RESULT_FAILED;
        }
        self->coi = coi;
    }

    /* Search hashtable to see if classdecl is already added */
    if (coi->classesHash.nodes)
    {
        MI_Uint32 pos = StringHash_Find(&self->coi->classesHash, classDecl->name);
        if (pos != HASH_INVALID_POS)
        {
            *newClassDecl = self->coi->classes.data[pos]->classDecl;
            return MI_RESULT_OK;
        }
    }
    /* Search class array */
    else
    {
        for (i = 0; i < self->coi->classes.size; i++)
        {
            if (Tcscasecmp(self->coi->classes.data[i]->classDecl->name, classDecl->name) == 0)
            {
                *newClassDecl = self->coi->classes.data[i]->classDecl;
                return MI_RESULT_OK;
            }
        }
    }

    /* Add classdecl to cache */
    {
        MI_Result r;
        MI_Class* newclass;
        r = _NewClassOnClassDecl(self, classDecl, &newclass);
        if (r != MI_RESULT_OK)
        {
            return r;
        }
        _Analysis_assume_(newclass != NULL);
        /* Add ptr to array */
        {
            int c = Codec_PtrArray_Append_Batch(
                self->resultbatch,
                (Codec_PtrArray*)&self->coi->classes,
                newclass);
            if (c != 0)
            {
                mof_report_error(&self->errhandler, ID_OUT_OF_MEMORY, "");
                return MI_RESULT_FAILED;
            }
        }
        /* Initialize hash table if needed */
        if (self->coi->classes.size == HASH_THRESHOLD)
        {
            int r = StringHash_Init(self->resultbatch, &self->coi->classesHash);
            if (r != 0)
            {
                mof_report_error(&self->errhandler, ID_OUT_OF_MEMORY, "");
                return MI_RESULT_FAILED;
            }
            for (i = 0; i < self->coi->classes.size; i++)
            {
                const MI_ClassDecl *cd = self->coi->classes.data[i]->classDecl;
                r = StringHash_Add(self->resultbatch,
                    &self->coi->classesHash, i, cd->code, cd->name);
                if (r != 0)
                {
                    mof_report_error(&self->errhandler, ID_OUT_OF_MEMORY, "");
                    return MI_RESULT_FAILED;
                }
            }
        }
        /* Add classdecl to hash table */
        else if (self->coi->classes.size > HASH_THRESHOLD)
        {
            int r = StringHash_Add(self->resultbatch,
                &self->coi->classesHash,
                self->coi->classes.size-1,
                newclass->classDecl->code,
                newclass->classDecl->name);
            if (r != 0)
            {
                mof_report_error(&self->errhandler, ID_OUT_OF_MEMORY, "");
                return MI_RESULT_FAILED;
            }
        }
        *newClassDecl = newclass->classDecl;
        return MI_RESULT_OK;
    }
}

/* Helper function setup the callbacks of state object */
void _SetupStateCallback(
    _In_ MOF_State *state,
    _In_opt_ MI_MofCodec * self)
{
    state->Instance_InitDynamic = Mof_Instance_InitDynamic;
    state->onAliasDeclared = Mof_OnAliasDeclared;
    if (self)
    {
        state->Instance_New = self->Instance_New;
        self->errhandler.state = (void*) state;
        state->errhandler = &self->errhandler;
    }
    else
    {
        state->Instance_New = _GetInstanceNewFunc();
    }
    state->onNewClassDecl = Mof_OnNewClassDecl;
    state->onNewClassDeclData = (void*)self;
}

/* Initialize MI_MofCodec object */
_Use_decl_annotations_
MI_Result MI_MofCodec_Init(
    MI_Uint32 flags,
    MI_OperationOptions *options,
    MI_DeserializerCallbacks * callbacks,
    MI_Uint8 *buffer,
    MI_Uint32 bufferLength,
    MI_ClassA *classes,
    const MI_Char *serverName,
    const MI_Char *namespaceName,
    Codec_Type type,
    MI_MofCodec *self)
{
    MI_Result r;
    MI_UNREFERENCED_PARAMETER(options);
    MI_UNREFERENCED_PARAMETER(flags);

    self->errorCode = MI_RESULT_OK;
    self->errorInstance = NULL;
    self->parser = MOF_Parser_Init((void*)buffer, bufferLength, NULL, &r);
    if (NULL == self->parser)
    {
        switch(r)
        {
        case MI_RESULT_SERVER_LIMITS_EXCEEDED:
            mof_report_error(&self->errhandler, ID_OUT_OF_MEMORY, "");
            break;
        case MI_RESULT_NOT_SUPPORTED:
            mof_report_error(&self->errhandler, ID_PARAMETER_INVALID_BUFFER, "");
            break;
        default:
            break;
        }
        return MI_RESULT_FAILED;
    }

    /* Initialize self */
    self->type = type;
    self->bufferreadlength = 0;
    r = _SetOperationOptions(options, self);
    if (r != MI_RESULT_OK)
    {
        return r;
    }
    self->resultbatch = Batch_New(MAX_RESULT_PAGE_SIZE);
    if (NULL == self->resultbatch)
    {
        mof_report_error(&self->errhandler, ID_OUT_OF_MEMORY, "");
        return MI_RESULT_FAILED;
    }

    /* Initialize parser */
    self->parser->param.buffer = buffer;
    self->parser->param.bufferlength = bufferLength;
    self->parser->param.schemas = classes;
    self->parser->param.serverName = serverName;
    self->parser->param.namespaceName = namespaceName;
    if (callbacks)
    {
        memcpy(&self->parser->param.callbacks, callbacks, sizeof(MI_DeserializerCallbacks));
    }

    /* Initialize error handler, already initialized */

    /* Initialize state */
    _SetupStateCallback((MOF_State*)self->parser->state, self);

    return MI_RESULT_OK;
}

/* Deserialize one or multiple class(es) from given buffer */
_Use_decl_annotations_
MI_Result MI_MofCodec_Deserialize(MI_MofCodec *self)
{
    MI_Result r = MI_RESULT_NOT_SUPPORTED;
    MOF_State* state = (MOF_State*)self->parser->state;
    int res = MOF_Parser_Parse(self->parser);
    if (res != 0)
    {
        return MI_RESULT_FAILED;
    }
    self->bufferreadlength = (MI_Uint32)((char*)state->buf.cur - (char*)state->buf.buf);
    switch(self->type)
    {
    case DeserializeClassArray:
        {
            r = MI_MofCodec_InitOutputObject(self);
            if (r != MI_RESULT_OK)
            {
                return r;
            }
            self->classObjects->data = NULL;
            self->classObjects->size = 0;
            if (state->classDecls.size > 0)
            {
                MI_Uint32 i, j;
                MI_ClassA classtemp;
                classtemp.size = state->classDecls.size;
                classtemp.data = (MI_Class**)Batch_GetClear(self->resultbatch, sizeof(MI_Class*)*classtemp.size);
                if (NULL == classtemp.data)
                {
                    mof_report_error(&self->errhandler, ID_OUT_OF_MEMORY, "");
                    return MI_RESULT_FAILED;
                }
                for (i = 0; i < classtemp.size; i++)
                {
                    r = _NewClassOnClassDecl(self, state->classDecls.data[i], &classtemp.data[i]);
                    if (r != MI_RESULT_OK)
                    {
                        /* clean up temp data */
                        for (j = 0; j < i; j ++)
                        {
                            MI_Class_Delete(classtemp.data[i]);
                        }
                        return r;
                    }
                }
                /* Set final result */
                self->classObjects->data = classtemp.data;
                self->classObjects->size = classtemp.size;
            }
            self->resultbatch = NULL;
        }
        break;
    case DeserializeInstanceArray:
        {
            MOF_State* state = (MOF_State*)self->parser->state;
            r = MI_MofCodec_InitOutputObject(self);
            if (r != MI_RESULT_OK)
            {
                return r;
            }
            /* calculate how many instances need to return */
            {
                MI_Uint32 n = state->instanceDecls.size;
                MI_Uint32 i;
                MI_Uint32 count = 0;
                for (i = 0; i < n; i++)
                {
                    if (state->instanceDecls.data[i]->refs == 0 && state->instanceDecls.data[i]->instance != NULL)
                    {
                        count ++;
                    }
                }
                self->instanceObjects->data = NULL;
                self->instanceObjects->size = 0;
                if (count > 0)
                {
                    MI_Uint32 i;
                    MI_Uint32 instindex = 0;
                    MI_InstanceA instancetemp;
                    instancetemp.size = count;
                    instancetemp.data = (MI_Instance**)Batch_GetClear(
                        self->resultbatch,
                        sizeof(MI_Instance*)*count);
                    if (NULL == instancetemp.data)
                    {
                        mof_report_error(&self->errhandler, ID_OUT_OF_MEMORY, "");
                        return MI_RESULT_FAILED;
                    }
                    for (i = 0; i < n; i++)
                    {
                        if (state->instanceDecls.data[i]->refs == 0 && state->instanceDecls.data[i]->instance != NULL)
                        {
                            instancetemp.data[instindex++] = state->instanceDecls.data[i]->instance;
                            /* Detach from instance decl */
                            state->instanceDecls.data[i]->instance = NULL;
                        }
                    }
                    self->instanceObjects->data = instancetemp.data;
                    self->instanceObjects->size = instancetemp.size;
                }
                self->resultbatch = NULL;
            }
        }
        break;
    }
    return r;
}

/* Clean up codec object */
_Use_decl_annotations_
void MI_MofCodec_Delete(
    MI_MofCodec *self)
{
    if (self->parser)
    {
        MOF_Parser_Delete(self->parser);
    }
    if (self->errorInstance)
    {
        MI_Instance_Delete(self->errorInstance);
    }
    {
        /* Clean up cached schema(s) since returnned instance(s) */
        /* hold one reference to the schema */
        ClassesOfInstance* coi = self->coi;
        if (coi)
        {
            size_t i;
            for (i = 0; i < coi->classes.size; i++)
            {
                MI_Class_Delete(coi->classes.data[i]);
            }
        }
    }
    if (self->resultbatch)
    {
        Batch_Delete(self->resultbatch);
    }
}

_Use_decl_annotations_
void MI_MofCodec_onError(
    void * onErrorContext,
    MI_Uint32 errorCode,
    MI_Uint16 errorCategory,
    const MI_Char * errorType,
    const MI_Char * errorMessage)
{
    MI_MofCodec *self = (MI_MofCodec*)onErrorContext;
    if (self->errorInstance)
    {
        if ((errorCode == ID_SYNTAX_ERROR)||(errorCode == ID_INVALID_INITIALIZER))
        {
            /* Possible get ID_SYNTAX_ERROR after TOK_ERROR */
            /* Ignore in this case */
            return;
        }
        else
        {
            /* int * p =(int*)(void*)1; */
            /* *p = 0; */
            return;
        }
    }

    if (Tcscasecmp(errorType, MI_RESULT_TYPE_MI) == 0)
    {
        self->errorCode = (MI_Result)errorCode;
    }
    else
    {
        self->errorCode = MI_RESULT_FAILED;
    }

    {
        const MI_Char * eMessage = (errorMessage) ? errorMessage : MI_T("");
        const MI_Char * eType = (errorType) ? errorType : MI_T("");
        MI_Result r = MI_RESULT_OK;
#if defined(_MSC_VER)        
        r = CreateOMIError(eMessage, errorCode, eType, errorCategory, &(self->errorInstance));       
#else
        r = MI_Utilities_CimErrorFromErrorCode((MI_Uint32)errorCode, eType, eMessage, &(self->errorInstance));
        if( r == MI_RESULT_OK)
        {
            MI_Value value;
            value.uint16 = errorCategory;
            MI_Instance_SetElement(self->errorInstance, MI_T("OMI_Category"), &value, MI_UINT16, 0);
        }
#endif
#ifdef TEST_BUILD
        TASSERT(r == MI_RESULT_OK, L"Ignore out of memory error in unit test fault injection.");
#endif  
    if (r != MI_RESULT_OK)
        self->errorInstance = NULL;
    }
}

_Use_decl_annotations_
void MI_CALL MI_MOFParser_Delete(MOF_Parser* self)
{
    MOF_Parser_Delete(self);
}

_Use_decl_annotations_
MOF_Parser * MI_CALL MI_MOFParser_Init(
    void* buf,
    MI_Uint32 nBytes,
    Batch* batch)
{
    MOF_Parser * parser = MOF_Parser_Init(buf, nBytes, batch, NULL);
    if (parser == NULL)
    {
        return NULL;
    }
    parser->param.buffer = (MI_Uint8*)buf;
    parser->param.bufferlength = nBytes;
    parser->param.schemacheck = SCHEMA_CHECK_IGNORE;

    /* Initialize state */
    _SetupStateCallback((MOF_State*)parser->state, NULL);

    return parser;
}

_Use_decl_annotations_
int MI_CALL MI_MOFParser_Lex(MOF_Parser* self)
{
    return MOF_Parser_ParseLex(self);
}

_Use_decl_annotations_
int MI_CALL MI_MOFParser_Parse(MOF_Parser* self)
{
    return MOF_Parser_Parse(self);
}


/*
**==============================================================================
**
** Setup error handler of codec object, always success
**
**==============================================================================
*/
_Use_decl_annotations_
void MI_MofCodec_SetupErrorHandler(MI_MofCodec *self)
{
    self->errhandler.stringLookup = mof_LookupString;
    self->errhandler.onError = MI_MofCodec_onError;
    self->errhandler.onErrorContext = (void*)self;
    self->errhandler.state = NULL;
    self->Instance_New = _GetInstanceNewFunc();
}

/*
**==============================================================================
**
** Checking parameter via codec object, report error if false
**
**==============================================================================
*/
_Use_decl_annotations_
void MI_MofCodec_ParameterIsNull(
    MI_MofCodec *self,
    const MI_Char* paramname)
{
    mof_report_error(&self->errhandler,
        ID_PARAMETER_INVALID_VALUE_NULL,
        "",
        paramname);
}

_Use_decl_annotations_
void MI_MofCodec_ParameterIsNonZero(
    MI_MofCodec *self,
    const MI_Char* paramname)
{
    mof_report_error(&self->errhandler,
        ID_PARAMETER_INVALID_VALUE_UNEXPECTED_INTEGER,
        "",
        paramname,
        0);
}

_Use_decl_annotations_
void MI_MofCodec_ParameterOutOfRange(
    MI_MofCodec *self,
    const MI_Char* paramname,
    MI_Uint32 lbound,
    MI_Uint32 mbound,
    MI_Uint32 value)
{
    mof_report_error(&self->errhandler,
        ID_PARAMETER_INVALID_VALUE_OUT_OF_RANGE_INTEGER,
        "",
        paramname,
        lbound,
        mbound,
        value);
}

_Use_decl_annotations_
void MI_MofCodec_ParameterNotSupportStringValue(
    MI_MofCodec *self,
    const MI_Char* paramname,
    const MI_Char* value)
{
    mof_report_error(&self->errhandler,
        ID_PARAMETER_INVALID_VALUE_STRING,
        "",
        value,
        paramname);
}

void MI_MofCodec_InvalidResultClassCount(
    _In_ MI_MofCodec *self)
{
    mof_report_error(&self->errhandler,
        ID_PARAMETER_UNEXPECTED_RESULTCLASSCOUNT,
        "",
        MI_T("MI_Deserializer_DeserializeClassArray"));
}

void MI_MofCodec_InvalidResultInstanceCount(
    _In_ MI_MofCodec *self)
{
    mof_report_error(&self->errhandler,
        ID_PARAMETER_UNEXPECTED_RESULTINSTANCECOUNT,
        "",
        MI_T("MI_Deserializer_DeserializeInstanceArray"));
}


