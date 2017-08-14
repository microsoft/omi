# Enabling Kerberos Authentication on OMI

This document describes how to enable Kerberos on a domain for use with
OMI authentication.

Table of Contents:

- [Setting Up The Domain Controller](#setting-up-the-domain-controller)
    - [Identity Mapping](#identity-mapping)
- [Setting up the Client Machine](#setting-up-the-client-machine)
    - [Redhat/CentOS Linux 7 (all versions)](#redhatcentos-linux-7-all-versions--should-also-apply-to-fedora-24-and-later)
        - [Required Packages](#required-packages)
        - [Setup after Package Install](#setup-after-package-install)
        - [Hostname 15 char or less and fully qualified](#hostname-15-char-or-less-and-fully-qualified)
        - [Resolv.conf points to the ADC](#resolvconf-points-to-the-adc)
        - [authconfig](#authconfig)
        - [Verify/Setup the Kerberos Environment](#verifysetup-the-kerberos-environment)
        - [Join the domain using realm](#join-the-domain-using-realm)
        - [Add the HTTP service principal](#add-the-http-service-principal)
    - [Redhat/CentOS Linux 6 (all versions)](#redhatcentos-linux-6-all-versions--should-also-apply-to-fedora-23-and-before)
        - [Package install](#package-install)
        - [Setup winbind and authentication using authconfig](#setup-winbind-and-authentication-using-authconfig)
        - [Add the HTTP service principal](#add-the-http-service-principal-1)
    - [Ubuntu Platforms](#ubuntu-linux-1604-lts-and-1404-lts-1610-yakkety-and-1704-zesty)
        - [Setting up the Resolver](#setting-up-the-resolver)
        - [Install packages](#install-packages)
        - [Setting up NTP daemon](#setting-up-ntp-daemon)
        - [Setting up Kerberos](#setting-up-kerberos)
        - [Prepare realm and Join using realm](#prepare-realm-and-join-using-realm)
        - [Setup smb.conf](#setup-smbconf)
        - [On the server, add the HTTP principal](#on-the-server-add-the-http-principal)
        - [Optional: Setup directory auto-create](#optional-setup-directory-auto-create)
    - [Mac OSX 10.12](#mac-osx-1012)
        - [Join CONTOSO.COM domain](#join-contosocom-domain)
    - [SUSE 12](#suse-12)
    - [Solaris 11](#solaris-11)
    - [AIX 6 and AIX 7](#aix-6-and-aix-7)
- [Using Kerberos on the OMI Client](#using-kerberos-on-the-omi-client)
    - [Setting up Credentials](#setting-up-credentials)
- [Troubleshooting Authentication](#troubleshooting-authentication)
    - [Common Problems](#common-problems)
        - [Cause 1: Wrong domain/user/password on command line](#cause-1)
        - [Cause 2: Expired Credentials](#cause-2)
        - [Cause 3: Time out of sync with host](#cause-3)
        - [Cause 4: SSSD/ Winbind setup](#cause-4)
        - [Cause 5: KDC server dns issue](#cause-5)
        - [Cause 6: Lower case domain name](#cause-6)
        - [Cause 7: knvo inconsistent issue](#cause-7)
        - [Cause 8: keytab setting issue](#cause-8)
    - [Troubleshooting Steps](#troubleshooting-steps)
- [Kerberos Details](#kerberos-details)

-----

## Setting Up The Domain Controller

This document is a series of notes documenting experiences gained when setting up and using Kerberos authentication on the OMI client and server.

We will assume you have setup an active directory domain controller using windows server.  The domain controller
we have been using runs on Windows Server 2012 R2, but Windows Server 2016 should be quite similar.

First, to explain some terms:

   - Domain Name Services is a server protocol which resolves host names. The namespace the server provides names for is 
     called the DNS *domain*. By convention, the DNS domain is all lower case. (For example, contoso.com).

   - Kerberos is an authentication protocol which uses a trusted credential repository referred to as an authentication server
     or more usually, Key Distribution Center (KDC). The set of machines served by the KDC is a Kerberos *realm*. By 
     convention Kerberos realms are mixed case with the first part all upper (For example, CONTOSO.com).

     Users, hosts, and services identities are all *principals* in Kerberos. Each has a credential in either a file with 
     table of keys, or a credential cache. There are several credential cache methods, depending on the configuration and 
     environment variables. Users are in the form myuser@CONTOSO.com.  Hosts are referred to by their fully qualified 
     domain name, so myhost.contoso.com@CONTOSO.com.  Service Principals, also referred to as Service Principal Names or 
     SPNs (pronounced "spin") are in the form service name/host, or http/myhost.contoso.com@CONTOSO.com. 

     Usually a given user will only be directly aware of their own user. Host and service principals are usually setup 
     as part of the joining process. Some service principals, such as HTTP/myhost.contolso.com@CONTOSO.com will need to be 
     added after the joining process.

     There are two implementations of Kerberos, which are used by pretty much everybody.  The MIT implementation
     is installed by default in Linux distros. The Heimdal implementation is used in MacOS and Samba servers. These
     implementations interoperate, but there are sometimes detail differences that need to be considered.

   - Active Directory uses Kerberos and the Lightweight Directory Access Protocol (LDAP) protocols to authenticate 
     and authorize machines in an active directory *domain*. Though the three functions can be distributed to other servers, 
     normally a central server, the Active Directory Controller (ADC), provides DNS, LDAP and Kerberos services for all 
     the machines joined to the domain.  User, group and host information is provided by querying the ldap database 
     across the entire domain. Member user login and privilege information can be set up on the domain controller, 
     which is a single location for all the information. 

     An active domain *domain* is by convention all upper case (for example, CONTOSO.COM). 

So a given domain joined host will receive name services from myserver.contoso.com, Kerberos authentication services from
`myserver.contoso.com@CONTOSO.com` and user and group information from `ldap/myserver.contoso.com@CONTOSO.COM`, and you can 
login with ssh -K to `host/myserver.contols.com@CONTOSO.com`. The client will lookup password and group information via `ldap://_ldap.contoso.com`.

** Direct use of the domain controller should be done by your domain administrator.** On the active domain controller, You will need to verify:

  - In the Windows Server DNS manager:
     - Under forward lookup zones, you should have your DNS domain (CONTOSO.COM).

     - Under your DNS domain, you should see host entries (A records) for each machine you are expecting to see in the domain with the correct IP 
       address. If you do not have them, at the domain entry right click and select "New host (A or AAAA)". Type the short name into name field,
       and ensure the boxes "Create associated pointer record" and "Allow any authenticated user to update DNS records with the same owner name".

     - Under reverse lookup zones, lookup the zone corresponding to your subnet. Note the zone uses the IP address fields in reverse order, 
       so the reverse lookup zone for 10.1.124.230 would be 124.1.10.in-addr.arpa. Under that section, you should have PTR records for each host
       in your domain. If your domain spans multiple subnets, then check them all.  If you do not have a PTR record, go back to the forward lookup section, 
       delete the old host record and recreate it.

     - In the forward lookup zone for your domain, verify the presence of _Kerberos.CONTOSO.com TXT record containing the name of the 
       Kerberos realm ("CONTOSO.com"). This is used by Kerberos to correctly generate the names of well known service principals, and is 
       used heavily by both MIT and Heimdal Kerberos implementations. This appears not to be set by default so must be set manually.
       *Note, not setting this will result in problems that are difficult to diagnose. It is not set by default*.

    - You should have folders for _tcp and _udp with SRV records for _kerberos, _ldap, _kpasswd.

  - We have found the procedure of updating forward lookup and PTR records for each host to be somewhat labor intensive for a significant (~100 hosts) domain. 
    We use a script which uses nslookup to perform updates, run from a cron job every few minutes to manage updating DNS records for each host. The script
    is available on [GitHub](https://github.com/jeffaco/msft-updatedns), note that it will require minor modifications to run in other DNS domains.

  - Reverse DNS records for registered hosts is a common problem, as those are often managed by enterprise IT 
    or IP organizations. It is used heavily by default, but flags and configuration options are available to compensate.
    If there are problems with rdns (reverse DNS), you can identify reverse DNS issues by using `dig`. Running `dig` on a host in the domain, 
    ```
    dig 10.1.10.192 
    ```
    should return a fully qualified domain name, such as "myhost.contoso.com".  If it returns nothing, or an erroneous name, like  "myhost.enterprise.contoso.com"
    you should have rdns issues. 


  - In Windows Server Domain Users and Computers:
    - Computer Account: You should have an account reflecting your computers short name (in the case of myhost.contoso.com, that would be myhost). 
      We strongly recommend that name be 15 characters or less.  If the computer account is not present, right click on "computers"->"new"->"computer".
      Under computer name, type the short name of the host. The pre-win2000 computer name will be automatically populated.

      The act of joining the domain via `realm` or `net ads` will attempt to create a computer account if none is present, but we recommend 
      precreating the account.  

    - User Account: The accounts of every domain user should be present under the "Users" section. If not, add the user via "new"->"user". Fill in 
      the form, press the next button, add the password. Then right click on the user and select "properties"->"account".

      - We recommend that the check box "Use Kerberos DES encryption types for this account" be disabled. DES encryption is considered weak, and 
      not allowed on many platforms. 

      - We recommend that the boxes "This account supports Kerberos AES 128 bit encryption" and "This account supports Kerberos AES 256 bit encryption" be
      enabled.

      - We recommend that the box "Do not require Kerberos preauthentication" be disabled. Windows will authenticate in that case, but only as 
        anonymous_user.
  
    - Service Principals for all expected services must be added to the computer account.  This should be done after joining. The service principal
      HTTP/myhost.contoso.com@CONTOSO.COM is required by OMI and not created by the domain joining tools.

  - Authoritative user account with permission to join machines to domain. Which accounts are authorized to add machines to the domain is controlled 
    by group policy. By default, the only account that can do that is CONTOSO\Administrator.

### Identity Mapping

Linux, MacOS and Unix identify users via an integer user ID (uid). That user is then given privileges according to is membership 
in various groups, which are identified by an integer group id.  The utility id will show both of these for a given user. 

In Windows the user id is in the form of an SID, which is much longer, variable in length, and hierarchical. Groups also have SIDs.
The user information provided by the Active Directory Controller is in the form of SIDs and must be mapped to the simpler 
Linux/MacOS/Unix format. This is done in a very simple form by winbind or sssd on the client, but there are additional packages
such as IdM or FreeIPA that perform this operation with considerably more sophistication.

We have not found it necessary to use these tools. Your application may require a more sophisticated mapping.

## Setting up the Client Machine

Different Linux distributions and UNIX implementations have different tools to accomplish it, but to connect to AD, one must: 

  - Set up automatic time sync with ADC/KDC. This is usually via the network time protocol, ntp.
  - DNS set up so it sees the AD server and is part of the servers DNS domain.
  - Have a hostname shorted to 15 characters or less. Use fully qualified hostnames by default.
  - Kerberos and LDAP setup (sssd/realm or winbind and `net ads`)
  - `/etc/nsswitch.conf` set to use ldap and sss or winbind
  - PAM modules added to allow Kerberos authentication.

Winbind, which directly uses the samba service, was universally used as an active domain agent on Linux until the
most recent version of CentOS/RH, SLES and Ubuntu.  It is being supplanted by the Red Hats
System Security Services Daemon (sssd) which is more secure and handles identity mapping better.

Winbind uses the utility `net ads` as a command line interface to join a domain, leave the domain, manage keytabs,
add users and computers, etc.

Both sssd and winbind use `net ads` to perform a number of useful operations.

MacOS uses its own suite of utilities based on a fork of the [Heimdal Kerberos implementation](http://www.h5l.org).

Much of the process of joining machine to an active domain is a matter of preparation. If the server and client 
machine is already set up properly, then the process of joining usually goes very smoothly. If there are problems in the setup, 
then debugging becomes difficult. This document will try to call out the things to check in advance.

Due to the limitations of netbios which are still reflected in the system, it is a good idea to limit hostnames to 15 characters.

Microsoft recommends this, and violating that rule will cause problems. The reason is that 
the netbios host name (referred to in the domain controllers data as SAM) is based on the netbios name. Deviation between the short name and the SAM name can cause problems. See this [document](https://technet.microsoft.com/en-us/library/cc726016(v=ws.10).aspx) for more information.

In summary:

  - The actual creation of computer and user accounts is done via the "Active Domain Users And Computers" utility on the ADC.
  - Service Principals are created using the setspn.exe command line utility. 
  - Information about the active domain state can be gotten from via ldapsearch (Windows or client side) or through powershell,
    via the get-ADComputer() and get-ADUser cmdlets.
  - For 1.4.0 or later OMI version, you need to set keytab file permission: `chown omi:omi /etc/krb5.keytab`. 

### Redhat/CentOS Linux 7 (all versions)  (Should also apply to Fedora 24 and later)

Redhat has an excellent write up on setting up an active domain client 
[here](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/7/html/Linux_Domain_Identity_Authentication_and_Policy_Guide/index.html)
which describes the process with all of the possible considerations.  Some might find it a bit long, but it is recommended
reading.

#### Required Packages

We recommend you use realmd to join. The required packages for realmd are: 
```
    sudo yum install sssd sssd-client krb5-workstation samba openldap-clients open-ssl authconfig realmd oddjob oddjob-mkhomedir adcli 
```

#### Setup after Package Install


Tasks:

  - Hostname - edit `/etc/hostname` to create an fqdn with a short name (the hostname proper) of 15 characters or less.

  - DNS - point at the ADC as the dns name server by editing the source `/etc/resolv.conf`. Optionally add an entry in `/etc/hosts`
    pointing at the ADC to ensure that is available.

    Note:  If you are using Network Manager, just modifying `/etc/resolv.conf` will not me sufficient in the long run as 
    Network Manager clobbers `/etc/resolv.conf` on every reboot. If so, modify the network manager configuration files 
    using the redhat-network-configuration tool or as needed,
    *but ensure you have a fully qualified domain name by default before proceeding*.

  - NTP is necessary. It should point at the ADC plus a number of pool servers. Authentication will fail
    if the system time is out of sync by more than five minutes between the kdc, client and host its trying to 
    communicate with.

  - Kerberos: Add `/etc/krb5.conf`.  We recommend that you keep a master krb5.conf and just copy it to each machine. The 
    contents of `/etc/krb5.conf` are not host sensitive, though they are, of course, unique to the domain.  Realmd and 
    other authconfigure tools depend on at least a minimal `/etc/krb5.conf` in order to function.

  - Authconfig will setup the configuration files `/etc/nsswitch`, `/etc/smb.conf`, `/etc/pam.d/*`, `/etc/sssd/sssd.conf`.

  - Realmd will complete the setup.

  - It will be necessary to add an additional service principal to the machine account after the join is complete.


#### Hostname 15 char or less and fully qualified

 In CentOS and RedHat you can alter the hostname by editing `/etc/sysconfig/network` to be the fully qualified domain name
 (and reboot).

#### Resolv.conf points to the ADC

 The effect we are looking for is that the world can ping the host by its fully qualified domain name (myhost.contoso.com), and
 the host can lookup names in the DNS domain via the nameservers, which we expect to be the Active Domain Controller.

 In RedHat and CentOS, `/etc/resolv.conf` is generated by network manager.  If you edit the file, the modifications
 will be clobbered on the next boot.

 So, add an entry for DNS1, DNS2, and DOMAIN into `/etc/sysconfig/network-script/if-eth0`, then reboot if network
 manager is active. The resulting ifcfg-eth0 file should look like


```
TYPE="Ethernet"
BOOTPROTO="dhcp"
DEFROUTE="yes"
IPV4_FAILURE_FATAL="no"
IPV6INIT="yes"
IPV6_AUTOCONF="yes"
IPV6_DEFROUTE="yes"
IPV6_FAILURE_FATAL="no"
IPV6_ADDR_GEN_MODE="stable-privacy"
NAME="eth0"
UUID="xxxxxxxxxx"
DEVICE="eth0"
ONBOOT="yes"
PEERDNS="yes"
PEERROUTES="yes"
IPV6_PEERDNS="yes"
IPV6_PEERROUTES="yes"
IPV6_PRIVACY="no"
DNS1=10.xxx.xxx.xxx
DNS2=10.xxx.xxx.xxx
DNS_DOMAIN=contoso.com
DNS_SEARCH=contoso.com
```

 If Network manager is active, it may be necessary to remove the name server entries already in the `/etc/resolv.conf` file.
 If Network Manager is not active, just edit `/etc/resolv.conf`. Either way, `/etc/resolv.conf` should end up looking like this
 (where xx are valid IP addresses):

```
domain contoso.com
search contoso.com
nameserver 10.xx.xx.xx
nameserver 10.xx.xx.xx

```

If you are using network manager and add the DNSx and DNS_DOMAIN entries, and they don't show up in `/etc/resolv.conf`, chances
are that the ONBOOT entry is set to off. Set it to on and try again.

To verify, you should be able to ping a known host on the network, and ping the fully qualified host name from another
host. It will probably be necessary to add the dns record for the new host on the ADC using the DNS tool, in the
"DNS forward zones" category.

When you are done, the critical thing is the default hostname is a fully qualified domain name, so
```
   # hostname
   myhost.contoso.com
```

   This is critical. Make sure to resolve this before proceeding. If it is not right, look in `/etc/sysconfig/network` at the
   HOSTNAME entry. 

 
#### authconfig

 Redhat (and CentOS, and Fedora) have a utility, *authconfig*, which does the majority of the configuration automatically.  
 The command line is:
```
         authconfig --enablesssd --enablesssdauth --enablelocauthorize --enablekrb5 --update --krb5realm=CONTOSO.COM --krb5kdc=mykddc.contoso.com
```

#### Verify/Setup the Kerberos Environment

At the end of this, you should be able to 
```
    kinit domain_user@CONTOSO.COM
```
where domain user is a known user already defined in the ADC.
Then list the credential using
```
   klist domain_user@CONTOSO.COM
```


#### Join the domain using realm

If you have a correct setup, you should be able to see the specifics using realm.


```
     sudo realm info CONTOSO.COM
```

Note that realmd will not join if there is an `/etc/sssd/sssd.conf` file.  If you have one, move it to `/etc/sssd/sssd.conf.old`.
Then:

```
     sudo realm join CONTOSO.COM -U Administrator
```

You can verify this initially by doing a getent:
```
    getent passwd domain_user@CONTOSO.COM
```

If that worked, you can actually log into your domain user:
```
    % su - root
    password for root:
    # su - domain_user@CONTOSO.COM
    domainuser@CONTOSO.COM
    % exit
    # exit
    %
```

and exit.  

#### Add the HTTP service principal

To use OMI, you need to talk to the HTTP service principal for the host. This principal is not created by default
and needs to be added. If you have access, you could log into the ADC and use *setspn*. **These commands should be done by your domain administrator.**

The *setspn -L* command lists the service principals associated with a machine account:
```
PS C:\Windows\system32> setspn -L myhost
Registered ServicePrincipalNames for CN=MYHOST,CN=Computers,DC=CONTOSO,DC=com:
        HOST/myhost.contoso.com
        HOST/MYHOST
```

The *setspn -S* command will add the principal:
```
PS C:\Windows\system32> setspn -S HTTP/myhost.contoso.com myhost
Checking domain DC=CONTOSO,DC=com

Registering ServicePrincipalNames for CN=MYHOST,CN=Computers,DC=CONTOSO,DC=com
        HTTP/myhost.contoso.com
Updated object
```

You must update the keytab on the client as well. In order to do that, you can `realm leave` and the `realm join`,
but it can be done with `net ads`, which is dependent on samba configuration (realm does not touch your samba configuration).

To set your samba configuration, edit the `/etc/samba/smb.conf` file to make it Kerberos aware. The "[global]" section should look like:

```
[global]
        workgroup = CONTOSO
        security = ads
        realm = CONTOSO.COM

        passdb backend = tdbsam

        printing = cups
        printcap name = cups
        load printers = yes
        cups options = raw
```

Most of the lines are already there. Note the `CONTOSO` setting in "workgroup". Workgroup 
needs to be set to *only* the first part of the ADS domain.

After you have done that, you should be able to use `net ads`. To verify:
```
   % net ads info CONTOSO.COM
   LDAP server: 10.xxx.xxx.xxx
   LDAP server name: CONTOSO-DC02.CONTOSO.com
   Realm: CONTOSO.COM
   Bind Path: dc=CONTOSO,dc=COM
   LDAP port: 389
   Server time: Fri, 19 May 2017 13:58:00 EDT
   KDC server: 10.xxx.xxx.xxx
   Server time offset: 1
```

You should now be able to use use *net ads* to create a SPN.
```
# net ads keytab add HTTP -U Administrator
```

Note that the above command only adds the SPN to the local keytab.  

You are set. You should be able to run omicli or server as Kerberos after the usual setup.


### Redhat/CentOS Linux 6 (all versions)  (Should also apply to Fedora 23 and before)

Though sssd is present in rhel6, Red Hat recommends the use of winbind instead of sssd.

There is a good write up of the process of setting up winbind [here](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/7/html/Windows_Integration_Guide/winbind-auth.html).

Again, the first step is to ensure the hostname is a FQDN and DNS is able to resolve the Active Directory Controller and 
vice versa. That is exactly the same process as used for CentOS/Red Hat 7.

#### Package install

Install the packages:

```
   # yum install samba samba-winbind krb5-workstation samba-winbind-krb5-locator openldap-clients open-ssl authconfig oddjob oddjob-mkhomedir
```
#### Setup winbind and authentication using authconfig

This command will setup winbind, pam, and smb. Run as superuser or root.

```
  # authconfig --update --enablewinbind --enablewins --enablewinbindauth  --enablekrb5 --smbsecurity ads --smbworkgroup="CONTOSO" --smbrealm "CONTOSO.COM" --smbservers="contosodc1.contoso.com" --krb5realm="CONTOSO.com" --enablewinbindoffline  --winbindtemplateshell=/bin/bash --winbindjoin=Administrator  --enablelocauthorize
```

Validate the results by doing *getent passwd* and su into the domain account as described in the CentOS 7 section above.


#### Add the HTTP service principal

As above, you need to add the HTTP service principal.


### Ubuntu Linux 16.04 LTS and 14.04 LTS, 16.10 Yakkety, and 17.04 Zesty

Ubuntu does not have authconfig. As a result, you must set up some files manually.

The tasks are:

    1. Set up `/etc/hostname` for the fully qualified domain name.
    2. Set up `/etc/resolvconf/resolv.conf.d/head` to make sure you are pointing at the dns domain served by the ADC
    3. Set up `/etc/ntp.conf` for the net time daemon.
    4. Set up `/etc/realmd.conf` for the realm daemon
    5. Set up `/etc/samba/smb.conf` to allow `net ads` to run.

#### Setting up the Resolver

Ubuntu keeps the hostname for the machine in the file `/etc/hostname`. In order to ensure the fully qualified domain name
is present, set it up in that file.

```
myhost.contoso.com
```

In addition, in the file `/etc/resolvconf/resolv.conf.d/head`, if you have not set up the resolver to point 
to the ADC as it the machines primary nameserver, it is important to do so now.

```
domain contoso.com
search contoso.com
nameserver 10.xxx.xxx.xxx
nameserver 10.xxx.xxx.xxx
```
Either reboot or run ``` resolvconf -u ```.
 

#### Install packages

```
   sudo apt-get -y install realmd sssd sssd-tools samba-common krb5-user packagekit samba-common-bin samba-libs adcli ntp
```
The krb5-user package might require you to set the name of your Kerberos realm and KDCs. Set these to the appropriate 
realm (CONTOSO.COM) and host names (contosodc1.contoso.com) 


#### Setting up NTP daemon

Add the kdc as primary time sync server.  This is not strictly necessary, but time sync issues are very difficult 
to recognize and troubleshoot. Add the server just below the comment:
```
   # Specify one or more NTP servers.
   server  contosodc1.contoso.com
```

#### Setting up Kerberos

The file `/etc/krb5.conf` defines information regarding the Kerberos domain, kdc server, admin server, and the 
relationship between the DNS domain name and Kerberos realm name.  Usually, there is a master `/etc/krb5.conf` file for the domain. 
If so, it is best to use that, or borrow one from an already existing domain joined machine, for example a redhat
or CentOS machine that was already set up. 

Failing that, the key points are :

Run kinit for a domain user to prime the credential cache.
```
   % kinit domain_user@CONTOSO.COM
```

#### Prepare realm and Join using realm

Create a file `/etc/realmd.conf`.


```
[users]
default-home = /home/%D/%U
default-shell = /bin/bash

[active-directory]
default-client = sssd
os-name = Ubuntu Desktop Linux
os-version = 16.04

[service]
automatic-install = no

[dom.example.int]
fully-qualified-names = no
automatic-id-mapping = yes
user-principal = yes
manage-system = no
```

Then join the domain, using the administrative user on the domain controller for authentication. This is important because, by default,
the right to join a non-windows machine to the domain is only available to the Administrator. Join as 
super user or root.


```
  sudo realm --verbose join contoso.com -U Administrator 
```


#### Setup smb.conf

`net ads` contains a number of useful utilities, but depends on smb.conf 

Add the lines:
```
        workgroup = CONTOSO
        security = ads
        realm = CONTOSO.COM
```

under the section heading global and remove any duplicates.


#### On the server, add the HTTP principal

For whatever reason, only a few service principals are set up by realmd when you join. OMI uses the HTTP SPN, which is not 
setup by realm. In order to add the HTTP service principal, it will be necessary to log into the ADC and add it
using setspn. As with CentOS the `setspn -L` command lists the service principals associated with a machine account.
```
PS C:\Windows\system32> setspn -L myhost
Registered ServicePrincipalNames for CN=MYHOST,CN=Computers,DC=CONTOSO,DC=com:
        HOST/myhost.contoso.com
        HOST/MYHOST
```

And `setspn -S` will add the principal.
```
PS C:\Windows\system32> setspn -S HTTP/myhost.contoso.com myhost
Checking domain DC=CONTOSO,DC=com

Registering ServicePrincipalNames for CN=MYHOST,CN=Computers,DC=CONTOSO,DC=com
        HTTP/myhost.contoso.com
Updated object
```

#### Optional: Setup directory auto-create

Add pam_mkhomedir to `/etc/pam.d/common-session`:

```
   # and here are more per-package modules (the "Additional" block)
   session required        pam_unix.so
   session optional                        pam_sss.so
   session optional        pam_systemd.so

   session required pam_mkhomedir.so skel=/etc/skel/ umask=0077
```


By default, the created home dir will be in the form <domain>/<user>. Many will want to change that to <user>@<Domain>. 
If so, change the file `/etc/sssd/sssd.conf` line to:

```
  fallback_homedir = /home/%u@%d

```

Reboot the machine, then validate the join by doing getent passwd, and logging in as a domain user.


### Mac OSX 10.12

#### Join CONTOSO.COM domain

You can join CONTOSO.COM domain using GUI according to [Integrating OS_X with Active Directory](http://training.apple.com/pdf/Best_Practices_for_Integrating_OS_X_with_Active_Directory.pdf) and [OS X El Capitan: Join your Mac to a network account server](https://support.apple.com/kb/PH21988?locale=en_US).

Another way is using command to join CONTOSO.COM domain: 
```
   # dsconfigad -a macmachine-01 -u Administrator -ou "CN=Computers,DC=CONTOSO,DC=COM" -domain CONTOSO.COM -localhome enable -useuncpath enable -groups "Domain Admins,Enterprise Admins" -alldomains enable
```

### SUSE 12 

TBD

### Solaris 11

TBD

### AIX 6 and AIX 7

## Using Kerberos on the OMI Client

TBD

### Setting up Credentials

TBD

## Troubleshooting Authentication

### Common Problems

 - <a name="cause-1">Cause 1: Wrong domain/user/password on command line</a>
 - <a name="cause-2">Cause 2: Expired Credentials</a>
   - you may get the error "kinit: Credentials cache keyring 'persistent:0:0' not found" when running klist command, 
     just run kinit again will fix this issue, or you can run kinit with long expiration duration: kinit -l 1000h kdcaccount@DOMAINNAME.COM.

 - <a name="cause-3">Cause 3: Time out of sync with host</a>
 - <a name="cause-4">Cause 4: SSSD/ Winbind setup</a>
 - <a name="cause-5">Cause 5: KDC server dns issue</a>
   - you get the meet error "kinit: Cannot find KDC for requested realm while getting initial credentials" when running klist command, just change "dns_lookup_kdc = false" to "dns_lookup_kdc = true" in /etc/krb5.conf will fix this issue.

 - <a name="cause-6">Cause 6: Lower case domain name</a>
   - If you get the error "kinit: KDC reply did not match expectations while getting initial credentials", please use upper case domain name.
   - If you get the error "Kerberos log: KDC reply did not match expectations", please use upper case domain name in /etc/krb5.conf.
     (To enable Kerberos log:`export KRB5_TRACE=/tmp/krb5.txt`.)

 - <a name="cause-7">Cause 7: knvo inconsistent issue</a>
   - you may get the error "Key version number for principal in key table is incorrect", just run these commands to fix this issue:
     ```
     kdestory(or rm -rf /etc/krb5.keytab)
     net ads keytab add HTTP -U Administrator
     klist -k
     ```
	 (To enable Kerberos log:`export KRB5_TRACE=/tmp/krb5.txt`.)

 - <a name="cause-8">Cause 8: keytab setting issue</a>
   - you may get the error "Server not found in Kerberos database", just run these commands to fix this issue:
     ```
     net ads keytab add HTTP -U Administrator 
     realm --verbose join CONTOSO.COM -U Administrator
     ```
	 (To enable Kerberos log:`export KRB5_TRACE=/tmp/krb5.txt`.)

#### Troubleshooting steps

TBD

## Kerberos Details

Kerberos gives protection for Authentication and Message Wrapping.  Authorization is usually handled by the Lightweight
Directory Access Protocol (LDAP) which in turn uses Kerberos for authentication.

Authentication is a way of making an external agent prove it is who it says it is. The simplest form of authentication
is sending a user name and password over the network. If you send the password unencrypted, anyone listening can capture
the password and use it. This is called a replay attack.  In order to fight replay attacks,  more robust protocols
use a one way hash that uses an external mutually known secret, for example a sequence number. NTLM is such a system.

In this case, while security is better, it is still vulnerable to various other attacks, like "pass the hash".
One vulnerability is that if you can listen to the entire conversation, you can probably reverse the hash since you 
will know the sequence number in the captured packets. 

The most secure method is to have a shared secret, but never send it anywhere. In order to do this, you need a third actor,
the Authentication Server, or Key Distribution Center, who has a shared secrets with both of you. When you want to authenticate,
you request and receive a ticket from the Authentication Server with your mutual shared secret encrypted using a time stamp. 

You present that ticket to the destination. The destination can only see part of it, and sends the secret part back to the 
Authentication Server (AS or KDC). The AS vouches for the tickets authenticity, which it can do because it knows the contents,
and how to decrypt them, in advance. 

The process is straight forward: You had to send the KDC something like a password at one point, so if someone had control of the KDC, and knew 
your password and keys, they could pretend to be you, but basically that's it. Once the KDC has that information (known as 
pre-authorization) the information is secure. It will not get sent out again in any form that can be decrypted. Kerberos is
completely free from replay attacks because the extra secret that it uses is both a sequence number and the time of day. 

For example: say you have shown your badge or drivers license to the guard, so they know you are who you say you are.  At this
point, the question is: Are you allowed in?  In Active Directory, this question is settled using LDAP. The Active
Directory Domain controller maintains a list of computers, users and groups, each with their related security attributes. 

That database of information is examined by the pluggable access modules (PAM) agent in the Linux/Unix/MacOS world, or 
the System Access Module in Windows. They take the identity information passed in the ticket and match it against 
the privileges listed in the system.  In the Unix/Linux/MacOS (\*ix) world this means relating your user name 
(bob@CONTOSO.COM) to a numeric User Identifier (UID) which is then used to lookup group memberships as needed. If a 
file is writable by the user or group, then that privilege is available. If a program is executable by that user or 
group, then that action is available.

In Windows, the authorization process is much more fine grained, and thus requires additional information. The difference is because 
Windows has domains, and nested domains, which allow different privileges to be granted and revoked for particular users
or group in a hierarchical tree. To make this efficient, the Kerberos ticket contains an additional structure, the Privilege
Access Certificate, or PAC.  

The PAC is maintained by the active directory domain controller, and looks to the member machines as just part of the 
Kerberos key, although it is very large for a key.  This PAC is only maintained by the Active Directory Domain Controller. 
If you generate a key from a kdc not part of the active directory domain, you will still have a valid key but you will
not be validate for access on windows machines.
