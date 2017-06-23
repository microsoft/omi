TOP = ..
include $(TOP)/config.mak

CXXPROGRAM = omicli

SOURCES = cli_c.c climain_c.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = HOOK_BUILD MI_CONST=

LIBRARIES = mi $(PALLIBS) xmlserializer base micodec mofparser

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)
