TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_wsman

$(shell mkdir -p $(OBJDIR)/unittest)

SOURCES = $(TOP)/ut/omitestcommon.cpp \
    $(TOP)/ut/omifaultsimtest.cpp \
    $(TOP)/tests/base/schema.c \
    test_auth.cpp \
    test_wsbuf.cpp \
    test_wsman.cpp \
    test_wsman_inproc.cpp \
    test_NumberProvider.cpp \
    utils.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES = TEST_BUILD

LIBRARIES = omiclient micxx omi_error wsman xmlserializer http protocol sock xml base $(UNITTESTLIBS) pal $(INDICMNLIB) $(INDIMGRLIB) omi_error wsman xmlserializer base

CACHEGRIND_ARGS = $(TARGET)

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)

vg:
	$(call RUNVALGRIND)
