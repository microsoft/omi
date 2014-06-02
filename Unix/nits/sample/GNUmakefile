TOP = ../..
include $(TOP)/config.mak

CXXSHLIBRARY = nitssample

SOURCES = Product.c \
    Shim.c \
    NitsNewInterfaceTests.cpp \
    NitsNewInterfaceTests1.cpp \
    test.cpp \

DEFINES = UNICODE 

INCLUDES = . $(TOP) $(TOP)/common

LIBRARIES = pal nits

include $(TOP)/mak/rules.mak