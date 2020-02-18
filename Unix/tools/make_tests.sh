#!/bin/bash
#
# shell script used by "make tests" target
#
# Three position parameters are required.  Format of command is:
#      make_tests.sh $(LIBDIR) $(BINDIR) $(TMPDIR)

libdir=$1
bindir=$2
tmpdir=$3

dir=`pwd`
cd "${libdir}"
cd ..
outputdir=`pwd`
cd $dir

echo "make tests, outputdir = " $outputdir

. ./tools/auth_tests_setup.sh $outputdir

LD_LIBRARY_PATH=$libdir
export LD_LIBRARY_PATH
DYLD_FALLBACK_LIBRARY_PATH=$libdir
export DYLD_FALLBACK_LIBRARY_PATH
DYLD_LIBRARY_PATH=$libdir
export DYLD_LIBRARY_PATH

#
# We could use id -u and id -g except solaris 10 and hpux dont support it, so we use perl instead
#
set -x 
tmpfile=$tmpdir/file$$
echo ' ($name, $passwd, $uid, $gid, $quota, $comment, $gcos, $dir, $shell ) = getpwuid($<); printf "%d %d %d %d\n", @ARGV[0], @ARGV[1], $uid, $gid '  >$tmpfile
echo -e '#!/bin/sh\n' "perl -l $tmpfile " '$1 $2' " > $tmpdir/cli_preexec.txt"  >$bindir/cli_preexec.sh
chmod +x $bindir/cli_preexec.sh

set +x

$bindir/nits -file:$tmpdir/nitsargs.txt
e=$?

./tools/auth_tests_cleanup.sh

exit $e
