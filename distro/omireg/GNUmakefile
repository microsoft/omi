TOP = ..
include $(TOP)/config.mak

CXXPROGRAM = omireg

SOURCES = omireg.cpp $(TOP)/base/clientft.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS

LIBRARIES = omiclient micxx base io

include $(TOP)/mak/rules.mak
