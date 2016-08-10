/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <string>
#include <vector>
#include <iostream>
#include <ut/ut.h>
#include <pal/shlib.h>
#include <base/paths.h>
#include <base/base.h>

#if MI_CHAR_TYPE == 1
typedef std::string String;
#else
typedef std::wstring String;
#endif

static inline Shlib* LoadLib(const char* file)
{
    TChar path[PAL_MAX_PATH_SIZE];
    Shlib_Format(path, OMI_GetPath(ID_LIBDIR), file);
    Shlib* lib = Shlib_Open(path);

    if (lib)
        return lib;

    if (TcsStrlcpy(path, file, PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
        return NULL;

    /* try just name - needed by build team, since they have different output folders */
    return Shlib_Open(path);
}

using namespace std;

//==============================================================================
//
// Context
//
//==============================================================================

#define CONTEXT_MAGIC 0X82D183A8

class Context : public MI_Context
{
public:

    Context()
    {
        // Set magic number.
        magic = CONTEXT_MAGIC;

        Batch_Init(&batch, 64);

        // Initialize function table.
        memset(&_ft, 0, sizeof(_ft));
        _ft.PostResult = Context::_PostResult;
        _ft.ConstructInstance = Context::_ConstructInstance;
        _ft.ConstructParameters = Context::_ConstructParameters;
        _ft.PostInstance = Context::_PostInstance;
        ft = &_ft;
    }

    ~Context()
    {
        magic = 0;
        clearResults();

        Batch_Destroy(&batch);
    }

    Batch batch;
    MI_Result result;
    vector<MI_Instance*> instances;

    void clearResults()
    {
        result = MI_RESULT_OK;

        for (size_t i = 0; i < instances.size(); i++)
        {
            MI_Result r = __MI_Instance_Delete(instances[i]);
            UT_ASSERT(r == MI_RESULT_OK);
        }

        instances.clear();
    }

private:

    MI_ContextFT _ft;

    static MI_Result MI_CALL _PostResult(
        MI_Context* context,
        MI_Result result)
    {
        Context* ctx = (Context*)context;
        UT_ASSERT(ctx->magic == CONTEXT_MAGIC);

        ctx->result = result;
        return MI_RESULT_OK;
    }

    static MI_Result MI_CALL _ConstructInstance(
        MI_Context* context,
        const MI_ClassDecl* classDecl,
        MI_Instance* instance)
    {
        Context* ctx = (Context*)context;

        UT_ASSERT(ctx->magic == CONTEXT_MAGIC);

        MI_Result r = Instance_Construct(instance, classDecl, &ctx->batch);

        if (r != MI_RESULT_OK)
            return MI_RESULT_FAILED;

        return MI_RESULT_OK;
    }

    static MI_Result MI_CALL _ConstructParameters(
        MI_Context* context,
        const MI_MethodDecl* methodDecl,
        MI_Instance* instance)
    {
        Context* ctx = (Context*)context;
        UT_ASSERT(ctx->magic == CONTEXT_MAGIC);

        MI_Result r = Parameters_Init(instance, methodDecl, &ctx->batch);

        if (r != MI_RESULT_OK)
            return MI_RESULT_FAILED;

        return MI_RESULT_OK;
    }

    static MI_Result MI_CALL _PostInstance(
        MI_Context* context,
        const MI_Instance* instance)
    {
        Context* ctx = (Context*)context;
        UT_ASSERT(ctx->magic == CONTEXT_MAGIC);

        ctx->result = MI_RESULT_OK;

        UT_ASSERT(instance != 0);

        MI_Instance* inst = NULL;

        Instance_Clone(instance, &inst, &ctx->batch);
        UT_ASSERT(inst != NULL);
        ctx->instances.push_back(inst);

        return MI_RESULT_OK;
    }

    MI_Uint32 magic;
};

//==============================================================================
//
// Module
//
//==============================================================================

//extern "C" MI_EXPORT MI_Module* MI_Main(MI_Context* context);
typedef MI_Module* (*PfnMI_Main)(MI_Context* context);

class ModuleHandle
{
public:

    ModuleHandle(Context& context, const MI_Char* className, const char* lib_file) : 
        _context(context),
        _classDecl(0),
        _classSelf(0),
        _className(className)
    {
        _lib = LoadLib(lib_file);

        UT_ASSERT( _lib != 0 );

        PfnMI_Main pfn = (PfnMI_Main)Shlib_Sym(_lib, "MI_Main" );
        UT_ASSERT( pfn != 0 );

        // Call MI_Main() to get an instance of the provider.
        _module = pfn((MI_Context*)&_context);
        UT_ASSERT(_module != 0);
        UT_ASSERT(_module->version == MI_VERSION);
        UT_ASSERT(_module->schemaDecl != 0);

        // Load the provider.
        UT_ASSERT(_module->Load);
        _module->Load(&_moduleSelf, (MI_Context*)&_context);
    }

    ~ModuleHandle()
    {
        _context.clearResults();
        // Unload the provider.
        UT_ASSERT(_module != 0);
        UT_ASSERT(_module->Unload != 0);
        UT_ASSERT(_context.ft != 0);
        _module->Unload(_moduleSelf, (MI_Context*)&_context);

        if ( _lib != 0 )
            Shlib_Close(_lib);

    }

    MI_Instance* newClass()
    {
        UT_ASSERT(_classDecl != 0);
        MI_Instance* inst;
        MI_Result r = Instance_New(&inst, _classDecl, &_context.batch);
        UT_ASSERT(r == MI_RESULT_OK);
        return inst;
    }

    MI_Instance* newClass(const MI_Char* className)
    {
        MI_ClassDecl* cd = SchemaDecl_FindClassDecl(_module->schemaDecl, 
            className);
        UT_ASSERT(cd != 0);
        MI_Instance* inst;
        MI_Result r = Instance_New(&inst, cd, &_context.batch);
        UT_ASSERT(r == MI_RESULT_OK);
        return inst;
    }

    MI_Instance* newParameters(const MI_Char* methodName)
    {
        UT_ASSERT(_classDecl != 0);
        MI_MethodDecl* md = ClassDecl_FindMethodDecl(_classDecl, methodName);
        UT_ASSERT(md);

        MI_Instance* result;
        MI_Result r = Parameters_New(&result, md, &_context.batch);
        UT_ASSERT(r == MI_RESULT_OK);

        return result;
    }

    void callLoad()
    {
        // Find the class declaration for the given class.
        _classDecl = SchemaDecl_FindClassDecl(
            _module->schemaDecl, _className.c_str());

        UT_ASSERT(_classDecl != 0);

        // Call the class initialize function.
        UT_ASSERT(_classDecl->providerFT);
        UT_ASSERT(_classDecl->providerFT->Load);
        _classDecl->providerFT->Load(&_classSelf, _moduleSelf, (MI_Context*)&_context);
    }

    void callUnload()
    {
        // Unload the class provider.
        UT_ASSERT(_classDecl->providerFT);
        UT_ASSERT(_classDecl->providerFT->Unload);
        _classDecl->providerFT->Unload(_classSelf, (MI_Context*)&_context);
        _classDecl = 0;
    }

    void callGet(
        const MI_Instance* instanceName,
        const MI_PropertySet* propertySet)
    {
        UT_ASSERT(_classDecl);
        return _classDecl->providerFT->GetInstance(
            _classSelf, 
            (MI_Context*)&_context, 
            __nameSpace,
            __className,
            instanceName, 
            propertySet);
    }

    void callInvoke(
        const MI_Char* methodName,
        const MI_Instance* instanceName,
        const MI_Instance* parameters)
    {
        UT_ASSERT(instanceName != 0);
        UT_ASSERT(parameters != 0);
        UT_ASSERT(_classDecl != 0);
        MI_MethodDecl* md = ClassDecl_FindMethodDecl(_classDecl, 
            methodName);
        UT_ASSERT(md);

        return md->function(_classSelf, (MI_Context*)&_context, 
            __nameSpace, __className, __methodName, instanceName, parameters);
    }

    void callEnumerate()
    {
        UT_ASSERT(_classDecl);
        return _classDecl->providerFT->EnumerateInstances(
            _classSelf, 
            (MI_Context*)&_context, 
            __nameSpace,
            __className,
            NULL, 
            MI_FALSE, 
            NULL);
    }

    void callCreate(
        const MI_Instance* newInstance)
    {
        return _classDecl->providerFT->CreateInstance(
            _classSelf, 
            (MI_Context*)&_context, 
            __nameSpace,
            __className,
            newInstance);
    }

    void callModify(
        const MI_Instance* modifiedInstance,
        const MI_PropertySet* propertySet)
    {
        UT_ASSERT(_classDecl);
        return _classDecl->providerFT->ModifyInstance(
            _classSelf, 
            (MI_Context*)&_context, 
            __nameSpace,
            __className,
            modifiedInstance, 
            propertySet);
    }

    void callDelete(
        const MI_Instance* instanceName)
    {
        UT_ASSERT(_classDecl);
        return _classDecl->providerFT->DeleteInstance(
            _classSelf, 
            (MI_Context*)&_context, 
            __nameSpace,
            __className,
            instanceName);
    }

    void callAssociators(MI_Instance* instanceName)
    {
        UT_ASSERT(_classDecl);

        const MI_Char* role1 = 0;
        const MI_Char* role2 = 0;

        for (MI_Uint32 i = 0; i < _classDecl->numProperties; i++)
        {
            const MI_PropertyDecl* pd = _classDecl->properties[i];

            if (pd->type == MI_REFERENCE)
            {
                if (!role1)
                    role1 = pd->name;
                else if (!role2)
                    role2 = pd->name;
            }
        }

        _classDecl->providerFT->AssociatorInstances(
            _classSelf, 
            (MI_Context*)&_context, 
            __nameSpace,
            __className,
            instanceName, /* instanceName */
            NULL, /* resultClass */
            role1, /* role */
            role2, /* resultRole */
            NULL, /* propertySet */
            MI_FALSE, /* keysOnly */
            NULL); /* filter */

        _classDecl->providerFT->AssociatorInstances(
            _classSelf, 
            (MI_Context*)&_context, 
            __nameSpace,
            __className,
            instanceName, /* instanceName */
            NULL, /* resultClass */
            role2, /* role */
            role1, /* resultRole */
            NULL, /* propertySet */
            MI_FALSE, /* keysOnly */
            NULL); /* filter */
    }

    void callReferences(MI_Instance* instanceName)
    {
        UT_ASSERT(_classDecl);

        const MI_Char* role1 = 0;
        const MI_Char* role2 = 0;

        for (MI_Uint32 i = 0; i < _classDecl->numProperties; i++)
        {
            const MI_PropertyDecl* pd = _classDecl->properties[i];

            if (pd->type == MI_REFERENCE)
            {
                if (!role1)
                    role1 = pd->name;
                else if (!role2)
                    role2 = pd->name;
            }
        }

        _classDecl->providerFT->ReferenceInstances(
            _classSelf, 
            (MI_Context*)&_context, 
            __nameSpace,
            __className,
            instanceName, /* instanceName */
            role1, /* role */
            NULL, /* propertySet */
            MI_FALSE, /* keysOnly */
            NULL); /* filter */

        _classDecl->providerFT->ReferenceInstances(
            _classSelf, 
            (MI_Context*)&_context, 
            __nameSpace,
            __className,
            instanceName, /* instanceName */
            role2, /* role */
            NULL, /* propertySet */
            MI_FALSE, /* keysOnly */
            NULL); /* filter */
    }

    MI_ClassDecl* getClassDecl() 
    {
        return _classDecl;
    }

private:

    ModuleHandle();

    ModuleHandle& operator=(const ModuleHandle&);

    Context& _context;

    // Module and self.
    MI_Module* _module;
    MI_Module_Self* _moduleSelf;

    // Person class and self.
    MI_ClassDecl* _classDecl;
    void* _classSelf;

    String _className;
    Shlib* _lib;
};

//==============================================================================
//
// Test functions
//
//==============================================================================

NitsSetup(TestPersonProviderSetup)
NitsEndSetup

NitsCleanup(TestPersonProviderSetup)
NitsEndCleanup

static void ExpectNotFound(
    Context& ctx, 
    ModuleHandle& mh,
    MI_Uint32 key)
{
    MI_Result r;

    // Prepare instanceName
    MI_Instance* instanceName = mh.newClass();
    {
        MI_Value value;
        value.uint32 = key;
        r = __MI_Instance_SetElement(instanceName, MI_T("Key"), &value, MI_UINT32, 0);
        UT_ASSERT(r == MI_RESULT_OK);
    }

    // Call the provider's Get method.
    mh.callGet((MI_Instance*)instanceName, NULL);

    // Check the result.
    UT_ASSERT(ctx.result == MI_RESULT_NOT_FOUND);
    UT_ASSERT(ctx.instances.size() == 0);
    ctx.instances.clear();

    __MI_Instance_Delete(instanceName);
}

static void GetPerson(
    Context& ctx, 
    ModuleHandle& mh,
    MI_Uint32 key,
    const MI_Char* first,
    const MI_Char* last)
{
    MI_Result r;

    // Prepare instanceName
    MI_Instance* instanceName = mh.newClass();
    {
        MI_Value value;
        value.uint32 = key;
        r = __MI_Instance_SetElement(instanceName, MI_T("Key"), &value, MI_UINT32, 0);
        UT_ASSERT(r == MI_RESULT_OK);
    }

    // Call the provider's Get method.
    mh.callGet((MI_Instance*)instanceName, NULL);
    __MI_Instance_Delete(instanceName); instanceName = 0;

    // Check the result.
    UT_ASSERT(ctx.result == MI_RESULT_OK);
    UT_ASSERT(ctx.instances.size() == 1);

    MI_Instance* inst = ctx.instances[0];
    ctx.instances.clear();

    // Check MSFT_Person.Key
    {
        MI_Uint32 flags;
        MI_Value value;
        MI_Type type;
        r = __MI_Instance_GetElement(inst, MI_T("Key"), &value, &type, &flags, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(type == MI_UINT32);
        UT_ASSERT(!(flags & MI_FLAG_NULL));
        UT_ASSERT(value.uint32 == key);
    }

    // Check MSFT_Person.First
    {
        MI_Uint32 flags;
        MI_Value value;
        MI_Type type;
        r = __MI_Instance_GetElement(inst, MI_T("First"), &value, &type, &flags, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(type == MI_STRING);
        UT_ASSERT(!(flags & MI_FLAG_NULL));
        UT_ASSERT(value.string != NULL);
        UT_ASSERT(value.string == String(first));
    }

    // Check MSFT_Person.Last
    {
        MI_Uint32 flags;
        MI_Value value;
        MI_Type type;
        r = __MI_Instance_GetElement(inst, MI_T("Last"), &value, &type, &flags, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(type == MI_STRING);
        UT_ASSERT(!(flags & MI_FLAG_NULL));
        UT_ASSERT(value.string != NULL);
        UT_ASSERT(value.string == String(last));
    }

    __MI_Instance_Delete(inst);
}

static void EnumeratePerson(
    Context& ctx, 
    ModuleHandle& mh)
{
    MI_Result r;

    // Call the provider's enumeate method.
    mh.callEnumerate();

    // Check the result.
    UT_ASSERT(ctx.result == MI_RESULT_OK);
    UT_ASSERT(ctx.instances.size() == 2);

    MI_Instance* inst0 = ctx.instances[0];
    MI_Instance* inst1 = ctx.instances[1];
    ctx.instances.clear();

#if 0
    __MI_Instance_Print(stdout, inst0);
#endif

    // Check inst0:
    {
        MI_Uint32 flags;
        MI_Value value;
        MI_Type type;
        r = __MI_Instance_GetElement(inst0, MI_T("Key"), &value, &type, &flags, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(type == MI_UINT32);
        UT_ASSERT(!(flags & MI_FLAG_NULL));
        UT_ASSERT(value.uint32 == 1);
    }
    {
        MI_Uint32 flags;
        MI_Value value;
        MI_Type type;
        r = __MI_Instance_GetElement(inst0, MI_T("First"), &value, &type, &flags, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(type == MI_STRING);
        UT_ASSERT(!(flags & MI_FLAG_NULL));
        UT_ASSERT(value.string != NULL);
        UT_ASSERT(value.string == String(MI_T("George")));
    }
    {
        MI_Uint32 flags;
        MI_Value value;
        MI_Type type;
        r = __MI_Instance_GetElement(inst0, MI_T("Last"), &value, &type, &flags, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(type == MI_STRING);
        UT_ASSERT(!(flags & MI_FLAG_NULL));
        UT_ASSERT(value.string != NULL);
        UT_ASSERT(value.string == String(MI_T("Washington")));
    }

    __MI_Instance_Delete(inst0);

    // Check inst1:
    {
        MI_Uint32 flags;
        MI_Value value;
        MI_Type type;
        r = __MI_Instance_GetElement(inst1, MI_T("Key"), &value, &type, &flags, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(type == MI_UINT32);
        UT_ASSERT(!(flags & MI_FLAG_NULL));
        UT_ASSERT(value.uint32 == 2);
    }
    {
        MI_Uint32 flags;
        MI_Value value;
        MI_Type type;
        r = __MI_Instance_GetElement(inst1, MI_T("First"), &value, &type, &flags, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(type == MI_STRING);
        UT_ASSERT(!(flags & MI_FLAG_NULL));
        UT_ASSERT(value.string != NULL);
        UT_ASSERT(value.string == String(MI_T("John")));
    }
    {
        MI_Uint32 flags;
        MI_Value value;
        MI_Type type;
        r = __MI_Instance_GetElement(inst1, MI_T("Last"), &value, &type, &flags, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(type == MI_STRING);
        UT_ASSERT(!(flags & MI_FLAG_NULL));
        UT_ASSERT(value.string != NULL);
        UT_ASSERT(value.string == String(MI_T("Adams")));
    }

    __MI_Instance_Delete(inst1);
}

static void CreatePerson(
    Context& ctx, 
    ModuleHandle& mh,
    MI_Uint32 key,
    const MI_Char* first,
    const MI_Char* last)
{
    MI_Result r;

    // Prepare the newInstance argument.
    MI_Instance* newInstance = mh.newClass();
    {
        MI_Value value;
        value.uint32 = key;

        // MSFT_Person.Key:
        r = __MI_Instance_SetElement(newInstance, MI_T("Key"), &value, MI_UINT32, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        // MSFT_Person.First:
        value.string = (MI_Char*)first;
        r = __MI_Instance_SetElement(newInstance, MI_T("First"), &value, MI_STRING, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        // MSFT_Person.Last:
        value.string = (MI_Char*)last;
        r = __MI_Instance_SetElement(newInstance, MI_T("Last"), &value, MI_STRING, 0);
        UT_ASSERT(r == MI_RESULT_OK);
    }

    // Call the provider's Create method.
    mh.callCreate((MI_Instance*)newInstance);
    UT_ASSERT(ctx.result == MI_RESULT_OK);
    UT_ASSERT(ctx.instances.size() == 1);

    ctx.clearResults();

    // Call the provider's Create method.
    mh.callModify((MI_Instance*)newInstance, NULL);
    __MI_Instance_Delete(newInstance); newInstance = 0;
    UT_ASSERT(ctx.result == MI_RESULT_NOT_SUPPORTED);
    UT_ASSERT(ctx.instances.size() == 0);
}

static void DeletePerson(
    Context& ctx, 
    ModuleHandle& mh,
    MI_Uint32 key)
{
    MI_Result r;

    // Prepare instanceName
    MI_Instance* instanceName = mh.newClass();
    {
        MI_Value value;
        value.uint32 = key;
        r = __MI_Instance_SetElement(instanceName, MI_T("Key"), &value, MI_UINT32, 0);
        UT_ASSERT(r == MI_RESULT_OK);
    }

    // Call the provider's Delete method.
    mh.callDelete((MI_Instance*)instanceName);
    __MI_Instance_Delete(instanceName); instanceName = 0;

    // Check the result.
    UT_ASSERT(ctx.result == MI_RESULT_OK);
}

static void InvokePersonAdd(
    Context& ctx, 
    ModuleHandle& mh)
{
    // Prepare instanceName
    MI_Instance* instanceName = mh.newClass();
    Instance_SetUint32(instanceName, MI_T("Key"), 1);
    {
        MI_Result r;
        MI_Instance* params = mh.newParameters(MI_T("Add"));
        UT_ASSERT(params);

        Instance_SetReal32(params, MI_T("X"), 100);
        Instance_SetReal32(params, MI_T("Y"), 200);

#if 0
        __MI_Instance_Print(stdout, params);
#endif

        mh.callInvoke(MI_T("Add"), instanceName, params);
        __MI_Instance_Delete(instanceName); instanceName = 0;
        __MI_Instance_Delete(params); params = 0;

        UT_ASSERT(ctx.result == MI_RESULT_OK);
        UT_ASSERT(ctx.instances.size() == 1);
        MI_Instance* out = ctx.instances[0];
        UT_ASSERT(out != 0);
        ctx.instances.clear();

        MI_Real32 z;
        r = Instance_GetReal32(out, MI_T("Z"), &z);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(z == 300.0);

#if 0
        __MI_Instance_Print(stdout, out);
#endif
        __MI_Instance_Delete(out);
    }

}

template<typename T, typename C_ARRAY_T, MI_Type type>
static void TestArray(const MI_Char* prop_name, const vector< T >& in_array, MI_Instance* param)
{
    C_ARRAY_T value;

    T sum = 0;
    for ( size_t i = 0; i < in_array.size(); i++ )
        sum += in_array[i];

    UT_ASSERT(MI_RESULT_OK == Instance_GetValue(param,prop_name,&value,type));
    UT_ASSERT(value.size == 2);
    UT_ASSERT(value.data[0] == (T)in_array.size());
    UT_ASSERT(value.data[1] == sum);
}


static void InvokeTestAllTypes(
    Context& ctx, 
    ModuleHandle& mh)
{
    // Prepare instanceName
    MI_Instance* instanceName = mh.newClass();
    Instance_SetUint32(instanceName, MI_T("Key"), 1);
    {
        MI_Instance* params = mh.newParameters(MI_T("TestAllTypes"));
        UT_ASSERT(params);

        UT_ASSERT(MI_RESULT_OK == Instance_SetBoolean(params, MI_T("b"), MI_TRUE));
        UT_ASSERT(MI_RESULT_OK == Instance_SetUint8(params, MI_T("u8"), 8));
        UT_ASSERT(MI_RESULT_OK == Instance_SetSint8(params, MI_T("s8"), -8));
        UT_ASSERT(MI_RESULT_OK == Instance_SetUint16(params, MI_T("u16"), 16));
        UT_ASSERT(MI_RESULT_OK == Instance_SetSint16(params, MI_T("s16"), -16));
        UT_ASSERT(MI_RESULT_OK == Instance_SetUint32(params, MI_T("u32"), 32));
        UT_ASSERT(MI_RESULT_OK == Instance_SetSint32(params, MI_T("s32"), -32));
        UT_ASSERT(MI_RESULT_OK == Instance_SetUint64(params, MI_T("u64"), 64));
        UT_ASSERT(MI_RESULT_OK == Instance_SetSint64(params, MI_T("s64"), -64));
        UT_ASSERT(MI_RESULT_OK == Instance_SetReal32(params, MI_T("r32"), 32.32f));
        UT_ASSERT(MI_RESULT_OK == Instance_SetReal64(params, MI_T("r64"), 64.64));
        MI_Datetime dt;
        dt.isTimestamp = 1;
        dt.u.timestamp.year = 1;
        dt.u.timestamp.month = 2;
        dt.u.timestamp.day = 3;
        dt.u.timestamp.hour = 4;
        dt.u.timestamp.minute = 5;
        dt.u.timestamp.second = 6;
        dt.u.timestamp.microseconds = 7;
        dt.u.timestamp.utc = 8;

        UT_ASSERT(MI_RESULT_OK == Instance_SetDatetime(params, MI_T("dt"), &dt));
        UT_ASSERT(MI_RESULT_OK == Instance_SetString(params, MI_T("s"), MI_T("input string")));
        UT_ASSERT(MI_RESULT_OK == Instance_SetChar16(params, MI_T("c16"), 1616));

        // reference
        MI_Instance* new_ref = mh.newClass();
        MI_Value value;
        value.reference = new_ref;
        UT_ASSERT(MI_RESULT_OK == Instance_SetUint32(value.reference, MI_T("Key"), 19));
        UT_ASSERT(MI_RESULT_OK == __MI_Instance_SetElement(params, MI_T("rf"), &value, MI_REFERENCE, 0));

        // arrays of types
        MI_Boolean ba[] = {MI_FALSE};
        value.booleana.data = ba;
        value.booleana.size = MI_COUNT(ba);
        UT_ASSERT(MI_RESULT_OK == __MI_Instance_SetElement(params, MI_T("ba"), &value, MI_BOOLEANA, 0));

#define DECLARE_ARRAY_SET_PROP(a_type,a_name,a_size,a_value_field,a_var_str_name,a_enum_type)   \
        vector<a_type>  a_name;  \
        { int count = a_size; while( count-- > 0 ) {a_name.push_back( (a_type)rand());}  }\
        /* several special values */ \
        a_name.push_back(0); a_name.push_back((a_type)-1); a_name.push_back( (a_type)((MI_Uint64(1)<<(sizeof(a_type)*8-1))-1) ); \
        /*MI_Sint8 s8A[] = {-128,0,7,127,4}; */  \
        value.a_value_field.data = &a_name[0]; \
        value.a_value_field.size = (MI_Uint32)a_name.size(); \
        /*value.sint8a.data = s8A;         value.sint8a.size = MI_COUNT(s8A); */ \
        UT_ASSERT(MI_RESULT_OK == __MI_Instance_SetElement(params, a_var_str_name, &value, a_enum_type, 0));

        DECLARE_ARRAY_SET_PROP(MI_Uint8,u8A,554,uint8a,MI_T("u8A"),MI_UINT8A);
        DECLARE_ARRAY_SET_PROP(MI_Sint8,s8A,4,sint8a,MI_T("s8A"),MI_SINT8A);
        DECLARE_ARRAY_SET_PROP(MI_Uint16,u16A,4,uint16a,MI_T("u16A"),MI_UINT16A);
        DECLARE_ARRAY_SET_PROP(MI_Sint16,s16A,4,sint16a,MI_T("s16A"),MI_SINT16A);
        DECLARE_ARRAY_SET_PROP(MI_Uint32,u32A,4,uint32a,MI_T("u32A"),MI_UINT32A);
        DECLARE_ARRAY_SET_PROP(MI_Sint32,s32A,4,sint32a,MI_T("s32A"),MI_SINT32A);
        DECLARE_ARRAY_SET_PROP(MI_Uint64,u64A,4,uint64a,MI_T("u64A"),MI_UINT64A);
        DECLARE_ARRAY_SET_PROP(MI_Sint64,s64A,40,sint64a,MI_T("s64A"),MI_SINT64A);

        // arrays of types
        MI_String sa[] = {(MI_Char*)MI_T("in str1"),(MI_Char*)MI_T("in str2") };
        value.stringa.data = sa;
        value.stringa.size = MI_COUNT(sa);
        UT_ASSERT(MI_RESULT_OK == __MI_Instance_SetElement(params, MI_T("sa"), &value, MI_STRINGA, 0));

#if 0
        __MI_Instance_Print(stdout, params);
#endif

        mh.callInvoke(MI_T("TestAllTypes"), instanceName, params);
        __MI_Instance_Delete(instanceName); instanceName = 0;
        __MI_Instance_Delete(params); params = 0;
        __MI_Instance_Delete(new_ref); new_ref = 0;

        UT_ASSERT(ctx.result == MI_RESULT_OK);
        UT_ASSERT(ctx.instances.size() == 1);
        MI_Instance* out = ctx.instances[0];
        UT_ASSERT(out != 0);
        ctx.instances.clear();

        // verify output
        MI_Boolean b;
        UT_ASSERT(MI_RESULT_OK == Instance_GetBoolean(out, MI_T("b"), &b));
        UT_ASSERT( b == MI_FALSE );

        MI_Uint8 u8;
        UT_ASSERT(MI_RESULT_OK == Instance_GetUint8(out, MI_T("u8"), &u8));
        UT_ASSERT( u8 == 9 );

        MI_Sint8 s8;
        UT_ASSERT(MI_RESULT_OK == Instance_GetSint8(out, MI_T("s8"), &s8));
        UT_ASSERT( s8 == -7 );

        MI_Uint16 u16;
        UT_ASSERT(MI_RESULT_OK == Instance_GetUint16(out, MI_T("u16"), &u16));
        UT_ASSERT( u16 == 17 );

        MI_Sint16 s16;
        UT_ASSERT(MI_RESULT_OK == Instance_GetSint16(out, MI_T("s16"), &s16));
        UT_ASSERT( s16 == -15 );

        MI_Uint32 u32;
        UT_ASSERT(MI_RESULT_OK == Instance_GetUint32(out, MI_T("u32"), &u32));
        UT_ASSERT( u32 == 33 );

        MI_Sint32 s32;
        UT_ASSERT(MI_RESULT_OK == Instance_GetSint32(out, MI_T("s32"), &s32));
        UT_ASSERT( s32 == -31 );

        MI_Uint64 u64;
        UT_ASSERT(MI_RESULT_OK == Instance_GetUint64(out, MI_T("u64"), &u64));
        UT_ASSERT( u64 == 65 );

        MI_Sint64 s64;
        UT_ASSERT(MI_RESULT_OK == Instance_GetSint64(out, MI_T("s64"), &s64));
        UT_ASSERT( s64 == -63 );

        MI_Real32 r32;
        UT_ASSERT(MI_RESULT_OK == Instance_GetReal32(out, MI_T("r32"), &r32));
        UT_ASSERT(r32 == -32.32f);

        MI_Real64 r64;
        UT_ASSERT(MI_RESULT_OK == Instance_GetReal64(out, MI_T("r64"), &r64));
        UT_ASSERT(r64 > -64.65 && r64 < -64.63);

        UT_ASSERT(MI_RESULT_OK == Instance_GetDatetime(out, MI_T("dt"), &dt));
        UT_ASSERT(dt.isTimestamp == 1 &&
            dt.u.timestamp.year == 2 &&
            dt.u.timestamp.month == 3 &&
            dt.u.timestamp.day == 4 &&
            dt.u.timestamp.hour == 5 &&
            dt.u.timestamp.minute == 6 &&
            dt.u.timestamp.second == 7 &&
            dt.u.timestamp.microseconds == 8 &&
            dt.u.timestamp.utc == 9);

    
        MI_Instance* rf = 0;
        MI_Uint32 rf_key = 0;

        UT_ASSERT(MI_RESULT_OK == Instance_GetReference(out, MI_T("rf"), &rf));
        UT_ASSERT( 0 != rf );
        UT_ASSERT(MI_RESULT_OK == Instance_GetUint32(rf,MI_T("Key"), &rf_key ));
        UT_ASSERT(rf_key == 20);

        // string
        MI_String s = 0;
        UT_ASSERT(MI_RESULT_OK == Instance_GetString(out,MI_T("s"), &s ));
        UT_ASSERT(0 == memcmp(s, MI_T("inp!"),5*sizeof(MI_Char)));


        // char16
        MI_Char16 c16;
        UT_ASSERT(MI_RESULT_OK == Instance_GetChar16(out,MI_T("c16"), &c16 ));
        UT_ASSERT(1617 == c16);

        // return value
        UT_ASSERT(MI_RESULT_OK == Instance_GetString(out,MI_T("MIReturn"), &s ));
        UT_ASSERT(0 == memcmp(s, MI_T("100"),4*sizeof(MI_Char)));

        // arrays
        MI_BooleanA out_ba;
        UT_ASSERT(MI_RESULT_OK == Instance_GetValue(out,MI_T("ba"),&out_ba,MI_BOOLEANA));
        UT_ASSERT(out_ba.size == 2);
        UT_ASSERT(out_ba.data[0] == 0);
        UT_ASSERT(out_ba.data[1] == 1);

        TestArray<MI_Uint8,MI_Uint8A,MI_UINT8A>(MI_T("u8A"),u8A,out);
        TestArray<MI_Sint8,MI_Sint8A,MI_SINT8A>(MI_T("s8A"),s8A,out);
        TestArray<MI_Uint16,MI_Uint16A,MI_UINT16A>(MI_T("u16A"),u16A,out);
        TestArray<MI_Sint16,MI_Sint16A,MI_SINT16A>(MI_T("s16A"),s16A,out);
        TestArray<MI_Uint32,MI_Uint32A,MI_UINT32A>(MI_T("u32A"),u32A,out);
        TestArray<MI_Sint32,MI_Sint32A,MI_SINT32A>(MI_T("s32A"),s32A,out);
        TestArray<MI_Uint64,MI_Uint64A,MI_UINT64A>(MI_T("u64A"),u64A,out);
        TestArray<MI_Sint64,MI_Sint64A,MI_SINT64A>(MI_T("s64A"),s64A,out);

        // strings
        MI_StringA out_sa;
        UT_ASSERT(MI_RESULT_OK == Instance_GetValue(out,MI_T("sa"),&out_sa,MI_STRINGA));
        UT_ASSERT(out_sa.size == 3);
        UT_ASSERT(0 == memcmp(out_sa.data[0], MI_T("str1"),5*sizeof(MI_Char)));
        UT_ASSERT(0 == memcmp(out_sa.data[1], MI_T("str2"),5*sizeof(MI_Char)));
        UT_ASSERT(0 == memcmp(out_sa.data[2], MI_T("*"),2*sizeof(MI_Char)));

#if 0
        __MI_Instance_Print(stdout, out);
#endif
        __MI_Instance_Delete(out);
    }

}

NitsTestWithSetup(TestCloning, TestPersonProviderSetup)
{
    MI_Result r;

    // find rtti form person provider
    Context ctx;
    ModuleHandle mh(ctx, MI_T("MSFT_Person"), "PersonProvider");
    mh.callLoad();

    MI_ClassDecl* cl = mh.getClassDecl();


    // Create a new person.
    MI_Instance* inst1;
    r = Instance_New(&inst1, cl, &ctx.batch);
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst1 != 0);
    {
        MI_Value value;
        value.uint32 = 1;

        // MSFT_Person.Key:
        r = __MI_Instance_SetElement(inst1, MI_T("Key"), &value, MI_UINT32, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        // MSFT_Person.First:
        value.string = (MI_Char*)MI_T("George");
        r = __MI_Instance_SetElement(inst1, MI_T("First"), &value, MI_STRING, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        // MSFT_Person.Last:
        value.string = (MI_Char*)MI_T("Washington");
        r = __MI_Instance_SetElement(inst1, MI_T("Last"), &value, MI_STRING, 0);
        UT_ASSERT(r == MI_RESULT_OK);
    }

    // Check fields.
    {
        // Check MSFT_Person.Key
        {
            MI_Uint32 flags;
            MI_Value value;
            MI_Type type;
            r = __MI_Instance_GetElement(inst1, MI_T("Key"), &value, &type, &flags, 0);
            UT_ASSERT(r == MI_RESULT_OK);
            UT_ASSERT(type == MI_UINT32);
            UT_ASSERT(!(flags & MI_FLAG_NULL));
            UT_ASSERT(value.uint32 == 1);
        }

        // Check MSFT_Person.First
        {
            MI_Uint32 flags;
            MI_Value value;
            MI_Type type;
            r = __MI_Instance_GetElement(inst1, MI_T("First"), &value, &type, &flags, 0);
            UT_ASSERT(r == MI_RESULT_OK);
            UT_ASSERT(type == MI_STRING);
            UT_ASSERT(!(flags & MI_FLAG_NULL));
            UT_ASSERT(value.string != NULL);
            UT_ASSERT(value.string == String(MI_T("George")));
        }

        // Check MSFT_Person.Last
        {
            MI_Uint32 flags;
            MI_Value value;
            MI_Type type;
            r = __MI_Instance_GetElement(inst1, MI_T("Last"), &value, &type, &flags, 0);
            UT_ASSERT(r == MI_RESULT_OK);
            UT_ASSERT(type == MI_STRING);
            UT_ASSERT(!(flags & MI_FLAG_NULL));
            UT_ASSERT(value.string != NULL);
            UT_ASSERT(value.string == String(MI_T("Washington")));
        }
    }

    // Clone the person.
    MI_Instance* inst2;
    Instance_Clone(inst1, &inst2, &ctx.batch);
    UT_ASSERT(inst2 != NULL);

    // Get fields back.
    {
        // Check MSFT_Person.Key
        {
            MI_Uint32 flags;
            MI_Value value;
            MI_Type type;
            r = __MI_Instance_GetElement(inst2, MI_T("Key"), &value, &type, &flags, 0);
            UT_ASSERT(r == MI_RESULT_OK);
            UT_ASSERT(type == MI_UINT32);
            UT_ASSERT(!(flags & MI_FLAG_NULL));
            UT_ASSERT(value.uint32 == 1);
        }

        // Check MSFT_Person.First
        {
            MI_Uint32 flags;
            MI_Value value;
            MI_Type type;
            r = __MI_Instance_GetElement(inst2, MI_T("First"), &value, &type, &flags, 0);
            UT_ASSERT(r == MI_RESULT_OK);
            UT_ASSERT(type == MI_STRING);
            UT_ASSERT(!(flags & MI_FLAG_NULL));
            UT_ASSERT(value.string != NULL);
            UT_ASSERT(value.string == String(MI_T("George")));
        }

        // Check MSFT_Person.Last
        {
            MI_Uint32 flags;
            MI_Value value;
            MI_Type type;
            r = __MI_Instance_GetElement(inst2, MI_T("Last"), &value, &type, &flags, 0);
            UT_ASSERT(r == MI_RESULT_OK);
            UT_ASSERT(type == MI_STRING);
            UT_ASSERT(!(flags & MI_FLAG_NULL));
            UT_ASSERT(value.string != NULL);
            UT_ASSERT(value.string == String(MI_T("Washington")));
        }
    }

    // Release the instances.
    __MI_Instance_Delete(inst1);
    __MI_Instance_Delete(inst2);
}
NitsEndTest

static void TestPersonProvider(const char* provider_file)
{
    Context ctx;
    ModuleHandle mh(ctx, MI_T("MSFT_Person"), provider_file);

    mh.callLoad();

    // Test create:
    ExpectNotFound(ctx, mh, 1);
    CreatePerson(ctx, mh, 1, MI_T("George"), MI_T("Washington"));
    ExpectNotFound(ctx, mh, 2);
    CreatePerson(ctx, mh, 2, MI_T("John"), MI_T("Adams"));

    // Test get:
    GetPerson(ctx, mh, 1, MI_T("George"), MI_T("Washington"));
    GetPerson(ctx, mh, 2, MI_T("John"), MI_T("Adams"));

    // Test enumerate:
    EnumeratePerson(ctx, mh);

    // Test delete:
    DeletePerson(ctx, mh, 1);
    ExpectNotFound(ctx, mh, 1);

    // Test Person.Add():
    InvokePersonAdd(ctx, mh);

    mh.callUnload();
}

static void TestPersonProviderAllTypes(const char* provider_file)
{
    Context ctx;
    ModuleHandle mh(ctx, MI_T("MSFT_Person"), provider_file);

    mh.callLoad();

    // Test Person.Add():
    InvokeTestAllTypes(ctx, mh);

    mh.callUnload();
}


static void TestFriendsProvider(const char* provider_file)
{
    Context ctx;
    ModuleHandle mh(ctx, MI_T("MSFT_Friends"), provider_file);
    MI_Result r;

    // Load the 'MSFT_Friends' provider.
    mh.callLoad();

    // Create an instance of class MSFT_Person.
    MI_Instance* person = mh.newClass(MI_T("MSFT_Person"));
    UT_ASSERT(person != NULL);

    r = Instance_SetUint32(person, MI_T("Key"), 1);
    UT_ASSERT(r == MI_RESULT_OK);

#if 0
    __MI_Instance_Print(stdout, person);
#endif

    // Find associators of this person.
    mh.callAssociators(person);

    // Check the result.
    UT_ASSERT(ctx.result == MI_RESULT_OK);

    // Check that we got back exactly one friend.
    UT_ASSERT(ctx.instances.size() == 1);
    MI_Instance* inst = ctx.instances[0];
    UT_ASSERT(inst != 0);
    ctx.instances.clear();

    // Print the instance.
#if 0
    __MI_Instance_Print(stdout, inst);
#endif

    // Now call references.
    mh.callReferences(person);
    UT_ASSERT(ctx.result == MI_RESULT_NOT_SUPPORTED);
    __MI_Instance_Delete(person);    person=0;

    // Unload the 'MSFT_Friends' class provider.
    mh.callUnload();

    // Release the instance.
    __MI_Instance_Delete(inst);
}

NitsTestWithSetup(TestPersonProvider_C, TestPersonProviderSetup)
{
    TestPersonProvider("PersonProvider");
}
NitsEndTest

NitsTestWithSetup(TestPersonProviderAllTypes_C, TestPersonProviderSetup)
{
    TestPersonProviderAllTypes("PersonProvider");
}
NitsEndTest

NitsTestWithSetup(TestFriendsProvider_C, TestPersonProviderSetup)
{
    TestFriendsProvider("PersonProvider");
}
NitsEndTest

NitsTestWithSetup(TestPersonProvider_CXX, TestPersonProviderSetup)
{
    TestPersonProvider("PersonProviderCXX");
}
NitsEndTest

NitsTestWithSetup(TestPersonProviderAllTypes_CXX, TestPersonProviderSetup)
{
    TestPersonProviderAllTypes("PersonProviderCXX");
}
NitsEndTest

NitsTestWithSetup(TestFriendsProvider_CXX, TestPersonProviderSetup)
{
    TestFriendsProvider("PersonProviderCXX");
}
NitsEndTest




