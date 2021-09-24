#!/bin/bash

if [ "$#" != 1 -a "$#" != 2 ]; then
    echo "Usage: $0 OMIZIPFILE [--dev]"
    exit 1
fi

if [ ! -f "$1" ]
then
    echo "$1 does not exists!"
    exit 1
fi

if [ "$#" = 2 ];
then
    if [ "$2" = "--dev" ]; then
        run_dev=1
    else
        echo "Usage: $0 OMIZIPFILE [--dev]"
        exit 1
    fi
fi

# Create directories for validation purpose
CURTIMESTAMPE=`date +'%s'`
ROOTDIR=/OMI
WORKDIR=$ROOTDIR/$CURTIMESTAMPE
UNZIPDIR=$WORKDIR/UNZIP
SRCDIR=$WORKDIR/SRC
TMPDIR=$WORKDIR/TMP

if [ ! -d "$SRCDIR" ]
then
    mkdir --parents $SRCDIR
fi

if [ ! -d "$TMPDIR" ]
then
    mkdir --parents $TMPDIR
fi

if [ ! -d "$UNZIPDIR" ]
then
    mkdir --parents $UNZIPDIR
fi

unzip $1 -d $UNZIPDIR >unzip.txt

if [ $? = 0 ]
then
    echo "$1 was unzipped to $UNZIPDIR."
else
    echo "$1 is not a valid zip file!"
    exit 1
fi
#############################################################
# Clean up source code under $UNZIPDIR and copy to $SRCDIR  #
#############################################################

cd $UNZIPDIR

# (1) Remove all sources/dirs files
find ./ -iname "sources" -type f > $TMPDIR/sourceslist
find ./ -iname "sources" -type f -print | xargs /bin/rm -f
find ./ -iname "dirs" -type f > $TMPDIR/dirslist
find ./ -iname "dirs" -type f -print | xargs /bin/rm -f

# (2) Remove all win directories
find ./ -not -iname "win" -type d > $TMPDIR/dirlist

echo '=================' > $TMPDIR/cplog
echo "$WORKDIR" >> $TMPDIR/cplog
echo '=================' >> $TMPDIR/cplog

DIRS=`cat $TMPDIR/dirlist`
for i in $DIRS
do
    echo "=start to copy $i=" >> $TMPDIR/cplog

    if [ ! -d "$SRCDIR/$i" ]
    then
        mkdir --parents $SRCDIR/$i >> $TMPDIR/cplog 2>&1
    fi
    cp $i/*.* $SRCDIR/$i >> $TMPDIR/cplog 2>&1
    cp $i/* $SRCDIR/$i >> $TMPDIR/cplog 2>&1

    echo "_" >> $TMPDIR/cplog
done

#rm -f $TMPDIR/dirlist

#############################################################
# Enable scripts                                            #
#############################################################

cd $SRCDIR
chmod 777 $SRCDIR/scripts/fixdist
$SRCDIR/scripts/fixdist
chmod 777 $SRCDIR/configure
chmod 777 $SRCDIR/configure-optimize 
chmod 777 $SRCDIR/configure-size 
chmod 777 $SRCDIR/configure-wchar 
chmod 777 $SRCDIR/configure-world 
chmod 777 $SRCDIR/buildtool 
chmod 777 $SRCDIR/regress

#############################################################
# Run regression tests                                      #
#############################################################
$SRCDIR/configure
if [ "$run_dev" = "1" ]; then
   $SRCDIR/regress --runs=char
else
   $SRCDIR/regress
fi
