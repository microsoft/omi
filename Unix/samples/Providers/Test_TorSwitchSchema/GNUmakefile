TOP = ../../..
include $(TOP)/config.mak

CSHLIBRARY = Test_TorSwitchSchema
SOURCES = $(wildcard *.c)

INCLUDES = $(TOP) $(TOP)/common 

include $(TOP)/mak/rules.mak

$(LIBRARY): $(OBJECTS)
	$(CC) $(CSHLIBFLAGS) $(OBJECTS) -o $(LIBRARY)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

reg:
	$(BINDIR)/omireg $(CURDIR)/$(LIBRARY)

regtest:
	$(BINDIR)/omireg -n root/cimomtestprov $(TARGET)
	$(BINDIR)/omireg -n root/cimomtestprov_oop -o @requestor@ $(TARGET)

