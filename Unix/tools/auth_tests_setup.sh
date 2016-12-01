#!/bin/sh
#

username=$OMI_USER
userpasswd=$OMI_PASSWORD

if [ "x$username" != "x" -a "x$userpasswd" != "x" ]; then
    export SUDO_PATH=`which sudo`

##==============================================================================
## NTLM setup
##==============================================================================

    ntlm_file=$HOME/.ntlm
    hostname=`uname -n`
    if [ -f $ntlm_file ]; then
        rm -f $ntlm_file
    fi

    echo $hostname":"$username":"$userpasswd > $ntlm_file
    export NTLM_USER_FILE=$ntlm_file
    export NTLM_DOMAIN=$hostname
fi
