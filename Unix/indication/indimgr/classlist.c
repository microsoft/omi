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

#include <indication/common/indilog.h>
#include <base/result.h>
#include <base/log.h>
#include <base/list.h>
#include <pal/format.h>
#include <pal/strings.h>
#include <omi_error/OMI_Error.h>
#include <omi_error/omierror.h>
#include <indication/indimgr/subscrip.h>
#include "classlist.h"
#include "host.h"

MI_ConstString _SubscribeStatusNames[] = {
    MI_T("SUBSCRIBE_INITED"),
    MI_T("SUBSCRIBE_SUB_STARTED"),
    MI_T("SUBSCRIBE_SUB_SUBSCRIBED"),
    MI_T("SUBSCRIBE_SUB_FAILED"),
    MI_T("SUBSCRIBE_SUB_CANCELLED"),
};

const MI_Char* SubscribeStatusName(SubscribeStatus status)
{
    if ((MI_Uint32)status <= (MI_Uint32) SUBSCRIBE_SUB_CANCELLED)
    {
        return _SubscribeStatusNames[(MI_Uint32)status];
    }
    return MI_T("UNKNOWN Status");
}

/* class type name for logging purpose */
MI_ConstString g_nRegType[3] = {
    MI_T("Default"),        /* PROVREG_DEFAULT */
    MI_T("Indication"),     /* PROVREG_INDICATION */
};

MI_INLINE MI_ConstString GetRegClassTypeName(_In_ ProvRegType regtype)
{
    DEBUG_ASSERT((MI_Uint32)regtype <= (MI_Uint32)PROVREG_INDICATION);
    return g_nRegType[regtype];
}

/* Figure out target class type based on given filter */
static SubscriptionTargetType _GetTargetType(
    _In_ Filter* filter)
{
    switch(filter->base.type)
    {
    case FILTER_UNARY_TEMP:
        return GetSubscriptionTargetType(filter->wql->className);
    default:
        return SUBSCRIP_TARGET_UNSUPPORTED;
    }
}

/*
* Discover reg info of given class and all its children
* and add into list
*/
static int _DiscoverClassAndChildrenClasses(
    _In_opt_z_ const MI_Char* cn,
    _In_z_ const MI_Char* ns,
    _Inout_ IndicationClassList *list,
    _Inout_ MI_Uint32* classcount,
    _In_ MI_Boolean children,
    _In_ ProvRegType regtype)
{
    /* Find the class first */
    MI_Result r;
    ProvRegPosition pos;
    const ProvRegEntry* e = ProvReg_FindProviderForClassByType(list->provreg, ns, cn, regtype, &r);
    if (e)
    {
        if (IndicationClassList_AddEntry(list, e))
        {
            trace_DiscoverClassesFoundTypeClass( GetRegClassTypeName(regtype), e->className );
            (*classcount)++;
        }
        else
            trace_DiscoverClassesFailedToAdd(e->className, r);
    }
    else
        trace_DiscoverClassesNoRegInfo(GetRegClassTypeName(regtype), (cn) ? cn : PAL_T(""), ns);

    /* return if no need to discover children class */
    if (MI_FALSE == children)
        return 0;

    /* Begin enumeration of classes for this request */
    {
        r = ProvReg_BeginClasses(list->provreg, ns, cn, MI_TRUE, &pos, MI_FALSE);
        if (MI_RESULT_OK != r)
        {
            trace_DiscoverClassesBeginFailed(r, tcs(Result_ToString(r)), tcs(ns), tcs(cn));
            return -1;
        }
    }

    /* While more classes */
    for (;;)
    {
        const ZChar* derived = NULL;
        MI_Boolean done;

        r = ProvReg_NextClass(&pos, &derived, &done);

        if (done)
            break;

        if (MI_RESULT_OK != r)
        {
            trace_DiscoverClassesNextFailed(r, tcs(Result_ToString(r)), tcs(ns), tcs(cn));
            return -1;
        }
        e = ProvReg_FindProviderForClassByType(list->provreg, ns, derived, regtype, &r);
        if (e)
        {
            if (IndicationClassList_AddEntry(list, e))
            {
                trace_DiscoverClassesFoundTypeClass(GetRegClassTypeName(regtype), e->className);
                (*classcount)++;
            }
            else
                trace_DiscoverClassesFailedToAdd(e->className, r);
        }
    }

    /* Finalize enumeration */
    {
        r = ProvReg_EndClasses(&pos);
        if (MI_RESULT_OK != r)
        {
            trace_DiscoverClassesEndFailed(r, tcs(Result_ToString(r)));
            return -1;
        }
    }
    return 0;
}


