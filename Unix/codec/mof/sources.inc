############################################################################
#
#   Copyright (C) Microsoft Corporation.
#
#   All rights reserved.
#
############################################################################

WMIV2ROOT=$(PROJECT_ROOT)\wmi\wmiv2

TOP=..\..\..

TARGETNAME=mimofcodec
TARGETTYPE=DYNLINK
TARGET_DESTINATION=WINOMI\bin

TARGETLIBS= \

INCLUDES= $(INCLUDES); \
    $(TOP); \
    $(TOP)\common; \
    $(TOP)\codec\common; \
    $(TOP)\codec\mof\parser; \
    $(WMIV2ROOT); \
    $(WMIV2ROOT)\Common; \

SOURCES= \
    ..\codecimpl.c \
    ..\mofcodec.rc \
    ..\mofcodec.c \
    ..\dllmain.c \
    ..\strings.c \
    ..\instanceutil.c \
    ..\mofserializer.c \
    ..\buf.c \
    ..\strset.c

# The TARGETLIBS macro specifies additional libraries to link against your target
# image. Each library path specification should contain an asterisk (*)
# where the machine-specific subdirectory name should go.
TARGETLIBS=$(TARGETLIBS)\
    $(SDK_LIB_PATH)\mi.lib \
    $(OBJECT_ROOT)\admin\wmi\winomi\codec\mof\parser\$O\mofparser.lib \
    $(OBJECT_ROOT)\admin\wmi\winomi\base\$O\base.lib \
    $(ADMIN_LIB_PATH)\pal.lib \
    $(OBJECT_ROOT)\admin\wmi\wmiv2\common\win8\$O\miutils.lib \
    $(OBJECT_ROOT)\admin\wmi\winomi\omiutils\blue\$O\omiutils.lib \
!ifdef TEST_BUILD
    $(ADMIN_LIB_PATH)\nitsdll.lib \
!endif

UNICODE=1
USE_MSVCRT=1

C_DEFINES= $(C_DEFINES) \
    /DMI_INTERNAL \
    /DWINBUILD \
    /D_UNICODE \
    /DUNICODE \
    /DCONFIG_ENABLE_WCHAR \
    /DMI_CONST= \
    /DHOOK_BUILD \
!ifdef TEST_BUILD
    /DTEST_BUILD
!endif

DLLDEF=$(OBJ_PATH)\$O\mofcodec.def

DLLDEF_OBJECTS= \
    $(ADMIN_LIB_PATH)\nitsstub.obj \
