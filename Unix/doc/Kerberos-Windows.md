# Detail Steps To Configure Kerberos Client on Windows

## Setup Win Env
```
winrm quickconfig
enable-PSRemoting
winrm set winrm/config/client/auth '@{Basic="true"}'
winrm set winrm/config/service/auth '@{Basic="true"}'
Set-Item "wsman:\localhost\client\trustedhosts" -Value '*' –Force
winrm set winrm/config/client '@{AllowUnencrypted="true"}'
winrm set winrm/config/service '@{AllowUnencrypted="true"}'
```

## Setup Linux(Kerberos-Client)

Sometimes you need to insert the server's IP and hostname into /etc/hosts file in the Linux machine and add machine(s) and IP(s) to the hosts file(C:\Windows\System32\drivers\etc) on Windows machine too.

## Install packages on Windows

1. Install [Heimdal-AMD64-full-1-6-2-0]( http://www.secure-endpoints.com/heimdal/)

2. Install [netidmgr-sdk-AMD64-rel-2_0_102_907 and netidmgr-AMD64-rel-2_0_102_907](https://www.secure-endpoints.com/netidmgr/v2/)

## Run "Network Identity Manager" and configure it

1. Open "Network Identity Manager" windows

2. Select "KeyStore" -> click "Credential" -> "New Credential"->"Obtain new credentials .."

3. Add ADC account:kdc_account@CONTOSO.COM

4. Input password for kdc_account@CONTOSO.COM and confirm password on textbox


## Configure ADC account kdc_account@CONTOSO.COM

1. Open Select "kdc_account@CONTOSO.COM" and right click -> select "Show identity options", it will show up  a windows

2. Configure "Network Identity Manager Configuration in the General setion. Tick the checkbox for “Log trace events to trace log at the following location:”


## Modify C:\ProgramData\Kerberos\krb5.conf 

```
[libdefaults]
default_realm = CONTOSO.COM
 [realms]
CONTOSO.COM = {
kdc = CONTOSO-DC01.CONTOSO.COM
           admin_server = CONTOSO-DC01.CONTOSO.COM
}
 [domain_realm]
      CONTOSO.com = CONTOSO.COM
      .CONTOSO.com = CONTOSO.COM
 ```

Check the realm name has been changed in Kerberos V5 configuration window 


## Add the HTTP service principal via running commands on Windows 

```
setspn -L WINDOWSHOSTNAME
setspn -S HTTP/WINDOWSHOSTNAME.CONTOSO.COM WINDOWSHOSTNAME
```

## Check to correspond with kdc_account

```
cd C:\Program Files\Heimdal\bin 
C:\Program Files\Heimdal\bin>kinit.exe kdc_account@CONTOSO.COM
C:\Program Files\Heimdal\bin>klist.exe
```

## Test Kerberos Authentication

1. Run command on Linux (Kerberos-Client) and test WINDOWSHOSTNAME works for Kerberos

```
/opt/omi/bin/omicli --hostname WINDOWSHOSTNAME -u kdc_account@CONTOSO.COM -p kdc_account_password --auth Kerberos --port 5985  ei root/cimv2 Win32_Share
```

2. Sample

```
/opt/omi/bin/omicli --hostname WINDOWSHOSTNAME -u kdc_account@CONTOSO.COM -p kdc_account_password --auth Kerberos --port 5985  ei root/cimv2 Win32_Share
instance of Win32_Share
{
    AllowMaximum=true
    Caption=Remote Admin
    Description=Remote Admin
    Name=ADMIN$
    Path=C:\Windows
    Status=OK
    Type=2147483648
}
instance of Win32_Share
{
    AllowMaximum=true
    Caption=Default share
    Description=Default share
    Name=C$
    Path=C:\
    Status=OK
    Type=2147483648
}
instance of Win32_Share
{
    AllowMaximum=true
    Caption=Remote IPC
    Description=Remote IPC
    Name=IPC$
    Path=
    Status=OK
    Type=2147483651
}
 ```
