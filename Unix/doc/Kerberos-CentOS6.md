# Detail Steps To Configure Kerberos Client on CentOS6

## Update Software Repos

```
root@omi64-cent6x64-05  # yum update –y 
```

## Install the OMI Package

```
rpm -ivh omi-1.2.0-139.ssl_100.ulinux.x64.rpm
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

3. Restart OMI service process:

```
/opt/omi/bin/service_control restart
```

## Install required Packages

```
yum -y install epel-release
yum -y install gssntlmssp.x86_64
yum -y install realmd sssd ssd-client sssd-tools  samba  samba-common-tools
yum -y install krb5-server krb5-devel krb5-libs krb5-workstation openldap-clients authconfig oddjob oddjob-mkhomedir adcli
yum -y install libnss-sss libpam-sss
```

## Join CONTOSO domain

```
net ads keytab add HTTP –U Administrator
```

## Host and DNS settings


Add an entry for DNS1, DNS2 and DOMAIN into /etc/sysconfig/network-scripts/ifcfg-eth0 as follow

```
DHCP_HOSTNAME=omi64-cent6x64-06
DEVICE="eth0"
BOOTPROTO=dhcp
ONBOOT="yes"
PEERDNS=no
DNS1=10.228.124.13
DNS2=10.177.9.182
DNS_DOMAIN=CONTOSO.COM
DNS_SEARCH=CONTOSO.COM
```

## Register KDC

1. Set 'default_realm = CONTOSO.COM' in this /etc/krb5.conf file first and then run following command:
```
authconfig --update --enablewinbind --enablewins --enablewinbindauth --enablekrb5 --smbsecurity ads --smbworkgroup="CONTOSO" --smbrealm "CONTOSO.COM" --smbservers="CONTOSO-DC01.CONTOSO.COM" --krb5realm="CONTOSO.COM" --enablewinbindoffline --winbindtemplateshell=/bin/bash --winbindjoin=Administrator --enablelocauthorize
 
```

2. Check to correspond with kdc_account@CONTOSO.COM
```
kinit kdc_account@CONTOSO.COM
```

3. Run command to list Kerberos credentials:
```
root@omi64-cent6x64-05  # klist
```

## Test Kerberos Authentication

1. Test command:
```
/opt/omi/bin/omicli --hostname omi64-cent6x64-05 --auth Kerberos -u kdc_account@CONTOSO.COM -p kdc_account_password --port 5985 gi root/cimv2 { MSFT_President Key 1 }
```

2. Sample:
```
root@omi64-cent6x64-05  # /opt/omi/bin/omicli --hostname omi64-cent6x64-05 --auth Kerberos -u kdc_account@CONTOSO.COM -p kdc_account_password --port 5985 gi root/cimv2 { MSFT_President Key 1 }
instance of MSFT_President
{
    Key=1
    First=George
    Last=Washington
}
```