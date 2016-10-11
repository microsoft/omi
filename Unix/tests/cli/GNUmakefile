TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_cli

SOURCES = $(TOP)/ut/omitestcli.cpp $(TOP)/ut/omifaultsimtest.cpp test_cli.cpp \
    ../../cli/cli_c.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = TEST_BUILD

LIBRARIES = omiclient micxx wql miapi  protocol sock base $(UNITTESTLIBS) pal omi_error wsman http xmlserializer xml base micodec mofparser  ${GSSLIB}

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)
