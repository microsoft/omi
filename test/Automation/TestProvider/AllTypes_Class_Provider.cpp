/* @migen@ */
#include <MI.h>
#include "AllTypes_Class_Provider.h"

MI_BEGIN_NAMESPACE

AllTypes_Class_Provider::AllTypes_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

AllTypes_Class_Provider::~AllTypes_Class_Provider()
{
}

void AllTypes_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void AllTypes_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void AllTypes_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
        AllTypes_Class inst;

    inst.id_value(1);
    inst.boolValue_value(MI_TRUE);
    inst.char16Value_value(1044); 
    inst.uint8Value_value(172);
    inst.sint8Value_value(-123);
    inst.uint16Value_value(1745);
    inst.sint16Value_value(-1746);
    inst.uint32Value_value(17567);
    inst.sint32Value_value(-17568);
    inst.uint64Value_value(MI_ULL(18446744073709551613));
    inst.sint64Value_value(-MI_LL(9223372036854775805));
    inst.stringValue_value(MI_T("string value"));

    Datetime dt(2010, 7, 14, 11, 35, 11, 900675, -7);
    inst.datetimetValue_value(dt);

    inst.real32Value_value(32.32f);
    inst.real64Value_value(64.6464);

	//INSTANCE
	{   
        Main_Class instance;
        instance.SN_value(003);
		instance.Name_value("Windows");
        inst.instanceTest_value(instance);
    }

	//REFERENCE
	{
		Main_Class instMain;
		instMain.SN_value(001);
		instMain.Name_value("Microsoft");
		inst.refMain_value(instMain);

		Reference_Class instRef;
		instRef.Description_value("other reference");
		inst.refRef_value(instRef);
	}

	// fill in array types

	//BOOLEANA
    {
        BooleanA ba;
        ba.PushBack(MI_TRUE);
        ba.PushBack(MI_FALSE);
        inst.boolArray_value(ba);
    }

	//UINT8A
	{
        Uint8A u8a;
        u8a.PushBack(0);
        u8a.PushBack(255);
        u8a.PushBack(128);
        inst.uint8Array_value(u8a);
    }

	//SINT8A
    {
        Sint8A s8a;
        s8a.PushBack(0);
        s8a.PushBack(-128);
        s8a.PushBack(127);
        inst.sint8Array_value(s8a);
    }

	//UINT16A
    {
        Uint16A u16a;
        u16a.PushBack(0);
        u16a.PushBack(64000);
        inst.uint16Array_value(u16a);
    }

	//SINT16A
    {
        Sint16A s16a;
        s16a.PushBack(0);
        s16a.PushBack(-1216);
        s16a.PushBack(258);
        inst.sint16Array_value(s16a);
    }

	//UINT32A 
	{
		Uint32A u32a;
        u32a.PushBack(17567);
        u32a.PushBack(17599);
        inst.uint32Array_value(u32a);
	}

	//SINT32A
	{
		Sint32A s32a;
        s32a.PushBack(-17568);
        s32a.PushBack(-17500);
        inst.sint32Array_value(s32a);
	}

	//UINT64A
	{
		Uint64A u64a;
        u64a.PushBack(MI_ULL(18446744073709551615));
        u64a.PushBack(MI_ULL(18446744073709551613));
        inst.uint64Array_value(u64a);
	}

	//SINT64A
	{
		Sint64A s64a;
        s64a.PushBack(MI_LL(-9223372036854775807));
        s64a.PushBack(MI_LL(9223372036854775807));
        inst.sint64Array_value(s64a);
	}

	//REAL32A
	{
		Real32A r32a;
		r32a.PushBack(32.32f);
		r32a.PushBack(32.38f);
		inst.real32Array_value(r32a);
	}
	 
	//REAL64A
	{
		Real64A r64a;
		r64a.PushBack(64.6464);
		r64a.PushBack(64.6469);
		inst.real64Array_value(r64a);
	}

	////DATETIMEA
	//{
	//	DatetimeA dtimea;
	//	Datetime dt1(2010, 7, 14, 11, 35, 11, 900675, -7);
	//	dtimea.PushBack(dt1);

	//	inst.datetimeArray_value(dtimea);
	//}

	//STRINGA
	{
		StringA sa;
		sa.PushBack("string1");
		sa.PushBack("string2");
		inst.stringArray_value(sa);
	}

	//CHAR16A
	{
        Char16A c16a;
        c16a.PushBack('&');
        c16a.PushBack('\t');
        c16a.PushBack('<');
        inst.char16Array_value(c16a);
    }

	//INSTANCEA
	{
		Main_ClassA instances;
		Main_Class insta;
        insta.SN_value(004);
		insta.Name_value("SharePoint");
		instances.PushBack(insta);
        insta.SN_value(006);
		insta.Name_value("XBOX");
		instances.PushBack(insta);
		inst.instanceArrayTest_value(instances);
	}

	//REFERENCEA CODE HERE
	//{
	//}

	context.Post(inst);
    context.Post(MI_RESULT_OK);
}

void AllTypes_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const AllTypes_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void AllTypes_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const AllTypes_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void AllTypes_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const AllTypes_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void AllTypes_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const AllTypes_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void AllTypes_Class_Provider::AssociatorInstancesrefMain(
    Context& context,
    const String& nameSpace,
    const Main_Class& instanceName, 
    const String& resultClass,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void AllTypes_Class_Provider::AssociatorInstancesrefRef(
    Context& context,
    const String& nameSpace,
    const Reference_Class& instanceName, 
    const String& resultClass,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void AllTypes_Class_Provider::ReferenceInstancesrefMain(
    Context& context,
    const String& nameSpace,
    const Main_Class& instanceName, 
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void AllTypes_Class_Provider::ReferenceInstancesrefRef(
    Context& context,
    const String& nameSpace,
    const Reference_Class& instanceName, 
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
