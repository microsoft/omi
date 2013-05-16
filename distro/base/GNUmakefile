TOP = ..
include $(TOP)/config.mak

ifeq ($(OS)-$(ARCH),HPUX-PARISC)
CXXSHLIBRARY = base
else
LIBRARY = base
endif

SOURCES = \
    base.c \
    batch.c \
    buf.c \
    classdecl.c \
    instance.c \
    instanceprint.c \
    messages.c \
    messagesprint.c \
    lib.c \
    list.c \
    parameters.c \
    result.c \
    schemadecl.c \
    stringarray.c \
    strings.c \
    types.c \
    log.c \
    logging.c \
    packing.c \
    helpers.c \
    naming.c \
    field.c \
    fieldprint.c \
    dir.c \
    env.c \
    time.c \
    process.c \
    pidfile.c \
    paths.c \
    strarr.c \
    user.c \
    credcache.c \
    conf.c \
    atomic.c \
    getopt.c \
    file.c \
    hashtable.c \
    base64.c \
    indent.c \
    miextras.c \
    ptrarray.c \
    clientft.cpp

ifdef SUNOS_SPARC_SUNPRO
    SOURCES += sunsparc8_atomic.s
endif

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS

include $(TOP)/mak/rules.mak
