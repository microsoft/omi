#!/bin/sh
#
# shell script used by "make tests" target
#
# Three position parameters are required.  Format of command is:
#      make_tests.sh $(LIBDIR) $(BINDIR) $(TMPDIR)

. ./tools/auth_tests_setup.sh

LD_LIBRARY_PATH=$1
export LD_LIBRARY_PATH
DYLD_FALLBACK_LIBRARY_PATH=$1
export DYLD_FALLBACK_LIBRARY_PATH
DYLD_LIBRARY_PATH=$1
export DYLD_LIBRARY_PATH

$2/nits -file:$3/nitsargs.txt
e=$?

./tools/auth_tests_cleanup.sh

exit $e
