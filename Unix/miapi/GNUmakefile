TOP = ..
include $(TOP)/config.mak

LIBRARY = miapi

SOURCES = \
	Application.c \
	Session.c \
	Operation.c \
	HostedProvider.c \
	SafeHandle.c \
	ProtocolHandlerCache.c \
	InteractionProtocolHandler.c \
	Options.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS HOOK_BUILD

include $(TOP)/mak/rules.mak
