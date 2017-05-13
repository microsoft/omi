/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include <MI.h>
#include "Color_Class_Provider.h"

#define T MI_T

MI_BEGIN_NAMESPACE

Color_Class_Provider::Color_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

Color_Class_Provider::~Color_Class_Provider()
{
}

void Color_Class_Provider::Load(
        Context& context)
{
	this->Colors = new Color_Class[100];
	
	Color_Class color;

    color.Id_value(1001);
    color.Caption_value(T("This is Red"));
    color.Name_value(T("Red"));
	this->Colors[0] = color;
	
	color.Id_value(1002);
    color.Caption_value(T("This is Green"));
    color.Name_value(T("Green"));
	this->Colors[1] = color;
	
	color.Id_value(1003);
    color.Caption_value(T("This is Blue"));
    color.Name_value(T("Blue"));
	this->Colors[2] = color;
	
	color.Id_value(1004);
    color.Caption_value(T("This is Yellow"));
    color.Name_value(T("Yellow"));
	this->Colors[3] = color;
	
    context.Post(MI_RESULT_OK);
}

void Color_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Color_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
	for(int i=0;i<100;i++)
	{
		if(this->Colors[i].Id_exists())
		{
			context.Post(this->Colors[i]);
		}
	}

    context.Post(MI_RESULT_OK);
}

void Color_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const Color_Class& instanceName,
    const PropertySet& propertySet)
{
	for(int i=0;i<100;i++)
	{
		if(this->Colors[i].Id_exists() && instanceName.Id_value()==this->Colors[i].Id_value())
		{
			context.Post(this->Colors[i]);
		}
	}
    context.Post(MI_RESULT_OK);
}

void Color_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const Color_Class& newInstance)
{
	for(int i=0;i<100;i++)
	{
		if(!this->Colors[i].Id_exists())
		{
			this->Colors[i].Id_value(newInstance.Id_value());
			this->Colors[i].Caption_value(newInstance.Caption_value());
			this->Colors[i].Name_value(newInstance.Name_value());
			context.Post(this->Colors[i]);
			break;
		}
	}
    context.Post(MI_RESULT_OK);
}

void Color_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const Color_Class& modifiedInstance,
    const PropertySet& propertySet)
{
	for(int i=0;i<100;i++)
	{
		if(this->Colors[i].Id_exists()&& modifiedInstance.Id_value()==this->Colors[i].Id_value())
		{
			this->Colors[i].Id_value(modifiedInstance.Id_value());
			this->Colors[i].Caption_value(modifiedInstance.Caption_value());
			this->Colors[i].Name_value(modifiedInstance.Name_value());
			context.Post(this->Colors[i]);
			break;
		}
	}
    context.Post(MI_RESULT_OK);
}

void Color_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const Color_Class& instanceName)
{
	for(int i=0;i<100;i++)
	{
		if(this->Colors[i].Id_exists()&& instanceName.Id_value()==this->Colors[i].Id_value())
		{
			this->Colors[i].Id_clear();
			this->Colors[i].Caption_clear();
			this->Colors[i].Name_clear();
			context.Post(instanceName);
			break;
		}
	}
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
