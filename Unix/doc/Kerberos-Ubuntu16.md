# Detail Steps to Configure Kerberos Client on Ubuntu 16.04

## Update Software Repos

```
apt-get update -y
```

## Install the OMI Package

```
dpkg -i omi-1.2.0-139.ssl_100.ulinux.x64.deb
```

## Add HTTP and HTTPS ports

1. Add http port 5985 and https port 5986 to /etc/opt/omi/conf/omiserver.conf file on Linux:

```
sed 's#httpport=0#httpport=0,5985#g' /etc/opt/omi/conf/omiserver.conf > /etc/opt/omi/conf/omiserver.conf.new && mv /etc/opt/omi/conf/omiserver.conf.new /etc/opt/omi/conf/omiserver.conf
sed 's#httpsport=0#httpsport=0,5986#g' /etc/opt/omi/conf/omiserver.conf > /etc/opt/omi/conf/omiserver.conf.new && mv /etc/opt/omi/conf/omiserver.conf.new /etc/opt/omi/conf/omiserver.conf
```

2. Restart OMI service:

```
/opt/omi/bin/service_control restart
```

## Upload and Register the required provider

1. Upload libPresidentProvider.so file to client, code is here: [President Provider](https://github.com/Microsoft/omi/tree/master/Unix/samples/Providers/President)

2. Register the libPresidentProvider.so file via running command:

```
/opt/omi/bin/omireg --hosting '@requestor@' -n root/cimv2 /root/ libPresidentProvider.so
```

3. Restart OMI service:

```
/opt/omi/bin/service_control restart
```

## Install required Packages

```
apt-get -y install realmd sssd sssd-tools samba-common krb5-user packagekit samba-common-bin samba-libs adcli ntp
```

## Join CONTOSO domain

```
realm --verbose join CONTOSO.COM -U Administrator
```

## Host and DNS settings

1. Run command

```
      echo '.CONTOSO.COM '>> /etc/hostname    
```

2. Add ip and hostname into /etc/hosts

3. Add an entry for DNS1, DNS2 and DOMAIN in /etc/resolvconf/resolv.conf.d/head

```
echo 'domain CONTOSO.COM
search CONTOSO.COM
nameserver 10.228.124.13
nameserver 10.177.9.182' >>/etc/resolvconf/resolv.conf.d/head
```

4. Restart server or run below command

```
resolvconf –u;
```

5. Edit /etc/ntp.conf

```
echo 'server CONTOSO-DC.CONTOSO.COM'>> /etc/ntp.conf
```

6. Add configure message to /etc/realmd.conf 

```
echo '[users]
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
manage-system = no' > /etc/realmd.conf
```

7. Edit /etc/samba/smb.conf and add following message

```
[global]
workgroup = CONTOSO
security = ads
realm = CONTOSO.COM
Comment  workgroup = ***
```

8. Edit /etc/pam.d/common-session

```
echo 'session required pam_mkhomedir.so skel=/etc/skel/ umask=0077'>>/etc/pam.d/common-session
```

9. Edit the fallback_homdir like below

```
change fallback_homedir = /home/%u/%d
to fallback_homedir = /home/%u@%d
```

## Register KDC

1. Check to correspond with kdc_account@CONTOSO.COM

```
kinit kdc_account@CONTOSO.COM
```

2. Set the iptables

```
iptables -I INPUT -p tcp -m tcp --dport 5985 -j ACCEPT
iptables -I INPUT -p tcp -m tcp --dport 5986 -j ACCEPT
/opt/omi/bin/service_control restart
```

## Test Kerberos Authentication

1. Test command

```
/opt/omi/bin/omicli --hostname omi-ub16x64-01--auth Kerberos -u kdc_account@CONTOSO.COM -p kdc_account_password --port 5985 gi root/cimv2 { MSFT_President Key 1 }
```

2. Sample
```
root@omi-ub16x64-01 # /opt/omi/bin/omicli --hostname omi-ub16x64-01 --auth Kerberos -u kdc_account@CONTOSO.COM -p kdc_account_password --port 5985 gi root/cimv2 { MSFT_President Key 1 }
instance of MSFT_President
{
    Key=1
    First=George
    Last=Washington
}
```