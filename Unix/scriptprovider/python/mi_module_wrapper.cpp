#include "mi_module_wrapper.hpp"


#include "mi_wrapper.hpp"
#include "mi_context.hpp"
#include "mi_schema_wrapper.hpp"


#include "functor.hpp"


#include <cassert>


namespace
{


typedef util::function_holder<scx::Load_Unload_Functor,
                              int,
                              scx::MI_Module::Ptr const&,
                              scx::MI_Context::Ptr const&> LoadFNHolder_t;

typedef util::function_holder<scx::Load_Unload_Functor,
                              int,
                              scx::MI_Module::Ptr const&,
                              scx::MI_Context::Ptr const&> UnloadFNHolder_t;


}


namespace scx
{


/*static*/ char const MI_Module_Wrapper::NAME[] = "MI_Module";
/*static*/ char const MI_Module_Wrapper::OMI_NAME[] = "omi.MI_Module";
/*static*/ char const MI_Module_Wrapper::DOC[] = "omi.MI_Module utility";
/*static*/ PyTypeObject MI_Module_Wrapper::s_PyTypeObject = {};


/*static*/ void
MI_Module_Wrapper::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_Module_Wrapper::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_Module_Wrapper);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_init = init;
    s_PyTypeObject.tp_new = newObj;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (
            pModule, NAME, reinterpret_cast<PyObject*>(&s_PyTypeObject));
    }
}


/*static*/ void
MI_Module_Wrapper::dealloc (
    PyObject* pObj)
{
    //SCX_BOOKEND ("MI_Module_Wrapper::dealloc");
    if (NULL != pObj)
    {
        MI_Module_Wrapper* pDecl =
            reinterpret_cast<MI_Module_Wrapper*>(pObj);
        pDecl->~MI_Module_Wrapper ();
        pDecl->ob_type->tp_free (pObj);
    }
}


PyObject*
MI_Module_Wrapper::newObj (
    PyTypeObject* pType,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Module_Wrapper::newObj");
    PyObject* pObj = pType->tp_alloc (pType, 0);
    return pObj;
}


