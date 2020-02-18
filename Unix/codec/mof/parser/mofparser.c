/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "mofcommon.h"
#include "utility.h"
#include "mofparser.h"
#include "mof.qualifiers.h"

#define MAX_MOFPARSER_PAGE 1024000

MOF_GlobalData g_d = {0};

#if !defined(aix)
__attribute__((constructor)) 
#endif
void GlobalInitialize()
{
    g_d.b = Batch_New(MAX_MOFPARSER_PAGE);
    if (!g_d.b)
    {
        return;
    }
    {
        MI_QualifierDecl *d = gQualifiers;
        MI_Uint32 size = 0;
        MI_Uint32 i = 0;
        while(d->name != NULL)
        {
            size++;
            d++;
        }
        g_d.qualifierDecls.size = size;
        g_d.qualifierDecls.data = (MI_QualifierDecl**)Batch_Get(g_d.b, size * sizeof(MI_QualifierDecl *));
        if (g_d.qualifierDecls.data == NULL)
            return;
        d = gQualifiers;
        while(d->name != NULL)
        {
            g_d.qualifierDecls.data[i++] = d++;
        }
    }
    g_d.inited = MI_TRUE;
}

/*=============================================================================
**
** Free global data object
**
=============================================================================*/
#if !defined(aix)
__attribute__((destructor)) 
#endif
void GlobalFinalize()
{
    g_d.inited = MI_FALSE;
    Batch_Delete(g_d.b);
}

/*=============================================================================
**
** Initialize parser
**
=============================================================================*/
_Use_decl_annotations_
MOF_Parser * MOF_Parser_Init(void* buf, MI_Uint32 nBytes, Batch* batch, MI_Result *r)
{
    MOF_Parser *self = NULL;
    MI_Boolean deleteBatch = MI_FALSE;
    
    if (r) *r = MI_RESULT_OK;

    /* Check input buffer & encoding */
    if (nBytes <= 4)
    {
        if (r) *r = MI_RESULT_NOT_SUPPORTED;
        return NULL;
    }

    /* Create batch if none */
    if (!batch)
    {
        batch = Batch_New(MAX_MOFPARSER_PAGE);
        if (!batch)
        {
            if (r) *r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            return NULL;
        }
        deleteBatch = MI_TRUE;
    }

    /* Allocate the parser object */
    {
        self = (MOF_Parser*)Batch_GetClear(batch, sizeof(MOF_Parser));

        if (!self)
        {
            if (deleteBatch)
                Batch_Delete(batch);
            if (r) *r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            return NULL;
        }
    }

    /* Initialize MOF_Parser object */
    self->deleteBatch = deleteBatch;
    self->param.buffer = (MI_Uint8*)buf;

    /* Allocate the state object */
    {
        MOF_State *state = (MOF_State*)Batch_GetClear(batch, sizeof(MOF_State));

        if (!state)
        {
            if (deleteBatch) Batch_Delete(batch);
            if (r) *r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            return NULL;
        }

        /* Initialize parser state */
        {
            MI_Result res = mof_setupbuffer(self->param.buffer, nBytes, batch, &state->buf);
            if (res != MI_RESULT_OK)
            {
                if (deleteBatch) Batch_Delete(batch);
                if (r) *r = res;
                return NULL;
            }
        }
        state->parser = self;
        state->batch = batch;
        self->state = state;
    }
    return self;
}

/*=============================================================================
**
** Free parser
**
=============================================================================*/
_Use_decl_annotations_
void MOF_Parser_Delete(MOF_Parser* self)
{
    MOF_State * state = (MOF_State *) self->state;

    /* Delete class(es) read from classObjectNeeded callback*/
    if (self->classaObjectNeeded.size)
    {
        MI_Uint32 i;
        for (i = 0; i<self->classaObjectNeeded.size; i++)
        {
            if (self->classaObjectNeeded.data[i] != NULL)
            {
                MI_Class_Delete(self->classaObjectNeeded.data[i]);
                self->classaObjectNeeded.data[i] = NULL;
            }
        }
    }
    /* Delete created instance(s) if have */
    {
        MI_Uint32 n = state->instanceDecls.size;
        MI_Uint32 i;
        for (i = 0; i < n; i++)
        {
            if (state->instanceDecls.data[i]->instance != NULL)
            {
                MI_Instance_Delete(state->instanceDecls.data[i]->instance);
            }
        }
    }
    /* Delete batch */
    if (self->deleteBatch)
    {      
        Batch_Delete(state->batch);
    }
}

extern int moflex(MOF_State * state);

/*=============================================================================
**
** Get next token from buffer
**
=============================================================================*/
_Use_decl_annotations_
int MOF_Parser_ParseLex(MOF_Parser* self)
{
    return moflex((MOF_State*)self->state);
}


/*=============================================================================
**
** Declare YACC parser function
**
=============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

int mymofparser(MOF_State *state);

#ifdef __cplusplus
}
#endif

/*=============================================================================
**
** Parse the given mof buffer into  MI Data structure(s)
**
=============================================================================*/
_Use_decl_annotations_
int MOF_Parser_Parse(MOF_Parser* self)
{
    MOF_State* state = (MOF_State*)self->state;
    int r = mymofparser(state);
    /* Clean up included file buffer stack */
    while(state->bufTop > 0)
    {
        closeIncludeFile(state);
    }
    return r;
}
