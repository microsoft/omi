TOP = ..
include $(TOP)/config.mak

CXXPROGRAM = omigen

SOURCES = \
    gen.cpp  \
    Parser.cpp  \
    QualifierDecls.cpp \
    main.cpp

INCLUDES = $(TOP) $(TOP)/common $(TOP)/mof

DEFINES = MI_CONST=

LIBRARIES = mof base io

include $(TOP)/mak/rules.mak
