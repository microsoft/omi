/* @migen@ */
#include <MI.h>
#include "Test_Class_Provider.h"
#if !defined(_MSC_VER)
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#endif

MI_BEGIN_NAMESPACE

Test_Class_Provider::Test_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

Test_Class_Provider::~Test_Class_Provider()
{
}

void Test_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Test_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}
Test_Class GetIdentify(String methodName, String nameSpace)
{
	Test_Class inst;
    Identifier_Class instId;
	//Reference_Class instRf;
	//instRf.Description_value(MI_T("TestProvider"));
    instId.ClassName_value(MI_T("Identifier_Class"));
    instId.MethodName_value(methodName);
	instId.NameSpace_value(nameSpace);
#if !defined(_MSC_VER)
    instId.pid_value(getpid());
    /* user name */
    struct passwd* pwd = 0;
    char buf[1024];
    struct passwd current;
    if (0 == getpwuid_r(getuid(), &current, buf, sizeof(buf), &pwd) &&
        pwd &&
        pwd->pw_name)
    {
        instId.user_value(pwd->pw_name);
    }
    instId.uid_value(getuid());
    /* group name */
    struct group grbuf;
    struct group* gr;
    if (getgrgid_r(getgid(), &grbuf, buf, sizeof(buf), &gr) == 0  &&
        gr &&
        gr->gr_name)
    {
        instId.group_value(gr->gr_name);
    }
    instId.gid_value(getgid());
#endif	
	inst.Id_value(instId);
	//inst.Rf_value(instRf);
    return inst;
}
 
void Test_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
context.Post(GetIdentify(MI_T("EnumerateInstances"), nameSpace));
    context.Post(MI_RESULT_OK);
}

void Test_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const Test_Class& instanceName,
    const PropertySet& propertySet)
{
context.Post(GetIdentify(MI_T("GetInstance"), nameSpace));
    context.Post(MI_RESULT_OK);
}

void Test_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const Test_Class& newInstance)
{
context.Post(GetIdentify(MI_T("CreateInstance"), nameSpace));
    context.Post(MI_RESULT_OK);
}

void Test_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const Test_Class& modifiedInstance,
    const PropertySet& propertySet)
{
context.Post(GetIdentify(MI_T("ModifyInstance"), nameSpace));
    context.Post(MI_RESULT_OK);
}

void Test_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const Test_Class& instanceName)
{
context.Post(GetIdentify(MI_T("DeleteInstance"), nameSpace));
    context.Post(MI_RESULT_OK);
}

void Test_Class_Provider::AssociatorInstancesId(
    Context& context,
    const String& nameSpace,
    const Identifier_Class& instanceName, 
    const String& resultClass,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
context.Post(GetIdentify(MI_T("AssociatorInstancesId"), nameSpace));
    context.Post(MI_RESULT_OK);
}

void Test_Class_Provider::AssociatorInstancesRf(
    Context& context,
    const String& nameSpace,
    const Reference_Class& instanceName, 
    const String& resultClass,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
context.Post(GetIdentify(MI_T("AssociatorInstancesRf"), nameSpace));
    context.Post(MI_RESULT_OK);
}

void Test_Class_Provider::ReferenceInstancesId(
    Context& context,
    const String& nameSpace,
    const Identifier_Class& instanceName, 
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
context.Post(GetIdentify(MI_T("ReferenceInstancesId"), nameSpace));
    context.Post(MI_RESULT_OK);
}

void Test_Class_Provider::ReferenceInstancesRf(
    Context& context,
    const String& nameSpace,
    const Reference_Class& instanceName, 
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
context.Post(GetIdentify(MI_T("ReferenceInstancesRf"), nameSpace));
    context.Post(MI_RESULT_OK);
}

void Test_Class_Provider::Invoke_StaticFun(
    Context& context,
    const String& nameSpace,
    const Test_Class& instanceName,
    const Test_StaticFun_Class& in)
{
context.Post(GetIdentify(MI_T("Invoke_StaticFun"), nameSpace));
    context.Post(MI_RESULT_OK);
}

void Test_Class_Provider::Invoke_InstanceFun(
    Context& context,
    const String& nameSpace,
    const Test_Class& instanceName,
    const Test_InstanceFun_Class& in)
{
context.Post(GetIdentify(MI_T("Invoke_InstanceFun"), nameSpace));
    context.Post(MI_RESULT_OK);
}


MI_END_NAMESPACE
