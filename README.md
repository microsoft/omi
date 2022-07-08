# Open Management Infrastructure [![Build Status](https://travis-ci.org/Microsoft/omi.svg?branch=master)](https://travis-ci.org/Microsoft/omi)

Open Management Infrastructure (OMI) is an open source project to
further the development of a production quality implementation of the
DMTF CIM/WBEM standards. The OMI CIMOM is also designed to be portable
and highly modular. In order to attain its small footprint, it is
coded in C, which also makes it a much more viable CIM Object Manager
for embedded systems and other infrastructure components that have
memory constraints for their management processor. OMI is also
designed to be inherently portable. It builds and runs today on most
UNIX® systems and Linux. In addition to OMI's small footprint, it also
demonstrates very high performance.


### Additional Resources

- [OMI Getting Started Guide](Unix/doc/omi/omi.pdf)
- [Diagnosing OMI Failures](Unix/doc/diagnose-omi-problems.md)


### Get OMI

RPM and DEB packages are provided for the installation of OMI on most
enterprise Linux distributions. To install OMI, download the correct
package for your Linux computer. Choose from:

- 32-bit (x86) or 64-bit (x64) architecture
- OpenSSL version 1.0.x or 1.1.x (to determine your OpenSSL version, run: `openssl version`)
- RPM or Debian package format

You can download and install OMI from the [Releases] page. While
version numbers change from release to release, the following
downloads illustrates the package types for OMI:

