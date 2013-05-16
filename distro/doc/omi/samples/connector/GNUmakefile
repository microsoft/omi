include ../../../../output/$(shell hostname)/omi.mak

PROVIDER = xyzconnector
SOURCES = $(wildcard *.c *.cpp)
CLASSES = XYZ_Gadget=GadgetXYZ_Widget=WidgetXYZ_Connector=Connector 

$(LIBRARY): $(OBJECTS)
	$(CXX) $(CXXSHLIBFLAGS) $(OBJECTS) -o $(LIBRARY) $(CXXLIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< $(CLIBS) -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

reg:
	$(BINDIR)/omireg $(CURDIR)/$(LIBRARY)

gen:
	$(BINDIR)/omigen -m xyzconnector --cpp schema.mof XYZ_Gadget=Gadget XYZ_Widget=Widget XYZ_Connector=Connector

clean:
	rm -f $(LIBRARY) $(OBJECTS) $(PROVIDER).reg


