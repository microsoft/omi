TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_base

SOURCES = test_auth.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES =

LIBRARIES = micxx base ut $(PALLIBS)

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)
