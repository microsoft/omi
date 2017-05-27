# Enabling Kerberos Authentication on OMI

## Setting Up The Domain Controller

This doocument is a series of notes passing on the experience we have had within our group in setting up and using kerberos authentication on the omi client and server. 

We will assume you have setup an active directory domain controller using windows server.  The domain controller
we have been using runs on Windows Server 2012 R2, but Windows Server 2016 should be quite similar.

First, to explain some terms:

   - Domain Name Services is a server protocol which resolves host names. The namespace the server provides names for is 
     called the DNS *domain*. By convention, the DNS domain is all lower case. ( For example, contoso.com).

   - Kerberos is an authentication protocol which uses a trusted credential repository referred to as an authentication server
     or more usually, Key Distribution Center (KDC). The set of machines served by the KDC is a kerberos *realm*. By 
     convention kerberos realms are mixed case with the first part all upper ( For example, CONTOSO.com ).

     Users, hosts, and services identities are all *principals* in kerberos. Each has a credential in either a file with 
     table of keys, or a credential cache. There are several credential cache methods, depending on the configuration and 
     environment variables. Users are in the form myuser@CONTOSO.com.  Hosts are referred to by their fully qualified 
     domain name, so myhost.contoso.com@CONTOSO.com.  Service Prinicpals, also referred to as Service Principal Names or 
     SPNs (pronounced "spin") are in the form service name/host, or http/myhost.contoso.com@CONTOSO.com. 

     Usually a given user will be only be directly aware of their own user. Host and service principals are usually setup 
     as part of the joining process. Some service principals, such as HTTP/myhost.contolso.com@CONTOSO.com will need to be 
     added after the joining process.

     There are basically two implementations of kerberos, which are used by pretty much everybody.  The MIT implementation
     is installed by default in Linux distros. The Heimdal implementation is used in MacOS and Samba servers. These
     implementations interoperate, but there are sometimes detail differences that need to be considered.

   - Active Directory uses Kerberos and the Lightweight Directory Access Protocol (LDAP) protocols to authenticate 
     and authorise machines in an active directory *domain*. Though the three functions can be distributed to other servers, 
     normally a central server, the Active Directory Controller (ADC), provides DNS, LDAP and Kerberos services for all 
     the machines joined to the domain.  User, group and host information is provided by querying the ldap database 
     across the entire domain. Member user login and privelege information can be set up on the domain controller, 
     which is a single location for all the information. 

     An active domain *domain* is by convention all upper case ( for example, CONTOSO.COM ). 

So a given domain joined host will receive name services from myserver.contoso.com, kerberos authentication services from
myserver.contoso.com@SCX.com and user and group information from ldap/myserver.contoso.com@CONTOSO.COM, and you can 
login with ssh -K to host/myserver.contols.com@CONTOSO.com.

On the active domain controller, You will need to verify:

  - Computer Account
  - User Account
  - Service Principals for all expected services must be added to the computer account. 

  - Presence of _kerberos.mydomain.com TXT record containing the name of the kerberos realm ("CONTOSO.com"). This 
    is used by kerberos to correcly generate the names of well known service principals, and is used heavily by both
    MIT and heimdal kerberos implementations. This appears not to be set by default so must be set manually. *Note, not
    setting this will result in some very mysterious problems*. 

  - Reverse DNS records for registered hosts is a common problem, as those are often managed by enterprise IT 
    or IP organizations. It is used heavily by default, but flags and configuration options are available to compensate
    if there are problems with it. You can identify reverse dns issues by using dig to
    check. 

  - Authoratative user account with permission to join machines to domain

### Identity Mapping

Linux, MacOS and Unix identify users via an integer user ID (uid). That user is then given privileges according to is membership 
in various groups, which are identified by an integer group id.  The utility id will show both of these for a given user. 

In Windows the user id is in the form of an SID, which is much longer, variable in length, and heirarchical. Groups also have SIDs.
The user information provided by the Active Directory Controller is in the form of SIDs and must be mapped to the simpler 
Linux/MacOS/Unix format. This is done in a very simple form by winbind or sssd on the client, but there are additional packages
such as FreeIPA that perform this operation with considerably more sophistication.

We have not found it necessary to use these.

## Setting up the client machine

Different Distros and Unix implementations have different tools to accomplish it, but to connect to AD, one must: 

    - Set up automatic time sync with ADC/KDC. This is ussaly via the network time protocol, ntp.
    - DNS set up so it sees the AD server and is part of the servers DNS domain.
    - Hostname shorted to 15 characters or less, if needed. Fully qualified hostname by default.
    - Kerberos and LDAP setup (sssd/realm or winbind and net ads)
    - nsswitch.conf set to use ldap and sss or winbind
    - PAM modules added to allow kerberos authentication.

