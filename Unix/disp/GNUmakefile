TOP = ..
include $(TOP)/config.mak

LIBRARY = disp

SOURCES = disp.c agentmgr.c

ifeq ($(ENABLE_PREEXEC),1)
 SOURCES += preexec.c
endif

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= HOOK_BUILD

LIBRARIES = provreg provmgr base

include $(TOP)/mak/rules.mak

top:
	( cd $(TOP); make )
