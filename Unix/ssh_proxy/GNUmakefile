TOP = ..
include $(TOP)/config.mak

CXXPROGRAM = omi_proxy

SOURCES = OMIProxy.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES = HOOK_BUILD MI_CONST= DETECT_FORBIDDEN_FUNCTIONS

LIBRARIES = miapi protocol sock wql base disp provreg provmgr $(PALLIBS) wql base xml indimgr indicmn omi_error wsman http xmlserializer xml disp micodec mofparser

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)
