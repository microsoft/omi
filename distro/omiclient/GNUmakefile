TOP = ..
include $(TOP)/config.mak

CXXSHLIBRARY = omiclient

SOURCES = \
    client.cpp \
    handler.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = protocol sock micxx base io

DEFINES += BUILDING_OMICLIENT

include $(TOP)/mak/rules.mak
