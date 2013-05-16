TOP = ..
include $(TOP)/config.mak

LIBRARY = disp

SOURCES = disp.c agentmgr.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST=

LIBRARIES = provreg provmgr base

include $(TOP)/mak/rules.mak

top:
	( cd $(TOP); make )
