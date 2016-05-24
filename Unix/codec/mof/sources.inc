############################################################################
#
#   PowerShell Desired State Configuration for Linux
#
#   Copyright (c) Microsoft Corporation
#
#   All rights reserved. 
#
#   MIT License
#
#   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
    $(ADMIN_LIB_PATH)\nitsstub.lib \
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
