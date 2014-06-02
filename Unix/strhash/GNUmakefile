TOP = ..
include $(TOP)/config.mak

CXXPROGRAM = strhash

SOURCES = strhash.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES =

ARGUMENTS = states.txt

GENFILES = $(TOP)/protocol/quickstr.inc \
         $(TOP)/protocol/quickstr.h \
         $(TOP)/protocol/hashtest/hash.inc \
         $(TOP)/protocol/hashtest/simple.inc \
         $(TOP)/protocol/hashtest/test_strhash.cpp

include $(TOP)/mak/rules.mak
