TOP = ..
include $(TOP)/config.mak

CXXSHLIBRARY = micxx

SOURCES = \
    array.cpp \
    atomic.cpp \
    context.cpp \
    datetime.cpp \
    instance.cpp \
    propertyset.cpp \
    string.cpp \
    dinstance.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES = BUILDING_MICXX MI_CONST= DETECT_FORBIDDEN_FUNCTIONS


LIBRARIES = base io

ifeq ($(OS),LINUX)
CXXFLAGS = -fno-exceptions -fno-enforce-eh-specs -fno-rtti
endif

include $(TOP)/mak/rules.mak
