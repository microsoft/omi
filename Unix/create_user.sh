#!/bin/sh
#
# Script to create user account and password for use by OMI
# This file should be executed via ".", as it sets environment variables

username=$OMI_USER

if [ "x$username" = "x" ]; then
    echo "Creating new user..."
    username=omi_$USER
fi

egrep "^$username" /etc/passwd >/dev/null
if [ $? -eq 0 ]; then
    echo "User $username exists!"
else
    useradd=`which useradd`
    if [ "x$useradd" = "x" ]; then
        echo "Failed to find 'useradd'"
        exit 1
    fi

    sudo $useradd -m $username
    [ $? -eq 0 ] && echo "User $username has been added to system!" || echo "Failed to add a user!"
fi

userpasswd=`cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 28 | head -n 1`
if [ "x$userpasswd" = "x" ]; then
    echo "Failed to generate password"
    exit 1
fi

echo $username:$userpasswd | sudo chpasswd
[ $? -eq 0 ] && echo "User password has been changed!" || echo "Failed to change password!"

export OMI_USER=$username
export OMI_PASSWORD=$userpasswd
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
