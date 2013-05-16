TOP = ../../../..
include $(TOP)/config.mak

CXXPROGRAM = PersonProvider

SOURCES = test_PersonProvider.cpp

INCLUDES = $(TOP) $(TOP)/common 

LIBRARIES = base ut io

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)
