TOP = ../../..
include $(TOP)/config.mak

LIBRARY = mofparser

SOURCES = \
	buffer.c \
	moflex.c \
	ptrarray.c \
	types.c \
	utility.c \
	mofparser.c \
	mofyacc.c \
	mofhash.c 

INCLUDES = $(TOP)/common  $(TOP) $(TOP)/codec/common $(TOP)/nits/base 

DEFINES = MI_CONST= 

include $(TOP)/mak/rules.mak