int
MI_Module_Wrapper::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_Module_Wrapper::init");
    char* KEYWORDS[] = {
        "schemaDecl",
        "load",
        "unload",
        NULL
    };
    int rval = -1;
    PyObject* pSchemaDeclObj = NULL;
    PyObject* pLoadObj = NULL;
    PyObject* pUnloadObj = NULL;
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "OOO", KEYWORDS,
            &pSchemaDeclObj, &pLoadObj, &pUnloadObj))
    {
        SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        if (PyObject_TypeCheck (
                pSchemaDeclObj,
                const_cast<PyTypeObject*>(
                    MI_SchemaDecl_Placeholder::getPyTypeObject ())))
        {
            if (PyCallable_Check (pLoadObj) &&
                PyCallable_Check (pUnloadObj))
            {
                std::ostringstream strm;
                strm << "MI_SchemaDecl_Placeholder address: " << std::hex
                     << static_cast<void*>(pSchemaDeclObj);
                SCX_BOOKEND_PRINT (strm.str ());
                strm.str ("");
                strm.clear ();
                MI_SchemaDecl_Placeholder::ConstPtr pSchemaDecl_PH (
                    reinterpret_cast<MI_SchemaDecl_Placeholder*>(pSchemaDeclObj));
                MI_Module::LoadFn::Ptr pLoadFn (
                    new LoadFNHolder_t (
                        Load_Unload_Functor (
                            py_ptr<PyObject> (pLoadObj, DO_NOT_INC_REF))));
                MI_Module::UnloadFn::Ptr pUnloadFn (
                    new UnloadFNHolder_t (
                        Load_Unload_Functor (
                            py_ptr<PyObject> (pUnloadObj, DO_NOT_INC_REF))));
                MI_Module_Wrapper* pModule =
                    reinterpret_cast<MI_Module_Wrapper*>(pSelf);
                new (const_cast<MI_SchemaDecl_Placeholder::ConstPtr*>(
                         &(pModule->m_pSchemaDecl_PH)))
                    MI_SchemaDecl_Placeholder::ConstPtr (pSchemaDecl_PH);
                new (const_cast<MI_Module::LoadFn::Ptr*>(&(pModule->m_pLoadFn)))
                    MI_Module::LoadFn::Ptr (pLoadFn);
                new (const_cast<MI_Module::UnloadFn::Ptr*>(&(pModule->m_pUnloadFn)))
                    MI_Module::UnloadFn::Ptr (pUnloadFn);
                new (&(pModule->m_pModule)) MI_Module::Ptr ();
                rval = 0;
            }
            else
            {
                SCX_BOOKEND_PRINT ("pLoadObj ot pUnloadObj are not callable");
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("pSchemaDeclObj is not MI_SchemaDecl_Placeholder");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
    }
    return rval;
}


/*static*/ PyTypeObject const*
MI_Module_Wrapper::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


/*static*/
MI_Module_Wrapper::PyPtr
MI_Module_Wrapper::createPyPtr (
        MI_Module::Ptr const& pModule)
{
    SCX_BOOKEND ("MI_Module::createPyPtr");
    PyObjPtr pModuleObj (s_PyTypeObject.tp_alloc (&s_PyTypeObject, 0));
    if (pModuleObj)
    {
        return PyPtr (
            new (pModuleObj.release ()) MI_Module_Wrapper (pModule));
    }
    return PyPtr ();
}

    
/*dtor*/
MI_Module_Wrapper::~MI_Module_Wrapper ()
{
    SCX_BOOKEND ("MI_Module_Wrapper::dtor");
}


MI_Module::Ptr const&
MI_Module_Wrapper::createModule (
    PyObject* const pPyModule)
{
    SCX_BOOKEND ("MI_Module_Wrapper::createModule");
    assert (0 != pPyModule);
    if (!m_pModule)
    {
        if (m_pSchemaDecl_PH)
        {
            SCX_BOOKEND_PRINT ("m_pSchemaDecl_PH is not NULL");
        }
        else
        {
            SCX_BOOKEND_PRINT ("m_pSchemaDecl_PH is NULL");
        }
        std::ostringstream strm;
        strm << "MI_SchemaDecl_Placeholder address: " << std::hex
             << static_cast<const void*>(m_pSchemaDecl_PH.get ());
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
        MI_SchemaDecl::Ptr pSchemaDecl =
            m_pSchemaDecl_PH->createSchemaDecl (pPyModule);
        if (pSchemaDecl)
        {
            SCX_BOOKEND_PRINT ("MI_SchemaDecl creation succeeded");
            m_pModule = new MI_Module (pSchemaDecl, m_pLoadFn, m_pUnloadFn);
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_SchemaDecl creation failed");
        }
    }
    return m_pModule;
}


/*ctor*/
MI_Module_Wrapper::MI_Module_Wrapper (
    MI_SchemaDecl_Placeholder::ConstPtr const& pSchemaDecl_PH,
    MI_Module::LoadFn::Ptr const& pLoadFn,
    MI_Module::UnloadFn::Ptr const& pUnloadFn)
    : m_pSchemaDecl_PH (pSchemaDecl_PH)
    , m_pLoadFn (pLoadFn)
    , m_pUnloadFn (pUnloadFn)
{
    SCX_BOOKEND ("MI_Module_Wrapper::ctor (MI_Schema, LoadFn, UnloadFn)");
}


/*ctor*/
MI_Module_Wrapper::MI_Module_Wrapper (
    MI_Module::Ptr const& pModule)
    : m_pModule (pModule)
{
    SCX_BOOKEND ("MI_Module_Wrapper::ctor (MI_Module)");
}


} // namespace scx
