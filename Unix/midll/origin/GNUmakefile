TOP = ../..
include $(TOP)/config.mak

CSHLIBRARY = mi_origin

SOURCES = \
	../gnumain.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST=
LIBRARIES = miapi protocol sock wql base omi_error wsman http $(PALLIBS) xmlserializer xml micodec mofparser

EXPORTS=../libmi.exp

include $(TOP)/mak/rules.mak

# Setting this after rules as we are overriding the default one we use
ifeq ($(OS),DARWIN)
LIBNAMEOPT=$(shell $(BUILDTOOL) libname @rpath/$(shell $(BUILDTOOL) shlibname mi))
else
LIBPATHFLAGS = $(shell $(BUILDTOOL) libpath \'\$$ORIGIN\' )
endif

nm:
	( nm -g $(TARGET)|grep -v U )
