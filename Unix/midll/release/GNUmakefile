TOP = ../..
include $(TOP)/config.mak

CSHLIBRARY = mi

SOURCES = \
	../gnumain.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST=

LIBRARIES = miapi protocol sock wql base $(PALLIBS) omi_error wsman http xmlserializer xml micodec mofparser pal

EXPORTS=../libmi.exp

include $(TOP)/mak/rules.mak

nm:
	( nm -g $(TARGET)|grep -v U )
