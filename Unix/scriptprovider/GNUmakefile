# define some aliases
MKDIR:=mkdir -p -m 777
RM:=rm -f
SED:=sed
COPY:=cp
MKDEP:=-MD


LOCAL_DIR:=$(shell pwd)
TOP?=$(shell cd ..; pwd)


include $(TOP)/output/omi.mak


BIN_PATH:=$(LOCAL_DIR)/bin


PROVIDER=ScriptProvider
LIBRARY=lib$(PROVIDER).so


$(BIN_PATH)/$(LIBRARY) :


INCLUDE_PATH+=$(INCLUDEDIR)


CPPFLAGS+=$(addprefix -I,$(INCLUDE_PATH))

SOURCES:=client.cpp
SOURCES+=debug_tags.cpp
SOURCES+=mi_context.cpp
SOURCES+=mi_function_table.cpp
SOURCES+=mi_instance.cpp
SOURCES+=mi_main.cpp
SOURCES+=mi_memory_helper.cpp
SOURCES+=mi_module.cpp
SOURCES+=mi_schema.cpp
SOURCES+=mi_script_extensions.cpp
SOURCES+=mi_value.cpp
SOURCES+=server.cpp
SOURCES+=server_protocol.cpp
SOURCES+=shared_protocol.cpp
SOURCES+=socket_wrapper.cpp


OBJECTS:=$(SOURCES:.cpp=.o)


# add bin path dependencies to the object files
$(addprefix $(BIN_PATH)/,$(OBJECTS)) : | $(BIN_PATH)


CPPFLAGS+=$(INCLUDES)

PRINT_BOOKENDS?=0
CPPFLAGS+=-DPRINT_BOOKENDS=$(PRINT_BOOKENDS)


# compile rule
$(BIN_PATH)/%.o : %.cpp
	@echo ...compiling: $(@F)
	$(COMPILE.cpp) $(MKDEP) $< -o $@
	@-$(COPY) $(BIN_PATH)/$*.d $(BIN_PATH)/$*.P;
	@$(SED) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' \
	    -e 's/$$/ :/' < $(BIN_PATH)/$*.d >> $(BIN_PATH)/$*.P
	@$(RM) $(BIN_PATH)/$*.d



# link rule
$(BIN_PATH)/$(LIBRARY) : \
	$(addprefix $(BIN_PATH)/,$(OBJECTS))
	@echo ...linking: $(LIBRARY)
	$(CXX) -shared -o $@ $^


# a rule to make root bin directory
$(BIN_PATH) :
	$(MKDIR) $(BIN_PATH)


# rules for output when running the clean target
.phony : clean-text
clean-text :
	@echo ...deleting: library, object, and dependency files!


# rules doing the cleanup in the root bin directory
.phony : clean-action
clean-action :
	@$(RM) $(BIN_PATH)/lib$(PROVIDER).so \
	$(addprefix $(BIN_PATH)/,$(OBJECTS)) \
	$(addprefix $(BIN_PATH)/,$(OBJECTS:.o=.P))


# master clean target
clean : clean-text clean-action


# include shared dependency files
-include $(BIN_PATH)/*.P
