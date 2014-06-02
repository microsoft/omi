TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = multiplex

SOURCES = multiplex.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = sock base $(PALLIBS) ut

include $(TOP)/mak/rules.mak

CACHEGRIND_ARGS = $(TARGET) mserver

server:
	$(TARGET) server

client:
	$(TARGET) client

mserver:
	$(TARGET) mserver

mclient:
	$(TARGET) mclient
