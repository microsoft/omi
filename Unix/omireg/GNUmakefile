TOP = ..
include $(TOP)/config.mak

CXXPROGRAM = omireg

SOURCES = omireg.cpp 

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= HOOK_BUILD

LIBRARIES = omiclient micxx omi_error wsman http xml xmlserializer $(BASELIBS) $(PALLIBS)

include $(TOP)/mak/rules.mak
