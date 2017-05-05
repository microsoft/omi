# define some aliases
MKDIR:=mkdir -p -m 777
RM:=rm -f
SED:=sed
COPY:=cp
MKDEP:=-MD


LOCAL_DIR:=$(shell pwd)
TOP?=$(shell cd ../..; pwd)
SCRIPTPROVIDER_DIR:=$(shell cd ..; pwd)
SCRIPTPROVIDER_BIN:=$(SCRIPTPROVIDER_DIR)/bin


include $(TOP)/output/omi.mak


BIN_PATH:=$(LOCAL_DIR)/bin


EXECUTABLE:=Test


$(BIN_PATH)/$(EXECUTABLE) :


INCLUDE_PATH+=$(INCLUDEDIR)
INCLUDE_PATH+=$(SCRIPTPROVIDER_DIR)


INCLUDES+=$(addprefix -I,$(INCLUDE_PATH))


SOURCES:=main.cpp
SOURCES+=test_helper.cpp
SOURCES+=traits_test.cpp
SOURCES+=repeat_test.cpp
SOURCES+=default_delete_test.cpp
SOURCES+=internal_counted_ptr_test.cpp
SOURCES+=unique_ptr_test.cpp
SOURCES+=mi_type_test.cpp
SOURCES+=mi_script_extensions_test.cpp
SOURCES+=mi_memory_helper_test.cpp
SOURCES+=socket_wrapper_test.cpp
SOURCES+=shared_protocol_test.cpp


OBJECTS:=$(SOURCES:.cpp=.o)


# add bin path dependencies to the object files
$(addprefix $(BIN_PATH)/,$(OBJECTS)) : | $(BIN_PATH)


LDFLAGS+=-L/home/ermumau/omi-git/Unix/scriptprovider/bin -dynamic
LIBS+= -lScriptProvider


CPPFLAGS+=$(INCLUDES)


# compile rule
$(BIN_PATH)/%.o : %.cpp
	@echo ...compiling: $(@F)
	$(COMPILE.cpp) $(MKDEP) $< -o $@
	@-$(COPY) $(BIN_PATH)/$*.d $(BIN_PATH)/$*.P;
	@$(SED) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' \
	    -e 's/$$/ :/' < $(BIN_PATH)/$*.d >> $(BIN_PATH)/$*.P
	@$(RM) $(BIN_PATH)/$*.d


# link rule
$(BIN_PATH)/$(EXECUTABLE) : \
	$(addprefix $(BIN_PATH)/,$(OBJECTS))
	@echo ...linking: $(EXECUTABLE)
	$(LINK.cpp) -o $@ $^ $(LIBS)


# a rule to make root bin directory
$(BIN_PATH) :
	$(MKDIR) $(BIN_PATH)


# rules for output when running the clean target
.phony : clean-text
clean-text :
	@echo ...deleting: executable, object, and dependency files!


# rules doing the cleanup in the root bin directory
.phony : clean-action
clean-action :
	@$(RM) $(BIN_PATH)/$(EXECUTABLE) \
	$(addprefix $(BIN_PATH)/,$(OBJECTS)) \
	$(addprefix $(BIN_PATH)/,$(OBJECTS:.o=.P))


# master clean target
clean : clean-text clean-action


# include shared dependency files
-include $(BIN_PATH)/*.P