/* Represents an operand or operator appearing in the WHERE clause */
/* Extend WQL_Symbol for detecting whether ISA operator within OR clause */
typedef struct _WQL_SymbolEx
{
    WQL_Symbol base;
    MI_Boolean isa;
}
WQL_SymbolEx;

/*
**
** Find ISA operator and its target classname; Take following query for example,
**  Select * from CIM_InstCreation where SourceInstance isa "Win32_process"
**      (1) It's a lifecycle indication query
**      (2) It's target class is Win32_process
** 
** Following query is invalid since OR operator makes the target class ambiguous,
**  Select * from CIM_InstCreation where SourceInstance isa "Win32_process" OR (2>1)
** This query targets to all classes under the namespace, which is NOT a valid scenario
** to support; This function is to find whether an given query is a valid lifecycle
** indication query; If yes return 0 and output the target class name; otherwise return non 0;
**
**
*/
static MI_Result _FindLifecycleClass(
    _In_ SubscriptionTargetType stt,
    _In_ const WQL* wql,
    _Outptr_result_maybenull_z_ const ZChar** targetClassname,
    _Outptr_result_maybenull_z_ const MI_Char** errormessage)
{
    static const ZChar* sSourceInstanceProperty = ZT("SourceInstance");
    static const ZChar* sPreviousInstanceProperty = ZT("PreviousInstance");

    size_t i;
    WQL_SymbolEx symbols[WQL_MAX_SYMBOLS];
    size_t nsymbols = 0;
    MI_Boolean foundISA = MI_FALSE;
    MI_Result r = MI_RESULT_NOT_SUPPORTED;

    DEBUG_ASSERT (wql && wql->className && targetClassname && errormessage);

    *targetClassname = NULL;
    *errormessage = NULL;

    /* Fail if there is no WHERE clause */
    if (wql->nsymbols == 0)
        return MI_RESULT_OK;

    /* Perform postfix evaluation */
    for (i = 0; i < wql->nsymbols; i++)
    {
        const WQL_Symbol* sym = &wql->symbols[i];
        WQL_Type type = sym->type;

        if (nsymbols >= WQL_MAX_SYMBOLS)
            return r;

        switch (type)
        {
            case WQL_TYPE_AND:
            case WQL_TYPE_OR:
            {
                if (nsymbols < 2)
                    return r;

                {
                    WQL_SymbolEx s2 = symbols[--nsymbols];
                    WQL_SymbolEx s1 = symbols[--nsymbols];
                    WQL_SymbolEx s;
                    memset(&s, 0, sizeof(WQL_SymbolEx));
                    if (type == WQL_TYPE_OR)
                    {
                        if (s1.isa || s2.isa)
                        {
                            *errormessage = STR_LIFECYCLE_INDICATION_QUERY_ISA_OPERATOR_WITHIN_OR;
                            trace_FindLifecycleClass_InvalidLifecycleQuery();
                            return r;
                        }
                    }
                    if (s1.base.type != WQL_TYPE_BOOLEAN)
                        return r;
                    if (s2.base.type != WQL_TYPE_BOOLEAN)
                        return r;
                    s.base.type = WQL_TYPE_BOOLEAN;
                    s.base.value.boolean = 0;
                    s.isa = s1.isa || s2.isa;
                    symbols[nsymbols++] = s;
                }
                break;
            }
            case WQL_TYPE_NOT:
            {
                if (nsymbols < 1)
                    return r;
                {
                    WQL_SymbolEx s1 = symbols[--nsymbols];
                    WQL_SymbolEx s;
                    memset(&s, 0, sizeof(WQL_SymbolEx));
                    if (s1.base.type != WQL_TYPE_BOOLEAN)
                        return r;
                    s.base.type = WQL_TYPE_BOOLEAN;
                    s.base.value.boolean = 0;
                    s.isa = s1.isa;
                    symbols[nsymbols++] = s;
                }
                break;
            }
            case WQL_TYPE_EQ:
            case WQL_TYPE_NE:
            case WQL_TYPE_LT:
            case WQL_TYPE_LE:
            case WQL_TYPE_GT:
            case WQL_TYPE_GE:
            case WQL_TYPE_LIKE:
            {
                if (nsymbols < 2)
                    return r;
                {
                    WQL_SymbolEx s2 = symbols[--nsymbols];
                    WQL_SymbolEx s1 = symbols[--nsymbols];
                    WQL_SymbolEx s;
                    memset(&s, 0, sizeof(WQL_SymbolEx));
                    s.base.type = WQL_TYPE_BOOLEAN;
                    s.base.value.boolean = 0;
                    s.isa = s1.isa || s2.isa;
                    symbols[nsymbols++] = s;
                }
                break;
            }
            case WQL_TYPE_IDENTIFIER:
            {
                WQL_SymbolEx s;
                memset(&s, 0, sizeof(WQL_SymbolEx));
                s.base.type = WQL_TYPE_BOOLEAN;
                s.base.value.boolean = 0;
                s.isa = MI_FALSE;
                symbols[nsymbols++] = s;
                break;
            }
            case WQL_TYPE_BOOLEAN:
            case WQL_TYPE_INTEGER:
            case WQL_TYPE_REAL:
            case WQL_TYPE_STRING:
            case WQL_TYPE_NULL:
            case WQL_TYPE_ANY:
            {
                WQL_SymbolEx s;
                memcpy(&s.base, sym, sizeof(WQL_Symbol));
                s.isa = MI_FALSE;
                symbols[nsymbols++] = s;
                break;
            }
            case WQL_TYPE_ISA:
            {
                WQL_SymbolEx s2;
                WQL_SymbolEx s1;

                if (foundISA == MI_TRUE)
                {
                    *errormessage = STR_LIFECYCLE_INDICATION_QUERY_MORETHANONE_ISA_OPERATOR;
                    trace_FindLifecycleClass_UnsupportedLifecycleQuery();
                    return r;
                }

                if (nsymbols < 2)
                {
                    trace_FindLifecycleClass_TooFewOperandsISA();
                    return r;
                }

                s2 = symbols[--nsymbols];
                s1 = symbols[--nsymbols];

                if (s1.base.type != WQL_TYPE_STRING)
                {
                    trace_FindLifecycleClass_InvalidTokenType();
                    return r;
                }
                if (s2.base.type != WQL_TYPE_STRING)
                {
                    trace_FindLifecycleClass_InvalidTokenType();
                    return r;
                }

                /* Check Embedded property name is valid or not */
                {
                    int cmpresult = Tcscasecmp(sSourceInstanceProperty, s1.base.value.string);
                    if (cmpresult != 0)
                    {
                        if (stt == SUBSCRIP_TARGET_LIFECYCLE_MODIFY)
                        {
                            cmpresult = Tcscasecmp(sPreviousInstanceProperty, s1.base.value.string);
                        }
                    }
                    if (cmpresult != 0)
                    {
                        *errormessage = STR_LIFECYCLE_INDICATION_QUERY_ISA_HAS_WRONG_PROPERTYNAME;
                        r = MI_RESULT_INVALID_QUERY;
                        trace_FindLifecycleClass_InvalidEmbeddedProperty(s1.base.value.string);
                        return r;
                    }
                }

                /* Put ISA result symbol into stack */
                {
                    WQL_SymbolEx s;
                    memset(&s, 0, sizeof(WQL_SymbolEx));
                    s.base.type = WQL_TYPE_BOOLEAN;
                    s.base.value.boolean = MI_FALSE;
                    s.isa = MI_TRUE;
                    symbols[nsymbols++] = s;
                    *targetClassname = s2.base.value.string;
                    foundISA = MI_TRUE;
                    trace_FindLifecycleClass_FoundISAOperator(s1.base.value.string, s2.base.value.string);
                }
                break;
            }
        }
    }

    /* There should be exactly 1 symbol left on stack */
    if (nsymbols != 1)
    {
        trace_FindLifecycleClass_EvalHasMoreThanOneSymbol(nsymbols);
        return r;
    }

    /* There should be exactly 1 symbol left on stack */
    /* Final token on stack should be boolean */
    if (symbols[0].base.type != WQL_TYPE_BOOLEAN)
    {
        trace_FindLifecycleClass_EvalResultIsNotBool();
        return r;
    }

    if ( MI_FALSE == foundISA )
    {
        *errormessage = STR_LIFECYCLE_INDICATION_QUERY_NO_ISA_OPERATOR;
        return r;
    }
    else
        return MI_RESULT_OK;
}