Platform | Release | Architecture | SSL   | Filename
-------- |-------- |------------  | ---   | --------
Linux    | Debian  | x64          | 1.1.0 | [omi-MAJOR.MINOR.PATCH-BUILD.ssl_110.ulinux.x64.deb](https://github.com/Microsoft/omi/releases/latest)
Linux    | Debian  | x64          | 1.0.0 | [omi-MAJOR.MINOR.PATCH-BUILD.ssl_100.ulinux.x64.deb](https://github.com/Microsoft/omi/releases/latest)
Linux    | RPM     | x64          | 1.1.0 | [omi-MAJOR.MINOR.PATCH-BUILD.ssl_110.ulinux.x64.rpm](https://github.com/Microsoft/omi/releases/latest)
Linux    | RPM     | x64          | 1.0.0 | [omi-MAJOR.MINOR.PATCH-BUILD.ssl_100.ulinux.x64.rpm](https://github.com/Microsoft/omi/releases/latest)
Linux    | Debian  | x86          | 1.0.0 | [omi-MAJOR.MINOR.PATCH-BUILD.ssl_100.ulinux.x86.deb](https://github.com/Microsoft/omi/releases/latest)
Linux    | RPM     | x86          | 1.0.0 | [omi-MAJOR.MINOR.PATCH-BUILD.ssl_100.ulinux.x86.rpm](https://github.com/Microsoft/omi/releases/latest)

**Note:** MAJOR, MINOR, PATCH, and BUILD refer to the version number information for the specific version of OMI that you wish to install.

[Releases]: https://github.com/Microsoft/omi/releases

Alternatively, you can now also download from Microsoft Repo. Instructions
on setting this up can be found [here](https://technet.microsoft.com/en-us/windows-server-docs/compute/Linux-Package-Repository-for-Microsoft-Software).  Follow the instructions for your platform.  You can then use your platform's package tool to install OMI (i.e. `sudo apt-get install omi` or `sudo yum install omi`).

The latest version of all supported platform packages can also be found [here](https://github.com/Microsoft/omi-kits), but where possible we recommend downloading from the Microsoft Repo.

### Supported Linux Operating Systems

We support most modern Linux platforms (and some that aren't so modern). That
said, our formal tested matrix of Linux platforms includes the following:

- CentOS 6 and 7 (x86 and x64)
- CentOS 8 x64 (omi>=1.6.5-0)
- Debian 8 (x86 and x64) and Debian 9 x64
- Debian 10 x64 (omi>=1.6.8-0)
- Oracle Linux 5, 6, and 7 (x86 and x64)
- Oracle Linux 8 x64 (omi>=1.6.8-0)
- Red Hat Enterprise Linux Server 5 and 6, and 7 (x86 and x64)
  - Note: Red Hat 7.1 or later also runs on the PPC platform
- Red Hat Enterprise Linux Server 8 x64 (omi>=1.6.4-0)
- SUSE Linux Enterprise Server 11, 12 (x86 and x64), 12 ppc and 15.
- Ubuntu 14.04 LTS, 16.04 LTS and 18.04 LTS (x86 and x64)
- Ubuntu 20.04 LTS x64 (omi>=1.6.8-0)

### Supported Unix Operating Systems

As well as the Linux platforms supported, OMI is also tested to work on the following platforms:

- AIX 7.1 and 7.2
- HPUX 11.31 (ia64 only)
- Solaris 10 and 11 (Sparc and x86)

### Sample Installation Instructions

- For RPM based systems (RedHat, Oracle, CentOS, SuSE):
```
sudo rpm -Uvh ./omi-1.3.0-2.ssl_100.ulinux.x64.rpm
```

- For DPKG based systems (Debian, Ubuntu, etc.):
```
sudo dpkg -i ./omi-1.3.0-2.ssl_100.ulinux.x64.deb
```

**Note:** 1.3.0-2 is just an example, you should use the latest release version of OMI.

### Building and Developing OMI

To download the source code to OMI for build purposes or to further develop
OMI, please see repository [Build-omi](https://github.com/Microsoft/Build-omi).

### Setting Up Credentials

 - Setup of credentials for NTLM authentication is covered in [setup-ntlm-omi](Unix/doc/setup-ntlm-omi.md) (omi version >= v1.2.0-35)
 - Setup of credentials for Kerberos authentication is covered in [setup-kerberos-omi](Unix/doc/setup-kerberos-omi.md) (omi version >= v1.4.0-6)

### Running

Installing OMI configures a daemon named "omid" which can be
controlled with standard service controllers: `service` or
`systemctl`. Additionally, a service control script can be found at:
`/opt/omi/bin/service_control`

Restarting OMI: `sudo /opt/omi/bin/service_control restart`


### Testing OMI

To test that OMI is functional locally, the `omicli` command be used:
```
sudo /opt/omi/bin/omicli ei root/omi OMI_Identify
```

This command enumerates all instances of the `OMI_Identify` class in the `root/omi` namespace.


### Configuring OMI Server

OMI's server configuration is set in the file:
`/etc/opt/omi/conf/omiserver.conf`.  Important configuration
properties include:

Property           | Purpose
-----------------  | -------
httpsport          | The HTTPs port(s) to listen on. The default is 5986. Multiple ports can be defined as a comma-separated list
httpport           | The HTTP port to listen on. It is recommended that HTTP remain disabled (httpport=0) to prevent unencrypted communication
loglevel           | The logging option for MI server. Valid options are: ERROR, WARNING, INFO, DEBUG, VERBOSE (debug build), default value is: WARNING
agentDebugging     | When `true`, each provider runs in its own omiagent process; when `false`, all providers run in same omiagent process, default value is: `false`. (omi version >= v1.4.3-1)
AuthorizedGroups   | Setting for authorized user groups, for example: `AuthorizedGroups=SCX\scx local admins, SCX\domain users, omi_allowed_group`; its format is separated by commas, please check [Allow Deny Handling](Unix/doc/allow-deny-handling.md) for more detail. (omi version >= v1.4.3-1)
UnauthorizedGroups | Setting for unauthorized user groups, for example: `UnauthorizedGroups=SCX\denied domain users, omi_denied_group`; its format is separated by commas, please check [Allow Deny Handling](Unix/doc/allow-deny-handling.md) for more detail. (omi version >= v1.4.3-1)
pemfile            | The certificate to use for TLS/SSL communication
keyfile            | The private key that corresponds to the TLS/SSL certificate
NoSSLv2            | When `true`, the SSLv2 protocol is disabled
NoSSLv3            | When `true`, the SSLv3 protocol is disabled. If NoSSLv2 and NoSSLv3 are both set to `true`, only TLS encryption will be negotiated
NoTLSv1_0          | When `true`, the TLSv1.0 protocol is disabled
NoTLSv1_1          | When `true`, and if available on the platform, the TLSv1.1 protocol is disabled
NoTLSv1_2          | When `true`, and if available on the platform, the TLSv1.2 protocol is disabled
sslciphersuite     | The prioritized list of allowed SSL/TLS ciphers. For example, set `sslciphersuite=ALL:!SSLv2:!SSLv3:!TLSv1:!RC4-MD5:!RC4-SHA:!SEED-SHA` in `/etc/opt/omi/conf/omiserver.conf` to disable all SSLv2,SSLv3,TLSv1 ciphers and 3 weak ciphers: RC4-MD5,RC4-SHA,SEED-SHA; then run `sudo /opt/omi/bin/service_control restart` to take effect, for more information, check `man ciphers` or search internet with `openssl man ciphers` 

### Configuring OMI Client

Similar to configuring the server, the client configuration file is located at `/etc/opt/omi/conf/omicli.conf`.

### Log Rotation Configuration

The log rotate configuration for omi can be found at: `/etc/logrotate.d/omi` (omi version >= 1.6.0)

The default settings are 
```
# omi logs rotate configuration settings
/var/opt/omi/log/*.log /var/opt/omi/log/*.trc {
    # keep 5 worth of backlogs
    rotate 5

    # If the log file is missing, go on to the next one
    # without issuing an error message.
    missingok

    # Do not rotate the log if it is empty,
    # this overrides the ifempty option.
    notifempty

    # Old versions of log files are compressed with gzip by default.
    compress

    # Log files are rotated only if they grow bigger then 100M.
    size 100M

    # Truncate the original log file in place after creating a copy,
    # instead of moving the old log file and optionally creating a new one.
    copytruncate
}
```

**Note:**
1. To make log rotate every 15 minutes, we install a cron job at:`/etc/cron.d/omilogrotate` (omi version >= 1.6.0) 
The default setting is `*/15 * * * * root /usr/sbin/logrotate /etc/logrotate.d/omi >/dev/null 2>&1`.
2. If selinux is enabled on Linux machine, omi will install a selinux module called 'omi-logrotate' to make omi log rotate work fine on Linux platforms and Red Hat 7.1 PPC.
3. Supported platforms for selinux log rotate: [Supported Linux Operating Systems](#supported-linux-operating-systems)
4. If cron or crond doesn't install on the machine, omi will not install omi log rotate cron job for omi logs to be rotated.
5. If you don't want omi cron to rotate omi logs, you can just remove it: `sudo rm -f /etc/cron.d/omilogrotate`.
6. If you want omi cron to rotate omi logs, but cron or crond doesn't start, then you can start it:`sudo service cron start`, `sudo service crond start` or `sudo systemctl enable cron;sudo systemctl start cron`.
7. If you want omi cron to rotate omi logs, but cron or crond doesn't install, then you can install it:`sudo apt-get install -y cron`, `sudo yum install -y crond`, `sudo yum install -y cronie` or `sudo zypper in cron -y`.


### Remoting

#### Connecting from Linux to Linux
```
/opt/omi/bin/omicli ei root/omi OMI_Identify --auth Basic --hostname yourlinuxhostname -u root -p rootpwd --port 5985
```

#### Connecting from Linux to Windows
```
/opt/omi/bin/omicli ei root/cimv2 Win32_Environment --auth Basic --hostname yourwinmachine -u administrator -p adminpassword --port 5985
```

#### Connecting from Windows to Linux
```
winrm enumerate http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/OMI_Identify?__cimnamespace=root/omi -r:http://yourlinuxhostname:5985 -auth:Basic -u:root -p:"rootpassword" -skipcncheck -skipcacheck -encoding:utf-8 -unencrypted
```

Note: If your root password contains escaped character like 'rootpa^ssword', you need to use double quotes like -p:"rootpa^ssword" for winrm on Windows. These escaped characters need to use double quotes after '-p:' : 
```
%^&<>|'`,;=()!"\[].*?
```

### OMI Providers

OMI Provider examples:

Provider Name                                                | Official Site
------------------------------------------------------------ | -------------
PowerShell Desired State Configuration - for Linux           | [DSC](https://github.com/Microsoft/PowerShell-DSC-for-Linux)
System Center Cross Platform Provider for Operations Manager | [SCXcore](https://github.com/Microsoft/scxcore)
PowerShell Remoting Protocol                                 | [PSRP](https://github.com/PowerShell/psl-omi-provider)
Docker Monitoring Agent for OMI Server                       | [Docker Provider](https://github.com/Microsoft/Docker-Provider)
MySQL Monitoring Agent for OMI Server                        | [MySQL Provider](https://github.com/Microsoft/MySQL-Provider)
Apache Monitoring Agent for OMI Server                       | [Apache Provider](https://github.com/Microsoft/Apache-Provider)
Python Script Provider for OMI Server                        | [Python Provider](https://github.com/Microsoft/omi-script-provider)

### Microsoft Products that use OMI

The following table lists the Microsoft products and Azure services that use OMI to orchestrate configuration management and log collection on Linux VMs:


Product Name                                                 | Official Site
------------------------------------------------------------ | -------------
Azure Automation Desired State Configuration                 | [Azure Automation Desired State Configuration, DSC Extension](https://docs.microsoft.com/en-us/azure/virtual-machines/extensions/dsc-linux)
System Center Operations Manager (SCOM)                      | [System Center Operations Manager (SCOM) Management Pack for UNIX and Linux Operating Systems](https://docs.microsoft.com/en-us/system-center/scom/plan-planning-agent-deployment?view=sc-om-2022)
Log Analytics Agent                                          | [Log Analytics Agent](https://docs.microsoft.com/en-us/azure/azure-monitor/agents/agent-linux)
Azure Security Center                                        | [Azure Security Center](https://docs.microsoft.com/en-us/azure/defender-for-cloud/faq-data-collection-agents)
Container Monitoring Solution                                | [Container Monitoring Solution](https://docs.microsoft.com/en-us/azure/azure-monitor/containers/containers)
Azure Sentinel                                               | [Azure Sentinel](https://docs.microsoft.com/en-us/azure/sentinel/overview)
Azure Stack Hub                                              | [Azure Stack Hub](https://docs.microsoft.com/en-us/azure-stack/operator/azure-stack-overview?view=azs-2102)
Azure HDInsight                                              | [Azure HDInsight](https://docs.microsoft.com/en-us/azure/hdinsight/hdinsight-overview)
Azure Automation                                             | [Azure Automation](https://docs.microsoft.com/en-us/azure/automation/automation-runbook-execution)
Azure Automation Update Management                           | [Azure Automation Update Management](https://docs.microsoft.com/en-us/azure/automation/update-management/overview)
Azure Diagnostics (LAD)                                      | [Azure Diagnostics (LAD)](https://docs.microsoft.com/en-us/azure/virtual-machines/extensions/diagnostics-linux?context=%2Fazure%2Fvirtual-machines%2Fcontext%2Fcontext&tabs=azcli)


### Code of Conduct

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).  For more
information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact
[opencode@microsoft.com](mailto:opencode@microsoft.com) with any
additional questions or comments.
