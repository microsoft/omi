TOP = ..
include $(TOP)/config.mak

CXXPROGRAM = omiconfigeditor

SOURCES = configeditor.cpp 

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS HOOK_BUILD

LIBRARIES = omiclient micxx $(BASELIBS) $(PALLIBS)

include $(TOP)/mak/rules.mak
