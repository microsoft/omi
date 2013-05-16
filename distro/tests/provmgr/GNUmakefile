TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_provmgr

SOURCES = test_provmgr.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = provmgr wsman http protocol sock xml wql base $(UNITTESTLIBS)

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)
