TOP = ../../../..
include $(TOP)/config.mak
CXXUNITTEST = test_mimofcodec
SOURCES= \
    consts.c \
    test_lex.cpp \
    test_parser.cpp \
    test_mofserializer.cpp \
    instance.c \
    schema.c \
    class.c \
    qualifierset.c \
    parameterset.c

INCLUDES= \
    $(TOP) \
    $(TOP)/codec/common \
    $(TOP)/codec/mof/parser \
    $(TOP)/common \
    $(TOP)/common/linux \
    $(TOP)/nits/base \

DEFINES= TEST_BUILD

LIBRARIES = micodec mi moftestutil pal $(UNITTESTLIBS) mofparser base pal

include $(TOP)/mak/rules.mak

