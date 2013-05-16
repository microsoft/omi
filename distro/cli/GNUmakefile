TOP = ..
include $(TOP)/config.mak

CXXPROGRAM = omicli

SOURCES = cli.cpp climain.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS

LIBRARIES = omiclient micxx protocol sock wql base io

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)