/*
** Explore target indication classes' reg info based on given filter,
** and add into list
*/
static int _DiscoverIndicationClass(
    _In_ Filter* filter,
    _Inout_ IndicationClassList *list)
{
    MI_Uint32 classcount = 0;
    OMI_Error* omierror = NULL;
    MI_Result r = MI_RESULT_NOT_FOUND;
    MI_ConstString errmsg = STR_INDICATION_CLASS_NOT_FOUND;
    list->targetType = _GetTargetType(filter);

    switch(filter->base.type)
    {
    case FILTER_UNARY_TEMP:
        {
            /* Find target class */
            _DiscoverClassAndChildrenClasses(
                filter->wql->className,
                filter->SourceNamespaces.data[0],
                list,
                &classcount,
                MI_TRUE,
                PROVREG_INDICATION);

            /* Find target class if it is lifecycle query */
            switch( list->targetType)
            {
            case SUBSCRIP_TARGET_DEFAULT:
                break;
            case SUBSCRIP_TARGET_LIFECYCLE_ALL:
            case SUBSCRIP_TARGET_LIFECYCLE_CREATE:
            case SUBSCRIP_TARGET_LIFECYCLE_MODIFY:
            case SUBSCRIP_TARGET_LIFECYCLE_DELETE:
            case SUBSCRIP_TARGET_LIFECYCLE_READ:
            case SUBSCRIP_TARGET_LIFECYCLE_METHODCALL:
                /* Discover target classes for lifecycle indications */
                {
                    MI_ConstString classname = NULL;
                    MI_Result findresult = _FindLifecycleClass(list->targetType, filter->wql, &classname, &errmsg);
                    if (findresult == MI_RESULT_OK)
                    {
                        if (classname)
                        {
                            _DiscoverClassAndChildrenClasses(
                                classname,
                                filter->SourceNamespaces.data[0],
                                list,
                                &classcount,
                                MI_TRUE,
                                PROVREG_DEFAULT);
                        }
                        /* else - no where clause in the query */
                    }
                    else
                    {
                        r = findresult;
                        if (errmsg == NULL)
                            errmsg = STR_LIFECYCLE_INDICATION_QUERY_INVALID;
                        trace_DiscoverIndicationClass_InvalidLifeCycleQuery();
                    }
                }
                break;
            default:
                {
                    r = MI_RESULT_NOT_SUPPORTED;
                    trace_DiscoverIndicationClass_UnsupportedTargetClassType((int) list->targetType);
                    break;
                }
            }
        }
        break;
    default:
        break;
    }

    trace_DiscoverIndicationFoundClasses(classcount);
    if (classcount > 0)
        return 0;
    else
    {
        MI_Result res = OMI_ErrorFromErrorCode(
            NULL, 
            r,
            MI_RESULT_TYPE_MI,
            errmsg,
            &omierror);

        if (res != MI_RESULT_OK)
            trace_DiscoverIndicationClass_CreateInstanceFailed(res);
         
        Filter_SetLastError(filter, (omierror ? (&omierror->__instance) : NULL), r);
                
        return -1;
    }
}

