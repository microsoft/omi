TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_base

SOURCES = $(TOP)/ut/omitestcommon.cpp $(TOP)/ut/omifaultsimtest.cpp test_base.cpp schema.c test_credcache.cpp test_timer.cpp test_class.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES = DETECT_FORBIDDEN_FUNCTIONS TEST_BUILD

LIBRARIES = micxx omi_error wsman http xmlserializer xml protocol sock base ut pal nits

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)

OPTS= --cpp -D -M -V -S -n -s test_repos_classDecl

CLASSES = MSFT_Person MSFT_AllTypes MSFT_Process Inner Outer

gen:
	$(BINDIR)/omigen $(OPTS) schema.mof $(CLASSES)

vg:
	$(call RUNVALGRIND)
	
dt:
ifdef UTBUILD
	$(TARGET) TestWSManDatetime
else
	$(BINDIR)/nits $(TARGET):TestWSManDatetime
endif
