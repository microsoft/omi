TOP = ..\..

TARGETNAME=omiutils
TARGETTYPE=LIBRARY

INCLUDES= $(INCLUDES); \
    $(TOP); \
    $(TOP)\nits\base; \
    $(TOP)\pal; \
    $(TOP)\monitoring\etw; \
    $(TOP)\monitoring\perf; \


SOURCES= \
    ..\omiutils.c \
    ..\errorswrap.c \
