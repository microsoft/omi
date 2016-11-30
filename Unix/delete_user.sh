#!/bin/sh

username=$OMI_USER

if [ "x$username" = "x" ]; then
    username=omi_$USER
fi

egrep "^$username" /etc/passwd >/dev/null
if [ $? -eq 0 ]; then
    userdel=`which userdel`
    if [ "x$userdel" = "x" ]; then
        echo "Failed to find 'userdel'"
        exit 1
    fi
    sudo $userdel --force $username
    echo "Deleted user $username"

fi

ntlm_file=$HOME/.ntlm

if [ -f $ntlm_file ]; then
    rm -f $ntlm_file
fi
