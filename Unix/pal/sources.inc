TARGETTYPE=LIBRARY

TARGETLIBS=

TOP=..\..

INCLUDES= $(INCLUDES); \
    $(TOP); \
    $(TOP)\common; \
    $(TOP)\common\windows; \

SOURCES= \
    ..\atomic.c \
    ..\cpu.c \
    ..\sem.c \
    ..\once.c \
    ..\shlib.c \
    ..\sleep.c \
    ..\slist.c \
    ..\tls.c \
    ..\thread.c \
    ..\process.c \
    ..\condlock.c \
    ..\recursivelock.c \
    ..\readwritelock.c \
#    ..\cachedlock.c \
    ..\shmem.c \
    ..\strings.c \
    ..\dir.c \
    ..\file.c \
    ..\hashmap.c \
    ..\intlstr.c \
    ..\format.c \
    ..\encrypt.c \
    ..\ownedmemory.c

UNICODE=1

USE_MSVCRT=1

C_DEFINES= $(C_DEFINES) \
    /DMI_INTERNAL \
    /DWINBUILD \
    /D_UNICODE \
    /DUNICODE \
    /DCONFIG_ENABLE_WCHAR \
    /DMI_CONST= \
