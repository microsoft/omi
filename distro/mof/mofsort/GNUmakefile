TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = mofsort

SOURCES = mofsort.cpp

INCLUDES = $(TOP) $(TOP)/mof $(TOP)/common

LIBRARIES = mof base ut io

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)
