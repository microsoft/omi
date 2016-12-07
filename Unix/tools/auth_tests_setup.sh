#!/bin/sh
#
# Used by regress and 'make tests'.  Should be run at omi/Unix level.

username=$OMI_USER
userpasswd=$OMI_PASSWORD

#
# Clean up previous (if any) running omiserver
#
pidFile=./output/var/run/omiserver.pid
if [ -f $pidFile ]; then
    pid=`cat $pidFile`

    if [ "x${pid}" != "x" ]; then
        sudo kill -15 $pid
    fi
fi

#
# if required env variables don't exist, then quit
#
if [ "x${username}" != "x" -a "x${userpasswd}" != "x" ]; then
    SUDO_PATH=`which sudo`
    export SUDO_PATH

## NTLM setup

    ntlm_file=$HOME/.ntlm
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
