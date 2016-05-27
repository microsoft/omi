TOP = ..\..\..\..

TARGETNAME=codectestutils
TARGETTYPE=LIBRARY

INCLUDES= $(INCLUDES); \
	$(TOP)\common\windows; \
	$(TOP)\common; \
	$(TOP)\nits\base; \
	$(TOP)\pal; \

C_DEFINES=$(C_DEFINES)  \
    /D_UNICODE \
    /DUNICODE \
    /DCONFIG_ENABLE_WCHAR \
    /DTEST_BUILD \

SOURCES= \
    ..\codectestutils.cpp \
