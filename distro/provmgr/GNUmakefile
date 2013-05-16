TOP = ..
include $(TOP)/config.mak

LIBRARY = provmgr

SOURCES = provmgr.c context.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS

LIBRARIES = base

include $(TOP)/mak/rules.mak

top:
	( cd $(TOP); make )
