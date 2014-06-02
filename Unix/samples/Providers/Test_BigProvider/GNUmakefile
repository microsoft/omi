TOP = ../../..
include $(TOP)/config.mak

CSHLIBRARY = Test_BigProvider
SOURCES = $(wildcard *.c)

INCLUDES = $(TOP) $(TOP)/common 

include $(TOP)/mak/rules.mak

$(LIBRARY): $(OBJECTS)
	$(CC) $(CSHLIBFLAGS) $(OBJECTS) -o $(LIBRARY)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

reg:
	$(BINDIR)/omireg $(CURDIR)/$(LIBRARY)

