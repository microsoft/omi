TOP = ..
include $(TOP)/config.mak

LIBRARY = provreg

SOURCES = provreg.c regfile.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= HOOK_BUILD

LIBRARIES = base

include $(TOP)/mak/rules.mak

top:
	(cd $(TOP); $(MAKE) )
