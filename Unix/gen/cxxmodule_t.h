//==============================================================================
//
// cxxmodule.h - templates for generating 'module.h' and 'module.cpp'
//
//==============================================================================

#ifndef _migen_cxxmodule_t_h
#define _migen_cxxmodule_t_h

//==============================================================================
//
// MODULE_CPP_TEMPLATE
//
//==============================================================================

#define MODULE_CPP_TEMPLATE "\
#include <MI.h>\n\
#include \"module.h\"\n\
\n\
MI_BEGIN_NAMESPACE\n\
\n\
Module::Module()\n\
{\n\
}\n\
\n\
Module::~Module()\n\
{\n\
}\n\
\n\
MI_END_NAMESPACE\n"

//==============================================================================
//
// MODULE_H_TEMPLATE
//
//==============================================================================

#define MODULE_H_TEMPLATE "\
#ifndef _Module_t_h\n\
#define _Module_t_h\n\
\n\
#include <MI.h>\n\
#include <micxx/micxx.h>\n\
\n\
MI_BEGIN_NAMESPACE\n\
\n\
/*  instance of this class is automatically created when library is loaded;\n\
    it's a convenient place to store global data associated with the module */\n\
class Module\n\
{\n\
public:\n\
    Module();\n\
    ~Module();\n\
\n\
};\n\
\n\
MI_END_NAMESPACE\n\
#endif /* _Module_t_h */\n"

#endif /* _migen_cxxmodule_t_h */
