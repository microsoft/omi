/* @migen@ */
#include <MI.h>
#include "Main_Class_Provider.h"

MI_BEGIN_NAMESPACE

Main_Class_Provider::Main_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

Main_Class_Provider::~Main_Class_Provider()
{
}

void Main_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Main_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Main_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    {
		Main_Class g;
		g.SN_value(001);
		g.Name_value("SCX");
		context.Post(g);
	}
	
	{
		Main_Class g;
		g.SN_value(002);
		g.Name_value("CM");
		context.Post(g);
	}
	context.Post(MI_RESULT_OK);
}

void Main_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const Main_Class& instanceName,
    const PropertySet& propertySet)
{
    if (instanceName.SN_value() == 001)
	{
		
		Main_Class g;
		g.SN_value(001);
		g.Name_value("SCX");
		context.Post(g);
		context.Post(MI_RESULT_OK);
	}
	else if (instanceName.SN_value() == 002)
	{
		
		Main_Class g;
		g.SN_value(002);
		g.Name_value("CM");
		context.Post(g);
		context.Post(MI_RESULT_OK);
	}
	else
	{
		context.Post(MI_RESULT_NOT_FOUND);
	}
}

void Main_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const Main_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Main_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const Main_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Main_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const Main_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Main_Class_Provider::Invoke_ChangeState(
    Context& context,
    const String& nameSpace,
    const Main_Class& instanceName,
    const Main_ChangeState_Class& in)
{
    Main_ChangeState_Class out;

	// Print the input parameter:
	if (in.NewState_exists())
	{
		printf("NewState=%u\n", in.NewState_value());
		if (in.NewState_value() > 3)
		{
			// Set the output parameter:
			out.OldState_value(0);
		}
		else 
		{
			out.OldState_value(1);
		}
		// Set the return value:
		out.MIReturn_value(0);
		// Post the ¡¯out¡¯ object.
		context.Post(out);
		// Post the result status.
		context.Post(MI_RESULT_OK);
	}
}

void Main_Class_Provider::Invoke_HelloWorld(
    Context& context,
    const String& nameSpace,
    const Main_Class& instanceName,
    const Main_HelloWorld_Class& in)
{
    if (in.NewValue_exists())
	{	
		if(in.NewValue_value() > 6)
		{
			Main_Class mainInst;
			mainInst.SN_value(007);
			mainInst.Name_value("SystemCenter");
			context.Post(mainInst);
		}
		else
		{
			Main_Class mainInst;
			mainInst.SN_value(005);
			mainInst.Name_value("Microsoft");
			context.Post(mainInst);
		}
		context.Post(MI_RESULT_OK);
	}
}


MI_END_NAMESPACE
