TOP = ../..
include $(TOP)/config.mak

LIBRARY = test_util

SOURCES = util.c server.c indiprvdconfig.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= HOOK_BUILD MI_API_VERSION=2

include $(TOP)/mak/rules.mak

top:
	( cd $(TOP); make )
