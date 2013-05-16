TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_mof

SOURCES = test_mof.cpp

INCLUDES = $(TOP) $(TOP)/mof $(TOP)/common

LIBRARIES = mof base $(UNITTESTLIBS)

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)
