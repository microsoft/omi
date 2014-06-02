TOP = ..
include $(TOP)/config.mak

CXXPROGRAM = omicheck

SOURCES = check.cpp provmsg.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= HOOK_BUILD

LIBRARIES = wsman xmlserializer xml omi_error omiclient micxx wsman http xml xmlserializer protocol $(BASELIBS) $(PALLIBS)

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)
