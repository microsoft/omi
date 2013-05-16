TOP = ..
include $(TOP)/config.mak

CXXPROGRAM = omicheck

SOURCES = check.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST=

LIBRARIES = omiclient micxx wsman http protocol sock base io

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)
