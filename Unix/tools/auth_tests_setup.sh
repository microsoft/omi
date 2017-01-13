#!/bin/sh
#
# Used by regress and 'make tests'.  Should be run at omi/Unix level.

basedir=`basename ${PWD}`
if [ "$basedir" != "Unix" ]; then
    echo "Must be run from omi/Unix directory."
    exit 1
fi

if [ "x$OUTPUTDIR" = "x" ]; then
    echo "Must be run from make or regress."
    exit 1
fi

username=$OMI_USER
userpasswd=$OMI_PASSWORD

#
# Clean up previous (if any) running omiserver
#
for d in output*
do
    pidFile=$d/var/run/omiserver.pid
    echo "Examining pid file:  $pidFile..."
    if [ -f $pidFile ]; then
        pid=`cat $pidFile`
    
        if [ "x${pid}" != "x" ]; then
            ps -p ${pid} | grep omiserver > /dev/null
            if [ $? -eq 0 ]; then
                sudo kill -15 $pid
            fi
        fi
        sudo rm -f $pidFile
    fi
done

#
# if required env variables don't exist, then quit
#
if [ "x${username}" != "x" -a "x${userpasswd}" != "x" ]; then
    SUDO_PATH=`which sudo`
    export SUDO_PATH

## NTLM setup

    ntlm_file=$OUTPUTDIR/tmp/ntlm
    hostname=`uname -n`
    if [ -f $ntlm_file ]; then
        rm -f $ntlm_file
    fi

    echo $hostname":"$username":"$userpasswd > $ntlm_file
    NTLM_USER_FILE=$ntlm_file
    export NTLM_USER_FILE
    NTLM_DOMAIN=$hostname
    export NTLM_DOMAIN
fi

supported=`$basedir/buildtool ntlm`
NTLM_SUPPORTED_PLATFORM=$supported
export NTLM_SUPPORTED_PLATFORM
