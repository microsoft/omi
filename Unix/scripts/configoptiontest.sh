#!/bin/sh

##
## disable-indication
##
./configure --disable-indication --dev
make clean
make
make tests
if [ "$?" != "0" ]; then
    echo "-----------------disable-indication failed-----------------------"
    exit 1
fi

##
## disable-localsession
##
./configure --disable-localsession --dev
make clean
make
make tests
if [ "$?" != "0" ]; then
    echo "------------------disable-localsession failed--------------------"
    exit 1
fi

##
## enable-httpheaders
##
./configure --enable-httpheaders --dev
make clean
make
make tests
if [ "$?" != "0" ]; then
    echo "-------------------enable-httpheaders failed---------------------"
    exit 1
fi


##
## enable-preexec 
##
./configure --enable-preexec  --dev
make clean
make
make tests
if [ "$?" != "0" ]; then
    echo "--------------------enable-preexec failed------------------------"
    exit 1
fi

##
## enable-sections
##
./configure --enable-sections  --dev
make clean
make
make tests
if [ "$?" != "0" ]; then
    echo "--------------------enable-sections failed-----------------------"
    exit 1
fi


##
## singleimage
##
./configure --singleimage  --dev
make clean
make
make tests
if [ "$?" != "0" ]; then
    echo "--------------------singleimage failed---------------------------"
    exit 1
fi




##==============================================================================
##
## SUCCESS
##
##==============================================================================

echo ""
echo ""
echo "##===================##"
echo "##                   ##"
echo "## ALL TESTS PASSED! ##"
echo "##                   ##"
echo "##===================##"
echo ""
exit 0
