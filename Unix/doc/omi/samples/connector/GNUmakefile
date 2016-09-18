include /opt/omi/share/omi.mak

DEFINES = MI_API_VERSION=2
PROVIDER = xyzconnector
SOURCES = $(wildcard *.c)
CLASSES = XYZ_Gadget=GadgetXYZ_Widget=WidgetXYZ_Connector=Connector 

$(LIBRARY): $(OBJECTS)
	$(CC) $(CSHLIBFLAGS) $(OBJECTS) -o $(LIBRARY)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

reg:
	$(BINDIR)/omireg $(CURDIR)/$(LIBRARY)

gen:
	$(BINDIR)/omigen -m xyzconnector schema.mof XYZ_Gadget=Gadget XYZ_Widget=Widget XYZ_Connector=Connector

clean:
	rm -f $(LIBRARY) $(OBJECTS) $(PROVIDER).reg


