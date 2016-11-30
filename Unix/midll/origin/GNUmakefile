TOP = ../..
include $(TOP)/config.mak

CSHLIBRARY = mi_origin

SOURCES = \
	../gnumain.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS
LIBRARIES = miapi protocol sock wql base $(PALLIBS) omi_error wsman http xmlserializer xml micodec mofparser

EXPORTS=../libmi.exp

include $(TOP)/mak/rules.mak

# Setting this after rules as we are overriding the default one we use
LIBPATHFLAGS = $(shell $(BUILDTOOL) libpath \'\$$ORIGIN\' )

nm:
	( nm -g $(TARGET)|grep -v U )
