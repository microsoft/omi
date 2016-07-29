TOP = ..
include $(TOP)/config.mak

CXXSHLIBRARY = omiclient

SOURCES = \
    client.cpp \
    handler.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = protocol sock micxx base $(PALLIBS) omi_error wsman xmlserializer http base

DEFINES += BUILDING_OMICLIENT HOOK_BUILD

include $(TOP)/mak/rules.mak
