#Enabling SPNEGO/NTLM Authentication on OMI

   - [Setting up the machine](#setting-up-the-machine)
       - [Setup after package install](#setup-after-package-install)
       - [Setting up credentials](#setting-up-credentials)
       - [Setting up Winbind](#setting-up-winbind)

- [Using SPNEGO/NTLM on the OMI client](#using-spengontlm-on-the-omi-client)
- [Enabling SPNEGO/NTLM on the OMI server](#enabling-spnegontlm-on-the-omi-server)


OMI requests between the client and server have been up to this point
authenticated via Basic auth. Basic is very simple, but not at all secure, 
inasmuch as the username and password are transmitted in the clear, with only 
Base64 encoding which is easly decoded by someone able to see the traffic on the 
connection. For that reason we only recommend Basic never be used on other than a 
secure (https) conneciton.

A more secure method of authentication uses Secure Protected Negotitation protocol (SPNEGO), which enables
negotiation of the security protcol from a selection of options, Currently the only option available with
omi is the *NT Lan Manager protocol, version 2 (NTLMV2)* which is an improvment over Basic auth in two ways. 

- The password is hashed using an irreversable algorithm, so the password is more secure than Basic.

- The client and server support encryption of your data over http connections, so SSL certificates are not required. 

In order to use SPNEGO with NTLM, you will need to set up both the client and the server 
to provide the credentials. 

Note, NTLM support on gss is not available on MacOS. Solaris, HP-UX, AIX or older Linux distros
can be modified to support it, but that configuration is not currently supported.  

In the instructions following, the architecture x86_64 is assumed for simplicity. If you are
using other architectures (for example,  Power8) please make the appropriate substitutions.

###Setting up the machine
OMI uses the MIT implementation of the Generic Security Services API (libgssapi_krb5.so). This is the 
version installed by default in virtually all systems using anything like a UNIX/Linux OS. The MIT GSS 
allows plugins to be installed to handle different authentication mechanisms. The NTLM protocol plugin is 
provided by the gss-ntlmssp package. 

Both the client and host machine must be set up to use provide NTLM to the generic security services (gss) library.
To do this, the gss and gss-ntlmssp packages must be installed and up to date.  The packages required are:

<table>
<tr><th>Linux Verison</th><th>Packages Needed</th></tr>
<tr><tr><td>RHEL 7.3, CentOS 7.3 </td> <td>krb5-workstation-1.14.1-27.el7.x86_64 or later</td></tr>
    <tr><td/><td>gssntlmssp-0.7.0-1.el7.x86_6</td></tr></tr>
<tr><tr><td>Ubuntu 16.04 (xenial) </td> <td>libgssapi-krb5-2 version  1.13.2+dfsg-5 or later</td></tr>
    <tr><td/><td>gss-ntlmssp version 0.7.0 or later. <br/>
        <i>Note: The gss-ntlmssp 0.7.0 package is currently available in Canonical's proposed ppa</i>.</td></tr></tr>
<tr><tr><td>Ubuntu 14.04(trusty)</td> <td>libgssapi-krb5-2 version 1.14.3 or later.</td></tr>
    <tr><td/><td>gss-ntlmssp 0.7.0 <br/><i>built from sources from  https://fedorahosted.org/gss-ntlmssp as gss-ntlmssp is not provided by Canonical on trusty.</i></td></tr></tr>
</table>
	       

###Setup after package install

Verify that the required packages are installed using rpm or dpkg.
Once that is taken care of there are some post install steps to ensure the gss-ntlmssp plugin is properly.

####Ubuntu 16.04 (xenial)
In order to be known to gssapi, gssntlmssp.so needs to be configured. On xenial, that requires that the file 
/etc/gss/mech.ntlmssp be renamed to mech.ntlmssp.conf.  The file itself must contain the line: 

    gssntlmssp_v1       1.3.6.1.4.1.311.2.2.10          /usr/lib/x86_64-Linux-gnu/gssntlmssp/gssntlmssp.so

where the file location for the plugin shared object, gssntlmssp.so, correctly points to be shared object file. We strongly advise
checking the location and ensuring it is correct. If not, edit the file with the correct location.

####Ubuntu 14.04 (trusty)
In ubuntu 14.04 you will have to create the mechanism file. On trusty the file is /usr/etc/gss/mech and contains
entries for all of the mech plugins. To build the source, configure the source via 

```sh
    ./configure --prefix=/usr
```
then build via

```sh
make 
```
and install via

```sh
    sudo make install        
```

The file /usr/etc/gss/mech should have the line:

```
   ntlmssp_v1       1.3.6.1.4.1.311.2.2.10          /usr/local/lib/gssntlmssp/gssntlmssp.so
```

####RHEL 7.3, Centos 7.3

In Centos7.3, the mechanism configuration and shared object are properly placed and ready to use. Once the gssntlmssp package is installed, no further
action is necessary except the provision of credentials.

### Setting up credentials


#### The NTLM_USER_FILE

The NTLM user file is the simplest, but least secure method of getting credentials to the omi client. 
Clearly you want the file to be only readable by the file owner, and owned by either the user to be executing omicli or omiserver.     

The format of the file is as many instances as desired of

```
	domain:username:password
```

where domain is the the name of the machine or active domain. Note that the namesi
are taken literally, so bob@10.1.10.93 is not the same as bob@myhost. If you want to use multiple names for 
a given host credential, you must have multiple entries in the credential file, so:

```
    10.1.10.93:myself:MyPassword!
    myhost:myself:MyPassword!
```

Of course for a server, you must have entries for everyone who will be talking to the omiserver. 

The entries for the username and password on the client and server side must agree with each other, 
and must agree with the password entries on both sides of the omi transaction. 

While the advantage of the omi file is its simplicity, the disadvantage is the presence of a plain text password 
in the file. A more secure approach would be to use winbind to distribute credentials. 

###Setting up Winbind

If you find the NTLM_USER_FILE option insufficiently secure, winbind can be used to provide credentials
to ntlmssp even when the machine is being used standalone.  In that case, samba is set up to consider the
machine to be a domain with a single member.  We should note, though 
that winbind and samba interact. If you are using samba to mount cifs file shares, it may be necessary to 
modify these instructions. 


Winbind is a part of the samba suite. There are a number of good explanations and tutorials avaiable such as
https://www.samba.org/samba/docs/man/Samba-HOWTO-Collection/idmapper.html discussing winbinds role, but in 
short it provides credential caching from the machines password provider, and idmapping from the Windows SID
to and from the UNIX UID. 

To use winbind for credentials, 
- install needed packages
- modify the file /etc/nsswitch.conf to use winbind as a password source, 
- setup /etc/samba/smb.conf to perform the needed credentials and id mapping.

The credentials are cached from an sssd identity provider, which may be ldap or an active directory provider. 

The simplest way of establishing a credential source through winbind is to attach to an active directory domain controller.

##Using SPNEGO/NTLM on the OMI client

If the system does not have a winbind service set up to provide credentials, the omicli will expect credentials to be provided
in the file ~/.omi/ntlmcred. For security, the omi client expects the .omi directory must be owned by the user with permissions 700.
The file ntlmcred must be owned by the user with permissions 600.

You should have credentials provided for every combination of host and user you intend on using. The hostname and ip address
are not resolved in the credentials, so 10.1.10.17 and "bobs-host" are different credentials and must be separately specified.

We recommend that you provide the user name and password on the command line as well as the credentials file. The credentials
file will be consulted first, with winbind used to acquire the credential after the file if it is available. 

So, in ~/.omi/ntlmcred :

```
my_host:myself:my-passwd!

```
On the command line:

```sh
    omicli -host my_host -u myself@zmyhost  -p my-passwd! gi requestor/cool/provider { cool-thing key 1 }
```

##Enabling SPNEGO/NTLM on the OMI server


The most secure method for providing omiserver credentials is via winbind. There may be reasons why this would not be 
practical for a particular implementation, in which case it is possible to define a credential file, using the same format as
described for the client.  If this method is used, the location of the file is specified in the omiserver.conf file.

Note:*Credential file specification via the iomiserver file is not yet implemented*
