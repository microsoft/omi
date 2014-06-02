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

/* @migen@ */
#include <common.h>
#include <MI.h>
#include <pal/format.h>
#include "X_SmallNumber_Class_Provider.h"


MI_BEGIN_NAMESPACE

X_SmallNumber_Class_Provider::X_SmallNumber_Class_Provider(
        Module* module) :
    m_Module(module)
{
}

X_SmallNumber_Class_Provider::~X_SmallNumber_Class_Provider()
{
}
/* threading support */
extern "C"
{
typedef void* (MI_CALL *ThreadProc)(void* param);
}

#if defined(_MSC_VER)
typedef MI_Uint32   ThreadID;
#else
# include <pthread.h>
typedef pthread_t   ThreadID;
#endif

/* creates a thread; returns a handle. 
    each successful 'create-thread' has to be followed by 'close-thread-handle' */
static MI_Result _CreateThread(
    ThreadProc proc,
    void*  proc_param,
    ThreadID*  selfOut)
{
    MI_Result r = MI_RESULT_OK;
#if defined(_MSC_VER)
    HANDLE h = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(proc), proc_param, 0, 0);

    if (h != NULL)
    {
        r = MI_RESULT_OK;
        *selfOut = GetThreadId(h);
        CloseHandle(h);
    }
    else
    {
        r = MI_RESULT_FAILED;
    }
#else

    r = (0 == pthread_create(selfOut, NULL, proc, proc_param)) ? MI_RESULT_OK : MI_RESULT_FAILED;
#endif
    return r;
}

/* closes thread handle and frees related system resources;
    optionally, may wait for thread to complete */
static MI_Result _CloseThreadHanlde(
    ThreadID  self,
    MI_Boolean wait )
{
    MI_Result r = MI_RESULT_OK;
#if defined(_MSC_VER)
    if (wait)
    {
        HANDLE h = OpenThread( SYNCHRONIZE, FALSE, self);
        if (h != NULL)
        {
            DWORD res = WaitForSingleObject(h, INFINITE);
            r = (WAIT_OBJECT_0 == res) ? MI_RESULT_OK : MI_RESULT_FAILED;
            CloseHandle(h);
        }
        else
            r = MI_RESULT_FAILED;
    }
#else
    if (wait)
        pthread_join(self, 0);
    else
        pthread_detach(self);
#endif
    return r;
}


String _SpellNumber(Uint64 n, bool spellZero = true)
{
    if ( n > 999 )
    {
        String res = _SpellNumber(n / 1000);
        res += MI_T(" thousand ");
        res += _SpellNumber(n % 1000, false);
        return res;
    }
    else if ( n > 99 )
    {
        String res = _SpellNumber(n / 100);
        res += MI_T(" hundred ");
        res += _SpellNumber(n % 100, false);
        return res;
    }
    else if (n > 19 )
    {
        // tens
        static const String nums_20_90[] = 
        {
            MI_T("twenty"), 
            MI_T("thirty"), 
            MI_T("forty"), 
            MI_T("fifty"), 
            MI_T("sixty"), 
            MI_T("seventy"), 
            MI_T("eighty"), 
            MI_T("ninety")
        };
        String res = nums_20_90[n / 10 - 2];
        res += MI_T(" ");
        res += _SpellNumber(n % 10, false);
        return res;
    }
    else if (n == 0 && !spellZero)
        return String();
    else
    {
        // 0-19
        static const String nums_0_19[] = 
        {
            MI_T("zero"),
            MI_T("one"),
            MI_T("two"),
            MI_T("three"),
            MI_T("four"),
            MI_T("five"),
            MI_T("six"),
            MI_T("seven"),
            MI_T("eight"),
            MI_T("nine"),
            MI_T("ten"),
            MI_T("eleven"),
            MI_T("twelve"),
            MI_T("thirteen"),
            MI_T("fourteen"),
            MI_T("fifteen"),
            MI_T("sixteen"),
            MI_T("seventeen"),
            MI_T("eighteen"),
            MI_T("nineteen"),
        };
        return nums_0_19[n];
    }
}

X_SmallNumber_Class FillNumberByKey(
    Uint64 key)
{
    X_SmallNumber_Class inst;
    inst.Number_value(key);
    inst.SpelledNumber_value(_SpellNumber(key));
    inst.SetNamespace(MI_T("test/cpp"));
    return inst;
}

BEGIN_EXTERNC
static void* MI_CALL _EnumerateEven( void* param)
{
    Context* ctx = (Context*)param;

    for ( int i = 0; i < 1000; i++ )
    {
        if ( i % 2 != 0 )
            continue;

        ctx->Post(FillNumberByKey(i));
    }
    return 0;
}
END_EXTERNC

