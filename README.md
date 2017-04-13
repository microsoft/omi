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


### Get OMI

RPM and DEB packages are provided for the installation of OMI on most
enterprise Linux distributions. To install OMI, download the correct
package for your Linux computer. Choose from:

- 32-bit (x86) or 64-bit (x64) architecture
- OpenSSL version 0.9.8 or 1.0.x (to determine your OpenSSL version, run: `openssl version`)
- RPM or Debian package format

You can download and install OMI from the [Releases] page. While
version numbers change from release to release, the following
downloads illustrates the package types for OMI:

Platform | Release | Architecture | SSL   | Filename
-------- |-------- |------------  | ---   | --------
Linux    | Debian  | x64          | 1.0.0 | [omi-1.2.0-35.ssl_100.x64.deb](https://github.com/Microsoft/omi/releases/download/v1.2.0-35/omi-1.2.0-35.ssl_100.x64.deb)
Linux    | Debian  | x64          | 0.9.8 | [omi-1.2.0-35.ssl_098.x64.deb](https://github.com/Microsoft/omi/releases/download/v1.2.0-35/omi-1.2.0-35.ssl_098.x64.deb)
Linux    | RPM     | x64          | 1.0.0 | [omi-1.2.0-35.ssl_100.x64.rpm](https://github.com/Microsoft/omi/releases/download/v1.2.0-35/omi-1.2.0-35.ssl_100.x64.rpm)
Linux    | RPM     | x64          | 0.9.8 | [omi-1.2.0-35.ssl_098.x64.rpm](https://github.com/Microsoft/omi/releases/download/v1.2.0-35/omi-1.2.0-35.ssl_098.x64.rpm)
Linux    | Debian  | x86          | 1.0.0 | [omi-1.2.0-35.ssl_100.x86.deb](https://github.com/Microsoft/omi/releases/download/v1.2.0-35/omi-1.2.0-35.ssl_100.x86.deb)
Linux    | Debian  | x86          | 0.9.8 | [omi-1.2.0-35.ssl_098.x86.deb](https://github.com/Microsoft/omi/releases/download/v1.2.0-35/omi-1.2.0-35.ssl_098.x86.deb)
Linux    | RPM     | x86          | 1.0.0 | [omi-1.2.0-35.ssl_100.x86.rpm](https://github.com/Microsoft/omi/releases/download/v1.2.0-35/omi-1.2.0-35.ssl_100.x86.rpm)
Linux    | RPM     | x86          | 0.9.8 | [omi-1.2.0-35.ssl_098.x86.rpm](https://github.com/Microsoft/omi/releases/download/v1.2.0-35/omi-1.2.0-35.ssl_098.x86.rpm)

[Releases]: https://github.com/Microsoft/omi/releases

Alternatively, you can now also download from Microsoft Repo. Instructions
on setting this up can be found [here](https://technet.microsoft.com/en-us/windows-server-docs/compute/Linux-Package-Repository-for-Microsoft-Software).  Follow the instructions for your platform.  You can then use your platform's package tool to install OMI (i.e. "sudo apt-get install omi", or "sudo yum install omi").

### Supported Linux Operating Systems

- CentOS Linux 5,6, and 7 (x64)
- Debian GNU/Linux 6, 7, and 8 (x64)
- Oracle Linux 5,6, and 7 (x64)
- Red Hat Enterprise Linux Server 5,6 and 7 (x64)
- SUSE Linux Enteprise Server 11 and 12 (x64)
- Ubuntu 12.04 LTS, 14.04 LTS, 15.04, 15.10, 16.04 LTS (x64)


### Sample Installation Instructions

- For RPM based systems (RedHat, Oracle, CentOS, SuSE):
```
sudo rpm -Uvh ./omi-1.2.0-35.ssl_100.x64.rpm
```

- For DPKG based systems (Debian, Ubuntu, etc):
```
sudo dpkg -i ./omi-1.2.0-35.ssl_100.x64.deb
```


### Building and Developing OMI

To download the source code to OMI for build purposes or to further develop
OMI, please see repository [Build-omi](https://github.com/Microsoft/Build-omi).

### Setting Up Credentials

Setup of credentials for NTLM authentication is covered in [setup-ntlm-omi](Unix/doc/setup-ntlm-omi.md)

### Running

Installing OMI configures a daemon named "omid" which can be
controlled with standard service controllers: `service` or
`systemctl`. Additionally, a service_control script can be found at:
`/opt/omi/bin/service_control`

Restarting OMI: `sudo /opt/omi/bin/service_control restart`


### Testing OMI

To test that OMI is functional locally, the `omicli` command be used:
```
sudo /opt/omi/bin/omicli ei root/omi OMI_Identify
```

This command enumerates all instances of the *OMI_Identify* class in the *root/omi* namespace.


### Configuring OMI Server

OMI's server configuration is set in the file:
`/etc/opt/omi/conf/omiserver.conf`.  Important configuration
properties include:

Property  | Purpose
--------  | -------
httpsport | The HTTPs port(s) to listen on. The default is 5986. Multiple ports can be defined as a comma-separated list
httpport  | The HTTP port to listen on. It is recommended that HTTP remain disabled (httpport=0) to prevent unencrypted communication
pemfile   | The certificate to use for TLS/SSL communication
keyfile   | The private key that corresponds to the TLS/SSL certificate
NoSSLv2   | When `true`, the SSLv2 protocol is disabled
NoSSLv3   | When `true`, the SSLv3 protocol is disabled. If NoSSLv2 and NoSSLv3 are both set to `true`, only TLS encryption will be negotiated
NoTLSv1_0 | When `true`, the TLSv1.0 protocol is disabled
NoTLSv1_1 | When `true`, and if available on the platform, the TLSv1.1 protocol is disabled
NoTLSv1_2 | When `true`, and if available on the platform, the TLSv1.2 protocol is disabled
sslCipherSuite | The prioritized list of allowed SSL/TLS ciphers. For more information, see [OpenSSL's documentation](https://openssl.org/docs/manmaster/apps/ciphers.html "OpenSSL's documentation")

### Configuring OMI Client

Similar to configuring the server, the client configuration file is located at `/etc/opt/omi/conf/omicli.conf`.

### Code of Conduct

This project has adopted the [Microsoft Open Source Code of Conduct]
(https://opensource.microsoft.com/codeofconduct/).  For more
information see the [Code of Conduct FAQ]
(https://opensource.microsoft.com/codeofconduct/faq/) or contact
[opencode@microsoft.com](mailto:opencode@microsoft.com) with any
additional questions or comments.
