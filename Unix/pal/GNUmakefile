TOP = ..
include $(TOP)/config.mak

ifeq ($(OBJDIRBASE),nitspal)
  LIBRARY = nitspal
  DEFINES = TEST_BUILD NITS_INTERNAL
else
    LIBRARY = pal

    DEFINES = HOOK_BUILD

    ifeq ($(CONFIG_PREFIX),$(CONFIG_SRCDIR))
      DEFINES += ENABLE_UNITTESTING
    endif
endif

SOURCE_FILES = \
    atomic.c \
    cpu.c \
    sem.c \
    once.c \
    shlib.c \
    sleep.c \
    slist.c \
    tls.c \
    process.c \
    thread.c \
    condlock.c \
    recursivelock.c \
    readwritelock.c \
    shmem.c \
    strings.c \
    dir.c \
    file.c \
    hashmap.c \
    intlstr.c \
    format.c \
    encrypt.c \
    ownedmemory.c \
    log.c \
    alloc.c \
    atexit.c

ifeq ($(OBJDIRBASE),nitspal)
SOURCES = $(SOURCE_FILES)
else
SOURCES = $(SOURCE_FILES) \
    stub.c
endif

INCLUDES = . $(TOP) $(TOP)/common

include $(TOP)/mak/rules.mak
