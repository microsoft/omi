#!/bin/bash

##==============================================================================
##
## Check arguments
##
##==============================================================================

if [ "$#" = "0" ]; then
    echo "Usage: $0 (lib|cshlib|cxxshlib|cprog|cxxprog) [OPTIONS]"
    echo "Try --help for help."
    exit 1
fi

case $1 in
    -*)
        ;;
    *)
        TYPE=$1
        shift 1
esac

##==============================================================================
##
## Get command line arguments.
##
##==============================================================================

for opt
do

  arg=`expr "x$opt" : 'x[^=]*=\(.*\)'`

  case $opt in

    -h | --help)
      HELP=1
      ;;

    --top=*)
      TOP=$arg 
      ;;

    --project=*)
      PROJECT=$arg 
      ;;

    --sources=*)
      SOURCES=$arg 
      ;;

    --defines=*)
      DEFINES=$arg 
      ;;

    --includes=*)
      INCLUDES=$arg 
      ;;

    --libraries=*)
      LIBRARIES=$arg 
      ;;

    *)
      echo "$0: unknown option:  $opt"
      exit 1
      ;;

  esac
done

##==============================================================================
##
## Print the help message
##
##==============================================================================

if [ "$HELP" = "1" ]; then

cat<<EOF

Usage: $0 (lib|cshlib|cxxshlib|cprog|cxxprog) [OPTIONS]

OVERVIEW:
    This script generates a makefile (called 'GNUmakefile').

OPTIONS:
    -h, --help  Print this help message.
    --top       Relative directory that contains 'configure' script.
    --project   Name of project (defaults to current directory name).
    --sources   List of source files (defaults to *.c and *.cpp).
    --headers   List of headers files (defaults to *.h).
    --defines   List macros definitions.
    --includes  List of include paths (relative to current directory).
    --libraries List of dependent library names.

EOF

exit 0

fi

##==============================================================================
##
## $TYPE
##
##==============================================================================

case $TYPE in
    lib)
      TYPE=LIBRARY
      ;;
    cshlib)
      TYPE=CSHLIBRARY
      ;;
    cxxshlib)
      TYPE=CXXSHLIBRARY
      ;;
    cprog)
      TYPE=CPROGRAM
      ;;
    cxxprog)
      TYPE=CXXPROGRAM
      ;;
    *)
      echo "$0: unknown or missing type argument: '$TYPE'"
      echo ""
      exit 1
      ;;
esac

##==============================================================================
##
## $TOP
##
##==============================================================================

if [ "$TOP" == "" ]; then
    if [ -f "../configure" ]; then
        TOP=..
    fi
    if [ -f "../../configure" ]; then
        TOP=../..
    fi
    if [ -f "../../../configure" ]; then
        TOP=../../..
    fi
    if [ -f "../../../../configure" ]; then
        TOP=../../../..
    fi
    if [ -f "../../../../../configure" ]; then
        TOP=../../../../..
    fi
    if [ -f "../../../../../../configure" ]; then
        TOP=../../../../../..
    fi
    if [ -f "../../../../../../../configure" ]; then
        TOP=../../../../../../..
    fi

    if [ "$TOP" == "" ]; then
        echo "$0: unable to find top (please use --top option)"
        exit 1
    fi
fi

##==============================================================================
##
## $PROJECT
##
##==============================================================================

if [ "$PROJECT" = "" ]; then
    TMP=`pwd`
    PROJECT=`basename $TMP`
fi

##==============================================================================
##
## $SOURCES
##
##==============================================================================

if [ "$SOURCES" = "" ]; then
    SOURCES="`ls *.c 2> /dev/null``ls *.cpp 2> /dev/null`"
fi

##==============================================================================
##
## Write 'GNUmakefile'
##
##==============================================================================

cat > GNUmakefile <<END
TOP = $TOP
include \$(TOP)/config.mak

$TYPE = $PROJECT

SOURCES = $SOURCES

DEFINES = $DEFINES

INCLUDES = \$(TOP) \$(TOP)/common $INCLUDES

LIBRARIES = $LIBRARIES

include \$(TOP)/mak/rules.mak
END

echo "Created GNUmakefile"