Winbind, which directly uses the samba service, was universally used as an active domain agent on linux until the
most recent version of Centos/RH, SLES and Ubuntu.  It is being supplanted by the redhats
System Security Services Daemon (sssd) which is more secure and handles identity mapping better.


### Redhat/Centos Linux 7 (all versions)

####  Required Packages:

#### Setup after package install

    - hostname 15 char or less and fully qualified
    - Authconfig
    - realm join

##### Hostname needs to be less than 16 characters and fully qualified
##### nsswitch.conf, smb.conf, sssd.conf  are set up by authconfig
       
    - Setting up credentials
    - Setting up sssd

### Ubuntu Linux 16.04 LTS and 14.04 LTS




## Using Kerberos on the OMI client

Setting up credentials


### Setting up Winbind

##Using Kerberos on the OMI client

Troubleshooting Authentication

###The Process:

Cause 1: Wrong domain/user/password on command line
Cause 2: Expired Credntials
Cause 2: Time out of sync with host
Cause 3: SSSD/ Winbind setup

#### Troubleshooting steps:


## Kerberos

Kerberos gives protection for Authentication and Message Wrapping.  Authorisation is usually handled by the Lightweight
Directory Access Protocol (LDAP) which in turn uses Kerberos for authentication.

Authentication is a way of making an external agent prove it is who it says it is. The simplest form of authentication
is sending a user name and password over the network. If you send the password unencrypted, anyone listening can capture
the password and use it. This is called a replay attack.  In order to fight replay attacks,  more robust protocols
use a one way hash that uses an external mutually known secret, for example a sequence number. NTLM is such a system.

In this case, while security is better, it is still vulnerable to various other attacks, like "pass the hash".
One vulnerabilty is that if you can listen to the entire conversation, you can probably reverse the hash since you 
will know the sequence number in the captured packets. 

The most secure method is to have a shared secret, but never send it anywhere. In order to do this, you need a third actor,
the Authentication Server, or Key Distribution Center, who has a shared secrets with both of you. When you want to authenticate,
you request and receive a ticket from the Authentication Server with your mutual shared secret encrypted using a time stamp. 

You present that ticket to the destination. The destination can only see part of it, and sends the secret part back to the 
Authentication Server (AS or KDC). The AS vouches for the tickets authenticity, which it can do because it knows the contents,
and how to decrypt them, in advance. 

Its not magic. You had to send the KDC something like a password at one point, so if someone had control of the KDCi, knew 
your password and keys, they could pretend to be you, but basically thats it. Once the KDC has that information (known as 
preauthorization) the information is secure. It will not get sent out again in any form that can be decrypted. And it is 
completely free from replay attacks because the extra secret that it uses is both a sequence number and the time of day. 

So, you have shown your badge or drivers license to the guard, so they know you are who you say you are.  At this
point, the question is are you allowed in?  In Active Directory, this question is settled using LDAP. The Active 
Directory Domain controller maintains a list of computers, users and groups, each with their related security attributes. 

That database of information is examined by the pluggable access modules (PAM) agent in the Linux/Unix/MacOS world, or 
the System Access Module in Windows. They take the identity information passed in the ticket and match it against 
the privileges listed in the system.  In the Unix/Linux/MacOS (\*ix) world this means relating your user name 
(bob@HAMSTER.COM) to a numeric User Identifier (UID) which is then used to lookup group memberships as needed. If a 
file is writable by the user or group, then that privilege is available. If a program is executable by that user or 
group, then that action is available.

In Windows, the authorisation process is much more fine grained, so requires additional information. The difference is because 
Windows has domains, and nested domains, which allow different priveleges to be granted and revoked for particular usersi
or group in a heirachial tree. To make this efficient, the kerberos ticket contains an additional structure, the Privilege
Access Certificate, or PAC.  

The PAC is maintained by the active directory domain controller, and looks to the member machines as just part of the 
kerberos key, although it is very large for a key.  This PAC is only maintained by the Active Directory Domain Controller. 
If you generate a key from a kdc not part of the active directory domain, you will still have a valid key but you will
not be validate for access on windows machines.






The igoal of the Kerberos protocol is to allow you to authenticate without actually tansmitting password information over the network. To do this, we introduce another actor into the 
