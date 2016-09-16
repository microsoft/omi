include /opt/omi/share/omi.mak

DEFINES = MI_API_VERSION=2
PROVIDER = frog
SOURCES = $(wildcard *.c)
CLASSES = XYZ_Frog 

$(LIBRARY): $(OBJECTS)
	$(CC) $(CSHLIBFLAGS) $(OBJECTS) -o $(LIBRARY)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

reg:
	$(BINDIR)/omireg $(CURDIR)/$(LIBRARY)

gen:
	$(BINDIR)/omigen -m frog schema.mof XYZ_Frog

clean:
	rm -f $(LIBRARY) $(OBJECTS) $(PROVIDER).reg


