TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_base

SOURCES = test_base.cpp schema.c test_credcache.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES = DETECT_FORBIDDEN_FUNCTIONS

LIBRARIES = micxx base ut io

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)

OPTS= --cpp -D -M -V -S -n -s test_repos_classDecl

CLASSES = MSFT_Person MSFT_AllTypes MSFT_Process Inner Outer

gen:
	$(BINDIR)/omigen $(OPTS) schema.mof $(CLASSES)

vg:
	valgrind --tool=memcheck $(TARGET)

dt:
	$(TARGET) TestWSManDatetime
