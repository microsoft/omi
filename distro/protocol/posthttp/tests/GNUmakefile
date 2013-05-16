TOP = ../../..
include $(TOP)/config.mak

#include $(TOP)/mak/rules.mak

POSTHTTP=$(BINDIR)/posthttp

define NL


endef

all:

##==============================================================================
##
## testwsman 
##
##     Rule to run one WS-Management test. It performs the following steps:
##
##         (1) Sends the request given by $(1).request.xml to server.
##         (2) Gets response back.
##         (3) Applies edits given by SED file: $(1).sed
##         (4) Diffs edited file with expected file: $(1).response.xml
##
##     This function is called like this:
##
##         $(call testwsman,TESTNAME)
##
##     Where TESTNAME is the name of some test. Three files must exist:
##
##         TESTNAME.request.xml (contains request)
##         TESTNAME.sed (contains SED edits to be applied to response)
##         TESTNAME.response.xml (contains expected response)
##
##==============================================================================

testwsman = \
	@ echo "Testing $(1)..." $(NL) \
	@ $(POSTHTTP) $(1).request.xml > $(TMPDIR)/$(1).tmp $(NL) \
	@ sed -f $(1).sed $(TMPDIR)/$(1).tmp > $(TMPDIR)/$(1).xml $(NL) \
	@ diff $(TMPDIR)/$(1).xml $(1).response.xml

##==============================================================================
##
## tests:
##
##==============================================================================

tests:
	@ $(BINDIR)/omiserver -d -i --livetime 10
	@ sleep 1
	@ echo "==== $(POSTHTTP) tests:"
	$(call testwsman,test2)
	$(call testwsman,test3)
	@ echo
	@ $(BINDIR)/omiserver -s > /dev/null

clean:

depend:

stage:
	@ $(BINDIR)/omiserver -d -i --livetime 10
	@ sleep 1
	$(POSTHTTP) test3.request.xml

print:
	$(BINDIR)/printxml print.xml
