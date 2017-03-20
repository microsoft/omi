TOP = ..
include $(TOP)/config.mak

CXXPROGRAM = omigen

SOURCES = \
    py_gen.cpp \
    gen.cpp  \
    Parser.cpp  \
    QualifierDecls.cpp \
    main.cpp

INCLUDES = $(TOP) $(TOP)/common $(TOP)/mof

DEFINES = MI_CONST= HOOK_BUILD

LIBRARIES = mof base $(PALLIBS)

include $(TOP)/mak/rules.mak
