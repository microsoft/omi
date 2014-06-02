TOP = ../../../..
include $(TOP)/config.mak

CXXPROGRAM = fanclient

#SOURCES = fanclient.cpp
SOURCES = fan.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST=

LIBRARIES = omiclient micxx wsman http protocol sock wql base

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)
