TOP = ..
include $(TOP)/config.mak

CSHLIBRARY = mi

SOURCES = \
	gnumain.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS

LIBRARIES = miapi  protocol sock wql base $(PALLIBS) omi_error wsman http xmlserializer micodec mofparser

include $(TOP)/mak/rules.mak

nm:
	( nm -g $(TARGET)|grep -v U )
