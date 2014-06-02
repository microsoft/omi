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
    class.c \
    classdecl.c \
    instance.c \
    instanceprint.c \
    messages.c \
    messagesprint.c \
    interaction.c \
    list.c \
    parameters.c \
    result.c \
    schemadecl.c \
    stringarray.c \
    types.c \
    packing.c \
    helpers.c \
    naming.c \
    field.c \
    fieldprint.c \
    env.c \
    process.c \
    pidfile.c \
    paths.c \
    strand.c \
    strarr.c \
    user.c \
    credcache.c \
    conf.c \
    getopt.c \
    base64.c \
    indent.c \
    miextras.c \
    multiplex.c \
    ptrarray.c \
    timer.c \
    sock.c \
    addr.c \
    selector.c

ifdef SUNOS_SPARC_SUNPRO
    SOURCES += sunsparc8_atomic.s
endif

INCLUDES = $(TOP) $(TOP)/common $(TOP)/base

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS HOOK_BUILD

LIBRARIES = pal

include $(TOP)/mak/rules.mak
