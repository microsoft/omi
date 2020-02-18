TOP = ../..
include $(TOP)/config.mak

CSHLIBRARY = mi

SOURCES = \
	../gnumain.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST=

LIBRARIES = miapi protocol sock wql $(PALLIBS) omi_error wsman http base xmlserializer xml micodec mofparser pal

EXPORTS=../libmi.exp

include $(TOP)/mak/rules.mak

nm:
	( nm -g $(TARGET)|grep -v U )
