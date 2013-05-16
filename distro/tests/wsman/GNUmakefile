TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_wsman

$(shell mkdir -p $(OBJDIR)/unittest)

SOURCES = \
    $(TOP)/tests/base/schema.c \
    test_auth.cpp \
    test_wsbuf.cpp \
    test_wsman.cpp \
    test_wsman_inproc.cpp \
    test_NumberProvider.cpp \
    utils.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = omiclient micxx wsman http protocol sock xml base ut io

CACHEGRIND_ARGS = $(TARGET)

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)

vg:
	valgrind --tool=memcheck $(TARGET)