BEGIN_EXTERNC
static void* MI_CALL _EnumerateOdd( void* param)
{
    Context* ctx = (Context*)param;

    for ( int i = 0; i < 1000; i++ )
    {
        if ( i % 2 == 0 )
            continue;

        ctx->Post(FillNumberByKey(i));
    }
    return 0;
}
END_EXTERNC

BEGIN_EXTERNC
static void* MI_CALL _Enumerate( void* param)
{
    Context* ctx = (Context*)param;

    ThreadID t[2];
    _CreateThread( _EnumerateEven, ctx, &(t[0]));
    _CreateThread( _EnumerateOdd, ctx, &(t[1]));

    _CloseThreadHanlde( t[0], MI_TRUE );
    _CloseThreadHanlde( t[1], MI_TRUE );

    ctx->Post(MI_RESULT_OK);

    delete ctx;
    return 0;
}
END_EXTERNC


void X_SmallNumber_Class_Provider::EnumerateInstances(
    Context&  context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    static int counter;

    if (counter++ % 2)
    {
        ThreadID t;
        if ( MI_RESULT_OK == _CreateThread( _Enumerate, new Context(context), &t) )
        {
            _CloseThreadHanlde( t, MI_FALSE );
        }
        else
        {
            context.Post(MI_RESULT_FAILED);
        }
    }
    else
    {
        _EnumerateEven( &context );
        _EnumerateOdd( &context );
        context.Post(MI_RESULT_OK);
    }
}

void X_SmallNumber_Class_Provider::GetInstance(
    Context&  context,
    const String& nameSpace,
    const X_SmallNumber_Class& instance_ref,
    const PropertySet& propertySet)
{
    if ( instance_ref.Number_value() >= 10000 ) 
    {
        context.Post(MI_RESULT_NOT_FOUND);
        return;
    }

    context.Post(FillNumberByKey(instance_ref.Number_value()));
    context.Post(MI_RESULT_OK);
}

void X_SmallNumber_Class_Provider::CreateInstance(
    Context&  context,
    const String& nameSpace,
    const X_SmallNumber_Class& new_instance)
{
    if (new_instance.Description_exists())
    {
        X_SmallNumber_Class inst;

        inst.Number_value(10000);
        context.Post(inst);
        context.Post(MI_RESULT_OK);
        return;
    }

    context.Post(MI_RESULT_NOT_FOUND);
}

void X_SmallNumber_Class_Provider::ModifyInstance(
    Context&  context,
    const String& nameSpace,
    const X_SmallNumber_Class& new_instance,
    const PropertySet& propertySet)
{
    if (new_instance.Description_exists())
    {
        X_SmallNumber_Class inst;

        inst.Number_value(10000);
        inst.Description(new_instance.Description());
        context.Post(inst);
        context.Post(MI_RESULT_OK);
        return;
    }

    context.Post(MI_RESULT_NOT_FOUND);
}

void X_SmallNumber_Class_Provider::DeleteInstance(
    Context&  context,
    const String& nameSpace,
    const X_SmallNumber_Class& instance_ref)
{
    /* For unit-test suppport - allow to delete instance with number < 10 */
    if ( instance_ref.Number_value() >= 10 ) 
    {
        context.Post(MI_RESULT_NOT_FOUND);
        return;
    }

    context.Post(MI_RESULT_OK);
}

void X_SmallNumber_Class_Provider::Invoke_SpellNumber(
    Context&  context,
    const String& nameSpace,
    const X_SmallNumber_Class& instance,
    const X_SmallNumber_SpellNumber_Class& in_param )
{
    X_SmallNumber_SpellNumber_Class out;
    out.MIReturn_value(_SpellNumber(in_param.num_value()));

    context.Post(out);
    context.Post(MI_RESULT_OK);
}

void X_SmallNumber_Class_Provider::Invoke_GetFactors(
    Context&  context,
    const String& nameSpace,
    const X_SmallNumber_Class& instance,
    const X_SmallNumber_GetFactors_Class& in_param )
{
    X_SmallNumber_GetFactors_Class out;
    Uint64A res;
    StringA str_res;
    Uint64 num = instance.Number_value();
    Uint64 currentFactor = 2;

    if ( num >= 10000 ) 
    {
        context.Post(MI_RESULT_NOT_FOUND);
        return;
    }

    while (num > 1)
    {
        if ( num % currentFactor != 0 )
        {
            currentFactor++;
            continue;
        }

        num /= currentFactor;
        res.PushBack(currentFactor);
        str_res.PushBack(_SpellNumber(currentFactor));
    }

    if ( res.GetSize() )
    {
        out.numbers_value(res);
        out.spelled_numbers_value(str_res);
    }

    out.MIReturn_value(res.GetSize());
    context.Post(out);

    context.Post(MI_RESULT_OK);
}


MI_END_NAMESPACE
MI_BEGIN_NAMESPACE
void X_SmallNumber_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_SmallNumber_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