/* Creates a class entry object */
_Use_decl_annotations_
IndicationClassEntry* IndicationClassList_AddEntry(
    IndicationClassList* list,
    const ProvRegEntry* regentry)
{
    IndicationClassEntry *entry = (IndicationClassEntry*)Batch_GetClear(
        list->batch, sizeof(IndicationClassEntry));
    if (NULL == entry)
    {
        LOGD_BATCH_OOM;
        return NULL;
    }
    entry->container = (void*)list;
    entry->regentry = regentry;
    entry->status = SUBSCRIBE_INITED;
    entry->subid = 0;
    List_Append((ListElem**)&list->head, (ListElem**)&list->tail, (ListElem*)entry);
    list->totalclass ++;
    return entry;
}

/* Creates a classlist object */
_Use_decl_annotations_
IndicationClassList* IndicationClassList_NewByFilter(
    ProvReg* provreg,
    Filter* filter)
{
    IndicationClassList* clist;
    Batch* batch;
    DEBUG_ASSERT(filter);
    DEBUG_ASSERT(provreg);

    batch = Batch_New(BATCH_MAX_PAGES);
    if (NULL == batch)
    {
        LOGD_BATCH_CREATE_OOM;
        return NULL;
    }
    clist = (IndicationClassList*)Batch_GetClear(batch, sizeof(IndicationClassList));
    if (NULL == clist)
    {
        LOGD_BATCH_OOM;
        Batch_Delete(batch);
        return NULL;
    }
    clist->batch = batch;
    clist->provreg = provreg;
    if (_DiscoverIndicationClass(filter, clist) != 0)
    {
        trace_IndicationClassList_NewByFilter_NoClassFound(filter->Query);
        Batch_Delete(batch);
        return NULL;
    }
    trace_IndicationClassListCreated(clist);
    return clist;
}

/* Delete a classlist object */
_Use_decl_annotations_
void IndicationClassList_Delete(
    IndicationClassList* self)
{
    trace_IndicationClassListDelete(self);
    DEBUG_ASSERT(self);
    DEBUG_ASSERT(self->batch);
    if(self->batch)
    {
        Batch_Delete(self->batch);
    }
    trace_IndicationClassListDeleteCompleted(self);
}
