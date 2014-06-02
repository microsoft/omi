TOP = ..
include $(TOP)/config.mak

CXXPROGRAM = omicli

SOURCES = cli_c.c climain_c.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = HOOK_BUILD MI_CONST= DETECT_FORBIDDEN_FUNCTIONS

LIBRARIES = miapi protocol sock wql base $(PALLIBS) omi_error wsman xmlserializer base

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)
