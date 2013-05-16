TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_provreg

SOURCES = test_provreg.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = provreg base io ut

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)
