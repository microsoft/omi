#!/bin/sh
#
# Used by regress and 'make tests'.  Should be run at omi/Unix level.

basedir=`basename ${PWD}`
if [ "$basedir" != "Unix" ]; then
    echo "Must be run from omi/Unix directory."
    exit 1
fi

username=$OMI_USER
userpasswd=$OMI_PASSWORD

#
# Clean up previous (if any) running omiserver
#
pidFile=$OUTPUTDIR/var/run/omiserver.pid
echo "Examining pid file:  $pidFile..."
if [ -f $pidFile ]; then
    pid=`cat $pidFile`
    
    if [ "x${pid}" != "x" ]; then
        ps -p ${pid} | grep omiserver > /dev/null
        if [ $? -eq 0 ]; then
            sudo kill -15 $pid
        fi
    fi
fi

#
# if required env variables don't exist, then quit
#
if [ "x${username}" != "x" -a "x${userpasswd}" != "x" ]; then
    SUDO_PATH=`which sudo`
    export SUDO_PATH

## NTLM setup

    ntlm_file=./output/tmp/ntlm
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

#
# As of 12/2016, PowerShell supports following linux platforms only
# NTLM tests will run on these platforms only
#
# Ubuntu 14.04
# Ubuntu 16.04
# CentOS 7
# MacOS 10.11

supported=0

kernel=`uname -s`
if [ "$kernel" = "Darwin" ]; then
    echo "Running on a MAC 10.11"
    supported=1
elif [ "$kernel" = "Linux" ]; then
    if [ -f /etc/centos-release ]; then
        fgrep "release 7" /etc/centos-release > /dev/null
        if [ $? -eq 0 ]; then
            echo "Running on CentOS 7"
            supported=1
        fi
    elif [ -f /etc/lsb-release ]; then
        fgrep "DISTRIB_RELEASE=14.04" /etc/lsb-release > /dev/null
        if [ $? -eq 0 ]; then
            echo "Running on Ubuntu 14.04"
            supported=1
        else
            fgrep "DISTRIB_RELEASE=16.04" /etc/lsb-release > /dev/null
            if [ $? -eq 0 ]; then
                echo "Running on Ubuntu 16.04"
                supported=1
            fi
        fi
    else
        echo "Running on Linux"
        supported=1
    fi
fi

export NTLM_SUPPORTED_PLATFORM
NTLM_SUPPORTED_PLATFORM=$supported
