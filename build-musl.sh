#!/bin/sh

##==============================================================================
##
## build musl
##     Try build musl libmi.so on Ubuntu 16.04 x64
##
##==============================================================================


sudo apt install musl-tools -y
sudo cp -R /usr/include/security /usr/include/x86_64-linux-musl
sudo cp -R /usr/include/openssl /usr/include/x86_64-linux-musl
sudo cp -R /usr/include/x86_64-linux-gnu/openssl/ /usr/include/x86_64-linux-musl/
sudo cp -R /usr/include/mit-krb5/gssapi /usr/include/x86_64-linux-musl/
sudo cp -R /usr/include/mit-krb5/krb5 /usr/include/x86_64-linux-musl/
sudo cp /usr/include/mit-krb5/krb5.h /usr/include/x86_64-linux-musl/
sudo cp -R /usr/include/et /usr/include/x86_64-linux-musl/
cd Unix
./configure --with-cc=/usr/bin/musl-gcc
make -j
