TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_provmgr

SOURCES = $(TOP)/ut/omitestcommon.cpp $(TOP)/ut/omifaultsimtest.cpp test_provmgr.cpp

ifdef DISABLE_INDICATION
else
SOURCES += StrandHelper.cpp test_SubscriptionContext.cpp test_AggregationContext.cpp test_Context.cpp test_IndicationFilter.cpp test_LifecycleContext.cpp test_SubMgr.cpp schema.c XYZ_Test.c
endif

DEFINES = TEST_BUILD

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = provmgr miapi omi_error xmlserializer wsman http protocol sock xmlserializer xml wql base micxx omiclient $(UNITTESTLIBS) pal 

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)

reset:
	$(BINDIR)/nits -reset
