# Detail Steps To Configure Kerberos Client on RedHat7

## Update Software Repos

```
root@omi-rhe7x64-b1  # yum update -y
```

## Install the OMI Package

rpm -ivh omi-1.2.0-111.ssl_100.ulinux.x64.rpm

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
/opt/omi/bin/omireg --hosting '@requestor@' -n root/cimv2 /root/lib\*\*\*.so
```

3. Restart OMI service process:
```
/opt/omi/bin/service_control restart
```

## Install required Packages

```
yum -y install sssd-client krb5-workstation samba openldap-clients authconfig realmd oddjob oddjob-mkhomedir adcli
yum -y install krb5-server krb5-libs krb5-devel
yum -y install sssd-tools sssd libnss-sss libpam-sss adcli
```

## Join CONTOSO domain

```
realm join CONTOSO.COM
```

## Host and DNS settings

1. Edit /etc/hosts file like this to make sure machine name with domain name point to its IP address:
```
127.0.0.1   localhost localhost.localdomain localhost4 localhost4.localdomain4
::1         localhost localhost.localdomain localhost6 localhost6.localdomain6
10.248.163.71  omi64-rhel7-03.CONTOSO.COM
```

2. Add an entry for DNS1, DNS2 and DOMAIN into /etc/sysconfig/network-scripts/ifcfg-eth0 as follow

```
DHCP_HOSTNAME=omi64-rhel7-03
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
authconfig --enablesssd --enablesssdauth --enablelocauthorize --enablekrb5 --update --krb5realm=CONTOSO.COM --krb5kdc=CONTOSO-DC01.CONTOSO.COM
```

2. Check to correspond with kdc_account@CONTOSO.COM

```
kinit kdc_account@CONTOSO.COM
```

3. Run command to list Kerberos credentials:

```
root@omi64-cent7-05  # klist
```

## Test Kerberos Authentication

1. Test command:
```
/opt/omi/bin/omicli --hostname omi64-rhel7-03 --auth Kerberos -u kdc_account@CONTOSO.COM -p kdc_account_password --port 5985 gi root/cimv2 { MSFT_President Key 1 }
```

2. Sample:
```
root@omi64-rhel7-03 # /opt/omi/bin/omicli --hostname omi64-rhel7-03 --auth Kerberos -u kdc_account@CONTOSO.COM -p kdc_account_password --port 5985 gi root/cimv2 { MSFT_President Key 1 }
instance of MSFT_President
{
    Key=1
    First=George
    Last=Washington
}
```