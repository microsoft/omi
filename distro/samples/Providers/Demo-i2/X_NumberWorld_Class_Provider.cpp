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
#include <MI.h>
#include "X_NumberWorld_Class_Provider.h"
#include <stdlib.h>
#if !defined(_MSC_VER)
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <base/strings.h>
#endif

MI_BEGIN_NAMESPACE

X_NumberWorld_Class_Provider::X_NumberWorld_Class_Provider(
        Module* module) :
    m_Module(module)
{
}

X_NumberWorld_Class_Provider::~X_NumberWorld_Class_Provider()
{
}

X_NumberWorld_Class GetNumberWorld(const String& ns)
{
    X_NumberWorld_Class inst;
    inst.Description_value(MI_T("<&\t xml-encoding-test \t&>"));
    inst.Name_value(MI_T("theWorld"));
    inst.Version_value(MI_T("0.1"));
    inst.ns_value(ns);

#if !defined(_MSC_VER)
    inst.pid_value(getpid());

    /* user name */
    struct passwd* pwd = 0;
    char buf[1024];
    struct passwd current;

    if (0 == getpwuid_r(getuid(), &current, buf, sizeof(buf), &pwd) &&
        pwd &&
        pwd->pw_name)
    {
        MI_Char buf[128];
        inst.user_value(StrToZ(buf, sizeof(buf), pwd->pw_name));
    }
    inst.uid_value(getuid());

    /* group name */
    struct group grbuf;
    struct group* gr;

    if (getgrgid_r(getgid(), &grbuf, buf, sizeof(buf), &gr) == 0  &&
        gr &&
        gr->gr_name)
    {
        MI_Char buf[128];
        inst.group_value(StrToZ(buf, sizeof(buf), gr->gr_name));
    }
    inst.gid_value(getgid());
#endif

    inst.SetNamespace(MI_T("test/cpp"));
    return inst;
}

void X_NumberWorld_Class_Provider::EnumerateInstances(
    Context&  context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(GetNumberWorld(nameSpace));
    context.Post(MI_RESULT_OK);
}

void X_NumberWorld_Class_Provider::GetInstance(
    Context&  context,
    const String& nameSpace,
    const X_NumberWorld_Class& instance_ref,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_NumberWorld_Class_Provider::CreateInstance(
    Context&  context,
    const String& nameSpace,
    const X_NumberWorld_Class& new_instance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_NumberWorld_Class_Provider::ModifyInstance(
    Context&  context,
    const String& nameSpace,
    const X_NumberWorld_Class& new_instance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_NumberWorld_Class_Provider::DeleteInstance(
    Context&  context,
    const String& nameSpace,
    const X_NumberWorld_Class& instance_ref)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_NumberWorld_Class_Provider::Invoke_Terminate(
    Context& context,
    const String& nameSpace,
    const X_NumberWorld_Class& instance,
    const X_NumberWorld_Terminate_Class& in)
{
    exit(1);
    //context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_NumberWorld_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_NumberWorld_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_NumberWorld_Class_Provider::Invoke_ReturnNamespace(
    Context& context,
    const String& nameSpace,
    const X_NumberWorld_Class& instanceName,
    const X_NumberWorld_ReturnNamespace_Class& in)
{
    X_NumberWorld_ReturnNamespace_Class out;

    out.MIReturn_value(nameSpace);
    context.Post(out);

    context.Post(MI_RESULT_OK);
}


MI_END_NAMESPACE
