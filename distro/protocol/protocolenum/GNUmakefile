TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = protocolenum

SOURCES = protocolenum.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = protocol sock base io ut

CACHEGRIND_ARGS = $(TARGET)

include $(TOP)/mak/rules.mak

run:
	time $(TARGET)
