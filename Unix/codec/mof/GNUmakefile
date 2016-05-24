TOP = ../..
include $(TOP)/config.mak

LIBRARY = micodec

SOURCES = \
	codecimpl.c \
	mofcodec.c \
	strings.c \
	instanceutil.c \
	mofserializer.c \
	buf.c \
	strset.c

INCLUDES = $(TOP)/common  $(TOP) $(TOP)/codec/common $(OMI)/nits/base  $(TOP)/codec/mof/parser

DEFINES = MI_CONST=

include $(TOP)/mak/rules.mak

